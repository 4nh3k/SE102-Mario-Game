#include "Animation.h"
#include "debug.h"

void Animation::Add(string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	if (sprite == NULL)
		DebugOut(L"[ERROR] Sprite ID %d not found!\n", spriteId);

	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y, bool stopMoving)
{
	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		if (!Game::GetInstance()->GetCurrentScene()->IsPause() || !stopMoving)
		{
			DWORD t = frames[currentFrame]->GetTime();
			if (now - lastFrameTime > t)
			{
				currentFrame++;
				lastFrameTime = now;
				if (currentFrame == frames.size()) currentFrame = 0;
			}

		}
	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}

