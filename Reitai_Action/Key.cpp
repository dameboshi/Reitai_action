#include "DxLib.h"
#include "key.h"

PAD _pad;

void PAD::PadInput(int x){
	int Key; // 現在のPADの入力状態を格納する
	Key = GetJoypadInputState(x);
	for (int i = 0; i<28; i++){
		if (Key & (1 << i)){ // i番のキーコードに対応するキーが押されていたら
			PADkey[i]++;   // 加算
		}
		else {              // 押されていなければ
			PADkey[i] = 0; // 0にする
		}
	}

}

int PAD::PadGet(int PADCode){
	return PADkey[PADCode]; // KeyCodeの入力状態を返す
}