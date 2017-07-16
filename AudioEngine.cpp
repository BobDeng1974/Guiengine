#include "AudioEngine.h"
#include "GuiengineErrors.h"
namespace Guiengine {
	AudioEngine::AudioEngine()
	{
	}

	void SoundEffect::play(int loops/*loops = 0*/) {
		///Play on first open channel
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
			if (Mix_PlayChannel(0, m_chunk, loops) == -1)
				fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
		}
	}

	void Music::play(int loops/*loops = -1 */) {
		Mix_PlayMusic(m_music, loops);	
	}

	void  Music::pause() {
		Mix_PausedMusic();
	}
	void  Music::stop() {
		Mix_HaltMusic();
	}
	void  Music::resume() {
		Mix_ResumeMusic();
	}

	void AudioEngine::init() {
		//Parameter can be a bitwise combination of MIX_INIT_FAC,
		//MIX_INIT_MOD,MIX_INIT_MP3,MIX_INIT_OGG
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
			fatalError("MIX_INIT fail: " + std::string(Mix_GetError()));
		}
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,1024);
		m_isInit = true;
	}

	void AudioEngine::destroy() {
		if (m_isInit) {
			m_isInit = false;
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& soundPath) {
		auto it = m_effectMap.find(soundPath);
		SoundEffect  effect;
		Mix_Chunk* newChunk = Mix_LoadWAV(soundPath.c_str());
		if (newChunk == nullptr) {
			fatalError("Mix_LoadWAV fail: " + std::string(Mix_GetError()));
		}
		if (it == m_effectMap.end()) {
			//Failed to find the sound effect
			effect.m_chunk = newChunk;
			m_effectMap[soundPath] = newChunk;
			
		}else{
			//The sound effect was found in cache
			effect.m_chunk = (*it).second;
		}
		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& musicPath) {
		auto it = m_musicMap.find(musicPath);
		Music  music;
		Mix_Music* newMusic = Mix_LoadMUS(musicPath.c_str());
		if (newMusic == nullptr) {
			fatalError("Mix_LoadWAV fail: " + std::string(Mix_GetError()));
		}
		if (it == m_musicMap.end()) {
			//Failed to find the sound effect
			music.m_music = newMusic;
			m_musicMap[musicPath] = newMusic;

		}
		else {
			//The sound effect was found in cache
			music.m_music = (*it).second;
		}
		return music;
	}

	AudioEngine::~AudioEngine()
	{
		destroy();
	}

}

