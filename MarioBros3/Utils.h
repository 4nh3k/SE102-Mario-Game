#pragma once

#include <Windows.h>

#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "tileson.hpp"

#define NO_PROP INT_MIN
#define PROP_ID_REWARD		"reward_id"
#define PROP_ID_OBJECT		"object_id"
#define PROP_ID_SCENE		"scene_id" 
#define PROP_ID_ANI_PATH	"ani_path"


using namespace std;

vector<string> split(string line, string delimeter = "\t");
wstring ToWSTR(string st);
tson::Vector2f ToInGamePos(tson::Object);
int GetProperty(tson::Object, string propName);
string GetProperty(tson::Layer layer, string propName);

LPCWSTR ToLPCWSTR(string st);