#include "Arduino.h"

#include "lcd_wrapper.h"
#include "rtc_wrapper.h"
#include "sensors.h"
#include "config.h"
#include "EEPROMTyped.h"

#define NOTE_GS6 1661
#define NOTE_DS6 1245
#define NOTE_GS5 831
#define NOTE_AS5 932

/**
 * List of available states.
 */
enum state {
    ALARM,
    CLOCK,
    FACTORY_RESET,
    SHOW_DATE,
    SHOW_ENV
};


/**
 * Individual implementation of states.
 */

enum state state_clock();
enum state state_factory_reset();
enum state state_alarm();
enum state state_show_date();
enum state state_show_env();

// moje funkcie
byte snooze(byte snooze_count);
void alarm(const byte hours, const byte minutes);
void write_datetime(const byte day, const byte month, const int year, const byte hours, const byte minutes, const byte seconds, const byte dow);