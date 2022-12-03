#include "Camera.h"
RECT Camera::GetBound()
{
	RECT rect;
	rect.left = cam_x;
	rect.top = cam_y;
    // draw some tile outside of camera
	rect.bottom = heigh + 32;
	rect.right = width + 32;
	return rect;
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