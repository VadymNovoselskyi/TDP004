#ifndef GHOST_H
#define GHOST_H

#include <string>
#include "given.h"

class Ghost
{
public:
    Ghost(Pacman &pacman, Point pos);
    virtual ~Ghost() = default;

    virtual Point get_chase_point() const = 0;
    virtual Point get_scatter_point() const = 0;

    virtual std::string get_color() const = 0;

    void set_position(Point const &pos);
    Point get_position() const;

protected:
    Pacman &pacman;
    Point pos{};
};

class AngryGhost : public Ghost
{
public:
    AngryGhost(Pacman &pacman, Point pos);
    virtual ~AngryGhost() = default;

    bool is_angry() const;
    void set_angry(bool angry);

protected:
    bool angry;
};

class Blinky : public AngryGhost
{
public:
    Blinky(Pacman &pacman, Point pos);

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

    std::string get_color() const override;
};

class Pinky : public Ghost
{
public:
    Pinky(Pacman &pacman, Point pos);

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

    std::string get_color() const override;
};

class Clyde : public Ghost
{
public:
    Clyde(Pacman &pacman, Point pos);

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

    std::string get_color() const override;
};

#endif