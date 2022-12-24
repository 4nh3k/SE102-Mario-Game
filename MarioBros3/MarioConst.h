#pragma once


#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.35f
#define MARIO_JUMP_RUN_SPEED_Y	0.37f

#define MARIO_FRICTION			0.0003f
#define MARIO_GRAVITY			0.0008f
#define MARIO_FLY_SPEED_Y		0.18f
#define MARIO_FALL_DONW_SPEED_Y 0.02f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_KICK			1
#define MARIO_STATE_IDLE_HOLD		2
#define MARIO_STATE_TAIL_WHACK		3

#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_HOLD_RIGHT 101
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_WALKING_HOLD_LEFT 201

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_FLY				302

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_HOLD_RIGHT 401
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_RUNNING_HOLD_LEFT 501

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_KICK_TIMEOUT	100
#define MARIO_TAIL_WHACK_TIMEOUT 280
#define MARIO_FLY_TIMEOUT	200

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TANOOKI	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_TANOOKI_WIDTH 20

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_UNTOUCHABLE_TIME 2500

#define MARIO_HOLDING_OFFSET_X			(MARIO_BIG_BBOX_WIDTH/2 + 3)
#define MARIO_TANOOKI_HOLDING_OFFSET_X			(MARIO_TANOOKI_WIDTH /2 + 4)
#define MARIO_HOLDING_OFFSET_Y			1


#define MARIO_TAIL_OFFSET_X	(MARIO_TANOOKI_WIDTH/2)
#define MARIO_TAIL_OFFSET_Y	5

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT "big_idle_right"
#define ID_ANI_MARIO_IDLE_LEFT "big_idle_left"

#define ID_ANI_MARIO_IDLE_HOLD_RIGHT "big_idle_hold_right"
#define ID_ANI_MARIO_IDLE_HOLD_LEFT "big_idle_hold_left"

#define ID_ANI_MARIO_RUN_HOLD_RIGHT "big_run_hold_right"
#define ID_ANI_MARIO_RUN_HOLD_LEFT "big_run_hold_left"

#define ID_ANI_MARIO_JUMP_HOLD_RIGHT "big_jump_hold_right"
#define ID_ANI_MARIO_JUMP_HOLD_LEFT "big_jump_hold_left"

#define ID_ANI_MARIO_WALKING_RIGHT "big_walk_right"
#define ID_ANI_MARIO_WALKING_LEFT "big_walk_left"

#define ID_ANI_MARIO_RUNNING_RIGHT "big_run_right"
#define ID_ANI_MARIO_RUNNING_LEFT "big_run_left"

#define ID_ANI_MARIO_JUMP_WALK_RIGHT "big_walk_jump_right"
#define ID_ANI_MARIO_JUMP_WALK_LEFT "big_walk_jump_left"

#define ID_ANI_MARIO_JUMP_RUN_RIGHT "big_run_jump_right"
#define ID_ANI_MARIO_JUMP_RUN_LEFT "big_run_jump_left"

#define ID_ANI_MARIO_KICK_RIGHT "big_kick_right"
#define ID_ANI_MARIO_KICK_LEFT "big_kick_left"

#define ID_ANI_MARIO_SIT_RIGHT "big_sit_right"
#define ID_ANI_MARIO_SIT_LEFT "big_sit_left"

#define ID_ANI_MARIO_BRACE_RIGHT "big_brace_right"
#define ID_ANI_MARIO_BRACE_LEFT "big_brace_left"

#define ID_ANI_MARIO_FALL_DOWN_RIGHT "big_falldown_right"
#define ID_ANI_MARIO_FALL_DOWN_LEFT "big_falldown_left"

#define ID_ANI_MARIO_DIE "small_die"

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT "small_idle_right"
#define ID_ANI_MARIO_SMALL_IDLE_LEFT "small_idle_left"

#define ID_ANI_MARIO_SMALL_IDLE_HOLD_RIGHT "small_idle_hold_right"
#define ID_ANI_MARIO_SMALL_IDLE_HOLD_LEFT "small_idle_hold_left"

