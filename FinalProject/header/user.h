#ifndef USER_H
#define USER_H

void TimerOn();
void TimerOff();
void TimerISR();
ISR(TIMER1_COMPA_vect);
void TimerSet(unsigned long M);
void LCD_Command(unsigned char cmnd);

void LCD_Char (unsigned char char_data);


void LCD_Init (void);

void LCD_String (char *str);

void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();


void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void LCD_Cursor(unsigned char column);
void snake_dire();

void check_border();
void gene_score();


void set_PWM(double frequency);

void PWM_on();


void PWM_init();

#endif
