#include <cmath>
#include "ghost.h"


using namespace std;

// Base ghost
Ghost::Ghost(Pacman const &pacman, Point const &pos) : pacman{pacman}, pos{pos}
{
    if (pos.x > WIDTH or pos.x < 0 or pos.y > HEIGHT or pos.y < 0)
    {
        throw std::runtime_error("position outside valid range");
    }
}

void Ghost::set_position(Point const &pos)
{
    if (pos.x > WIDTH or pos.x < 0 or pos.y > HEIGHT or pos.y < 0)
    {
        throw std::runtime_error("position outside valid range");
    }
    this->pos = pos;
}

Point Ghost::get_position() const
{
    return this->pos;
}

// AngryGhost:
AngryGhost::AngryGhost(Pacman const &pacman, Point const &pos) : Ghost(pacman, pos), angry{false}
{
}


bool AngryGhost::is_angry() const
{
    return this->angry;
}

void AngryGhost::set_angry(bool angry)
{
    this->angry = angry;
}

// Blinky:
Blinky::Blinky(Pacman const &pacman, Point const &pos) : AngryGhost(pacman, pos)
{
}

Point Blinky::get_chase_point() const
{
    return this->pacman.get_position();
}

Point Blinky::get_scatter_point() const
{
    if (this->is_angry())
    {
        return this->get_chase_point();
    }

    return Point{WIDTH - 1, HEIGHT - 1};
}

string Blinky::get_color() const
{
    return "red";
}

// Pinky
Pinky::Pinky(Pacman const &pacman, Point const &pos) : Ghost(pacman, pos)
{
}

Point Pinky::get_chase_point() const
{
    Point player_pos{this->pacman.get_position()};
    Point player_dir{this->pacman.get_direction()};
    return {player_pos.x + player_dir.x * 2, player_pos.y + player_dir.y * 2};
}

Point Pinky::get_scatter_point() const
{
    return Point{0, HEIGHT - 1};
}

string Pinky::get_color() const
{
    return "pink";
}

// Clyde
Clyde::Clyde(Pacman const &pacman, Point const &pos, int target_range) : Ghost(pacman, pos), target_range{target_range}
{
}

Point Clyde::get_chase_point() const
{
    Point player_pos{this->pacman.get_position()};
    int dist_to_player = abs(player_pos.x - pos.x) + abs(player_pos.y - pos.y);
    if (dist_to_player > this->target_range)
    {
        return player_pos;
    }

    return {0, 0};
}

Point Clyde::get_scatter_point() const
{

    return Point{0, 0};
}

string Clyde::get_color() const
{
    return "orange";
}