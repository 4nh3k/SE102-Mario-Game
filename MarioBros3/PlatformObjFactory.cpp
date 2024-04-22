#include "Platform.h"
#include "SpecialPlatform.h"
#include "TheVoid.h"
#include "PlatformObjFactory.h"

GameObject* PlatformObjFactory::CreateGameObject(string enemy, tson::Vector2f position, 
	tson::Vector2i* size) {
	if (enemy == "Platform") {
		return new Platform(position.x, position.y, size->x, size->y);
	}
	else if (enemy == "Special_Platform") {
		return new SpecialPlatform(position.x, position.y, size->x, size->y);
	}
	else if (enemy == "TheVoid") {
		return new TheVoid(position.x, position.y, size->x, size->y);
	}
}