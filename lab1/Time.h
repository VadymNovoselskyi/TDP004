// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs

#include <string>

class Time
{
public:
    Time(int hour = 0, int minute = 0, int second = 0);
    Time(std::string time_string);
    std::string to_string();
    std::string to_string(bool);

    bool is_am();

    int get_hour();
    int get_minute();
    int get_second();

    Time operator++(int);
    Time &operator++();

    Time operator<(Time const &rhs);
    Time operator>(Time const &rhs);
    Time operator<=(Time const &rhs);   
    Time operator>=(Time const& rhs); 
    Time operator==(Time const& rhs); 
    Time operator!=(Time const& rhs); 

private:
    int hour{};
    int minute{};
    int second{};
};