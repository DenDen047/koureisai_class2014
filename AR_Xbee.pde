// Processing のプログラム
/*
	ポート番号を確認
	ls /dev/tty.*
*/


//シリアル通信ライブラリを取り入れる
import processing.serial.*;

//ポートのインスタンス
Serial port_mbed;
Serial port_xbee;
const int portrate = 9600;


void setup(){
  // シリアルポート設定
  port_mbed = new Serial(this, /*"シリアルポート"*/, portrate);
  port_xbee = new Serial(this, /*"シリアルポート"*/, portrate);
}

void draw(){

}










