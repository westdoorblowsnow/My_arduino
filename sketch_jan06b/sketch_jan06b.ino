 
/*
使用u8g2显示数据
图形显示器：OpenJumper 12864 OLED
设备核心：SSD1306
*/
 
#include <U8g2lib.h>
 
#define rst  2
U8G2_SSD1306_128X64_NONAME_F_HW_I2C  u8g2(U8G2_R0 , rst);
 
const char rook_bitmap[] = {
  0x00,         // 00000000 
  0x55,         // 01010101
  0x7f,          // 01111111
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x3e,         // 00111110
  0x3e,         // 00111110 
  0x7f           // 01111111
};

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.drawBitmapP( 0, 0, 1, 8, rook_bitmap);
}

void setup(void) {
}

void loop(void) {
  // picture loop
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  
  // rebuild the picture after some delay
  delay(1000);
}
