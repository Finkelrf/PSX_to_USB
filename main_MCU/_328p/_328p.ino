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

#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 8
#define cmndPin 9
#define attPin 11
#define clockPin 10

#define LEDPin 13
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
Psx Psx;                                                  // Initializes the library

unsigned int data = 0;                                    // data stores the controller response

void setup()
{
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
  pinMode(LEDPin, OUTPUT);                                // Establishes LEDPin as an output so the LED can be seen
  Serial.begin(115200);
}

void loop()
{
  data = Psx.read();                                      // Psx.read() initiates the PSX controller and returns
                                                          // the button data

  checkButtons(data);
  
  //Serial.println(data);                                   // Display the returned numeric value

}

bool is_bit_set(unsigned int data, unsigned int bit_pos){
  return (data | ~(bit_pos)) == ~((unsigned int)0);
}
void checkButtons(unsigned int data){

  if(is_bit_set(data,4)){
    Serial.print('d');
  }
  if(is_bit_set(data,1)){
    Serial.print('q');
  }
  if(is_bit_set(data,8)){
    Serial.print('p');
  }
  if(is_bit_set(data,2)){
    Serial.print('m');
  }
  if(is_bit_set(data,256)){
    Serial.print('s');
  }
  if(is_bit_set(data,512)){
    Serial.print('z');
  }
  if(is_bit_set(data,8192)){
    Serial.print('a');
  }
    if(is_bit_set(data,4096)){
    Serial.print('e');
  }
  delay(20);
}

