#define DEBUG    1

#include <Wire.h>
#include <EVShield.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>

#include <EVs_UIModule.h>

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
/*
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 7
#define _dc 8
#define _rst 9
 */

EVShield          evshield(0x34,0x36);

char str[40];

EVs_UIModule uim = EVs_UIModule( 7, 8, 9 );

void  setup()
{
    Serial.begin(115200);       // start serial for output
    delay(1000);                // wait two seconds, allowing time to
    // activate the serial monitor
    Serial.println ("before EVShield init");
    evshield.init( SH_HardwareI2C );
    uim.begin();
    Serial.println ("after uim.begin");

    evshield.bank_a.centerLedSetRGB(0,0,100);
    Serial.println ("after first led");
    evshield.bank_a.ledSetRGB(0,0,100);
    Serial.println ("after second led");
    evshield.bank_b.ledSetRGB(0,0,100);
    Serial.println ("after third led");

    Serial.println ("before testText");
    testText();
    Serial.println ("after testText");
    delay(2000);
    shieldInfo();
    delay(1000);
    //uim.clearScreen();
    Serial.println ("Press Buttons");

    uim.writeLine(0,6,"  Press Buttons",true,EVs_UIM_WHITE);
    //uim.writeLine(0,6,"        UP",false,EVs_UIM_RED);
    //uim.waitForButtonPress(EVs_BTN_UP);
    //uim.writeLine(0,6,"Running ...",false,EVs_UIM_WHITE);
}

unsigned long testText() {
    uim.clearScreen();
    unsigned long start = micros();
    //uim.setCursor(0,15);
    //uim.println("EVShield");

    uim.setCursor(0,75);
    uim.setTextColor(EVs_UIM_WHITE);  uim.setTextSize(4);
    uim.println("EVShield");
    uim.setTextColor(EVs_UIM_YELLOW); uim.setTextSize(2);
    uim.println("mindsensors.com");
    uim.setTextColor(EVs_UIM_GREEN);    uim.setTextSize(2);
    uim.println("Arduino Shield for");
    uim.setTextColor(EVs_UIM_RED);    uim.setTextSize(2);
    uim.println("LEGO EV3 Sensors & Motors");
    uim.println();
    delay(500);
    return micros() - start;
}

void shieldInfo(){
    uim.clearScreen();
    uim.writeLine(50,1,evshield.bank_a.getDeviceID(),true,EVs_UIM_GREEN);
    uim.writeLine(50,2,evshield.bank_a.getVendorID(),true,EVs_UIM_YELLOW);
    uim.writeLine(50,3,evshield.bank_a.getFirmwareVersion(),true,EVs_UIM_WHITE);
    Serial.println(evshield.bank_a.getDeviceID());
    Serial.println(evshield.bank_a.getVendorID());
    Serial.println(evshield.bank_a.getFirmwareVersion());
}

void loop()
{
    if ( uim.getButtonState(EVs_BTN_LEFT) == true ) {
        //uim.setTextColor(EVs_UIM_WHITE);    uim.setTextSize(2);
        //uim.println("LEFT pressed");
        uim.writeLine(50,8,"LEFT pressed",true,EVs_UIM_WHITE);
        delay(300);
    }
    if ( uim.getButtonState(EVs_BTN_RIGHT) == true ) {
        //uim.setTextColor(ILI9340_RED);    uim.setTextSize(2);
        //uim.println("RIGHT pressed");
        uim.writeLine(50,8,"RIGHT pressed",true,EVs_UIM_RED);
        delay(300);
    }
    if ( uim.getButtonState(EVs_BTN_UP) == true ) {
        //uim.setTextColor(EVs_UIM_GREEN);    uim.setTextSize(2);
        //uim.println("UP pressed");
        uim.writeLine(50,8,"UP pressed",true,EVs_UIM_GREEN);
        delay(300);
    }
    if ( uim.getButtonState(EVs_BTN_DOWN) == true ) {
        //uim.setTextColor(EVs_UIM_CYAN);    uim.setTextSize(2);
        //uim.println("DOWN pressed");
        uim.writeLine(50,8,"DOWN pressed",true,EVs_UIM_CYAN);
        delay(300);
    }
    if ( uim.getButtonState(EVs_BTN_CLICK) == true ) {
        //uim.setTextColor(EVs_UIM_BLUE);    uim.setTextSize(2);
        //uim.println("Button Clicked");
        uim.writeLine(50,8,"Button Clicked",true,EVs_UIM_BLUE);
        delay(300);
    }

}
