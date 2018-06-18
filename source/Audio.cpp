
#include "include/Audio.h"

bool Audio::Load()
{

	muFarm.openFromFile("audio/music/farm.wav");

	sbHandgunShot.loadFromFile("audio/character/handgun_shot.wav");
	sbWalking.loadFromFile("audio/character/walking.wav");

	soundShot.setBuffer(sbHandgunShot);
	soundWalk.setBuffer(sbWalking);

	soundWalk.setLoop(true);
	soundWalk.setPitch(1.4);
	soundWalk.setVolume(10);

	return true;
}
