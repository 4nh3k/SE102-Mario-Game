#include "EnemyObjFactory.h"
#include "GhostBlock.h"
#include "Goomba.h"
#include "GreenVenus.h"
#include "Koopa.h"
#include "ParaGoomba.h"
#include "ParaKoopa.h"
#include "PiranhaPlant.h"
#include "PiranhaPlant.h"
#include "RedKoopa.h"
#include "VenusFireTrap.h"
#include "EnemyObjFactory.h"

GameObject* EnemyObjFactory::CreateGameObject(string enemy, tson::Vector2f position, tson::Vector2i* size) {
	if (enemy == "Koopa")
	{
		return new Koopa(position.x, position.y);
	}
	else if (enemy == "RedKoopa")
	{
		return new RedKoopa(position.x, position.y);
	}
	else if (enemy == "ParaKoopa")
	{
		return new ParaKoopa(position.x, position.y);
	}
	else if (enemy == "Goomba")
	{
		return new Goomba(position.x, position.y);
	}
	else if (enemy == "Venus")
	{
		return new VenusFireTrap(position.x, position.y);
	}
	else if (enemy == "GreenVenus")
	{
		return new GreenVenus(position.x, position.y);
	}
	else if (enemy == "PiranhaPlant")
	{
		return new PiranhaPlant(position.x, position.y);
	}
	else if (enemy == "ParaGoomba")
	{
		return new ParaGoomba(position.x, position.y);
	}

	return nullptr;
}
