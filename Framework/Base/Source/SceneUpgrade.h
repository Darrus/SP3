#ifndef SCENEUPGRADE_H
#define SCEMEUPGRADE_H

#include "SceneBase.h"
#include "Weapon.h"

class SceneUpgrade : public SceneBase
{
public:
	enum WEAPONDISPLAY
	{
		DISPLAY_PISTOL,
		DISPLAY_RIFLE,
		DISPLAY_SHOTGUN,
		DISPLAY_SNIPER,
		DISPLAY_END,
	};

	SceneUpgrade();
	virtual ~SceneUpgrade();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	//Render Stuff
	void DisplayWeapons();
	void RenderArrow();
	void DisplayUpgradePistol();
	void DisplayUpgradeRifle();
	void DisplayUpgradeShotgun();
	void DisplayUpgradeSniper();
	
	void selectWeapon();

	WEAPONDISPLAY weaponDisplay;

	int selectedWeapon;

};


















#endif