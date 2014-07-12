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


char[] roboData="nnnn";



void setup(){
	port_mbed = new Serial(this, /*"シリアルポート"*/, portrate);	// シリアルポート設定
    port_xbee = new Serial(this, /*"シリアルポート"*/, portrate);	// xbeeの初期設定
}




void draw(){

}



void serialEvent(Serial p) {
	if (p == port_mbed) {
		while (p.available()) {

		}
	}
}







