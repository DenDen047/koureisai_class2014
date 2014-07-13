#include <math.h>
#include "mbed.h"
// #include "XBee.h"
#define PI 3.14159265358979 // 円周率πの定義
#define NODAMAGETIME 1.0	// 無敵状態の時間

// プロトタイプ宣言
void MOVE(char direction, char lr);



DigitalIn  SenserIn(p5);	// 受光センサからのinput
DigitalOut SenserOut(p6);	// 受光センサにoutput
DigitalOut Laser(p7);		// レーザーにoutput

// モータPWMの制御用変数
PwmOut PwmMoterFL(p21), PwmMoterFR(p22);
PwmOut PwmMoterBL(p23), PwmMoterBR(p24);
PwmOut PwmMoterCL(p25), PwmMoterCR(p26);

Timer timerNoDamage;	// 無敵状態のためのタイマー
Timer timerLaser;		// レーザー用タイマー

// シリアル通信について
Serial XbeeRobo(p13, p14);	// tx, rx

// XBeeの設定
// XBee   XbeeRobo(p13, p14);	// tx, rx



// ロボットの状態を表す構造体
typedef struct {
	bool canActive;	// 結果は出てないか？
	bool noDamage;  // 無敵状態かどうか？
	bool canLaser;	// レーザーは打てるか？
	int  hp;		// HP
	int  bullet;	// 残弾数
} RoboStatus;


// モータの個体値調整用変数
float mFL = 0, mFR = 0;
float mCL = 0, mCR = 0;
float mBL = 0, mBR = 0;





int main(void)
{
	XbeeRobo.baud(9600);
	RoboStatus robo;	// ロボットの初期状態
		robo.canActive = true;
		robo.noDamage  = false;
		robo.canLaser  = true;
		robo.hp        = 10;
		robo.bullet    = 100;
	char pcData[4+1] = "nnnn";	// 受信データ格納用
								// {ジョイスティック, LR, レーザー, コマンド}
	char c;
	int i=0;	// ループカウント用変数　




	while(1) {
		i = (i<10) ? ++i : 0;	// ループ回数を記録


		// 操作データを受信して、モータを制御（シリアル通信）
		// 割り込み式にした方がいいかも
		for(int count=0 ;; count++) {
			if (XbeeRobo.readable()) {
				c = XbeeRobo.getc();
				pcData[count] = c;
				if (c == '\0' && pcData[5] == '\0') break;	// nullの位置が一致しているかを確認して同期をとる
			} else break;
		}


		// ダーメジに関する処理
		if (i==0) {
			timerNoDamage.stop();
			if (timerNoDamage.read()>NODAMAGETIME) {	// 無敵状態がNODAMAGETIME秒以上続いていたら、無敵状態終了
				timerNoDamage.reset();
				robo.noDamage = false;
			} else timerNoDamage.start();	// 違ったら、無敵状態継続
		}
		if (SenserIn && !robo.noDamage) {	// ダメージ処理
			if (--robo.hp < 1) {	// 負けたときの処理
				XbeeRobo.putc('L');
				robo.canActive = false;
				break;
			}
			robo.noDamage = true;
			timerNoDamage.start();	// ダーメジを受けたので一時的に無敵状態
		}


		for(int count=0 ;; count++) {
			if (XbeeRobo.readable()) {
				c = XbeeRobo.getc();
				pcData[count] = c;
				if (c == '\0' && pcData[5] == '\0') break;	// nullの位置が一致しているかを確認して同期をとる
			} else break;
		}

		// ロボットの状態をPCに送信
		XbeeRobo.putc(robo.canActive);
		XbeeRobo.putc(robo.noDamage);
		XbeeRobo.putc(robo.canLaser);
		XbeeRobo.putc(robo.hp);
		XbeeRobo.putc(robo.bullet);
		XbeeRobo.putc('\0');



		if (!robo.canActive) continue;	// ロボットが動く必要がない場合、アクチュエータを動かさない

		MOVE(pcData[0],  pcData[1]);	// 0:ジョイスティック  1:LR

		// レーザーコマンドの処理
		if (pcData[2]=='l') {
			if (robo.canLaser) {
				Laser = 1;
				timerLaser.start();
			} else {
				timerLaser.stop();
				if (timerLaser.read() > 0.5) {
					Laser = 0;
					robo.canLaser = true;
					timerLaser.reset();
				} else {
					timerLaser.start();
				}
			}
		}

		// コマンドの処理
		switch (pcData[3]) {
			case 'n':
			default:
				break;
		}
	}
	return 0;
}




/*---  モータの制御関数  ---*/
void MOVE(char direction, char lr)
{
	float fl, fr;
	float cl, cr;
	float bl, br;

	// 進行方向コマンド -> モータ制御
	switch (direction) {
		case 'n':	// none
			fl =  0.0,  fr =  0.0;
			cl =  0.0,  cr =  0.0;
			bl =  0.0,  br =  0.0;
			break;
		case 'w':	// 前
			fl =  1.0,  fr =  1.0;
			cl =  1.0,  cr =  1.0;
			bl = -1.0,  br = -1.0;
			break;
		case 'e':	// 右斜め前
			fl =  0.0,  fr =  1.0;
			cl =  0.0,  cr =  0.0;
			bl = -1.0,  br =  0.0;
			break;
		case 'd':	// 右
			fl = -1.0,  fr =  1.0;
			cl =  0.0,  cr =  0.0;
			bl = -1.0,  br =  1.0;
			break;
		case 'c':	// 右斜め後ろ
			fl = -1.0,  fr =  0.0;
			cl =  0.0,  cr =  0.0;
			bl =  0.0,  br =  1.0;
			break;
		case 'x':	// 後ろ
			fl = -1.0,  fr = -1.0;
			cl = -1.0,  cr = -1.0;
			bl =  1.0,  br =  1.0;
			break;
		case 'z':	// 左斜め後ろ
			fl =  0.0,  fr = -1.0;
			cl =  0.0,  cr =  0.0;
			bl =  1.0,  br =  0.0;
			break;
		case 'a':	// 左
			fl =  1.0,  fr = -1.0;
			cl =  0.0,  cr =  0.0;
			bl =  1.0,  br = -1.0;
			break;
		case 'q':	// 左斜め前
			fl =  1.0,  fr =  0.0;
			cl =  0.0,  cr =  0.0;
			bl =  0.0,  br = -1.0;
			break;
		default:
			break;
	}

	// 旋回コマンド処理
	switch (lr) {
		case 'l':
			cl -= 0.5;  cr += 0.5;  break;
		case 'r':
			cr += 0.5;  cr -= 0.5;  break;
		default:
			break;
	}

	// それぞれのモータの個体値を調整
	PwmMoterFL = fl * mFL;    PwmMoterFR = fr * mFR;
	PwmMoterCL = cl * mCL;    PwmMoterCR = cr * mCR;
	PwmMoterBL = bl * mBL;    PwmMoterBR = br * mBR;
}







