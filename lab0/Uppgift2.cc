#include <iomanip>
#include <iostream>

using namespace std;

float calc_moms(float price, float moms)
{
    return price * moms / 100;
}

float calc_moms_price(float price, float moms)
{
    return price + calc_moms(price, moms);
}

int main()
{
    float first_price{};
    float last_price{};
    float step{};
    float moms{};

    cout << "INMATNINGSDEL" << endl;
    cout << "============" << endl;

    cout << "Mata in första pris: ";
    cin >> first_price;

    while (first_price < 0)
    {
        cout << "FEL: Första pris måste vara minst 0 (noll) kronor" << endl;
        cout << "Mata in första pris: ";
        cin >> first_price;
    }

    cout << "Mata in sista pris: ";
    cin >> last_price;

    while (last_price < 0 || last_price < first_price)
    {
        cout << "FEL: Sista pris måste vara minst 0 (noll) kronor och större än första priset" << endl;
        cout << "Mata in sista pris: ";
        cin >> last_price;
    }

    cout << "Mata in steglängd: ";
    cin >> step;

    while (step < 0.01)
    {
        cout << "FEL: Steglängd måste vara minst 0.01" << endl;
        cout << "Mata in steglängd: ";
        cin >> step;
    }

    cout << "Mata in momsprocent: ";
    cin >> moms;

    while (moms < 0 || moms > 100)
    {
        cout << "FEL: Momsprocenten behöver vara i intervallet 0 (noll) till 100 (hundra)" << endl;
        cout << "Mata in momsprocent: ";
        cin >> moms;
    }

    cout << "MOMSTABELLEN" << endl;
    cout << "============" << endl;

    cout << setfill(' ') << right << setw(12) << "Pris";
    cout << setfill(' ') << right << setw(12) << "Moms";
    cout << setfill(' ') << right << setw(20) << "Pris med moms" << endl;

    cout << setfill('-') << right << setw(44) << "" << endl;

    float price = first_price;

    while (price <= last_price)
    {
        float moms_amount = calc_moms(price, moms);
        float moms_price = calc_moms_price(price, moms);

        cout << setfill(' ') << right << setw(12) << fixed << setprecision(2) << price;
        cout << setfill(' ') << right << setw(12) << fixed << setprecision(2) << moms_amount;
        cout << setfill(' ') << right << setw(20) << fixed << setprecision(2) << moms_price << endl;
        price += step;
    }

    return 0;
}
