#include "DxLib.h"
#include "key.h"

PAD _pad;

void PAD::PadInput(int x){
	int Key; // ���݂�PAD�̓��͏�Ԃ��i�[����
	Key = GetJoypadInputState(x);
	for (int i = 0; i<28; i++){
		if (Key & (1 << i)){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			PADkey[i]++;   // ���Z
		}
		else {              // ������Ă��Ȃ����
			PADkey[i] = 0; // 0�ɂ���
		}
	}

}

int PAD::PadGet(int PADCode){
	return PADkey[PADCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}