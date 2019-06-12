#include "Sound.h"

Sound::Sound()
{
	ZeroMemory(this, sizeof(Sound));
}

Sound::~Sound()
{
	for (int i = 0; i < MAX_WAV; i++)
	{
		if (sourceVoice[i]) sourceVoice[i]->DestroyVoice();
	}
	for (int i = 0; i < MAX_WAV; i++) SAFE_DELETE(wavBuffer[i]);
	SAFE_RELEASE(xAudio2);

	CoUninitialize();
}

HRESULT Sound::initialize()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(XAudio2Create(&xAudio2, 0)))
	{
		CoUninitialize();
		return E_FAIL;
	}
	if (FAILED(xAudio2->CreateMasteringVoice(&masteringVoice)))
	{
		CoUninitialize();
		return E_FAIL;
	}
	return S_OK;

}

int Sound::load(char* fileName)
{
	static int index = -1;
	index++;
	HMMIO mmio = NULL;//WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
	DWORD wavDataSize = 0;//WAVファイル内　WAVデータのサイズ（WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一）
	WAVEFORMATEX* waveFormat;//WAVのフォーマット 例）16ビット、44110Hz、ステレオなど
	MMCKINFO ckInfo;//　チャンク情報
	MMCKINFO riffckInfo;// 最上部チャンク（RIFFチャンク）保存用
	PCMWAVEFORMAT pcmWaveForm;
	//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	mmio = mmioOpenA(fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	//ファイルポインタをRIFFチャンクの先頭にセットする
	mmioDescend(mmio, &riffckInfo, NULL, 0);
	// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(mmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	//フォーマットを読み込む
	mmioRead(mmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
	waveFormat = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(waveFormat, &pcmWaveForm, sizeof(pcmWaveForm));
	waveFormat->cbSize = 0;
	mmioAscend(mmio, &ckInfo, 0);
	// WAVファイル内の音データの読み込み	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(mmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);//データチャンクにセット
	wavDataSize = ckInfo.cksize;
	wavBuffer[index] = new BYTE[wavDataSize];
	DWORD dwOffset = ckInfo.dwDataOffset;
	mmioRead(mmio, (HPSTR)wavBuffer[index], wavDataSize);
	//ソースボイスにデータを詰め込む	
	if (FAILED(xAudio2->CreateSourceVoice(&sourceVoice[index], waveFormat)))
	{
		MSG("ソースボイス作成失敗");
		return E_FAIL;
	}
	wavSize[index] = wavDataSize;

	return index;
}

void Sound::PlaySound(int soundIndex, bool onLoop)
{
	XAUDIO2_VOICE_STATE state;
	sourceVoice[soundIndex]->GetState(&state);
	if (state.BuffersQueued > 0)
	{
		return;
	}

	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = wavBuffer[soundIndex];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = wavSize[soundIndex];
	if (onLoop)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	if (FAILED(sourceVoice[soundIndex]->SubmitSourceBuffer(&buffer)))
	{
		MSG("ソースボイスにサブミット失敗");
		return;
	}
	sourceVoice[soundIndex]->Start(0, XAUDIO2_COMMIT_NOW);
}

void Sound::StopSound(int soundIndex)
{
	sourceVoice[soundIndex]->Stop(0, XAUDIO2_COMMIT_NOW);
}