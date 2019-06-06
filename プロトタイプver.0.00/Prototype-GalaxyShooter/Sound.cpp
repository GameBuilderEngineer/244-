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
	HMMIO mmio = NULL;//Windows�}���`���f�B�AAPI�̃n���h��(Windows�}���`���f�B�AAPI��WAV�t�@�C���֌W�̑���p��API)
	DWORD wavDataSize = 0;//WAV�t�@�C�����@WAV�f�[�^�̃T�C�Y�iWAV�t�@�C����WAV�f�[�^�Ő�߂��Ă���̂ŁA�قڃt�@�C���T�C�Y�Ɠ���j
	WAVEFORMATEX* waveFormat;//WAV�̃t�H�[�}�b�g ��j16�r�b�g�A44110Hz�A�X�e���I�Ȃ�
	MMCKINFO ckInfo;//�@�`�����N���
	MMCKINFO riffckInfo;// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
	PCMWAVEFORMAT pcmWaveForm;
	//WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	mmio = mmioOpenA(fileName, NULL, MMIO_ALLOCBUF | MMIO_READ);
	//�t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
	mmioDescend(mmio, &riffckInfo, NULL, 0);
	// �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g����
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(mmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);
	//�t�H�[�}�b�g��ǂݍ���
	mmioRead(mmio, (HPSTR)&pcmWaveForm, sizeof(pcmWaveForm));
	waveFormat = (WAVEFORMATEX*)new CHAR[sizeof(WAVEFORMATEX)];
	memcpy(waveFormat, &pcmWaveForm, sizeof(pcmWaveForm));
	waveFormat->cbSize = 0;
	mmioAscend(mmio, &ckInfo, 0);
	// WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(mmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK);//�f�[�^�`�����N�ɃZ�b�g
	wavDataSize = ckInfo.cksize;
	wavBuffer[index] = new BYTE[wavDataSize];
	DWORD dwOffset = ckInfo.dwDataOffset;
	mmioRead(mmio, (HPSTR)wavBuffer[index], wavDataSize);
	//�\�[�X�{�C�X�Ƀf�[�^���l�ߍ���	
	if (FAILED(xAudio2->CreateSourceVoice(&sourceVoice[index], waveFormat)))
	{
		MSG("�\�[�X�{�C�X�쐬���s");
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
		MSG("�\�[�X�{�C�X�ɃT�u�~�b�g���s");
		return;
	}
	sourceVoice[soundIndex]->Start(0, XAUDIO2_COMMIT_NOW);
}

void Sound::StopSound(int soundIndex)
{
	sourceVoice[soundIndex]->Stop(0, XAUDIO2_COMMIT_NOW);
}