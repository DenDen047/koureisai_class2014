#include<stdio.h>


// モータの調整用変数
float mFR = 0;
float mFL = 0;
float mBR = 0;
float mBL = 0;
float mR  = 0;
float mL  = 0;


// モータPWMの制御用変数
float moterFR = 0;
float moterFL = 0;
float moterBR = 0;
float moterBL = 0;
float moterR  = 0;
float moterL  = 0;




void Move(int angle)
{
	float fr, fl, br, bl;

	// 角度によるモータの制御
	switch (angle) {
		case 1:
			fl =  1;  fr =  1;
			bl = -1;  br = -1;
			break;
		case 2:
			fl =  0;  fr =  1;
			bl = -1;  br =  0;
			break;
		case 3:
			fl = -1;  fr =  1;
			bl = -1;  br =  1;
			break;
		case 4:
			fl = -1;  fr =  0;
			bl =  0;  br =  1;
			break;
		case 5:
			fl = -1;  fr = -1;
			bl =  1;  br =  1;
			break;
		case 6:
			fl =  0;  fr = -1;
			bl =  1;  br =  0;
			break;
		case 7:
			fl =  1;  fr = -1;
			bl =  1;  br = -1;
			break;
		case 8:
			fl =  1;  fr =  0;
			bl =  0;  br = -1;
			break;
	}

	moterFR = fr * mFR;
	moterFL = fl * mFL;
	moterBR = br * mBR;
	moterBL = bl * mBL;

	return 0;
}




