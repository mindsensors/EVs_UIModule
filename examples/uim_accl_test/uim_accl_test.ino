#define DEBUG    1

#include <Wire.h>
#include <EVShield.h>
#include <EVs_AbsoluteIMU.h>

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

//
// declare the EVShield(s) attached to your Arduino.
//
EVShield          evshield(0x34,0x36);

//
// declare the i2c devices used on EVShield(s).
//

EVs_AbsoluteIMU imu (0x22);

char str[256];

EVs_UIModule uim = EVs_UIModule( 7, 8, 9 );

void  setup()
{
  char aa[80];        
  char str[256];          //sets length of character string  
  Serial.begin(115200);       // start serial for output
    delay(1000);                // wait two seconds, allowing time to
    // activate the serial monitor
    evshield.init( SH_HardwareI2C );
    uim.begin();
    imu.init( &evshield, SH_BAS1 );
    testText();
    delay(2000);
    //shieldInfo();
    //delay(1000);
    uim.clearScreen();
    Serial.println ("Press Buttons");

    Serial.println ("Press GO button to continue");
    uim.writeLine(0,1,"Press GO to continue",true,EVs_UIM_GREEN);
    evshield.waitForButtonPress(BTN_GO);
    
    //uim.writeLine(0,6,"        UP",false,EVs_UIM_RED);
    //uim.waitForButtonPress(EVs_BTN_UP);
    //uim.writeLine(0,6,"Running ...",false,EVs_UIM_WHITE);
    delay(500);
    /**  Displays Firmeware Version of sensor
*/
  strcpy(aa, imu.getFirmwareVersion() );
  sprintf (str, "FirmwareVersion: %s", aa);
  Serial.println(str);
  uim.writeLine(0,1,"Firmware Version: ",true,EVs_UIM_WHITE);
  uim.writeLine(205,1,imu.getFirmwareVersion(),false,EVs_UIM_YELLOW);
/**  Displays Device ID of sensor
 */
  strcpy(aa, imu.getDeviceID() );
  sprintf (str, "DeviceID: %s", aa);
  Serial.println(str);
  uim.writeLine(0,2,"Device ID: ",true,EVs_UIM_WHITE);
  uim.writeLine(120,2,imu.getDeviceID(),false,EVs_UIM_YELLOW);
/**  Gets and displays Vendor ID of sensor
 */
  strcpy(aa, imu.getVendorID() );
  sprintf (str, "VendorID: %s", aa);
  Serial.println(str);
  uim.writeLine(0,3,"Vendor ID: ",true,EVs_UIM_WHITE);
  uim.writeLine(120,3,imu.getVendorID(),false,EVs_UIM_YELLOW);
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
  char aa[80];        
  char str[256];          //sets length of character string
  uint8_t  result;
  char str2[256];          //sets length of character string 2
  char str3[256];          //sets length of character string 3 
  gyro mygyro;            //declares mygyro variable
  cmps mycmps;            //declares mycmps variable
  accl myaccl;            //declares myaccl variable
  magnetic_field mymgnt;  //declares mymgnt variable

/**  Displays Accelerometer reading
 */  
  Serial.println("Acceleration");
  uim.writeLine(0,5,"Acceleration:",false,EVs_UIM_WHITE);
  imu.readAccelerometer(myaccl);
  sprintf (str, "x: %d", myaccl.ax);
  Serial.println(str);  
  uim.writeLine(0,6,str,true,EVs_UIM_YELLOW);
  sprintf (str2, "y: %d", myaccl.ay);
  Serial.println(str);
  uim.writeLine(0,7,str2,true,EVs_UIM_YELLOW);
  sprintf (str3, "z: %d", myaccl.az);
  Serial.println(str);
  uim.writeLine(0,8,str3,true,EVs_UIM_YELLOW);
  delay (500);
}
