#include <math.h>
#include "mbed.h"
// #include "XBee.h"
#define PI 3.14159265358979 // 円周率πの定義

// プロトタイプ宣言

DigitalIn SWcommand(p1);
DigitalIn SWlaser(p2);
DigitalIn SWl(p4), SWr(p5);
AnalogIn  LR(p9), UD(p10);



// シリアル通信について
Serial PCsend(p16, p15);	// tx, rx

// XBeeの設定
// XBee   PCsend(p16, p15);	// tx, rx




int main(void)
{
	float lr, ud;
	bool  l, r;
	bool  laser;
	bool  command;
	char[] contrller = "nnnn";	// 0:方向
								// 1:LR
								// 2:レーザー
								// 3:コマンド
								// 4:null

	while(1) {
		// 測定したスイッチの状態を、ひとまず代入
		lr = LR;   ud = UD;
		l = SWl;   r = SWr;
		laser = SWlaser;
		command = SWcommand;

		// ジョイスティックの値を処理
		     if (/* condition */)  contrller[0] = 'n';
		else if (/* condition */)  contrller[0] = 'w';
		else if (/* condition */)  contrller[0] = 'e';
		else if (/* condition */)  contrller[0] = 'd';
		else if (/* condition */)  contrller[0] = 'c';
		else if (/* condition */)  contrller[0] = 'x';
		else if (/* condition */)  contrller[0] = 'z';
		else if (/* condition */)  contrller[0] = 'a';
		else if (/* condition */)  contrller[0] = 'q';

		// LRの処理
		if (!l && !r) {			// L:off  R:on
			contrller[1] = 0;
		} else if (l && !r) {	// L:on   R:off
			contrller[1] = -1;
		} else if (!l && r) {	// L:off  R:on
			contrller[1] = 1;
		} else if (l && r) {	// L:on   R:on
			contrller[1] = 0;
		} else {}

		// レーザーとコマンドのスイッチの処理
		contrller[2] = (SWlaser)  ?'H':0;
		contrller[3] = (SWcommand)?'H':0;

		// PCへ、データを送信
		PCsend.printf("%s", contrller); // 返事があればデータを送る

	}

	return 0;
}









