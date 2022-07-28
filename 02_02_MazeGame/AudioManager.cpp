#include "AudioManager.h"

AudioManager* AudioManager::s_pInstance = nullptr;

AudioManager* AudioManager::GetInstance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new AudioManager();
	}

	return s_pInstance;
}

void AudioManager::DestroyInstance()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

void AudioManager::PlayDoorClosedSound()
{
	Beep(500, 75);
	Beep(500, 75);
}

void AudioManager::PlayDoorOpenSound()
{
	Beep(1397, 200);
}

void AudioManager::PlayKeyPickupSound()
{
	Beep(1568, 50);
	Beep(1568, 200);
}

void AudioManager::PlayKeyDropSound()
{
	Beep(1568, 200);
	Beep(1568, 50);
}

void AudioManager::PlayMoneySound()
{
	Beep(1568, 50);
}

void AudioManager::PlayLoseLivesSound()
{
	Beep(200, 100);
}

void AudioManager::PlayLoseSound()
{
	Beep(500, 75);
	Beep(500, 75);
	Beep(500, 75);
	Beep(500, 75);
}

void AudioManager::PlayLifePickupSound()
{
	Beep(1568, 50);
	Beep(1568, 200);
}

void AudioManager::PlayWinSound()
{
	Beep(1568, 100);
	Beep(1568, 100);
	Beep(1568, 100);
	Beep(1245, 500);
	Beep(1397, 100);
	Beep(1397, 100);
	Beep(1397, 100);
	Beep(1175, 500);
}