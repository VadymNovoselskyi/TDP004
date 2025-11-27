#ifndef GHOST_H
#define GHOST_H

#include <string>

#include "given.h"

class Ghost {
  public:
    Ghost(Pacman const &pacman, Point const &pos);
    virtual ~Ghost() = default;

    virtual Point get_chase_point() const = 0;
    virtual Point get_scatter_point() const = 0;

    virtual std::string get_color() const = 0;

    void set_position(Point const &pos);
    Point get_position() const;

  protected:
    Pacman const &pacman;
    Point pos;

  private:
    void validate_position(Point const &p) const;
};

class Blinky : public Ghost {
  public:
    Blinky(Pacman const &pacman, Point const &pos);

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

    std::string get_color() const override;

    bool is_angry() const;
    void set_angry(bool angry);

  protected:
    bool angry;
};

class Pinky : public Ghost {
  public:
    Pinky(Pacman const &pacman, Point const &pos);

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

    std::string get_color() const override;
};

class Clyde : public Ghost {
  public:
    Clyde(Pacman const &pacman, Point const &pos, int target_range = 10);

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

    std::string get_color() const override;

  private:
    int target_range;
};

#endif