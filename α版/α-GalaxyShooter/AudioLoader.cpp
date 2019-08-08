//======================================================================================================================================================
// Document
//======================================================================================================================================================
// AudioLoader.cpp
// HAL東京 GP-12A-332 09 亀岡竣介
// 2019/08/09
//======================================================================================================================================================
#include "AudioLoader.h"
//======================================================================================================================================================
// Using Declaration
// using宣言
//======================================================================================================================================================
using namespace audioLoaderNS;
//======================================================================================================================================================
// Constructor
// コンストラクタ
//======================================================================================================================================================
AudioLoader::AudioLoader(void)
{
	audioName[BGM_SPLASH_TITLE] = { "BGM_Test_Ver_Splash_Title.wav" };
	audioName[BGM_CHARACTER_SELECT] = { "BGM_Test_Ver_Character_Select.wav" };
	audioName[BGM_GAME] = { "BGM_Test_Ver_Game.wav" };
	audioName[SE_SELECT] = { "SE_Test_Ver_Select.wav" };
	audioName[SE_DECISION] = { "SE_Test_Ver_Decision.wav" };
	audioName[SE_CANCEL] = { "SE_Test_Ver_Cancel.wav" };
	audioName[SE_ATTACK] = { "SE_Test_Ver_Attack.wav" };
	audioName[SE_DAMAGE_COVERED] = { "SE_Test_Ver_Damage_Covered.wav" };

	return;
}
//======================================================================================================================================================
// Destructor
// デストラクタ
//======================================================================================================================================================
AudioLoader::~AudioLoader(void)
{
	release();

	return;
}
//======================================================================================================================================================
// release
// 解放
//======================================================================================================================================================
void AudioLoader::release(void)
{
	for (int i = 0; i < TYPE::TYPE_MAX; i++)
	{
		audioName[i] = NULL;
	}

	return;

//======================================================================================================================================================
// load
// 読み込み
//======================================================================================================================================================
LPDIRECTSOUNDBUFFER8 AudioLoader::load(IDirectSound8* _directSound, int _index)
{
	// 変数宣言：初期化
	// MMIO：マルチメディアインプット/アウトプット( マルチメディアI/O( 入出力 ) )の略称
	// .wavファイルは、リフ( RIFF )というフォーマット形式に従っている( RIFF：Resource InterChange File Format )
	// これはチャンク( Chunk：塊 )と呼ばれるデータの一まとまりを並べて音の情報を整理している
	LPDIRECTSOUNDBUFFER Sound_Base_Buffer = NULL;	//	音源データの総合バッファ
	LPDIRECTSOUNDBUFFER8 Sound_Buffer = NULL;		//	音源データのバッファ
	DSBUFFERDESC Sound_Buffer_Config;				//	バッファの設定構造体
	HMMIO MultiMedia_Input_Output_Handle = NULL;	//	マルチメディアI/Oハンドル
	MMIOINFO MultiMedia_Input_Output_Data;			//	マルチメディアI/Oのデータ構造体
	MMRESULT MultiMedia_Input_Output_Result = NULL;	//	マルチメディア処理結果を格納する変数
	MMCKINFO Riff_Chunk;							//	チャンクデータの構造体
	MMCKINFO Format_Chunk;							//	チャンクデータの構造体
	MMCKINFO Data_Chunk;							//	チャンクデータの構造体
	DWORD Data_Size = NULL;							//	データのサイズを格納する変数
	WAVEFORMATEX Pulse_Code_Modulation;				//	音源データのフォーマット構造体
	LPVOID Secondary_Buffer = NULL;					//	セカンダリバッファのデータの書き込み先アドレス
	DWORD Secondary_Buffer_Size = NULL;				//	セカンダリバッファのサイズ

	// １．マルチメディアI/Oハンドルを元に音源ファイルを開く
	memset	//	memset関数：指定されたポインタが指すオブジェクトの先頭から、指定されたバイト数分に、指定した文字データを書き込むはたらきをする( ポインタが指しているメモリから各"1"バイトごとに文字をセットする )
	(
		&MultiMedia_Input_Output_Data,	//	セット先のメモリブロックアドレス ( セットする領域( ポインタ / メモリ )
		0,								//	セット元のメモリブロックアドレス ( セットする値 )
		sizeof(MMIOINFO)				//	セット元から、セット先にセットするメモリのブロックサイズを指定	( セットするサイズ )
	);
	MultiMedia_Input_Output_Handle = mmioOpen	//	mmioOpen関数：入出力のバッファリングを解除するか、入出力をバッファリングしてファイルを開く。開くことができるファイルは、標準ファイル・メモリファイル・またはカスタムの格納システム
	(
		(LPSTR)audioName[_index],		//	開くファイルのファイル名が入った文字列のアドレスを指定
		&MultiMedia_Input_Output_Data,	//	mmioOpen関数で使われる追加のパラメータが入った、MMIOINFO構造体のアドレスを指定
		MMIO_READ						//	オープン操作のためのフラグを指定( MMIO_READ：ファイルを読み取り専用として開く )
	);
	if (!MultiMedia_Input_Output_Handle)
	{
		// エラーメッセージの出力
		MSG("サウンドファイルのインプットに失敗しました");
	}

	// ２．ファイルの解析( 1 ) RIFFチャンクの検索
	// 検索ワードを指定
	Riff_Chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');	//	mmioFOURCC関数：４つの文字を４文字のコードに変換します( .wavファイルは"FOURCC"という４文字の文字列でチャンクの種類を区別している )
															//	mmioDescend関数は基本的にこの文字列を参照して、検索するチャンクを判断するため、これを設定しておく必要がある
	// キーワードを対象に検索
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend関数：mmioOpen関数で開いたRIFFファイルのチャンクに進入する。また、指定されたチャンクを検索することもできる
	(
		MultiMedia_Input_Output_Handle,	//	開いているRIFFファイルのファイルハンドルを指定
		&Riff_Chunk,					//	アプリケーション定義の"MMCKINFO"構造体のアドレスを指定
		NULL,							//	検索するチャンクの親を識別する：アプリケーション定義の"MMCKINFO"構造体のアドレスを指定。親チャンクが指定されていない場合、このパラメータを"NULL"に設定する
		MMIO_FINDRIFF					//	検索フラグを指定( MMIO_FINDRIFF：チャンク識別子が"RIFF"で、指定されたフォームタイプのチャンクを検索する )
	);
	// 検索に失敗したら異常終了
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		MSG("チャンクの検索に失敗しました");
	}

	// ３．ファイルの解析( 2 ) フォーマットチャンクの検索
	// 検索ワードを指定
	Format_Chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');	//	mmioFOURCC関数：４つの文字を４文字のコードに変換します( .wavファイルは"FOURCC"という４文字の文字列でチャンクの種類を区別している )
														//	mmioDescend関数は基本的にこの文字列を参照して、検索するチャンクを判断するため、これを設定しておく必要がある
	// キーワードを対象に検索
	MultiMedia_Input_Output_Result = mmioDescend	//	mmioDescend関数：mmioOpen関数で開いたフォーマットファイルのチャンクに進入する。また、指定されたチャンクを検索することもできる
	(
		MultiMedia_Input_Output_Handle,	//	開いているフォーマットファイルのファイルハンドルを指定
		&Format_Chunk,					//	アプリケーション定義の"MMCKINFO"構造体のアドレスを指定
		&Riff_Chunk,					//	検索するチャンクの親を識別する：アプリケーション定義の"MMCKINFO"構造体のアドレスを指定。親チャンクが指定されていない場合、このパラメータを"NULL"に設定する
		MMIO_FINDCHUNK					//	検索フラグを指定( MMIO_FINDCHUNK：指定されたチャンク識別子のチャンクを検索します )
	);
	// 検索に失敗したら異常終了
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		MSG("チャンクの検索に失敗しました");
	}

	// 検索情報を元に読み込み処理
	Data_Size = mmioRead	//	mmioRead関数：mmioOpen関数で開いたファイルから、指定されたバイト数を読み取る
	(
		MultiMedia_Input_Output_Handle,	//	読み取るファイルのファイルハンドルを指定
		(HPSTR)&Pulse_Code_Modulation,	//	ファイルから読み取られたデータが入るバッファのアドレスを指定
		Format_Chunk.cksize				//	ファイルから読み取るバイト数を指定
	);
	// 読み込みに失敗したら異常終了
	if (Data_Size != Format_Chunk.cksize)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		MSG("サウンドファイルハンドルのロードに失敗しました");
	}

	mmioAscend	//	mmioAscend関数：mmioDescend関数で進入した、またはmmioCreateChunk関数で作成したRIFFファイルのチャンクから退出する
	(
		MultiMedia_Input_Output_Handle,	//	開いているRIFFファイルのファイルハンドルを指定
		&Format_Chunk,					//	mmioDescend関数または、mmioCreateChunk関数で値が書き込まれているアプリケーション定義のMMCKINFO構造体のアドレスを指定
		0								//	予約されているので、"0"を指定
	);

	// ４．ファイルの解析( 3 ) データチャンクの検索
	// 検索ワードを指定
	Data_Chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');	//	mmioFOURCC関数：４つの文字を４文字のコードに変換します( .wavファイルは"FOURCC"という４文字の文字列でチャンクの種類を区別している )
														//	mmioDescend関数は基本的にこの文字列を参照して、検索するチャンクを判断するため、これを設定しておく必要がある
	MultiMedia_Input_Output_Result = mmioDescend		//	mmioDescend関数：mmioOpen関数で開いたフォーマットファイルのチャンクに進入する。また、指定されたチャンクを検索することもできる
	(
		MultiMedia_Input_Output_Handle,	//	開いているフォーマットファイルのファイルハンドルを指定
		&Data_Chunk,					//	アプリケーション定義の"MMCKINFO"構造体のアドレスを指定
		&Riff_Chunk,					//	検索するチャンクの親を識別する：アプリケーション定義の"MMCKINFO"構造体のアドレスを指定。親チャンクが指定されていない場合、このパラメータを"NULL"に設定する
		MMIO_FINDCHUNK					//	検索フラグを指定( MMIO_FINDCHUNK：指定されたチャンク識別子のチャンクを検索します )
	);
	// 検索に失敗したら異常終了
	if (MultiMedia_Input_Output_Result != MMSYSERR_NOERROR)
	{
		mmioClose	//	mmioClose関数：mmioOpen関数で開いたファイルを閉じる
		(
			MultiMedia_Input_Output_Handle,	//	閉じるファイルのファイルハンドルを指定
			0								//	クローズ操作のためのフラグを指定
		);
		// エラーメッセージの出力
		MSG("チャンクの検索に失敗しました");
	}

	// ５．データの読み込み
	// ポインタ変数宣言：初期化
	char *Data = new char[Data_Chunk.cksize];	//	必要な大きさの領域を確保して

	Data_Size = mmioRead	//	mmioRead関数：mmioOpen関数で開いたファイルから、指定されたバイト数を読み取る
	(
		MultiMedia_Input_Output_Handle,	//	読み取るファイルのファイルハンドルを指定
		(HPSTR)Data,					//	ファイルから読み取られたデータが入るバッファのアドレスを指定
		Data_Chunk.cksize				//	ファイルから読み取るバイト数を指定
	);
	// データの読み込みに失敗したら異常終了
	if (Data_Size != Data_Chunk.cksize)
	{
		// 削除
		delete[] Data;

		// エラーメッセージの出力
		MSG("サウンドファイルハンドルのロードに失敗しました");
	}

	// ６．音源データを読み込む「セカンダリバッファ」を用意
	ZeroMemory(&Sound_Buffer_Config, sizeof(DSBUFFERDESC));	//	ZeroMemoryマクロ：指定した変数の中身を"0"クリアするマクロ

	// 各種設定
	// DSBUFFERDESC：新しいバッファオブジェクトの特性を記述する
	Sound_Buffer_Config.dwSize = sizeof(DSBUFFERDESC);	//	構造体のサイズ( 単位：byte )を指定：構造体を使う前に、このメンバを初期化しなければならない
	Sound_Buffer_Config.dwFlags = (						//	バッファの能力を示すフラグ
		DSBCAPS_GETCURRENTPOSITION2 |
		DSBCAPS_GLOBALFOCUS |
		DSBCAPS_LOCDEFER |
		DSBCAPS_CTRLFX |
		DSBCAPS_CTRLVOLUME);
	Sound_Buffer_Config.dwBufferBytes = Data_Size;				//	新しいバッファのサイズ( 単位：byte )を指定
	Sound_Buffer_Config.lpwfxFormat = &Pulse_Code_Modulation;	//	バッファのウェーブフォームフォーマットを指定

	// 総合バッファを作成
	if (FAILED(_directSound->CreateSoundBuffer	//	CreateSoundBuffer関数：サンプリングオーディオを管理するために、サウンドバッファオブジェクトを作成する
	(
		&Sound_Buffer_Config,	//	作成するサウンドバッファが記述されている"DSBUFFERDESC"構造体のアドレス
		&Sound_Base_Buffer,		//	新しいバッファオブジェクトの"IDirectSoundBuffer"インターフェイスを受け取る変数のアドレス
		NULL					//	コンポーネントオブジェクトモデル( COM )集成に対する制御オブジェクトのIUnknownインターフェイスのアドレスへのポインタ。インターフェイスが集成されていない場合には"NULL" // 通常、呼び出し側は"NULL"を渡す
	)))
	{
		// エラーメッセージの出力
		MSG("サウンドバッファの作成に失敗しました");
	}

	// サウンドバッファの取り出し
	if (FAILED(Sound_Base_Buffer->QueryInterface	//	QueryInterface関数：オブジェクトが特定のコンポーネントオブジェクトモデル( COM )インターフェイスをサポートしているかどうかを判別する…インターフェイスがサポートされている場合、システムはオブジェクトの参照カウントを増やし、アプリケーションはそのインターフェイスをすぐに使える
	(
		IID_IDirectSoundBuffer8,	//	要求するインターフェイスの参照識別子
		(LPVOID*)&Sound_Buffer		//	目的のインターフェイスがサポートされている場合に、インターフェイスへのポインタが格納されるポインタ変数のアドレス
	)))
	{
		// エラーメッセージの出力
		MSG("サウンドインターフェイスの取得に失敗しました");
	}

	// サウンドバッファ取り出し後、総合バッファを削除
	SAFE_RELEASE(Sound_Base_Buffer);

	// ７．用意したセカンダリバッファにデータを転送
	// 書き込み可能にするため、バッファをロック
	if (FAILED(Sound_Buffer->Lock	//	Lock関数：デッドロックなしですべての引数をロックする
	(
		0,
		0,
		&Secondary_Buffer,
		&Secondary_Buffer_Size,
		NULL,
		NULL,
		DSBLOCK_ENTIREBUFFER
	)))
	{
		// エラーメッセージの出力
		MSG("サウンドバッファのロックに失敗しました");
	}

	// データの転送
	memcpy	//	memcpy関数：第2引数( コピー元 )から、第3引数( 指定サイズ )分、第1引数( コピー先 )へメモリをコピーする
	(
		Secondary_Buffer,		//	コピー先のメモリブロックアドレス
		Data,					//	コピー元のメモリブロックアドレス
		Secondary_Buffer_Size	//	コピー元から、コピー先にコピーするメモリのブロックサイズを指定
	);

	// 元の読み込み領域を削除
	delete[] Data;

	// バッファのロックを解除
	Sound_Buffer->Unlock	//	Unlock関数：レコードのロックを解除する
	(
		Secondary_Buffer,
		Secondary_Buffer_Size,
		0,
		0
	);

	// セカンダリバッファを戻り値として返す
	return Sound_Buffer;
}