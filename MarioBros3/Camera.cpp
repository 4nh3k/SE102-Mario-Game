#include "Camera.h"

RECT Camera::GetBound()
{
	RECT rect;
	rect.left = cam_x;
	rect.top = cam_y;
    // draw some tile outside of camera
	rect.bottom = cam_y + heigh + 32;
	rect.right = cam_x + width + 32;
	return rect;
}
bool Camera::IsContain(float x, float y)
{
    RECT camBBox = GetBound();
    if (x <= camBBox.right && x >= camBBox.left && y >= camBBox.top && y <= camBBox.bottom)
        return true;
    return false;
}
bool Camera::IsContain(RECT objectBBox)
{
    RECT camBBox = GetBound();
    if (
        objectBBox.left < camBBox.left + camBBox.right &&
        objectBBox.left + objectBBox.right > camBBox.left &&
        objectBBox.top < camBBox.top + camBBox.bottom &&
        objectBBox.bottom + objectBBox.top > camBBox.top
        ) {
        // Collision detected!
        return true;
    }
    else {
        // No collision
        return false;
    }
}