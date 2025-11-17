#include "ghost.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

/*
  Ledning och Tips:

  - Modifiera stukturen till en header-fil och en implementationsfil
  - Utöka 'run()' och 'draw_map()' med övrig funktionalitet.
  - Lägg alla spöken i en lämplig behållare som en datamedlem.
  - Bryt ut stora kodblock till egna funktioner.
  - Använd hjälpfunktioner för att undvika duplicering av kod.
  - Tänk på att varje funktion inte borde vara längre än 25 rader.
 */

class Ghost_Tester
{

public:
    Ghost_Tester()
        : pacman{}, ghosts{}, angry_ghosts{}, mode{"chase"}
    {
    }

    void run()
    {
        AngryGhost* blinky = new Blinky(this->pacman, {6, 6}); 
        angry_ghosts.push_back(blinky);
        ghosts.push_back(blinky);
        ghosts.push_back(new Pinky(this->pacman, {4, 8}));
        ghosts.push_back(new Clyde(this->pacman, {10, 4}));

        while (true)
        {
            this->draw_map();

            cout << "> ";
            string line{};
            getline(cin, line);
            istringstream iss{line};

            string command = this->get_command(iss);

            if (command == "pos")
            {
                Point new_pos{this->get_point(iss)};
                pacman.set_position(new_pos);
            }
            else if (command == "dir")
            {
                Point new_dir{this->get_point(iss)};
                this->pacman.set_direction(new_dir);
            }
            else if (command == "chase" || command == "scatter")
            {
                mode = command;
            }
            else if (command == "quit")
            {
                break;
            }
            else if (command == "anger")
            {
                for (AngryGhost* angry_ghost : angry_ghosts)
                {
                    angry_ghost->set_angry(true);
                }
            }
            else
            {
                for (Ghost *ghost : ghosts)
                {
                    if (ghost->get_color() != command)
                    {
                        continue;
                    }

                    Point new_pos{this->get_point(iss)};
                    ghost->set_position(new_pos);
                    break;
                }
                cout << "Command: \"" << command << "\" is invalid command" << endl;
            }
        }
    }

private:
    string get_command(istringstream &iss)
    {
        string command{};
        iss >> command;
        return command;
    }

    Point get_point(istringstream &iss)
    {
        Point new_point{};
        iss >> new_point;
        return new_point;
    }

    /*
      En hjälpfunktion som avgör vilka två tecken som ska ritas ut för en given position på
      spelplanen.
     */
    string to_draw(Point const &curr_pos)
    {
        string to_draw{"  "};

        for (Ghost *ghost : ghosts)
        {
            if (ghost->get_position() == curr_pos)
            {
                to_draw[0] = toupper((ghost->get_color())[0]);
            }

            else if (mode == "chase" && ghost->get_chase_point() == curr_pos)
            {
                to_draw[0] = tolower((ghost->get_color())[0]);
            }
            else if (mode == "scatter" && ghost->get_scatter_point() == curr_pos)
            {
                to_draw[0] = tolower((ghost->get_color())[0]);
            }
        }

        if (pacman.get_position() == curr_pos)
        {
            to_draw[1] = '@';
        }

        return to_draw;
    }

    /*
      En hjälpfunktion för att rita ut spelplanen för testprogrammet.

      Itererar över varje rad och column i kartan. Index för raderna är flippade för att placera
      y = 0 längst ned.

      Varje punkt i kartan ritas som två tecken eftersom ett tecken i terminalen är ca dubbelt så
      högt som det är brett.
    */
    void draw_map()
    {
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";

        for (int y{HEIGHT - 1}; y >= 0; --y)
        {
            cout << "|";
            for (int x{}; x < WIDTH; ++x)
            {
                cout << to_draw(Point{x, y});
            }
            cout << "|\n";
        }

        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+" << endl;
    }

    Pacman pacman;
    vector<Ghost *> ghosts;
    vector<AngryGhost *> angry_ghosts;

    string mode;
};

int main()
{
    Ghost_Tester gt{};
    gt.run();
    return 0;
}
