#include <linux/delay.h>
#include <linux/i2c.h>
#include "io_lcd1602.h"

#define LCD_BKL_OFF 0
#define LCD_BKL_ON 0x08

extern struct i2c_client  *ext_i2c_dev;

static unsigned char reg_LCD_BKL = 0;
static unsigned int acc_char=0;

int send_byte_to_LCD (unsigned char data) {
    int ret;
    ret = i2c_master_send(ext_i2c_dev, &data, 1);    
    return ret;
}

//--------------------------------------------------

void delayMicroseconds(int i1){
	udelay(i1);
}

void write_h4bit_cmd (unsigned char data_4bit) {
    send_byte_to_LCD((data_4bit & 0xf0) | 0x04 | reg_LCD_BKL);
    delayMicroseconds(1);
    send_byte_to_LCD((data_4bit & 0xf0) | 0x00 | reg_LCD_BKL);
    delayMicroseconds(50); // commands need > 37us to settle
}

void write_8bit_cmd (unsigned char data_8bit) {
    send_byte_to_LCD((data_8bit & 0xf0) | 0x04 | reg_LCD_BKL);
    delayMicroseconds(1);
    send_byte_to_LCD((data_8bit & 0xf0) | 0x00 | reg_LCD_BKL);
    delayMicroseconds(50);

    send_byte_to_LCD(((data_8bit << 4) & 0xf0) | 0x04 | reg_LCD_BKL);
    delayMicroseconds(1);
    send_byte_to_LCD(((data_8bit << 4) & 0xf0) | 0x00 | reg_LCD_BKL);
    delayMicroseconds(50);
    
}

void write_8bit_data ( unsigned char data_8bit) {
    send_byte_to_LCD((data_8bit & 0xf0) | 0x05 | reg_LCD_BKL);
    delayMicroseconds(1);
    send_byte_to_LCD((data_8bit & 0xf0) | 0x01 | reg_LCD_BKL);
    delayMicroseconds(50);

    send_byte_to_LCD(((data_8bit << 4) & 0xf0) | 0x05 | reg_LCD_BKL);
    delayMicroseconds(1);
    send_byte_to_LCD(((data_8bit << 4) & 0xf0) | 0x01 | reg_LCD_BKL);
    delayMicroseconds(50);
    
}

//-----------------
void LCD_BKL_on(void){
  reg_LCD_BKL=LCD_BKL_ON;  
  send_byte_to_LCD(reg_LCD_BKL);  
};

void LCD_BKL_off(void){
  reg_LCD_BKL=LCD_BKL_OFF;  
  send_byte_to_LCD(reg_LCD_BKL);  
};

void LCD_home(void){
  write_8bit_cmd(0x02); // cmd2:02 , home
  delayMicroseconds(2000);  
};

void LCD_clear(void){
  write_8bit_cmd(0x01); // cmd1:01 , clear display
  delayMicroseconds(2000);  
}

void LCD_pos_x1y1(void){
  write_8bit_cmd(0x80 | 0x00 ); // cmd8:02 , set DDRAM adrress first line
  delayMicroseconds(2000); 
  }
void LCD_pos_x1y2(void){
  write_8bit_cmd(0x80 | 0x40 ); // cmd8:02 , set DDRAM adrress 2nd line
  delayMicroseconds(2000); 
  } 
void LCD_write_char(char c1){
  write_8bit_data((unsigned char)c1);  
}
void LCD_init(void){
  send_byte_to_LCD(0x00);  
  send_byte_to_LCD(0x00);
  delayMicroseconds(1000);
  write_h4bit_cmd(0x30);
  delayMicroseconds(1000);

  write_h4bit_cmd(0x30);
  delayMicroseconds(1000);

  write_h4bit_cmd(0x30);
  delayMicroseconds(1000);  

  write_h4bit_cmd(0x20); // cmd6:28 ,change to 4bit mode
  delayMicroseconds(1000);   

  write_8bit_cmd(0x28); // cmd6:28 ,4bit mode, 2 line mode
  delayMicroseconds(1000);  

  write_8bit_cmd(0x0c); // cmd4:0c , enable display
  delayMicroseconds(1000);  

  write_8bit_cmd(0x06); // cmd3:06 , set cursor mode
  delayMicroseconds(2000);  
  
  LCD_clear();

  LCD_BKL_on();

  LCD_home();
  acc_char=0;
}

void LCD_parse_string (unsigned char *tmpbuf, unsigned int count ) {
	int i1;
	for (i1=0; i1 < count; i1++){
		if (tmpbuf[i1] == '\r'){

			LCD_clear();
			LCD_home();
			acc_char=0;
		} else if (tmpbuf[i1] == '\a') {
			LCD_BKL_on();
		} else if (tmpbuf[i1] == '\b'){
			LCD_BKL_off();
		} else if (tmpbuf[i1] == '\t'){
			LCD_home();
			acc_char=0;
		} else if (tmpbuf[i1] == '\n'){
			//do nothing
		} else {
			if (acc_char == 16){
				LCD_pos_x1y2();
			}
			LCD_write_char(tmpbuf[i1]);
			acc_char++;
		}
	}
}
