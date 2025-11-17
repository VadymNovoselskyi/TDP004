#include "given.h"

int WIDTH = 19;
int HEIGHT = 22;

bool operator==(Point const& lhs, Point const& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& operator>>(std::istream& is, Point& rhs)
{
    return is >> rhs.x >> rhs.y;
}

Pacman::Pacman()
    : pos {}, dir {1,0}
{}

Point Pacman::get_position() const
{
    return pos;
}

void Pacman::set_position(Point const& p)
{
    if (p.x > WIDTH or p.x < 0 or p.y > HEIGHT or p.y < 0)
    {
        throw std::runtime_error("position outside valid range");
    }
    pos = p;
}

Point Pacman::get_direction() const
{
    return dir;
}

void Pacman::set_direction(Point const& p)
{
    if (p.x > 1 or p.x < -1 or p.y > 1 or p.y < -1 or abs(p.x + p.y) != 1)
    {
        throw std::runtime_error("direction outside valid range");
    }
    dir = p;
}
