#include "TravelDetails.h"
#include <iostream>
using namespace std;

/* Prompt to fill TravelDetails from inputs. */
void TravelDetails::t_input(int travel_code)
{
    this->ID = travel_code;
    int choice;
    do
    {
        system("cls");
        cout << "TRAVEL DETAILS" << endl;
        cout << "~~~~~~~~~~~~~~~~~" << endl;
        cout << "Please enter the following details for your journey:" << endl;
        cout << "*Note:Options marked with '*' are compulsory.\tPlease do select them." << endl << endl;
        cout << "*1.Boarding and Destination\n*2.Date of Departure\n*3.Class\n4.Swimming Pool\n5.Gymnasuim\n6.Sports\n7.Salon\n8.Spa\n9.Back\n";
        cin >> choice;
        cin.ignore();  // in case a non numerical input is recieved
        switch (choice)
        {
        case 1:
            system("cls");
            cout << "Select Boarding point:\n1.Mumbai\n2.Cochin\n3.Chennai" << endl;
            cin >> this->boarding_point_id;
            cout << "\n*** Select Destination ***" << endl;
            cout << "1.New York\t\t6.Dubai\t\t\t11.Antananariv";
            cout << "\n2.Miami\t\t7.Lisbon\t\t12.Cairo";
            cout << "\n3.Rio De Janeiro\t8.London\t\t13.Perth";
            cout << "\n4.Colombo\t\t9.Copenhagen\t\t14.Sydney";
            cout << "\n5.Hong Kong\t\t10.Cape Town\t\t15.Wellington" << endl;
            cin >> this->disembarking_point_id;
            break;
        case 2:
            system("cls");
            cout << "Enter your preferred date(DD MM YYYY) of departure: ";
            cin >> this->day >> this->month >> this->year;
            break;
        case 3:
            system("cls");
            cout << "Enter The Choice OF Class\n1.First Class\n2.Business Class\n3.Economy Class" << endl;
            cin >> this->flight_class;
            break;
        case 4:
            system("cls");
            cout << "Would You Like To Avail The Facility Of A Swimming Pool\n0.No\n1.Yes\n";
            cin >> this->pool;
            break;
        case 5:
            system("cls");
            cout << "Would You Like To Avail The Facility Of A Gymnasium\n0.No\n1.Yes\n";
            cin >> this->gym;
            break;
        case 6:
            system("cls");
            cout << "Would You Like To Avail The Sports Facilities Offered\n0.No\n1.Yes\n";
            cin >> this->sports;
            break;
        case 7:
            system("cls");
            cout << "Would You Like To Avail The Facility Of Beauty Salon\n0.No\n1.Yes\n";
            cin >> this->salon;
            break;
        case 8:
            system("cls");
            cout << "Would You Like To Avail The Facility Of Spa\n0.No\n1.Yes\n";
            cin >> this->spa;
            break;
        }
    } while (choice != 9);
}

/* Print all TravelDetails. */
void TravelDetails::t_output()
{
        system("cls");
        cout << "##############TRAVEL DETAILS##############" << endl;
        cout << "\nBoarding Point: ";
        boarding_name(this->boarding_point_id);
        cout << "\nDestination: ";
        disembarking_name(this->disembarking_point_id);
        cout << "\nDate of departure: ";
        cout << day << "/" << month << "/" << year;
        cout << "\nClass: ";
        switch (this->flight_class)
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
        cout << endl << "\n\n\n\tFacilities availed for are:";
        if (this->pool)
            cout << "\nSwimming Pool";
        if (this->gym)
            cout << "\n";
        if (this->sports)
            cout << "\n";
        if (this->spa)
            cout << "\nSpa";
        if (this->salon)
            cout << "\nBeauty Salon";
    }

/* Calculate expenses and print them. */
void TravelDetails::compute_expenses()
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
    switch (this->disembarking_point_id)  // assign prices for activities and ticket per destination
    {
    case 1:
    case 2:
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
    
    switch (this->flight_class)
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
    cout << ":::::::::::::::::::::: BILL ::::::::::::::::::::::::::" << endl;
    cout << "Boarding point: ";
    boarding_name(this->boarding_point_id);
    cout << "\nDestination: ";
    disembarking_name(this->disembarking_point_id);
    cout << "\nDate of Departure: ";
    cout << day << "/" << month << "/" << year << endl;

    // hr refers to the period of stay?
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

    cout << "Date of Arrival: ";
    cout << day << "/" << month << "/" << year << endl << endl;
    cout << "Subject\t\tCost(for 1)\tNo of adults\tTotal";
    cout << "\n\nTravel\t\t" << dcst << "\t\t   " << this->adults_count << "\t\t" << this->adults_count * dcst;
    gttl += this->adults_count * dcst;  // cost of tickets for all members
    cout << "\nClass\t\t" << cls << "\t\t   " << this->adults_count << "\t\t" << cls * this->adults_count;
    gttl += cls * this->adults_count;  // cost of class status for all members

    // cost of extra expenses
    if (this->pool)
    {
        cout << "\nSwimming Pool\t" << swpool << "\t\t   " << this->adults_count << "\t\t" << swpool * this->adults_count;
        gttl += swpool * this->adults_count;
    }
    if (this->gym)
    {
        cout << "\nGym\t\t" << gm << "\t\t   " << this->adults_count << "\t\t" << gm * this->adults_count;
        gttl += gm * this->adults_count;
    }
    if (this->sports)
    {
        cout << "\nSports\t\t" << spfts << "\t\t   " << this->adults_count << "\t\t" << spfts * this->adults_count;
        gttl += spfts * this->adults_count;
    }
    if (this->salon)
    {
        cout << "\nSalon\t\t" << slon << "\t\t   " << this->adults_count << "\t\t" << slon * this->adults_count;
        gttl += slon * this->adults_count;
    }
    if (this->spa)
    {
        cout << "\nSpa\t\t" << sp << "\t\t   " << this->adults_count << "\t\t" << sp * this->adults_count;
        gttl += dcst * this->adults_count;
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
    cout << "\nAll Travellers below the age of 5 have not been charged" << endl;
}

/* Update adults count for corrent expense calculations. */
void TravelDetails::update_adults(int count)
{
    this->adults_count = count;
}

/* Get travel code, which is the same as ID. */
int TravelDetails::get_travel_code()
{
    return this->ID;
}

/* Print boarding point name inline by its id. */
void boarding_name(int id)
{
    switch (id)
    {
    case 1:
        cout << "Mumbai\t";
        break;

    case 2:
        cout << "Cochin\t";
        break;

    case 3:
        cout << "Chennai\t";
        break;
    }
}

/* Print disembarking point name inline by its id. */
void disembarking_name(int id)
{
    switch (id)
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

