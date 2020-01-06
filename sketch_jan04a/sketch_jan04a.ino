#include<U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

byte inByte;
long timeLast;
long timeNow;
int running = 1;

void showCpuState(){
  inByte = 0;
  char cpuFrame[20]="0123456789123456789";
  while(inByte!='C'){
      while(Serial.available()==0){
        timeNow = millis();
        if(timeNow-timeLast>3000){
          running = 0;
          return;
        }
      }
    inByte = Serial.read();
  }
  char d = '?';
  for(int i = 0; i < 20; i++){
     while(Serial.available()==0);
     d = Serial.read();
     if(d==' '){
       cpuFrame[i]=0;
     }else{
       cpuFrame[i]=d;
     }
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  //cpu使用率
  u8g2.drawStr(0, 15, "cupU:");
  u8g2.drawStr(56, 15, cpuFrame+1);
  u8g2.drawStr(115, 15, "%");
  //cpu功率
  u8g2.drawStr(0, 31, "cpuP:");
  u8g2.drawStr(56, 31, cpuFrame+5);
  u8g2.drawStr(115, 31, "W");
  //cup温度
  u8g2.drawStr(0, 47, "cpuT:");
  u8g2.drawStr(56, 47, cpuFrame+14);
  u8g2.drawStr(111, 47, "'C");
  u8g2.drawStr(24, 63, "blow_snow");
  u8g2.sendBuffer(); // 打到屏幕上
  timeLast = millis();
}

void showGpuState(){
  inByte = 0;
  char gpuFrame[20]="0123456789123456789";
  while(inByte!='G'){
      while(Serial.available()==0){
        timeNow = millis();
        if(timeNow-timeLast>2000){
          running = 0;
          return;
        }
      }
    inByte = Serial.read();
  }
  char d = '?';
  for(int i = 0; i < 19; i++){
     while(Serial.available()==0);
     d = Serial.read();
     if(d==' '){
       gpuFrame[i]=0;
     }else{
       gpuFrame[i]=d;
     }
  }
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  //gpu使用率
  u8g2.drawStr(0, 15, "gpuU:");
  u8g2.drawStr(56, 15, gpuFrame+1);
  u8g2.drawStr(115, 15, "%");
  //gpu功率
  u8g2.drawStr(0, 31, "gpuP:");
  u8g2.drawStr(56, 31, gpuFrame+5);
  u8g2.drawStr(115, 31, "W");
  //gup温度
  u8g2.drawStr(0, 47, "gpuT:");
  u8g2.drawStr(56, 47, gpuFrame+14);
  u8g2.drawStr(111, 47, "'C");
  u8g2.drawStr(24, 63, "blow_snow");
  u8g2.sendBuffer(); // 打到屏幕上
  timeLast = millis();
}

void showCpuAndGpu(){
  inByte = 0;
  char cpuAndGpuFrame[40]="012345678901234567890123456789123456789";
  while(inByte!='C'){
      while(Serial.available()==0){
        timeNow = millis();
        if(timeNow-timeLast>2000){
          running = 0;
          return;
        }
      }
    inByte = Serial.read();
  }
  char d = '?';
  for(int i = 0; i < 39; i++){
     while(Serial.available()==0);
     d = Serial.read();
     if(d==' '){
       cpuAndGpuFrame[i]=0;
     }else{
       cpuAndGpuFrame[i]=d;
     }
  }
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);

  u8g2.drawStr(14, 15, "CPU");
  u8g2.drawStr(66, 15, "GPU");
  
  u8g2.drawStr(0, 31, "U");
  u8g2.drawStr(0, 47, "P");
  u8g2.drawStr(0, 63, "T");
  u8g2.drawStr(118, 31, "%");
  u8g2.drawStr(118, 47, "W");
  u8g2.drawStr(111, 63, "'C");

  u8g2.drawStr(14, 31, cpuAndGpuFrame+1);
  u8g2.drawStr(14, 47, cpuAndGpuFrame+5);
  u8g2.drawStr(14, 63, cpuAndGpuFrame+14);
  
  u8g2.drawStr(66, 31, cpuAndGpuFrame+21);
  u8g2.drawStr(66, 47, cpuAndGpuFrame+25);
  u8g2.drawStr(66, 63, cpuAndGpuFrame+34);
  u8g2.sendBuffer(); // 打到屏幕上
  timeLast = millis();
}

void showBilibili(int x,int y){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  //gpu使用率
  u8g2.drawStr(x, y, "  Blow Snow  ");
  u8g2.sendBuffer(); // 打到屏幕上
  Serial.println("Serial Port Ready");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial)
    continue;
  
  timeLast = millis();
   u8g2.begin();
   u8g2.enableUTF8Print(); //开启后能显示一些中文字
   showBilibili(16,32);
   Serial.println("Serial Port Ready");
   
}

int kk = 1;

void loop() {
  if(running){
    kk = 1;
    showCpuAndGpu();
  }else{
    if(kk){
      showBilibili(16,32);
      kk = 0;
    }
    if(Serial.available()){
      running = 1;
      kk = 1;
      timeLast = millis();
    }
  }
}
