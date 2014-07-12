#include <math.h>
#include "mbed.h"

#define PI 3.14159265358979 // 円周率πの定義





// モータの個体値調整用変数
float mFL = 0, mFR = 0;
float mCL = 0, mCR = 0;
float mBL = 0, mBR = 0;

// モータPWMの制御用変数
PwmOut PwmMoterFL = 0,  PwmMoterFR = 0;
PwmOut PwmMoterBL = 0,  PwmMoterBR = 0;
PwmOut PwmMoterCL = 0,  PwmMoterCR = 0;




void Move(int angle)
{
	float fl, fr;
	float cl, cr;
	float bl, br;

	// 角度によるモータの制御
	switch (angle) {
		case 1:
			fl =  1,  fr =  1;
			cl =  1,  cr =  1;
			bl = -1,  br = -1;
			break;
		case 2:
			fl =  0,  fr =  1;
			cl =  0,  cr =  0;
			bl = -1,  br =  0;
			break;
		case 3:
			fl = -1,  fr =  1;
			cl =  0,  cr =  0;
			bl = -1,  br =  1;
			break;
		case 4:
			fl = -1,  fr =  0;
			cl =  0,  cr =  0;
			bl =  0,  br =  1;
			break;
		case 5:
			fl = -1,  fr = -1;
			cl = -1,  cr = -1;
			bl =  1,  br =  1;
			break;
		case 6:
			fl =  0,  fr = -1;
			cl =  0,  cr =  0;
			bl =  1,  br =  0;
			break;
		case 7:
			fl =  1,  fr = -1;
			cl =  0,  cr =  0;
			bl =  1,  br = -1;
			break;
		case 8:
			fl =  1,  fr =  0;
			cl =  0,  cr =  0;
			bl =  0,  br = -1;
			break;
		default:
			break;
	}

	// それぞれのモータの個体値を調整
	PwmMoterFL = fl * mFL;    PwmMoterFR = fr * mFR;
	PwmMoterCL = cl * mCL;    PwmMoterCR = cr * mCR;
	PwmMoterBL = bl * mBL;    PwmMoterBR = br * mBR;


	return 0;
}




