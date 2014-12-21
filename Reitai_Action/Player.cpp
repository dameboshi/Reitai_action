#include "player.h"
#include "key.h"
#include "DxLib.h"
#include "map.h"

Player::Player(){
	x = 0;
	y = 0;
	vx = vy = 1;
	alive = 0;
	direction = 0;
	jump_count = 0;
	jump_flag = 0;
	onGround = 0;
	state = RUN;
}

void Player::Init(int x,int y){
	this->x = x;
	this->y = y;

	alive = true;
}

void Player::Calc(){
	if (!alive)return;

	
	//縦
	x += vx;

	dx = vx;
	dy = vy;

	//左
	if ((nowMap->getMapdata(x - size / 2 + size, y - size / 2   ) == 1) ||//左上
		(nowMap->getMapdata(x - size / 2,y) == 1) ||//左真ん中
		(nowMap->getMapdata(x - size / 2 ,   y + size / 2   ) == 1))//左下
	{
		if (dx < 0)x = x - dx;
		vx = 0;
	}
	//右
	if ((nowMap->getMapdata(x + size / 2   , y - size / 2   ) == 1) ||//右上
		(nowMap->getMapdata(x + size / 2   , y) == 1) ||//右真ん中
		(nowMap->getMapdata(x + size / 2   , y + size / 2  ) == 1))//右下
	{
		if (dx > 0)x = x - dx;
		vx = 0;
	}

	//横
	y += vy;

	//上
	if ((nowMap->getMapdata(x + size / 2   , y - size / 2   ) == 1) ||//上右
		(nowMap->getMapdata(x, y - size / 2   ) == 1) ||//上真ん中
		(nowMap->getMapdata(x - size / 2   , y - size / 2   ) == 1))//上左
	{
		if (dy < 0)y = y - dy;
		y = (y / 32) * 32;
		jump_flag = 1;
		vy = 0;
	}
	//下
	if ((nowMap->getMapdata(x + size / 2   , y + size / 2   ) == 1) ||//下右
		(nowMap->getMapdata(x, y + size / 2  ) == 1) ||//下真ん中
		(nowMap->getMapdata(x - size / 2   , y + size / 2   ) == 1))//下左
	{
		onGround = 0;
		//ジャンプ関連の処理 長押しすると連続ジャンプになるから……
		if (_pad.PadGet(B_1) < 1){
			jump_flag = 0;
			jump_count = 0;
		}
		if (dy > 0)y = y - dy;
		y = (y / 32) * 32;
		vy = 0;
		state = WALK;
	}
	else onGround = 1;

	//ジャンプしようぜ
	//ちょっと微妙
	if (jump_flag == 0){
		if (_pad.PadGet(B_1) > 0 && jump_count < 8){
			state = JUMP;
			vy = -10.0;
			jump_count++;
		}
		else{
			if (state == JUMP){
				jump_flag = 1;
			}
		}
	}

	if (onGround == 1){
		state = JUMP;
	}

	//重力的な
	if (state == JUMP){
		vy += 1;
		if (vy > 8)vy = 8;
	}


	/*

	//----マップとの当たり判定----//
	px = x;
	py = y;

	dx = vx;
	dy = vy;

	//壁との衝突
	int ppx = px + dx;
	int ppy = py - size/2;
	ppx = ppx / size;
	ppy = ppy / size;

	if (nowMap->getMapdata(ppx, ppy) != 0){
		if (dx > 0)x = px + size;
		if (dx <= 0)x = px;
	}

	ppx = px + dx;
	ppy = py + size/2;
	ppx = ppx / size;
	ppy = ppy / size;

	if (nowMap->getMapdata(ppx, ppy) != 0){
		if (dx > 0)x = px + size;
		if (dx <= 0)x = px;
	}

	//床、天井との衝突
	ppy = py + dy;
	ppx = px - size/2;
	ppx = ppx / size;
	ppy = ppy / size;

	if (nowMap->getMapdata(ppx, ppy) != 0){
		if (dy > 0)y = py + size;
		if (dy <= 0)y = py;

		if (dy >= 0)state = WALK;
	}

	ppy = py + dy;
	ppx = px + size/2;
	ppx = ppx / size;
	ppy = ppy / size;

	if (nowMap->getMapdata(ppx, ppy) != 0){
		if (dy > 0)y = py + size;
		if (dy <= 0)y = py;

		if (dy >= 0)state = WALK;
	}
	*/

	//画面外に行かない設定
	if (x - size / 2 < 0)x = size / 2;
	if (x + size / 2 > nowMap->getWidth())x = nowMap->getWidth() - size / 2;

	if (y + size / 2 > nowMap->getHeight()){
		y = nowMap->getHeight() - size / 2;
	}

	


	if (_pad.PadGet(RIGHT) > 0){
		direction = 0;
		vx = 3.0;
	}
	if (_pad.PadGet(LEFT) > 0){
		direction = 1;
		vx = -3.0;
	}

	//摩擦力的な
	if (state == RUN || state == WALK){
		vy = 0;
		if (!direction){
			if (vx > 0)vx -= 0.8;
			else vx = 0;
		}
		else{
			if (vx < 0)vx += 0.8;
			else vx = 0;
		}
	}

}

void Player::Draw(int sx,int sy){
	if (!alive)return;
	DrawBox(x - size / 2 - sx , y - size / 2, x + size / 2 - sx, y + size / 2, BLACK, true);

	DrawFormatString(0, 80, BLACK, "jump_flag = %d,jump_count = %d \n", jump_flag,jump_count);
	DrawFormatString(0, 100, BLACK, "state = %d\n", state);
}