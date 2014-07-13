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
Serial PCsend(p13, p14);	// tx, rx

// XBeeの設定
// XBee   PCsend(p13, p14);	// tx, rx




int main(void)
{
	float lr, ud;
	char[] contrller = "nnnnn";	// 0:コマンド
									// 1:レーザー
									// 2:L
									// 3:R
									// 4:方向
									// 5:null

	while(1) {
		contrller[0] = (SWcommand)?'H':0;
		contrller[1] = (SWlaser)  ?'H':0;
		contrller[2] = (SWl)      ?'H':0;
		contrller[3] = (SWr)      ?'H':0;
		lr = LR;
		ud = UD;

		// ジョイスティックの値を処理
		     if (/* condition */)  contrller[4] = 'n';
		else if (/* condition */)  contrller[4] = 'w';
		else if (/* condition */)  contrller[4] = 'e';
		else if (/* condition */)  contrller[4] = 'd';
		else if (/* condition */)  contrller[4] = 'c';
		else if (/* condition */)  contrller[4] = 'x';
		else if (/* condition */)  contrller[4] = 'z';
		else if (/* condition */)  contrller[4] = 'a';
		else if (/* condition */)  contrller[4] = 'q';

	}



	return 0;
}









