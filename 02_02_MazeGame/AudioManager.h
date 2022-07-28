#pragma once
#include <Windows.h>

class AudioManager
{
	static AudioManager* s_pInstance;
	AudioManager() {}

public:
	static AudioManager* GetInstance();
	static void DestroyInstance();

	void PlayDoorClosedSound();
	void PlayDoorOpenSound();
	void PlayKeyPickupSound();
	void PlayKeyDropSound();
	void PlayMoneySound();
	void PlayLoseLivesSound();
	void PlayLoseSound();
	void PlayLifePickupSound();
	void PlayWinSound();
};