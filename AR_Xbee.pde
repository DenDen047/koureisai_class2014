// Processing のプログラム
/*
	ポート番号を確認
	ls /dev/tty.*
*/


// ライブラリのインポート
import processing.core.*;
import processing.serial.*;
import xbee.XBeeDataFrame;
import xbee.XBeeReader;



// ポートのインスタンス
Serial port_mbed;
Serial port_xbee;
const　unsigned int portrate = 9600;


// クラスの宣言
Robo robo;


void setup(){
	port_mbed = new Serial(this, /*"シリアルポート"*/, portrate);	// シリアルポート設定
    port_xbee = new Serial(this, /*"シリアルポート"*/, portrate);	// xbeeの初期設定
}




void draw(){

}



void serialEvent(Serial p) {
	// コントローラからの通信を受信したとき
	if (p == port_mbed) {
		while (!(port_mbed.available() > 4)) {}	// 5コすべてのデータが届くまで待つ
		for (int i=0; i<6; i++) robo.ControlData[i] = port_mbed.read();
	}

	// ロボットからの通信を受信したとき
	if (p == port_xbee) {
		while (port_xbee.available() > 5) {}	// 6コすべてのデータが届くまで待つ
		// 受け取ったデータを代入
		robo.canActive = port_xbee.read();
		robo.noDamage  = port_xbee.read();
		robo.canLaser  = port_xbee.read();
		robo.hp        = port_xbee.read();
		robo.bullet    = port_xbee.read();
	}
}





// ロボットに関するクラス
public class Robo {
	// コントローラに関する変数
	char[4+1] ControlData;	// コントローラからの受信データ格納用
							// {ジョイスティック, LR, レーザー, コマンド, null}

	// ロボットの状態に関する変数
	boolean canActive;	// 結果は出てないか？
	boolean noDamage;	// 無敵状態かどうか？
	boolean canLaser;	// レーザーは打てるか？
	int     hp;			// HP
	int     bullet;		// 残弾数
}














