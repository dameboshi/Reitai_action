#include "map.h"
#include "DxLib.h"
#include "common.h"
#include <math.h>

MAP::MAP(int stagenumber)throw(int)
{
	//���[�h���s��
	//�n���ꂽ�X�e�[�W�ԍ�����}�b�v�f�[�^��ǂݍ���
	//���łɃ}�b�v�̍L���A�������Ԃ��ǂݍ��ށH
	//��l���̏����ʒu�Ȃ񂩂��~��������

	//�}�b�v�̏�����
	for (int i = 0; i < MAP_MAXWIDTH; i++)
	{
		for (int j = 0; j < MAP_MAXHEIGHT; j++){
			mapdata[j][i] = 0;
		}
	}

	char buf[MAP_MAXWIDTH];
	int height_buf;//�����̈ꎞ�ۑ��ꏊ
	int filehandle;

	if (stagenumber != -1){
		filehandle = FileRead_open("map.txt");
		if (filehandle == 0)throw(-1);
	}

	//�t�@�C���ǂݍ��ݏꏊ�����炷
	FileRead_gets(buf, 4, filehandle);
	height_buf = atoi(buf);
    for (int i = 0; i < stagenumber; i++){
		FileRead_seek(filehandle, height_buf + 4 + 1, SEEK_CUR);//�����L���A�����ʒu�̕��A�}�b�v�����A�󔒂̕������炷
		FileRead_gets(buf, 4, filehandle);
		height_buf = atoi(buf);
	}

	//�}�b�v�̕��ƍ����̓ǂݍ���
	//FileRead_gets(buf, MAP_MAXHEIGHT, filehandle);
	//height = atoi(buf) * MAP_SIZE;
	height = height_buf * MAP_SIZE;
	FileRead_gets(buf, MAP_MAXWIDTH, filehandle);
	width = atoi(buf) * MAP_SIZE;

	//��l���̏����ʒu�̓ǂݍ���
	FileRead_gets(buf, 4, filehandle);
	first_x = atoi(buf) * MAP_SIZE;
	FileRead_gets(buf, 4, filehandle);
	first_y = atoi(buf) * MAP_SIZE;

	
	for (int i = 0; i < height/MAP_SIZE; i++)
	{
		FileRead_gets(buf, width/MAP_SIZE+1, filehandle);
		for (int j = 0; j < width/MAP_SIZE; j++){
			mapdata[j][i] = buf[j] - '0';
		}
	}
	
	FileRead_close(filehandle);
	
	/*
	for (int i = 0; i < height / MAP_SIZE; i++)
	{
		for (int j = 0; j < width / MAP_SIZE; j++){
			printfDx("%d", mapdata[j][i]);
		}
		printfDx("\n");
	}
	*/
	//�f�o�b�O�p
	/*
	first_x = 100;
	first_y = 100;
	width = MAP_MAXWIDTH;
	height = 480;
	*/

}

MAP::~MAP()
{
}

void MAP::Load(int stagenumber){
}

void MAP::Draw(int sx,int sy){

	for (int i = 0; i < height/MAP_SIZE; i++){
		for (int j = 0; j < width/MAP_SIZE; j++){
			switch (mapdata[j][i])
			{
			case 0:
				break;
			case 1:
				DrawBox(j * MAP_SIZE -sx, i * MAP_SIZE, j * MAP_SIZE + MAP_SIZE -sx, i * MAP_SIZE + MAP_SIZE, BLACK, FALSE);
				break;
			default:
				break;
			}
		}
	}
}


int MAP::getMapdata(int i, int j){
	return mapdata[i/32][j/32];
}