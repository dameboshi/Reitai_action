#include "player.h"
#include "key.h"
#include "DxLib.h"
#include "map.h"

Player::Player(){
	x = 0;
	y = 0;
	vx = vy = 0;
	alive = 0;
	direction = 0;
	jump_count = 0;
	jump_flag = 0;
}

void Player::Init(int x,int y){
	this->x = x;
	this->y = y;

	alive = true;
}

void Player::Calc(){
	if (!alive)return;


	//�c
	x += vx;

	dx = vx;
	dy = vy;

	//��
	if ((nowMap->getMapdata(x - size / 2 + size, y - size / 2   ) == 1) ||//����
		(nowMap->getMapdata(x - size / 2,y) == 1) ||//���^��
		(nowMap->getMapdata(x - size / 2 ,   y + size / 2 - 1  ) == 1))//����
	{
		if (dx < 0)x = x - dx;
		vx = 0;
	}
	//�E
	if ((nowMap->getMapdata(x + size / 2   , y - size / 2   ) == 1) ||//�E��
		(nowMap->getMapdata(x + size / 2   , y) == 1) ||//�E�^��
		(nowMap->getMapdata(x + size / 2   , y + size / 2 - 1 ) == 1))//�E��
	{
		if (dx > 0)x = x - dx;
		vx = 0;
	}

	//��
	y += vy;

	//��
	if ((nowMap->getMapdata(x + size / 2   , y - size / 2   ) == 1) ||//��E
		(nowMap->getMapdata(x, y - size / 2   ) == 1) ||//��^��
		(nowMap->getMapdata(x - size / 2   , y - size / 2   ) == 1))//�㍶
	{
		if (dy < 0)y = y - dy;
		y = (y / 32) * 32;
		vy = 0;
	}
	//��
	if ((nowMap->getMapdata(x + size / 2   , y + size / 2   ) == 1) ||//���E
		(nowMap->getMapdata(x, y + size / 2   ) == 1) ||//���^��
		(nowMap->getMapdata(x - size / 2   , y + size / 2   ) == 1))//����
	{
		if (dy > 0)y = y - dy;
		y = (y / 32) * 32;
		vy = 0;
		jump_flag = 0;
		jump_count = 0;
		state = WALK;
	}
	else state = JUMP;

	

	
	/*

	//----�}�b�v�Ƃ̓����蔻��----//
	px = x;
	py = y;

	dx = vx;
	dy = vy;

	//�ǂƂ̏Փ�
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

	//���A�V��Ƃ̏Փ�
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

	//��ʊO�ɍs���Ȃ��ݒ�
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

	//�d�͓I��
	if (state == JUMP){
		vy += 1;
		if (vy > 8)vy = 8;
	}

	//���C�͓I��
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

	//�W�����v���悤��
	//������Ɣ���
	if (jump_flag==0){
		if (_pad.PadGet(B_1) > 0 && jump_count < 8){
			state = JUMP;
			vy = -8.0;
			jump_count++;
		}
		else{
			jump_flag = 1;
		}
	}
}

void Player::Draw(){
	if (!alive)return;
	DrawBox(x - size / 2, y - size / 2, x + size / 2, y + size / 2, BLACK, true);
}