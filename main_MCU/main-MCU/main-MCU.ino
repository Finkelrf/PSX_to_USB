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
