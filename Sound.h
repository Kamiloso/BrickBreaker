#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <vector>

using namespace std;


class Sound
{
public:
	static void init();
	static void playSound(const string& name);
	static void playMusic(const string& name, bool loop = true);
	static void stopMusic();
	static void pauseMusic();
	static void resumeMusic();
	static void setGlobalVolume(float volume);
	static void setSoundVolume(float volume);
	static void setMusicVolume(float volume);
	static void doSoundCleaning(bool everything = false); // removes all nullptrs from activeSounds


private:
	static float globalVolume;
	static float soundVolume;
	static float musicVolume;
	static void loadSound(const string& name, const string& path, float local_volume, float local_pitch = 1.0f);
	static void loadMusic(const string& name, const string& path, float local_volume);
	static map<string, sf::SoundBuffer> soundBuffers;
	static map<string, float> localVolumes;
	static map<string, float> localPitches;
	static map<string, float> localVolumesMusic;
	static map<string, string> musicPaths;
	static vector<sf::Sound*> activeSounds;
	static sf::Music music;
};

