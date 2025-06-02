#include "Sound.h"
#include "GameWindow.h"

#include <iostream>

map<string, sf::SoundBuffer> Sound::soundBuffers;
map<string, float> Sound::localVolumes;
map<string, float> Sound::localPitches;
map<string, float> Sound::localVolumesMusic;
vector<sf::Sound*> Sound::activeSounds;
sf::Music Sound::music;
map<string, string> Sound::musicPaths;
float Sound::globalVolume;
float Sound::soundVolume;
float Sound::musicVolume;

void Sound::init()
{
	globalVolume = 1.0f;
	soundVolume = 1.0f;
	musicVolume = 1.0f;

	loadSound("ball-break", "Assets/Sounds/ball-die.wav", 0.4f);
	loadSound("damage", "Assets/Sounds/pong.wav", 0.5f, 0.85f);
	loadSound("spawn", "Assets/Sounds/magic.mp3", 0.37f);
	loadSound("fragile", "Assets/Sounds/fragile.wav", 0.5f);
	loadSound("speed-up", "Assets/Sounds/magic.mp3", 0.37f, 1.15f);
	loadSound("slow-down", "Assets/Sounds/magic.mp3", 0.37f, 0.85f);
	loadSound("reverse", "Assets/Sounds/magic.mp3", 0.37f);
	loadSound("size-up", "Assets/Sounds/magic.mp3", 0.37f);
	loadSound("size-down", "Assets/Sounds/magic.mp3", 0.37f);
	loadSound("metal", "Assets/Sounds/metal.wav", 0.26f, 0.9f);

	loadMusic("music-1", "Assets/Sounds/music-1.mp3", 0.2f);
}

void Sound::loadSound(const string& name, const string& path, float local_volume, float local_pitch)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path);
	soundBuffers[name] = buffer;
	localVolumes[name] = local_volume;
	localPitches[name] = local_pitch;
}

void Sound::loadMusic(const string& name, const string& path, float local_volume)
{
	musicPaths[name] = path;
	localVolumesMusic[name] = local_volume;
}

void Sound::playSound(const string& name)
{
	if (name == "")
		return;

	if (soundBuffers.find(name) == soundBuffers.end()) {
		std::cerr << "Sound \"" << name << "\" doesn't exist! Check file Sound.cpp" << std::endl;
		return;
	}

	// clean sounds (to avoid memory leaks)
	doSoundCleaning();

	// add sound
	activeSounds.push_back(new sf::Sound());
	sf::Sound& sound = *activeSounds.back();
	sound.setBuffer(soundBuffers[name]);
	sound.setVolume(soundVolume * globalVolume * localVolumes[name] * 100.f);
	sound.setPitch(localPitches[name] * (95 + GameWindow::getEntropy() % 11) / 100.0f);
	sound.play();
}

void Sound::stopMusic()
{
	music.stop();
}
void Sound::pauseMusic()
{
	music.pause();
}
void Sound::resumeMusic()
{
	if (music.getStatus() == sf::Music::Paused)
	{
		music.play();
	}
}
void Sound::setGlobalVolume(float volume)
{
	globalVolume = volume;
}
void Sound::setSoundVolume(float volume)
{
	soundVolume = volume;
}
void Sound::setMusicVolume(float volume)
{
	musicVolume = volume;
}
void Sound::doSoundCleaning(bool everything)
{
	constexpr int MAX_NULLPTRS = 32;
	int nullptrs = 0;

	// junk clean
	for (sf::Sound*& sound_ptr : activeSounds)
	{
		if (sound_ptr != nullptr)
		{
			if (sound_ptr->getStatus() == sf::Sound::Stopped || everything)
			{
				delete sound_ptr;
				sound_ptr = nullptr;
				nullptrs++;
			}
		}
		else nullptrs++;
	}

	if (nullptrs >= MAX_NULLPTRS)
	{
		// remove all nullptrs
		vector<sf::Sound*> new_vector;
		for (sf::Sound* sound_ptr : activeSounds)
			if (sound_ptr != nullptr)
			{
				new_vector.push_back(sound_ptr);
			}
		activeSounds.clear();
		activeSounds = new_vector;
	}
}
void Sound::playMusic(const string& name, bool loop)
{
	if (musicPaths.find(name) == musicPaths.end()) {
		cerr << "Music \"" << name << "\" doesn't exist! Check file Sound.cpp" << endl;
		return;
	}

	music.openFromFile(musicPaths[name]);
	music.setLoop(loop);
	music.setVolume(musicVolume * globalVolume * localVolumesMusic[name] * 100.f);
	music.play();
}
