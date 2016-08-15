#include "SoundEngine.h"
#include <iostream>


SoundEngine::SoundEngine()
{
	engine = createIrrKlangDevice();
}

SoundEngine::~SoundEngine()
{
	ClearSounds();
	if (engine)
		delete engine;
	engine = NULL;
}

SoundEngine& SoundEngine::GetInstance()
{
	static SoundEngine soundEngine;
	return soundEngine;
}

void SoundEngine::AddSound(string name, string fileLoc, bool repeat, float volume)
{

	if (sounds.find(name) == sounds.end())
	{	
		ISoundSource* source = engine->addSoundSourceFromFile(fileLoc.c_str());
		source->setDefaultVolume(volume);
		sources.insert(pair<string, ISoundSource*>(name, source));

		ISound* sound = engine->play2D(source, repeat, true);
		sound->setVolume(volume);
		sounds.insert(pair<string, ISound*>(name, sound));
	}
	else
	{
		std::cout << "File already exist!" << std::endl;
	}
}

void SoundEngine::Play(string name, bool repeat)
{
	map<string, ISound*>::iterator it = sounds.find(name);
	if (it != sounds.end())
	{
		if (!it->second || it->second->isFinished())
		{
			if (it->second)
				it->second->drop();
			
			it->second = engine->play2D(sources.find(name)->second, repeat);
		}
		else
			it->second->setIsPaused(false);
	}
	else
		std::cout << "Error playing " << name <<  " sound. Check filename." << std::endl;
}

void SoundEngine::Stop(string name)
{
	map<string, ISound*>::iterator it = sounds.find(name);
	if (it != sounds.end())
		it->second->setIsPaused(true);
	else
		std::cout << "Error stopping " << name << " sound. Check filename." << std::endl;
}

void SoundEngine::Remove(string name)
{
	map<string, ISound*>::iterator it = sounds.find(name);
	if (it != sounds.end())
	{
		engine->removeSoundSource(it->second->getSoundSource());
		if (it->second)
			it->second->drop();
		sounds.erase(it);

		map<string, ISoundSource*>::iterator sourceIt = sources.find(name);
		if (sourceIt->second)
			sourceIt->second->drop();
		sources.erase(sourceIt);
	}
	else
		std::cout << "Error removing " << name << " sound. Check filename." << std::endl;
}
void SoundEngine::ClearSounds()
{
	for (map<string, ISound*>::iterator it = sounds.begin(); it != sounds.end();)
	{
		if (it->second)
			it->second->drop();
		it = sounds.erase(it);
	}

	engine->removeAllSoundSources();

	for (map<string, ISoundSource*>::iterator it = sources.begin(); it != sources.end();)
	{
		it = sources.erase(it);
	}
}