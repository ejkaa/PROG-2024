#include "lcd_wrapper.h"
#include "config.h"
LiquidCrystal_I2C lcd(0x27,16,2);

byte degree[8] = {B00110, B01001, B01001, B00110, B00000, B00000, B00000, B00000};

void lcd_init(){
  lcd.init();
  lcd.createChar(1, degree);
}
void lcd_clear(){
  lcd.clear();
}

void lcd_set_cursor(int y, int x){
  lcd.setCursor(x,y);
}
void lcd_print(char* text){
  lcd.print(text);
}
void lcd_print_at(int y, int x, char* text){
  lcd.setCursor(x,y);
  lcd.print(text);
}

void lcd_backlight(bool state){
  if(state == 0) lcd.backlight();
  else lcd.noBacklight();
}

void lcd_show_date(const byte day, const byte month, const int year, const byte dow){
  char string[3];
  lcd_set_cursor(0,3);

  if(day<10) lcd_print("0");
  sprintf(string, "%d", day);
  lcd_print(string);
  lcd_print(".");

  if(month<10) lcd_print("0");
  sprintf(string, "%d", month);
  lcd_print(string);
  lcd_print(".");

  lcd_print("20");
  if(year<10) lcd_print("0");
  sprintf(string, "%d", year);
  lcd_print(string);

  char* mo = {"MO"};
  char* tu = {"TU"};
  char* we = {"WE"};
  char* th = {"TH"};
  char* fr = {"FR"};
  char* sa = {"SA"};
  char* su = {"SU"};
  char* week[] = {mo,tu,we,th,fr,sa,su};
  lcd_print_at(1,7, week[dow-1]);
}

void lcd_show_time(const byte hours, const byte minutes, const byte seconds){
  char string[3];
  lcd_set_cursor(0,4);

  if(hours<10) lcd_print("0");
  sprintf(string, "%d", hours);
  lcd_print(string);
  lcd_print(":");

  if(minutes<10) lcd_print("0");
  sprintf(string, "%d", minutes);
  lcd_print(string);
  lcd_print(":");

  if(seconds<10) lcd_print("0");
  sprintf(string, "%d", seconds);
  lcd_print(string);
}

void lcd_show_temphum(const float temperature, const int humidity){
  char string[3];
  lcd_print("Temp: ");
  sprintf(string, "%.1f", temperature);
  lcd_print(string);
  lcd.write(1);
  lcd_print("C");

  lcd_print_at(1,0, "Hum:");
  lcd_set_cursor(1,6);

  sprintf(string, "%d", humidity);
  lcd_print(string);
  lcd_print(" %");
}