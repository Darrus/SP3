#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <string>
#include <irrKlang.h>
#include <map>

using std::string;
using std::map;
using std::pair;
using namespace::irrklang;

class SoundEngine
{
private:
	map<string, ISoundSource*> sources;
	map<string, ISound*> sounds;
	ISoundEngine* engine;

public:

	SoundEngine();
	~SoundEngine();
	static SoundEngine& GetInstance();
	
	void AddSound(string name, string fileLoc, bool repeat = false, float volume = 1.f);
	void Play(string name, bool repeat = false);
	void Stop(string name);
	void Remove(string name);
	void ClearSounds();
};

#endif