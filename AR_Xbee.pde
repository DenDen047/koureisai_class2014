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
const int portrate = 9600;






void setup(){
	port_mbed = new Serial(this, /*"シリアルポート"*/, portrate);	// シリアルポート設定
    port_xbee = new Serial(this, /*"シリアルポート"*/, portrate);	// xbeeの初期設定
}




void draw(){

}



void serialEvent(Serial p) {
	// コントローラからの通信を受信したとき
	if (p == port_mbed) {

	}

	// ロボットからの通信を受信したとき
	if (p == port_xbee) {

	}
}





// ロボットに関するクラス
public class Robo {
	char[4+1] ControlData;	// コントローラからの受信データ格納用
							// {ジョイスティック, LR, レーザー, コマンド, null}
	char[5+1] RoboStatus;	// ロボットの状態
							// {動けるか, 無敵状態か, レーザーを打てるか, HP, 残段数, null}

	void SendRoboData(void) {
		for (int i=0; i<5; i++) {
			port_xbee.write(ControlData[i]);
		}
	}

	void ReceiveRoboStatus(void) {
		while (c==null) {
			RoboStatus[i] = port_xbee.read();
		}
	}
}














