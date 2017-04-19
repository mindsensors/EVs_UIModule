/*
  (c) mindsensors.com

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

typedef struct { uint8_t x; uint8_t y;} SNPoint;

SNPoint snakePoints[255];
uint8_t snakeLen = 5;
SNPoint frog;
uint16_t score = 0;

enum SNDirection { SN_NONE=0, SN_UP, SN_DOWN, SN_LEFT, SN_RIGHT};
SNDirection moveDirection = SN_NONE;

EVShield          evshield(0x34,0x36);

long timeGap = 500;
char scoreStr[40];

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
    showLogo();
    uim.clearScreen();

    snakePoints[0].x = 12;
    snakePoints[0].y = 8;
    randomSeed(analogRead(0));
    drawNewFrog();
}

void showLogo() {
    uim.clearScreen();

    uim.setCursor(0,35);
    uim.setTextColor(EVs_UIM_YELLOW); uim.setTextSize(2);
    uim.println("Snake and Frog Game");
    uim.println("");
    uim.setCursor(0,75);
    uim.setTextColor(EVs_UIM_WHITE);  uim.setTextSize(4);
    uim.println("EVShield");
    uim.setTextColor(EVs_UIM_YELLOW); uim.setTextSize(2);
    uim.println("mindsensors.com");
    uim.println();
    uim.setTextColor(EVs_UIM_RED); uim.setTextSize(2);
    uim.println("To begin, Press key:");
    uim.println("  left/right/up/down");
    delay(5000);
}


void drawNewFrog()
{
    uim.writeLine(frog.x*12,frog.y, "X", false, EVs_UIM_BLACK);
    frog.x = random(1,25);
    frog.y = random(1,15);
    uim.writeLine(frog.x*12,frog.y, "X", false, EVs_UIM_GREEN);
}

bool frogMatches()
{
    if ( snakePoints[0].x == frog.x && snakePoints[0].y == frog.y ) return true;
    return false;
}

void pushPoints()
{
    uint8_t i;
    for (i=254; i > 0; i--) {
        snakePoints[i].x = snakePoints[i-1].x;
        snakePoints[i].y = snakePoints[i-1].y;
    }
}

void delay_with_button_check(int delay)
{
  long t = millis();
  long t2;
  t2 = t + delay;

  while ( millis() < t2 ) {
    if ( uim.getButtonState(EVs_BTN_LEFT) == true ) {
        moveDirection = SN_LEFT;
    }
    if ( uim.getButtonState(EVs_BTN_RIGHT) == true ) {
        moveDirection = SN_RIGHT;
    }
    if ( uim.getButtonState(EVs_BTN_UP) == true ) {
        moveDirection = SN_UP;
    }
    if ( uim.getButtonState(EVs_BTN_DOWN) == true ) {
        moveDirection = SN_DOWN;
    }
    if ( uim.getButtonState(EVs_BTN_CLICK) == true ) {
        moveDirection = SN_NONE;
    }
  }
}

void loop()
{
    delay_with_button_check(timeGap);
    
    uim.writeLine(snakePoints[0].x*12,snakePoints[0].y,
                               "0", false, EVs_UIM_WHITE);
    for (int i=1; i < snakeLen; i++) {
        uim.writeLine(snakePoints[i].x*12,snakePoints[i].y,
                               "0", false, EVs_UIM_RED);
    }
    uim.writeLine(snakePoints[snakeLen].x*12,snakePoints[snakeLen].y,
                               "0", false, EVs_UIM_BLACK);

    switch (moveDirection) {
        case SN_NONE:
        break;
        case SN_UP:
            if ( score > 0) score --;
            if ( snakePoints[0].y > 1 ) {
                pushPoints();
                snakePoints[0].y = snakePoints[1].y - 1;
                snakePoints[0].x = snakePoints[1].x;
            }
        break;
        case SN_DOWN:
            if ( score > 0) score --;
            if ( snakePoints[0].y < 15 ) {
                pushPoints();
                snakePoints[0].y = snakePoints[1].y + 1;
                snakePoints[0].x = snakePoints[1].x;
            }
        break;
        case SN_LEFT:
            if ( score > 0) score --;
            if ( snakePoints[0].x > 1 ) {
                pushPoints();
                snakePoints[0].x = snakePoints[1].x - 1;
                snakePoints[0].y = snakePoints[1].y;
            }
        break;
        case SN_RIGHT:
            if ( score > 0) score --;
            if ( snakePoints[0].x < 25 ) {
                pushPoints();
                snakePoints[0].x = snakePoints[1].x + 1;
                snakePoints[0].y = snakePoints[1].y;
            }
        break;
    }
    if ( frogMatches() == true ) {
        score += 100;
        snakeLen ++;
        drawNewFrog();
        timeGap -= (timeGap/10);
    }
    uim.writeLine(12,15, scoreStr, false, EVs_UIM_BLACK);
    sprintf (scoreStr, "%d", score);
    uim.writeLine(12,15, scoreStr, false, EVs_UIM_BLUE);

}
