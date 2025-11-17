#ifndef GIVEN_H
#define GIVEN_H

/*
  I denna fil finns ett utval av kod från det dina kollegor skrivit till ert pacman-projekt. Det är
  precis det som du behöver för att skriva din del av koden.

  Tips: Du får utöka denna fil med saker som du behöver för att ditt program ska kompilera. Det är
  även okej att utöka Point med fler operatorer om det skulle behövas.
 */

#include <stdexcept>
#include <iostream>

/*
  Globala variabler för storlek på spelplanen.
 */
extern int WIDTH;
extern int HEIGHT;

extern int CLYDE_TARGET_RANGE;

/*
  Ett aggregat som använd för att representera punkter och riktninar på spelplanen.
  Aggregatet har också hjälpsamma operatorer som kan underlätta din implementation.

 */
struct Point
{
  int x;
  int y;
};
bool operator==(Point const &lhs, Point const &rhs);
std::istream &operator>>(std::istream &is, Point &rhs);
std::ostream &operator<<(std::ostream &os, Point const &rhs);

/*
  En klass för att representera spelarfiguren. Detta är en nedskalad version jämfört med det som
  kollegan skrev till spelet. Notera att din kod inte behöver ändras om man skulle gå från denna
  implementaion till den faktiska implementationen.
 */
class Pacman
{
public:
  Pacman();

  Point get_position() const;
  void set_position(Point const &p);

  Point get_direction() const;
  void set_direction(Point const &p);

private:
  Point pos{};
  Point dir{};
};

#endif
