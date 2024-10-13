#include "states.h"

byte snooze(byte snooze_count){
    if (snooze_count == 0) return 1;
    if (snooze_count == 1) return 2;
    if (snooze_count == 2) return 3;
    return 0;
}

void alarm(const byte hours, const byte minutes){
    byte alarm_hours = EEPROM.read(7);
    byte alarm_minutes = EEPROM.read(8);
    byte snooze_count = EEPROM.read(9);
    
    if (hours == alarm_hours && minutes == alarm_minutes) Serial.println(snooze_count);
    while (hours == alarm_hours && minutes == alarm_minutes){
        struct dt datetime = now();
        lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);

        tone(BUZZER_PIN, NOTE_GS6);
        delay(100);
        noTone(BUZZER_PIN);
        delay(100);

        tone(BUZZER_PIN, NOTE_DS6);
        delay(100);
        noTone(BUZZER_PIN);
        delay(100);

        if (digitalRead(BTN3_PIN)){
            while (digitalRead(BTN3_PIN)){}
            EEPROMTyped.write(8, minutes-1);
            return;
        }
        else if (digitalRead(BTN4_PIN)){
            while (digitalRead(BTN4_PIN)){}
            if(snooze_count > 2){
                snooze_count = 0;
                alarm_minutes--;
            }
            else{
                Serial.println(snooze_count);
                alarm_minutes += snooze(snooze_count);
                if(alarm_minutes > 59){
                    alarm_minutes -= 60;
                    alarm_hours += 1;
                    EEPROMTyped.write(7, alarm_hours);
                }
            }
            snooze_count++;

            EEPROMTyped.write(8, alarm_minutes);
            EEPROMTyped.write(9, snooze_count);
            Serial.println(EEPROM.read(9));
                        
            return;
        }

        tone(BUZZER_PIN, NOTE_GS5);
        delay(100);
        noTone(BUZZER_PIN);
        delay(100);

        tone(BUZZER_PIN, NOTE_AS5);
        delay(100);
        noTone(BUZZER_PIN);
        delay(300);

        if (digitalRead(BTN3_PIN)){
            while (digitalRead(BTN3_PIN)){}
            EEPROMTyped.write(8, minutes-1);
            return;
        }
        else if (digitalRead(BTN4_PIN)){
            while (digitalRead(BTN4_PIN)){}
            if(snooze_count > 2){
                snooze_count = 0;
                alarm_minutes--;
            }
            else{
                Serial.println(snooze_count);
                alarm_minutes += snooze(snooze_count);
                if(alarm_minutes > 59){
                    alarm_minutes -= 60;
                    alarm_hours += 1;
                    EEPROMTyped.write(7, alarm_hours);
                }
            }
            snooze_count++;

            EEPROMTyped.write(8, alarm_minutes);
            EEPROMTyped.write(9, snooze_count);
            Serial.println(EEPROM.read(9));
                        
            return;
        }
    }
}

void write_datetime(const byte day, const byte month, const int year, const byte hours, const byte minutes, const byte seconds, const byte dow){
    EEPROMTyped.write(1, day);
    EEPROMTyped.write(2, month);
    EEPROMTyped.write(3, year);
    EEPROMTyped.write(4, hours);
    EEPROMTyped.write(5, minutes);
    EEPROMTyped.write(6, seconds);
}

enum state state_clock(){
    struct dt datetime = now();
    lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
    delay(20);
    alarm(datetime.hours, datetime.minutes);

    if (digitalRead(BTN1_PIN)) return SHOW_DATE;
    
    else if (digitalRead(BTN2_PIN)) return SHOW_ENV;

    else if (digitalRead(BTN3_PIN)) return ALARM;
    
    else if (digitalRead(BTN4_PIN)) return FACTORY_RESET;

    else return CLOCK;
}

enum state state_show_date(){
    lcd_clear();
    struct dt datetime = now();

    lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
    while (digitalRead(BTN1_PIN)){}
    delay(500);
    lcd_clear();
    
    return CLOCK;
}

enum state state_show_env(){
    lcd_clear();
    float temperature = get_temperature();
    int humidity = get_humidity();

    lcd_show_temphum(temperature, humidity);
    while (digitalRead(BTN2_PIN)){}
    delay(500);
    lcd_clear();

    return CLOCK;
}

enum state state_alarm(){
    while (digitalRead(BTN3_PIN)){}

