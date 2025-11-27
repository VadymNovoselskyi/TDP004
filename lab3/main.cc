#include <iomanip>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ghost.h"

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

class Ghost_Tester {
  public:
    Ghost_Tester() : pacman{}, ghosts{}, mode{"chase"} {
    }

    void run() {
        ghosts.push_back(new Blinky(pacman, {6, 6}));
        ghosts.push_back(new Pinky(pacman, {4, 8}));
        ghosts.push_back(new Clyde(pacman, {10, 4}));

        while (true) {
            draw_map();

            cout << "> ";
            string line{};
            getline(cin, line);
            istringstream iss{line};

            string command = get_command(iss);

            if (command == "pos") {
                handle_pos_command(iss);
            } else if (command == "dir") {
                handle_dir_command(iss);
            } else if (command == "chase" || command == "scatter") {
                handle_mode_command(command);
            } else if (command == "quit") {
                handle_quit_command();
                break;
            } else if (command == "anger") {
                handle_anger_command();
            } else {
                bool valid_command = false;
                valid_command = handle_ghost_command(command, iss);
                if (!valid_command) {
                    cout << "Command: \"" << command << "\" is invalid command" << endl;
                }
            }
        }
    }

  private:
    void handle_pos_command(istringstream &iss) {
        Point new_pos{get_point(iss)};
        try {
            pacman.set_position(new_pos);
        } catch (runtime_error const &error) {
            cerr << "Couldn't move the pacman: " << error.what() << endl;
        }
    }

    void handle_dir_command(istringstream &iss) {
        Point new_dir{get_point(iss)};
        try {
            pacman.set_direction(new_dir);
        } catch (runtime_error const &error) {
            cerr << "Couldn't change the direction: " << error.what() << endl;
        }
    }

    void handle_mode_command(string const &command) {
        mode = command;
    }

    void handle_quit_command() {
        for (Ghost *ghost : ghosts) {
            delete ghost;
        }
    }

    void handle_anger_command() {
        for (Ghost *ghost : ghosts) {
            auto blinky = dynamic_cast<Blinky *>(ghost);
            if (blinky != nullptr) {
                blinky->set_angry(true);
            }
        }
    }

    bool handle_ghost_command(string const &command, istringstream &iss) {
        bool valid_command = false;
        for (Ghost *ghost : ghosts) {
            if (ghost->get_color() != command) {
                continue;
            }

            Point new_pos{get_point(iss)};
            try {
                ghost->set_position(new_pos);
            } catch (runtime_error const &error) {
                cerr << "Couldn't move the ghost: " << error.what() << endl;
                return false;
            }
            valid_command = true;
            break;
        }
        return valid_command;
    }

    string get_command(istringstream &iss) {
        string command{};
        iss >> command;
        return command;
    }

    Point get_point(istringstream &iss) {
        Point new_point{};
        iss >> new_point;
        return new_point;
    }

    /*
      En hjälpfunktion som avgör vilka två tecken som ska ritas ut för en given position på
      spelplanen.
     */
    string to_draw(Point const &curr_pos) {
        string to_draw{"  "};

        for (Ghost *ghost : ghosts) {
            if (ghost->get_position() == curr_pos) {
                to_draw[0] = toupper((ghost->get_color())[0]);
            }

            else if (mode == "chase" && ghost->get_chase_point() == curr_pos) {
                to_draw[0] = tolower((ghost->get_color())[0]);
            } else if (mode == "scatter" && ghost->get_scatter_point() == curr_pos) {
                to_draw[0] = tolower((ghost->get_color())[0]);
            }
        }

        if (pacman.get_position() == curr_pos) {
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
    void draw_map() {
        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+\n";

        for (int y{HEIGHT - 1}; y >= 0; --y) {
            cout << "|";
            for (int x{}; x < WIDTH; ++x) {
                cout << to_draw(Point{x, y});
            }
            cout << "|\n";
        }

        cout << "+" << setfill('-') << setw(WIDTH * 2) << "-" << "+" << endl;
    }

    Pacman pacman;
    vector<Ghost *> ghosts;

    string mode;
};

int main() {
    Ghost_Tester gt{};
    gt.run();
    return 0;
}
