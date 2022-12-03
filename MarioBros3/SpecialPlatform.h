#pragma once
#include "Platform.h"
#include "debug.h"
class SpecialPlatform :
    public Platform
{
public:
    SpecialPlatform(float x, float y,
        float width, float height) : Platform(x,y,width, height){}
    int IsBlocking(float nx, float ny) {
        DebugOutTitle(L"%f", ny);
        return (ny<0.0f ); };
};

