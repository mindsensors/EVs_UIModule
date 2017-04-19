/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  This program is written by mindsensors.com.
*/

#define DEBUG    1

#include <Wire.h>
#include <EVShield.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9340.h>

#include <EVs_UIModule.h>

uint16_t xPos = 100;
uint16_t yPos = 6;

uint16_t last_xPos, last_yPos;
uint8_t colorPos = 1;
uint8_t last_colorPos;
uint16_t colorTable[] = {
EVs_UIM_BLACK,
EVs_UIM_BLUE,
EVs_UIM_RED,
EVs_UIM_GREEN,
EVs_UIM_CYAN,
EVs_UIM_MAGENTA,
EVs_UIM_YELLOW,
EVs_UIM_WHITE
};

EVShield          evshield(0x34,0x36);

char str[40];

EVs_UIModule uim = EVs_UIModule( 7, 8, 9 );

/*
 * Connect the EVShield UI Module on EVShield
 *   Notice the '0' sign on the screen.
 *      Press button left/right/up/down to move the sign.
 *      Press button down (click) to change color.
 */
void  setup()
{
    Serial.begin(115200);       // start serial for output
    delay(1000);                // wait two seconds, allowing time to
    // activate the serial monitor
    evshield.init( SH_HardwareI2C );
    uim.begin();
    uim.clearScreen();
    Serial.println ("Press Button: up/down/left/right/click");
}

void loop()
{
    char str[200];
    if ( uim.getButtonState(EVs_BTN_LEFT) == true ) {
        delay(300);
        if ( xPos > 12 ) xPos -= 12;
    }
    if ( uim.getButtonState(EVs_BTN_RIGHT) == true ) {
        delay(300);
        if ( xPos < 300 ) {
            xPos += 12;
        }
    }
    if ( uim.getButtonState(EVs_BTN_UP) == true ) {
        delay(300);
        if ( yPos > 1 ) yPos --;
    }
    if ( uim.getButtonState(EVs_BTN_DOWN) == true ) {
        delay(300);
        if ( yPos < 15 ) yPos ++;
    }
    if ( uim.getButtonState(EVs_BTN_CLICK) == true ) {
        delay(300);
        if ( colorPos < 8 ) colorPos ++;
        else colorPos = 0;
    }
    if ( last_xPos != xPos || last_yPos != yPos || last_colorPos != colorPos) {
        uim.writeLine(xPos,yPos,"0", false, colorTable[colorPos]);
        sprintf (str, "xPos: %d, yPos: %d", xPos, yPos);
        Serial.println(str);
    }

    last_xPos = xPos;
    last_yPos = yPos;
    last_colorPos = colorPos;

}