#define ID_ANI_MARIO_SMALL_RUN_HOLD_RIGHT "small_run_hold_right"
#define ID_ANI_MARIO_SMALL_RUN_HOLD_LEFT "small_run_hold_left"

#define ID_ANI_MARIO_SMALL_JUMP_HOLD_RIGHT "small_jump_hold_right"
#define ID_ANI_MARIO_SMALL_JUMP_HOLD_LEFT "small_jump_hold_left"

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT "small_walk_right"
#define ID_ANI_MARIO_SMALL_WALKING_LEFT "small_walk_left"

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT "small_run_right"
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT "small_run_left"

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT "small_brace_right"
#define ID_ANI_MARIO_SMALL_BRACE_LEFT "small_brace_left"

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT "small_walk_jump_right"
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT "small_walk_jump_left"

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT "small_run_jump_right"
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT "small_run_jump_left"

#define ID_ANI_MARIO_SMALL_KICK_RIGHT "small_kick_right"
#define ID_ANI_MARIO_SMALL_KICK_LEFT "small_kick_left"

// TANOOKI MARIO
#define ID_ANI_MARIO_TANOOKI_IDLE_RIGHT "tanooki_idle_right"
#define ID_ANI_MARIO_TANOOKI_IDLE_LEFT "tanooki_idle_left"

#define ID_ANI_MARIO_TANOOKI_IDLE_HOLD_RIGHT "tanooki_idle_hold_right"
#define ID_ANI_MARIO_TANOOKI_IDLE_HOLD_LEFT "tanooki_idle_hold_left"

#define ID_ANI_MARIO_TANOOKI_RUN_HOLD_RIGHT "tanooki_run_hold_right"
#define ID_ANI_MARIO_TANOOKI_RUN_HOLD_LEFT "tanooki_run_hold_left"

#define ID_ANI_MARIO_TANOOKI_JUMP_HOLD_RIGHT "tanooki_jump_hold_right"
#define ID_ANI_MARIO_TANOOKI_JUMP_HOLD_LEFT "tanooki_jump_hold_left"

#define ID_ANI_MARIO_TANOOKI_WALKING_RIGHT "tanooki_walk_right"
#define ID_ANI_MARIO_TANOOKI_WALKING_LEFT "tanooki_walk_left"

#define ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT "tanooki_run_right"
#define ID_ANI_MARIO_TANOOKI_RUNNING_LEFT "tanooki_run_left"

#define ID_ANI_MARIO_TANOOKI_BRACE_RIGHT "tanooki_brace_right"
#define ID_ANI_MARIO_TANOOKI_BRACE_LEFT "tanooki_brace_left"

#define ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT "tanooki_walk_jump_right"
#define ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT "tanooki_walk_jump_left"

#define ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT "tanooki_run_jump_right"
#define ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT "tanooki_run_jump_left"

#define ID_ANI_MARIO_TANOOKI_KICK_RIGHT "tanooki_kick_right"
#define ID_ANI_MARIO_TANOOKI_KICK_LEFT "tanooki_kick_left"

#define ID_ANI_MARIO_TANOOKI_SIT_RIGHT "tanooki_sit_right"
#define ID_ANI_MARIO_TANOOKI_SIT_LEFT "tanooki_sit_left"

#define ID_ANI_MARIO_TANOOKI_FLY_RIGHT "tanooki_fly_right"
#define ID_ANI_MARIO_TANOOKI_FLY_LEFT "tanooki_fly_left"

#define ID_ANI_MARIO_TANOOKI_FALL_DOWN_RIGHT "tanooki_falldown_right"
#define ID_ANI_MARIO_TANOOKI_FALL_DOWN_LEFT "tanooki_falldown_left"

#define ID_ANI_MARIO_TANOOKI_WALK_FLY_RIGHT "tanooki_walk_fly_right"
#define ID_ANI_MARIO_TANOOKI_WALK_FLY_LEFT "tanooki_walk_fly_left"

#define ID_ANI_MARIO_TANOOKI_TAIL_WHACK_RIGHT "tanooki_tail_whack_right"
#define ID_ANI_MARIO_TANOOKI_TAIL_WHACK_LEFT "tanooki_tail_whack_left"


#pragma endregion