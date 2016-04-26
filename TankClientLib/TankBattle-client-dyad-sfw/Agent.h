#pragma once
#include "TankBattleHeaders.h"
#include "TankBattleNet.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Graph.h"

struct Vector2
{
	float x, y;
};

class TankAgent
{
public:
	tankNet::TankTacticalInfo enPrev, enCur;
	tankNet::TankBattleStateData myPrev, myCur;
	tankNet::TankBattleCommand tbc;

	COR::Vec2 myXZ;
	COR::Vec2 cannonXZ;
	COR::Vec2 enemyXZ;

	enum cannonState { SEARCH, AIM, FIRE };
	enum tankState   { ROAM, CHASE, AVOID };

	cannonState cS;
	tankState tS;

	float timer;
	int choice;

	void cSearch();
	void cAim();
	void cFire();

	void tRoam();
	void tChase();
	void tAvoid();

public:
	tankNet::TankBattleCommand update(const tankNet::TankBattleStateData &state);
};