#include "inventory.h"

int isValidDay(const char* day) {
    const char* validDays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(day, validDays[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int daysBetween(struct tm *start, struct tm *end) {
    time_t start_time = mktime(start);
    time_t end_time = mktime(end);
    return (int)difftime(end_time, start_time) / (60 * 60 * 24);
}

int isDayOfWeek(const char* day, struct tm *date) {
    char currentDay[10];
    strftime(currentDay, sizeof(currentDay), "%A", date);
    return strcmp(currentDay, day) == 0;
}

int custom_strptime(const char *date_str, struct tm *tm) {
    if (sscanf(date_str, "%d-%d-%d", &tm->tm_year, &tm->tm_mon, &tm->tm_mday) != 3) {
        return 0; // Parsing failed
    }
    tm->tm_year -= 1900; // Adjust year
    tm->tm_mon -= 1;     // Adjust month
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    tm->tm_isdst = -1;   // Not set by strptime
    return 1; // Parsing successful
}