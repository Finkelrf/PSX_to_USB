/*  PSX Controller Decoder Library (Psx.pde)
  Written by: Kevin Ahrendt June 22nd, 2008

  Controller protocol implemented using Andrew J McCubbin's analysis.
  http://www.gamesx.com/controldata/psxcont/psxcont.htm

  Shift command is based on tutorial examples for ShiftIn and ShiftOut
  functions both written by Carlyn Maw and Tom Igoe
  http://www.arduino.cc/en/Tutorial/ShiftIn
  http://www.arduino.cc/en/Tutorial/ShiftOut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty oftte,ptingtoente
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <PS2X_lib.h>                                          // Includes the Psx Library 
// Any pins can be used since it is done in software
#define dataPin 8
#define cmndPin 9
#define attPin 11
#define clockPin 10

#define LEDPin 13
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

unsigned int data = 0;                                    // data stores the controller response

void setup()
{
  Serial.begin(115200);
  error = ps2x.config_gamepad(clockPin, cmndPin, attPin, dataPin, false, true);

  /*if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  } else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }*/
}

void loop()
{
  if (error == 1) //skip loop if no controller found
    return;

  if (type == 2) { //Guitar Hero Controller
    return;
  }

  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    int lx= ps2x.Analog(PSS_LX);
    if(lx<100){
      Serial.print("0");
    }
    if(lx<10){
      Serial.print("0");
    }
    Serial.print(lx);
    Serial.print(ps2x.Button(PSB_BLUE));        //X
    Serial.print(ps2x.Button(PSB_PINK));        //square
    Serial.print(ps2x.Button(PSB_RED));                //circle
    Serial.print(ps2x.Button(PSB_GREEN));                //triangle
    Serial.print(ps2x.Button(PSB_PAD_UP));                //up
    Serial.print(ps2x.Button(PSB_PAD_DOWN));                //down
    Serial.print(ps2x.Button(PSB_PAD_LEFT));                //left
    Serial.print(ps2x.Button(PSB_PAD_RIGHT));                //right
    Serial.print(ps2x.Button(PSB_L1));                //L1
    Serial.print(ps2x.Button(PSB_L2));                //L2
    Serial.print(ps2x.Button(PSB_R1));                //R1
    Serial.print(ps2x.Button(PSB_R2));                //R2
    Serial.print(ps2x.Button(PSB_SELECT));                //select
    Serial.print(ps2x.Button(PSB_START));                //start
    Serial.print("N");
    delay(50);
  }


  delay(50);


}


