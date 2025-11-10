#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>

class Time
{
public:
    Time(int hour = 0, int minute = 0, int second = 0);
    Time(std::string time_string);
    std::string to_string(bool am_format = false) const;

    bool is_am() const;

    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    Time &operator++();   // pre-increment
    Time operator++(int); // post-increment

    bool operator<(Time const &rhs) const;
    bool operator>(Time const &rhs) const;
    bool operator<=(Time const &rhs) const;
    bool operator>=(Time const &rhs) const;
    bool operator==(Time const &rhs) const;
    bool operator!=(Time const &rhs) const;

private:
    int hour{};
    int minute{};
    int second{};

    void inc_second();
};

std::ostream &operator<<(std::ostream &os, Time const &rhs);

#endif