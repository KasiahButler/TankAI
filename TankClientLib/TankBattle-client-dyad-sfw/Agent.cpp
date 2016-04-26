#include "Agent.h"

void TankAgent::cSearch()
{
	tbc.cannonMove = tankNet::CannonMovementOptions::RIGHT;
	if (enCur.inSight)
	{
		cS = cannonState::AIM;
	}
	else cS = cannonState::SEARCH;
}

void TankAgent::cAim()
{
	if (enCur.isAlive && enCur.inSight)
	{
		tS = tankState::CHASE;
		cS = cannonState::FIRE;
	}
	else if (!enCur.isAlive || !enCur.inSight)cS = cannonState::SEARCH;
}

void TankAgent::cFire()
{
	tbc.fireWish = 1;
	cS = cannonState::AIM;
}

void TankAgent::tRoam()
{
	if (timer > 0)
	{
		switch (choice)
		{
		case 0: tbc.tankMove = tankNet::TankMovementOptions::FWRD; break;
		case 1: tbc.tankMove = tankNet::TankMovementOptions::BACK; break;
		case 2: tbc.tankMove = tankNet::TankMovementOptions::LEFT; break;
		case 3: tbc.tankMove = tankNet::TankMovementOptions::RIGHT; break;
		}
		--timer;
	}

	if (timer <= 0)
	{
		timer = 60;
		choice = rand() % 4;
	}

	if (enCur.inSight)
	{
		tS = tankState::CHASE;
	}

	else if (myCur.currentHealth <= 25 && enCur.health <= tankNet::TankHealthStatus::HEALTHY)
	{
		tS = tankState::AVOID;
	}
}
void TankAgent::tChase()
{
	tS = tankState::ROAM;
}
void TankAgent::tAvoid()
{

}

tankNet::TankBattleCommand TankAgent::update(const tankNet::TankBattleStateData &state)
{
	enPrev = enCur;
	myPrev = myCur;

	enCur = state.tacticoolData[0];
	myCur = state;

	enemyXZ.x = enCur.lastKnownPosition[0];
	enemyXZ.y = enCur.lastKnownPosition[2];

	cannonXZ.x = myCur.cannonForward[0];
	cannonXZ.y = myCur.cannonForward[2];
	myXZ.x = myCur.position[0];
	myXZ.y = myCur.position[2];

	
	switch (cS)
	{
	case cannonState::SEARCH: cSearch(); break;
	case cannonState::AIM:    cAim(); break;
	case cannonState::FIRE:   cFire(); break;
	}

	switch (tS)
	{
	case tankState::AVOID: tAvoid(); break;
	case tankState::CHASE: tChase(); break;
	case tankState::ROAM:  tRoam(); break;
	}

	return tbc;
}