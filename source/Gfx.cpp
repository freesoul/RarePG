
#include "include/Gfx.h"

bool Gfx::Load()
{
	//add fail cases to return false
	txBackgroundIntro.loadFromFile("images/menu/bg/intro.png");
	txBackgroundScore.loadFromFile("images/menu/bg/score.png");
	txBackgroundMenu.loadFromFile("images/menu/bg/menu.png");

	txMenuButtons.loadFromFile("images/menu/buttons.png");
	txMenuCursor.loadFromFile("images/menu/cursor.png");

	txTower.loadFromFile("images/level/torreta.png");
	txLifebar.loadFromFile("images/level/lifebar.png");
	txHospital.loadFromFile("images/level/hospital.png");
	txCrossHair.loadFromFile("images/level/crosshair.png");

	txFruits.loadFromFile("images/level/fruits.png");

	txBlood.loadFromFile("images/level/effects/blood.png");

	txBackground1.loadFromFile("images/level/bg/background1.png");

	txPulpo.loadFromFile("images/level/enemies/pulpo.png");
	txPollitos.loadFromFile("images/level/enemies/pollitos.png");
	txPolloNinja.loadFromFile("images/level/enemies/polloninja.png");
	txEstrellas.loadFromFile("images/level/enemies/estrellas.png");
	txMonoSmall.loadFromFile("images/level/enemies/monosmall.png");
	txMonoBig.loadFromFile("images/level/enemies/monobig.png");
	txBomba.loadFromFile("images/level/enemies/bomba.png");
	txMisiles.loadFromFile("images/level/enemies/rockets.png");

	txGuy.loadFromFile("images/player/character.png");
	txGuyArm.loadFromFile("images/player/guyarm.png");

	txHandgunLeft.loadFromFile("images/weapons/handgun/l_handgun.png");
	txHandgunRight.loadFromFile("images/weapons/handgun/r_handgun.png");
	txBullet.loadFromFile("images/weapons/handgun/bullet.png");

	txLaserWeapon.loadFromFile("images/weapons/laser/laserarma.png");
	txLaserLight.loadFromFile("images/weapons/laser/laser.png");

	txBola.loadFromFile("images/level/gui/bolagui.png");
	txMarcobola.loadFromFile("images/level/gui/marcobolagui.png");
	txFondoGUI.loadFromFile("images/level/gui/fondogui.png");
	txBotonGUI.loadFromFile("images/level/gui/botongui.png");

	txNube1.loadFromFile("images/level/ambient/nube1.png");
	txNube2.loadFromFile("images/level/ambient/nube2.png");
	txNube3.loadFromFile("images/level/ambient/nube3.png");

	txPalomitas.loadFromFile("images/level/ambient/palomitas.png");

	txDefaultCursor.loadFromFile("images/cursor/default.png");

	return true;
}
