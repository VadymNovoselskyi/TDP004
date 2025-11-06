#include <iostream>
#include <string>
#include <stdexcept>
#include "Time.h"

using namespace std;

bool check_time_validity(int hour, int minute, int second)
{
    if (hour < 0 || hour > 23)
    {
        throw logic_error("Invalid hour param, it should be between 0 and 23");
    }
    if (minute < 0 || minute > 59)
    {
        throw logic_error("Invalid minute param, it should be between 0 and 59");
    }
    if (second < 0 || second > 59)
    {
        throw logic_error("Invalid second param, it should be between 0 and 59");
    }
    return true;
}

Time::Time(int h, int m, int s)
    : hour{h}, minute{m}, second{s}
{
    check_time_validity(h, m, s);
}

Time::Time(string t_s)
{
    string string_hours = {};
    string string_minutes = {};
    string string_seconds = {};

    try
    {
        string_hours = t_s.substr(0, 2);
        string_minutes = t_s.substr(3, 2);
        string_seconds = t_s.substr(6, 2);
    }
    catch (const exception &e)
    {
        throw logic_error("Invalid time string format. It should be in this format: 'hh:mm:ss'");
    }

    int parsed_hours = {};
    int parsed_minutes = {};
    int parsed_seconds = {};

    try
    {
        parsed_hours = stoi(string_hours);
        parsed_minutes = stoi(string_minutes);
        parsed_seconds = stoi(string_seconds);
    }
    catch (const exception &e)
    {
        throw logic_error("Invalid arguments, couldn't parse the integers");
    }
    check_time_validity(parsed_hours, parsed_minutes, parsed_seconds);

    hour = parsed_hours;
    minute = parsed_minutes;
    second = parsed_seconds;
}

string Time::to_string(bool am_format) const
{
    string string_hour = {};
    if (am_format)
    {
        if (hour == 0)
        {
            string_hour = "12";
        }

        else if (hour > 12)
        {
            string_hour = std::to_string(hour - 12);
        }

        else
        {
            string_hour = std::to_string(hour);
        }
    }
    else
    {
        string_hour = std::to_string(hour);
    }

    string string_minute = std::to_string(minute);
    string string_second = std::to_string(second);

    if (string_hour.length() == 1)
    {
        string_hour = "0" + string_hour;
    }
    if (string_minute.length() == 1)
    {
        string_minute = "0" + string_minute;
    }
    if (string_second.length() == 1)
    {
        string_second = "0" + string_second;
    }

    string time_string = string_hour + ":" + string_minute + ":" + string_second;
    if (am_format)
    {
        return time_string + (is_am() ? "am" : "pm");
    }
    else
    {
        return time_string;
    }
}

bool Time::is_am() const
{
    return hour < 12;
}

int Time::get_hour() const
{
    return hour;
}
int Time::get_minute() const
{
    return minute;
}
int Time::get_second() const
{
    return second;
}

void Time::inc_second()
{
    if (second < 59)
    {
        second++;
        return;
    }
    second = 0;

    if (minute < 59)
    {
        minute++;
        return;
    }
    minute = 0;

    if (hour < 23)
    {
        hour++;
        return;
    }
    hour = 0;
}

// pre-increment
Time &Time::operator++()
{
    inc_second();
    return *this;
}

// post-increment
Time Time::operator++(int)
{
    Time time_before = *this;
    inc_second();
    return time_before;
}

bool Time::operator<(Time const &rhs) const
{
    // compare hours
    if (this->hour < rhs.hour)
    {
        return true;
    }
    else if (this->hour > rhs.hour)
    {
        return false;
    }

    // compare minuites
    else if (this->minute < rhs.minute)
    {
        return true;
    }
    else if (this->minute > rhs.minute)
    {
        return false;
    }

    // compare seconds
    else if (this->second < rhs.second)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Time::operator>(Time const &rhs) const
{
    return !(*this < rhs && *this == rhs);
}

bool Time::operator<=(Time const &rhs) const
{
    return (*this < rhs || *this == rhs);
}

bool Time::operator>=(Time const &rhs) const
{
    return (*this > rhs || *this == rhs);
}

bool Time::operator==(Time const &rhs) const
{
    return (
        (this->hour == rhs.hour) &&
        (this->minute == rhs.minute) &&
        (this->second == rhs.second));
}

bool Time::operator!=(Time const &rhs) const
{
    return !(*this == rhs);
}

ostream &operator<<(ostream &os, Time const &rhs)
{
    return os << rhs.to_string();
}
