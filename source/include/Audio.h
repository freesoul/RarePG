#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <SFML/Audio.hpp>

class Audio {

public:
	Audio() { }

	bool Load();

	// Music streams
	sf::Music muFarm;

	// Sound buffers
	sf::SoundBuffer sbHandgunShot;
	sf::SoundBuffer sbWalking;

	// Sound playables
	sf::Sound soundShot;
	sf::Sound soundWalk;
};

#endif
