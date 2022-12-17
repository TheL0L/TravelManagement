#include "TravelDetails.h"
#include <iostream>
using namespace std;


void TravelDetails::initial()
{
    pool = gym = sports = salon = 0;
}

void TravelDetails::t_input(int cd)
{
    initial();
    TravelCode = cd;
    int i = 1, opt;
    system("cls");
    do
    {
        system("cls");
        cout << endl;
        cout << "\nTRAVEL DETAILS\n";
        cout << "~~~~~~~~~~~~~~~~~";
        cout << "\nPlease enter the following details for your journey:";
        cout << "\n*Note:Options marked with '*' are compulsory.\tPlease do select them.";
        cout << "\n*1.Boarding and Destination\n*2.Date of Departure\n*3.Class\n4.Swimming Pool\n5.Gymnasuim\n6.Sports\n7.Salon\n8.Spa\n9.Back\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            system("cls");
            cout << "\nSelect Boarding point:\n1.Mumbai\n2.Cochin\n3.Chennai";
            cin >> BoardingPoint;
            cout << "\n*** Select Destination ***\n";
            cout << "1.New York\t\t6.Dubai\t\t\t11.Antananariv";
            cout << "\n2.Miami\t\t7.Lisbon\t\t12.Cairo";
            cout << "\n3.Rio De Janeiro\t8.London\t\t13.Perth";
            cout << "\n4.Colombo\t\t9.Copenhagen\t\t14.Sydney";
            cout << "\n5.Hong Kong\t\t10.Cape Town\t\t15.Wellington\n";
            cin >> DisembarkingPoint;
            break;
        case 2:
            system("cls");
            cout << "\n\nEnter your preferred date(DD MM YYYY) of departure: ";
            cin >> day >> month >> year;
            break;
        case 3:
            system("cls");
            cout << "\n\nEnter The Choice OF Class\n1.First Class\n2.Business Class\n3.Economy Class\n";
            cin >> Class;
            break;
        case 4:
            system("cls");
            cout << "\n\nWould You Like To Avail The Facility Of A Swimming Pool\n0.No\n1.Yes\n";
            cin >> pool;
            break;
        case 5:
            system("cls");
            cout << "\n\nWould You Like To Avail The Facility Of A Gymnasium\n0.No\n1.Yes\n";
            cin >> gym;
            break;
        case 6:
            system("cls");
            cout << "\n\nWould You Like To Avail The Sports Facilities Offered\n0.No\n1.Yes\n";
            cin >> sports;
            break;
        case 7:
            system("cls");
            cout << "\n\nWould You Like To Avail The Facility Of Beauty Salon\n0.No\n1.Yes\n";
            cin >> salon;
            break;
        case 8:
            system("cls");
            cout << "\n\nWould You Like To Avail The Facility Of Spa\n0.No\n1.Yes\n";
            cin >> spa;
            break;
        case 9:
            i = 0;
            break;
        }
    } while (i == 1);
}

void TravelDetails::t_output()
{
        system("cls");
        cout << "\n\n##############TRAVEL DETAILS##############";
        cout << "\nBoarding Point: ";
        boardpt(BoardingPoint);
        cout << "\nDestination: ";
        dest(DisembarkingPoint);
        cout << "\nDate of departure: ";
        cout << day << "/" << month << "/" << year;
        cout << "\nClass: ";
        switch (Class)
        {
        case 1:
            cout << "First Class";
            break;
        case 2:
            cout << "Business Class";
            break;
        case 3:
            cout << "Economy Clss";
            break;
        }
        cout << "\n\n\n\tFacilities availed for are:";
        if (pool == 1)
            cout << "\nSwimming Pool";
        if (gym == 1)
            cout << "\n";
        if (sports == 1)
            cout << "\n";
        if (spa == 1)
            cout << "\nSpa";
        if (salon == 1)
            cout << "\nBeauty Salon";
    }

