#include <iostream>
#include <iomanip> 

using namespace std;

int main()
{
    char charachter {};
    string my_string {};
    int integer {};
    double my_float {};

    // cout << "Skriv in ett heltal: "; 
    // cin >> integer;
    // cout << "Du skrev in talet: " << integer << endl; 

    // cout << "Skriv in fem heltal: ";
    // getline(cin, my_string, ' ');
    // cout << "Du skrev in talen: ";
    // cout << my_string << ", ";
    // getline(cin, my_string, ' ');
    // cout << my_string << ", ";
    // getline(cin, my_string, ' ');
    // cout << my_string << ", ";
    // getline(cin, my_string, ' ');
    // cout << my_string << ", ";
    // getline(cin, my_string);
    // cout << my_string << endl;

    // cout << "Skriv in ett flyttal: ";
    // cin >> my_float;
    // cout << fixed << setprecision(3) << my_float << endl;

    // cout << "Srkiv in ett heltal och ett flyttal: ";
    // cin >> integer >> my_float;
    // cout << "Du skrev in heltalet: " << setfill(' ') << right << setw(15) << integer << endl;
    // cout << "Du skrev in flyttalet: " << setfill(' ') << right << setw(14) << my_float << endl;

    // cout << "Srkiv in ett flyttal och ett heltal: ";
    // cin >> my_float >> integer;
    // cout << "Du skrev in heltalet:" << setfill('-') << right << setw(15) << integer << endl;
    // cout << "Du skrev in flyttalet:" << setfill('-') << right << setw(14) << my_float << endl;
    
    // cout << "Skriv in ett tecken: "; 
    // cin >> charachter;
    // cout << "Du skrev in tecknet: " << charachter << endl; 

    // cout << "Skriv in en sträng: "; 
    // cin >> my_string;
    // cout << "Strängen '" << my_string << "' har " << my_string.length() << " tecken." << endl; 

    cout << "Skriv in ett heltal och en sträng: "; 
    cin >> integer >> my_string;
    cout << "Du skrev in talet: |" << integer << "| och strängen |" << my_string << "|" << endl; 
    return 0;
}