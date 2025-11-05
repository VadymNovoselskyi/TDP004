// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h

#include "Time.h"
#include <string>
#include <stdexcept>

using namespace std;

Time::Time(int h, int m, int s)
    : hour{h}, minute{m}, second{s}
{
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

    hour = parsed_hours;
    minute = parsed_minutes;
    second = parsed_seconds;
}

string Time::to_string()
{
    string string_hour = to_string(hour);
    string string_minute = to_string(minute);
    string string_second = to_string(second);

    string time_string = string_hour + ":" + string_minute + ":" + string_second;
    return time_string;
}

string Time::to_string(bool)
{
    string string_hour = {};

    if (hour == 0)
    {
        string_hour = "12";
    }

    else if (hour > 12)
    {
        string_hour = to_string(hour - 12);
    }

    else
    {
        string_hour = to_string(hour);
    }

    string string_minute = to_string(minute);
    string string_second = to_string(second);

    string time_string = string_hour + ":" + string_minute + ":" + string_second;
    return time_string + (is_am ? "am" : "pm");
}

bool Time::is_am()
{
    return hour < 12;
}

int Time::get_hour()
{
    return hour;
}
int Time::get_minute()
{
    return minute;
}
int Time::get_second()
{
    return second;
}



int main()
{
    return 0;
}