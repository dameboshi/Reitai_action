#ifndef _KEYCONFIG_H_
#define _KEYCONFIG_H_

enum {
	DOWN,
	LEFT,
	RIGHT,
	UP,
	B_1,
	B_2,
	B_3,
	B_4,
};

class PAD{
	int PADkey[28]; // PAD‚Ì“ü—Íó‘ÔŠi”[—p•Ï”
public:
	void PadInit();
	void PadInput(int);
	int PadGet(int);
};

extern PAD _pad;

#endif