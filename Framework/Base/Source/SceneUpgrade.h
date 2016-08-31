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

	enum STATS
	{
		DAMAGE,
		FIRERATE,
		OVERHEAT,
		COOLDOWN,
		STATS_END,
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
	void RenderArrowWeapons();
	void RenderArrowStats();
	void DisplayStats();
	void DisplayUpgrades();

	
	void selectWeapon();
	void selectStats();
	void Upgrade();

	WEAPONDISPLAY weaponDisplay;
	STATS stats;

	int selectedWeapon;
	int selectedStats;

	bool selectable;
	bool statsDisplay;
	bool upgradable;
};
#endif