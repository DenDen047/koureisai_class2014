#include "mbed.h"

Serial pc(USBTX, USBRX); // tx, rx
Serial xbee(p28, p27);

DigitalOut FRin1(p11);
DigitalOut FRin2(p12);
PwmOut FRpwm(p25);

DigitalOut FLin1(p13);
DigitalOut FLin2(p14);
PwmOut FLpwm(p22);

DigitalOut BRin1(p15);
DigitalOut BRin2(p16);
PwmOut BRpwm(p24);

DigitalOut BLin1(p17);
DigitalOut BLin2(p18);
PwmOut BLpwm(p23);

DigitalOut Rin1(p5);
DigitalOut Rin2(p6);
PwmOut Rpwm(p26);

DigitalOut Lin1(p7);
DigitalOut Lin2(p8);
PwmOut Lpwm(p21);




int main() {
    float i = 1.0;

    while(1) {
        pc.printf("Hello World!\n");
        xbee.printf("Hello World!\n");


        FLpwm = i;  FRpwm = i;
        Rpwm  = i;  Lpwm  = i;
        BLpwm = i;  BRpwm = i;

        FRin1 = 1;   FRin2 = 0;
        FLin1 = 1;   FLin2 = 0;
        BRin1 = 1;   BRin2 = 0;
        BLin1 = 1;   BLin2 = 0;
        Rin1  = 1;   Rin2  = 0;
        Lin1  = 1;   Lin2  = 0;
        wait(1.0);

        FRin1 = 0;   FRin2 = 1;
        FLin1 = 0;   FLin2 = 1;
        BRin1 = 0;   BRin2 = 1;
        BLin1 = 0;   BLin2 = 1;
        Rin1  = 0;   Rin2  = 1;
        Lin1  = 0;   Lin2  = 1;
        wait(1.0);

        FRin1 = 1;   FRin2 = 1;
        FLin1 = 1;   FLin2 = 1;
        BRin1 = 1;   BRin2 = 1;
        BLin1 = 1;   BLin2 = 1;
        Rin1  = 1;   Rin2  = 1;
        Lin1  = 1;   Lin2  = 1;
        wait(0.3);

    }
    return 0;
}