#include "MapBush.h"
#include "MapTurtle.h"
#include "MapHelp.h"
#include "MapObjFactory.h"
  
GameObject* MapObjFactory::CreateGameObject(string enemy, tson::Vector2f position, tson::Vector2i* size) {
	if (enemy == "Bush") {
		return new MapBush(position.x, position.y);
	}
	else if (enemy == "Turtle") {
		return new MapTurtle(position.x, position.y);
	}
	else if (enemy == "Help") {
		return new MapHelp(position.x, position.y);
	}

	return nullptr;
}