void TravelDetails::compute()
{
    /*
        gttl - total travel expenses
        hr - days reserved (in hours, per location) ~ usage of hours is redundant
        dcst - ticket price (per location)
        cls - flight class base price
        cabn - ? ~ never used
        swpool, gm, spfts, slon, sp - base prices for expenses (per location)
        ttr - ? ~ never used
    */
    long int gttl = 0, hr, dcst, cls, cabn, swpool = 5000, gm = 2000, spfts = 7500, slon = 6000, sp = 20000, ttr = 500;
    switch (DisembarkingPoint)  // assign prices for activities and ticket per destination
    {
    case 1:;
    case 2:;
    case 3:
        hr = 30 * 24;
        dcst = 250000;
        break;
    case 4:;
    case 5:;
    case 6:
        hr = 7 * 24;
        dcst = 75000;
        break;
    case 7:;
    case 8:;
    case 9:
        hr = 24 * 24;
        dcst = 130000;
        break;
    case 10:;
    case 11:;
    case 12:
        hr = 15 * 24;
        dcst = 100000;
        break;
    case 13:;
    case 14:;
    case 15:
        hr = 12 * 24;
        dcst = 120000;
        break;
    }
    switch (Class)
    {
    case 1:
        cls = 1500;
        break;
    case 2:
        cls = 7500;
        break;
    case 3:
        cls = 5000;
    }
    system("cls");
    cout << "\n\n:::::::::::::::::::::: BILL ::::::::::::::::::::::::::";
    cout << "\nBoarding point: ";
    boardpt(BoardingPoint);
    cout << "\nDestination: ";
    dest(DisembarkingPoint);
    cout << "\nDate of Departure: ";
    cout << day << "/" << month << "/" << year;
    hr = hr / 24; // to calculate date of arrival (referring to return)
    day = day + hr;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day > 31)
        {
            month = month + 1;
            day = day % 31;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
        {
            month = month + 1;
            day = day % 30;
        }
    }
    if (month == 2)
    {
        if (day > 28)
        {
            month = month + 1;
            day = day % 28;
        }
    }
    if (month == 13)
    {
        month = 1;
        year++;
    }
    cout << "\nDate of Arrival: ";
    cout << day << "/" << month << "/" << year;
    cout << "\n\nSubject\t\tCost(for 1)\tNo of ppl\tTotal";
    cout << "\n\nTravel\t\t" << dcst << "\t\t   " << num1 << "\t\t" << num1 * dcst;
    gttl += num1 * dcst;  // cost of tickets for all members
    cout << "\nClass\t\t" << Class << "\t\t   " << num1 << "\t\t" << Class * num1;
    gttl += Class * num1;  // cost of class status for all members
    // cost of extra expenses
    if (pool == 1)
    {
        cout << "\nSwimming Pool\t" << swpool << "\t\t   " << num1 << "\t\t" << swpool * num1;
        gttl += swpool * num1;
    }
    if (gym == 1)
    {
        cout << "\nGym\t\t" << gm << "\t\t   " << num1 << "\t\t" << gm * num1;
        gttl += gm * num1;
    }
    if (sports == 1)
    {
        cout << "\nSports\t\t" << spfts << "\t\t   " << num1 << "\t\t" << spfts * num1;
        gttl += spfts * num1;
    }
    if (salon == 1)
    {
        cout << "\nSalon\t\t" << slon << "\t\t   " << num1 << "\t\t" << slon * num1;
        gttl += slon * num1;
    }
    if (spa == 1)
    {
        cout << "\nSpa\t\t" << sp << "\t\t   " << num1 << "\t\t" << sp * num1;
        gttl += dcst * num1;
    }
    // total cost printing ~ number formatting
    cout << "\nGrand Total:Rs ";
    if (gttl > 100000) // to provide comma's for grandtotal
    {
        cout << gttl / 100000 << ",";
        gttl = gttl % 100000;
    }
    if (gttl > 1000)
    {
        cout << gttl / 1000 << ",";
        gttl = gttl % 1000;
    }
    cout << gttl;
    if (gttl < 10)
        cout << "00";
    cout << "\nAll Travellers below the age of 5 have not been charged";
}

void TravelDetails::accept(int c)
{
    num1 = c;
}

int TravelDetails::gtcode()
{
    return TravelCode;
}

void boardpt(int c) // for easy o/p
{
    if (c == 1)
        cout << "Mumbai\t";
    if (c == 2)
        cout << "Cochin\t";
    if (c == 3)
        cout << "Chennai\t";
}

void dest(int d) // for easy o/p
{
    switch (d)
    {
    case 1:
        cout << "New York";
        break;
    case 2:
        cout << "Miami";
        break;
    case 3:
        cout << "Rio De Janero";
        break;
    case 4:
        cout << "Colombo";
        break;
    case 5:
        cout << "Hong Kong";
        break;
    case 6:
        cout << "Dubai";
        break;
    case 7:
        cout << "Lisbon";
        break;
    case 8:
        cout << "London";
        break;
    case 9:
        cout << "Copenhagen";
        break;
    case 10:
        cout << "Cape Town";
        break;
    case 11:
        cout << "Antananriv";
        break;
    case 12:
        cout << "Cairo";
        break;
    case 13:
        cout << "Perth";
        break;
    case 14:
        cout << "Sydney";
        break;
    case 15:
        cout << "Willington";
        break;
    }
}