    struct dt datetime = now();
    datetime.seconds = 0;
    byte hours = EEPROM.read(7);
    byte minutes = EEPROM.read(8);

    if(hours != NULL) datetime.hours = hours;
    if(minutes != NULL) datetime.minutes = minutes;

    lcd_clear();
    lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);

    while (digitalRead(BTN3_PIN) == 0){
        if (digitalRead(BTN1_PIN)){
            datetime.hours ++;
            if (datetime.hours > 23) datetime.hours = 0;
            while (digitalRead(BTN1_PIN)) {}

            delay(20);
            lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
        }
        
        if (digitalRead(BTN2_PIN)){
            datetime.minutes ++;
            if (datetime.minutes > 59) datetime.minutes = 0;
            while (digitalRead(BTN2_PIN)){}
        
            delay(20);
            lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
        }

        if (digitalRead(BTN4_PIN)) {
            EEPROMTyped.write(9, 0);
            Serial.println("Snooze set: 0");
            lcd_print_at(1,4, "Snooze 0");
            while (digitalRead(BTN4_PIN)){}
            delay(500);
            lcd_print_at(1,4, "        ");
        }
    }
    while (digitalRead(BTN3_PIN)){}
            
    EEPROMTyped.write(7, datetime.hours);
    EEPROMTyped.write(8, datetime.minutes);

    lcd_clear();
    return CLOCK;
}

enum state state_factory_reset(){
    while (digitalRead(BTN4_PIN)){}

    struct dt datetime = now();
    datetime.seconds = 0;
    lcd_clear();
    lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
    
    while (digitalRead(BTN4_PIN) == 0){
        if (digitalRead(BTN1_PIN)){
            datetime.hours ++;
            if (datetime.hours > 23) datetime.hours = 0;
            while (digitalRead(BTN1_PIN)) {}

            delay(20);
            lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
        }
        
        if (digitalRead(BTN2_PIN)){
            datetime.minutes ++;
            if (datetime.minutes > 59) datetime.minutes = 0;
            while (digitalRead(BTN2_PIN)){}
        
            delay(20);
            lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
        }

        if (digitalRead(BTN3_PIN)){
            datetime.seconds ++;
            if (datetime.seconds > 59) datetime.seconds = 0;
            while (digitalRead(BTN3_PIN)){}
        
            delay(20);
            lcd_show_time(datetime.hours, datetime.minutes, datetime.seconds);
        }
    }
    while (digitalRead(BTN4_PIN)){}

    lcd_clear();
    lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
    lcd_print_at(1,7, "  ");

    while (digitalRead(BTN4_PIN) == 0){
        if (digitalRead(BTN1_PIN)){
            datetime.day ++;
            if (datetime.day > 31) datetime.day = 1;
            while (digitalRead(BTN1_PIN)) {}

            delay(20);
            lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
            lcd_print_at(1,7, "  ");
        }
        
        if (digitalRead(BTN2_PIN)){
            datetime.month ++;
            if (datetime.month > 12) datetime.month = 1;
            while (digitalRead(BTN2_PIN)){}

            delay(20);
            lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
            lcd_print_at(1,7, "  ");
        }

        if (digitalRead(BTN3_PIN)){
            datetime.year ++;
            if (datetime.year > 99) datetime.year = 0;
            while (digitalRead(BTN3_PIN)){}

            delay(20);
            lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
            lcd_print_at(0,7, "  ");
        }
    }
    while (digitalRead(BTN4_PIN)){}

    lcd_clear();
    lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
    lcd_print_at(0,3, "          ");

    while (digitalRead(BTN4_PIN) == 0){
        if (digitalRead(BTN1_PIN)){
            datetime.dow ++;
            if (datetime.dow > 7) datetime.dow = 1;
            while (digitalRead(BTN1_PIN)) {}

            delay(20);
            lcd_show_date(datetime.day, datetime.month, datetime.year, datetime.dow);
            lcd_print_at(0,3, "          ");
        }
    }
    while (digitalRead(BTN4_PIN)){}
    
    set_datetime(datetime.day, datetime.month, datetime.year, datetime.hours, datetime.minutes, datetime.seconds, datetime.dow);
    write_datetime(datetime.day, datetime.month, datetime.year, datetime.hours, datetime.minutes, datetime.seconds, datetime.dow);
    EEPROMTyped.write(7, NULL);
    EEPROMTyped.write(8, NULL);
    EEPROMTyped.write(9, 0);

    lcd_clear();
    return CLOCK;
}