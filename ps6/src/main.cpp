#include <Arduino.h>

#include "rtc_wrapper.h"
#include "sensors.h"
#include "lcd_wrapper.h"
#include "states.h"
#include "config.h"

volatile byte btn_state;

void on_button_press(){
    btn_state = 0;

    if( digitalRead(BTN1_PIN) == HIGH) {
        btn_state |= BTN1_PRESSED;
    }

    if(digitalRead(BTN2_PIN) == HIGH){
        btn_state |= BTN2_PRESSED;
    }

    if(digitalRead(BTN3_PIN) == HIGH){
        btn_state |= BTN3_PRESSED;
    }

    if(digitalRead(BTN4_PIN) == HIGH){
        btn_state |= BTN4_PRESSED;
    }
}

void setup(){
    init();
    Serial.begin(9600);

    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
    pinMode(BTN3_PIN, INPUT);
    pinMode(BTN4_PIN, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), on_button_press, RISING);

    lcd_init();
    lcd_backlight(0);
    clock_init();
    sensors_init();
}


int main() {
    setup();

    enum state state = CLOCK;

    for(;;){
        switch(state){
            case CLOCK:
                state = state_clock();
                break;

            case SHOW_ENV:
                state = state_show_env();
                break;

            case FACTORY_RESET:
                state = state_factory_reset();
                break;

            case SHOW_DATE:
                state = state_show_date();
                break;
            
            case ALARM:
                state = state_alarm();
                break;
        }
    }
}