#include "HID-Project.h"

#define FINAL_CHAR 'N'

char buff[50] = {0};
int buff_ptr = 0;
void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  Gamepad.begin();
}

void loop() {
  while (!Serial1.available()) {}
  char s = Serial1.read();
  buff[buff_ptr++] = s;
  if (s == FINAL_CHAR) {
    if(buff_ptr==18){
      int n = 100*(buff[0] - '0');
      n+= 10*(buff[1] - '0');
      n+= 1*(buff[2] - '0');
      int i;
      for(i=0;i<14;i++){
        if(buff[i+3]=='1'){
          Gamepad.press(i+1);
        }else{
          Gamepad.release(i+1);
        }
      }
      Gamepad.xAxis(map(n,0,255,0,0xFFFF)+0x7FFF);
      Gamepad.write();
    }
    buff_ptr = 0;
  }
}
