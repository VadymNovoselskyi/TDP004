#include <iomanip>
#include <iostream>
#include <limits>
#include <ios>

using namespace std;

float calc_moms(float price, float moms) { return price * moms / 100; }

float calc_moms_price(float price, float moms) {
  return price + calc_moms(price, moms);
}

int main() {
  long int max_size = numeric_limits<streamsize>::max();
  float first_price{};
  float last_price{};
  float step{};
  float moms{};

  cout << "INMATNINGSDEL" << endl;
  cout << "============" << endl;

  do {
    cout << "Mata in första pris: ";
    cin >> first_price;
    if (first_price < 0) {
      cout << "FEL: Första pris måste vara minst 0 (noll) kronor" << endl;
    }

    cin.ignore(max_size, '\n');
  } while (first_price < 0);

  do {
    cout << "Mata in sista pris: ";
    cin >> last_price;
    if (last_price < 0 || last_price < first_price) {
      cout << "FEL: Sista pris måste vara minst 0 (noll) kronor och större än "
              "första priset"
           << endl;
    }

    cin.ignore(max_size, '\n');
  } while (last_price < 0 || last_price < first_price);

  do {
    cout << "Mata in steglängd: ";
    cin >> step;
    if (step < 0.01f) {
      cout << "FEL: Steglängd måste vara minst 0.01" << endl;
    }

    cin.ignore(max_size, '\n');
  } while (step < 0.01f);

  do {
    cout << "Mata in momsprocent: ";
    cin >> moms;
    if (moms < 0 || moms > 100) {
      cout << "FEL: Momsprocenten behöver vara i intervallet 0 (noll) till 100 "
              "(hundra)"
           << endl;
    }

    cin.ignore(max_size, '\n');
  } while (moms < 0 || moms > 100);

  int first_price_cents{static_cast<int>(first_price * 100)};
  int last_price_cents{static_cast<int>(last_price * 100)};
  int step_cents{static_cast<int>(step * 100)};

  cout << endl;
  cout << "MOMSTABELLEN" << endl;
  cout << "============" << endl;

  cout << setw(12) << "Pris";
  cout << setw(12) << "Moms";
  cout << setw(20) << "Pris med moms" << endl;

  cout << setfill('-') << setw(44) << "" << endl;

  int step_amount = ((last_price_cents - first_price_cents) / step_cents) + 1;
  int price_cents = first_price_cents;

  cout << setfill(' ') << fixed << setprecision(2);
  for (int i = 0; i < step_amount; i++) {
    float moms_amount = calc_moms(price_cents / 100.0f, moms);
    float moms_price = calc_moms_price(price_cents / 100.0f, moms);

    cout << setw(12) << price_cents / 100.0f;
    cout << setw(12) << moms_amount;
    cout << setw(20) << moms_price << endl;
    price_cents += step_cents;
  }

  return 0;
}