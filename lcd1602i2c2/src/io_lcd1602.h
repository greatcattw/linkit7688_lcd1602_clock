#ifndef IO_LCD1602_h
#define IO_LCD1602_h

void LCD_BKL_on(void);
void LCD_BKL_off(void);
void LCD_home(void);
void LCD_clear(void);
void LCD_pos_x1y1(void);
void LCD_pos_x1y2(void);
void LCD_write_char(char c1);
void LCD_init(void);
void LCD_parse_string (unsigned char *tmpbuf, unsigned int count );
#endif


