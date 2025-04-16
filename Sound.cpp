#include "Sound.h"

map<string, sf::SoundBuffer> Sound::soundBuffers;
map<string, float> Sound::localVolumes;
map<string, float> Sound::localVolumesMusic;
vector<sf::Sound> Sound::activeSounds;
sf::Music Sound::music;
map<string, string> Sound::musicPaths;
float Sound::globalVolume;
float Sound::soundVolume;
float Sound::musicVolume;

void Sound::init()
{
	globalVolume = 1.f;
	soundVolume = 1.f;
	musicVolume = 1.f;
	loadSound("1", "sound.wav", 0.45f);
	loadMusic("1", "Music1.mp3", 0.2f);
}

void Sound::loadSound(const string& name, const string& path, float local_volume)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path);
	soundBuffers[name] = buffer;
	localVolumes[name] = local_volume;
}

void Sound::loadMusic(const string& name, const string& path, float local_volume)
{
	musicPaths[name] = path;
	localVolumesMusic[name] = local_volume;
}

void Sound::playSound(const string& name)
{
	activeSounds.erase(remove_if(activeSounds.begin(), activeSounds.end(), [](const sf::Sound& sound) 
		{
		return sound.getStatus() == sf::Sound::Stopped;
		}),
		activeSounds.end()
		);
	activeSounds.emplace_back();
	sf::Sound& sound = activeSounds.back();
	sound.setBuffer(soundBuffers[name]);
	sound.setVolume(soundVolume * globalVolume * localVolumes[name] * 100.f);
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
void Sound::playMusic(const string& name, bool loop)
{
	music.openFromFile(musicPaths[name]);
	music.setLoop(loop);
	music.setVolume(musicVolume * globalVolume * localVolumesMusic[name] * 100.f);
	music.play();
}
