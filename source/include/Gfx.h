#ifndef _GFX_H_
#define _GFX_H_

#include <SFML/Graphics.hpp>

class Gfx {

public:
	Gfx() { }
	
	bool Load();


	sf::Texture txDefaultCursor;

	// Menu
	sf::Texture txBackgroundIntro;
	sf::Texture txBackgroundScore;
	sf::Texture txBackgroundMenu;
	
	sf::Texture txMenuButtons;

	sf::Texture txMenuCursor;

	// Level
	sf::Texture txTower;
	sf::Texture txLifebar;
	sf::Texture txHospital;
	sf::Texture txCrossHair;
	
	sf::Texture txFruits;

	sf::Texture txBlood;

	sf::Texture txBackground1;

	// GUI
	sf::Texture txBola;
	sf::Texture txMarcobola;
	sf::Texture txFondoGUI;
	sf::Texture txBotonGUI;

	// Monster
	sf::Texture txPulpo;
	sf::Texture txPollitos;
	sf::Texture txPolloNinja;
	sf::Texture txMonoSmall;
	sf::Texture txMonoBig;

	sf::Texture txBomba;
	sf::Texture txMisiles;
	sf::Texture txEstrellas;


	// Player
	sf::Texture txGuy;
	sf::Texture txGuyArm;

	// Weapons

	sf::Texture txHandgunLeft;
	sf::Texture txHandgunRight;
	sf::Texture txBullet;

	sf::Texture txLaserWeapon;
	sf::Texture txLaserLight;

	//Ambient
	sf::Texture txPalomitas;
	sf::Texture txNube1;
	sf::Texture txNube2;
	sf::Texture txNube3;



};

#endif