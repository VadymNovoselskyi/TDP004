#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Komplettering: Inkludera alla de biblotek ni använder.

// Kommentar: Utskrifterna matchar inte körexemplet exakt. Nära nog att
// jag släpper igenom det men håll i åtanke att det kan leda till
// komplettering så det är viktigt att vara noga

int main()
{
     char character{};
     string my_string{};
     int integer{};
     double my_float{};

     cout << "Skriv in ett heltal: ";
     cin >> integer;
     cout << "Du skrev in talet: " << integer << endl;
     cout << endl;
     cin.ignore(999999, '\n');
     

     cout << "Skriv in fem heltal: ";
     cin >> integer;
     cout << "Du skrev in talen: ";
     cout << integer << ", ";
     cin >> integer;
     cout << integer << ", ";
     cin >> integer;
     cout << integer << ", ";
     cin >> integer;
     cout << integer << ", ";
     cin >> integer;
     cout << integer << endl;
     cout << endl;
     cin.ignore(9999999999, '\n');
     

     cout << "Skriv in ett flyttal: ";
     cin >> my_float;
     cout << "Du skrev in flyttalet: " << fixed << setprecision(3) << my_float << endl;
     cout << endl;
     cin.ignore(9999999999,
                '\n');
                

     cout << "Srkiv in ett heltal och ett flyttal: ";
     cin >> integer >> my_float;
     cout << "Du skrev in heltalet:" << setw(10)
          << integer << endl;
     cout << "Du skrev in flyttalet:" << setw(9)
          << my_float << endl;
     cout << endl;
          cin.ignore(9999999999,
                '\n');
                

     cout << "Srkiv in ett flyttal och ett heltal: ";
     cin >> my_float >> integer;
     cout << "Du skrev in heltalet:" << setfill('-') << setw(10) << integer << endl;
     cout << "Du skrev in flyttalet:" << setw(9) << my_float << endl;
     cout << endl;
     cin.ignore(9999999999, '\n');
     

     cout << "Skriv in ett tecken: ";
     cin >> character;
     cout << "Du skrev in tecknet: " << character << endl;
     cout << endl;
     cin.ignore(9999999999,
                '\n');
                

     cout << "Skriv in en sträng: ";
     cin >> my_string;
     cout << "Strängen '" << my_string << "' har " << my_string.length()
          << " tecken." << endl;
     cout << endl;
          cin.ignore(9999999999,
                '\n');
                

     cout << "Skriv in ett heltal och en sträng: ";
     cin >> integer >> my_string;
     cout << "Du skrev in talet: |" << integer << "| och strängen |" << my_string
          << "|." << endl;
     cout << endl;
          cin.ignore(9999999999,
                '\n');
                

     cout << "Skriv in en sträng och ett flyttal: ";
     cin >> my_string >> my_float;
     cout << "Du skrev in \"" << my_float << "\" och \"" << my_string << "\"." << endl;
     cout << endl;
     cin.ignore(9999999999,
                '\n');
                

     cout << "Skriv in en hel rad med text: ";
     getline(cin, my_string);
     cout << "Du skrev in textraden: '" << my_string << "'" << endl;
     cout << endl;

     cout << "Skriv in en textrad som slutar med en negativt heltal: ";
     getline(cin, my_string, '-');
     cin >> integer;
     cout << "Du skrev textraden: '" << my_string << "' och heltalet '-" << integer
          << "'" << endl;
     return 0;
}
