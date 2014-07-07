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

// xbeeのインスタンス
XBeeReader xbee;
nt ad64H=0x0013A200;
int [] ad64L={0x403E17E5,0x403E17E6,0x403E17E3};
int [] ad16={0xFFFE,0xFFFE,0xFFFE};
String [] ni={" 204"," 203"," 205"};





void setup(){
	// シリアルポート設定
	port_mbed = new Serial(this, /*"シリアルポート"*/, portrate);

    // xbeeの初期設定
    port_xbee = new Serial(this, Serial.list()[0], 9600);
    xbee = new XBeeReader(this,port_xbee);
    xbee.startXBee();
    println("XBee Library version " + xbee.getVersion());
}




void draw(){

}











