#include "rtc_wrapper.h"
#include "config.h"
#include "Ds1302.h"

Ds1302 rtc(RTC_RST_PIN, RTC_CLK_PIN, RTC_DAT_PIN);

void clock_init(){
    rtc.init();
}

void set_datetime(const byte day, const byte month, const int year, const byte hours, const byte minutes, const byte seconds, const byte dow){
    Ds1302::DateTime datetime;
    datetime.year = year;
    datetime.month = month;
    datetime.day = day;
    datetime.hour = hours;
    datetime.minute = minutes;
    datetime.second = seconds;
    datetime.dow = dow;

    rtc.setDateTime(&datetime);
}

void set_date(const byte day, const byte month, const int year){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    Ds1302::DateTime datetime;
    datetime.day = day;
    datetime.month = month;
    datetime.year = year;
    datetime.hour = now.hour;
    datetime.minute = now.minute;
    datetime.second = now.second;

    rtc.setDateTime(&datetime);
}

void set_time(const byte hours, const byte minutes, const byte seconds){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    Ds1302::DateTime datetime;
    datetime.day = now.day;
    datetime.month = now.month;
    datetime.year = now.year;
    datetime.hour = hours;
    datetime.minute = minutes;
    datetime.second = seconds;

    rtc.setDateTime(&datetime);
}

byte get_day(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    return now.day;
}

byte get_month(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    return now.month;
}

int get_year(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    return now.year;
}

byte get_hours(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    return now.hour;
}

byte get_minutes(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    return now.minute;
}

byte get_seconds(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    return now.second;

}

struct dt now(){
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    struct dt new_datetime;
    new_datetime.day = now.day;
    new_datetime.month = now.month;
    new_datetime.year = now.year;
    new_datetime.hours = now.hour;
    new_datetime.minutes = now.minute;
    new_datetime.seconds = now.second;
    new_datetime.dow = now.dow;

    return new_datetime;
};