#include<Windows.h>
#include<mmsystem.h>
#include<Digitalv.h>
#include<string>
#include "mci.h"
#pragma comment(lib, "winmm.lib")
UINT Bgmid;
UINT Effectid;

void PlayBgm(LPCWSTR _soundname, int _volume)
{
	// 다시 불러졌을 때 기존꺼 닫기 위함.
	mciSendCommand(Bgmid, MCI_CLOSE, NULL, (DWORD)NULL);
	MCI_OPEN_PARMS openBgm; 
	openBgm.lpstrElementName = _soundname;
	// mp3: mpegvideo, wav: waveaudio
	openBgm.lpstrDeviceType = TEXT("mpegvideo");
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openBgm);
	Bgmid = openBgm.wDeviceID;

	// 볼륨 로직.
	std::wstring msg = L"setaudio " + std::wstring(_soundname) + L" volume to " + std::to_wstring(_volume);
	mciSendString(msg.c_str(), NULL,NULL,NULL);

	MCI_PLAY_PARMS playBgm;
	mciSendCommand(Bgmid, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&playBgm);
}

void PlayEffect(LPCWSTR _soundname)
{
	// OPEN
	MCI_OPEN_PARMS openEffect;
	openEffect.lpstrElementName = _soundname;
	openEffect.lpstrDeviceType = TEXT("mpegvideo");
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openEffect);
	Effectid = openEffect.wDeviceID;
	 
	// PLAY
	MCI_PLAY_PARMS playEffect;
	mciSendCommand(Effectid, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playEffect);
	mciSendCommand(Effectid, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&playEffect);

	// close
	mciSendCommand(Effectid, MCI_CLOSE, NULL, (DWORD)NULL);
}
