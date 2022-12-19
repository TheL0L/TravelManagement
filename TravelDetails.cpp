#include "TravelDetails.h"
#include <iostream>
#include "PriceSheet.h"
#include "PriceManager.h"
#include "Currency.h"
#include "Settings.h"
using namespace std;


/* Function for date calculation. */
void CalculateDate(int& day, int& month, int& year, int reserved)
{
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
}

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
        cout << endl << "\n\n\n\tFacilities availed for are:" << endl;
        if (this->pool)
            cout << "Swimming Pool" << endl;
        if (this->gym)
            cout << "Gym" << endl;
        if (this->sports)
            cout << "Sport Facilities" << endl;
        if (this->spa)
            cout << "Spa" << endl;
        if (this->salon)
            cout << "Beauty Salon" << endl;
    }

/* Calculate expenses and print them. */
void TravelDetails::compute_expenses(int dis)
{
    // pull currency type from settings
    Settings settings;
    CurrencyType coin_type = (CurrencyType)settings.default_currency;

    // pull relevant pricesheet
    PriceSheet prices;
    Get_PriceSheet(this->disembarking_point_id, prices);

    // calculate arival date
    int return_day = this->day;
    int return_month = this->month;
    int return_year = this->year;
    CalculateDate(return_day, return_month, return_year, prices.reservation_period);

    // calculate tickets
    int tickets_total = this->adults_count * prices.destination_ticket;
    
    // get class base price
    int class_cost = this->flight_class;
    switch (class_cost)
    {
    case 1:
        class_cost = 90;
        break;
    case 2:
        class_cost = 60;
        break;
    case 3:
        class_cost = 20;
        break;
    }

    // print basic info
    system("cls");
    cout << ":::::::::::::::::::::: BILL ::::::::::::::::::::::::::" << endl;
    cout << "Boarding point: ";
    boarding_name(this->boarding_point_id);
    cout << "\nDestination: ";
    disembarking_name(this->disembarking_point_id);
    cout << "\nDate of Departure: ";
    cout << this->day << "/" << this->month << "/" << this->year << endl;
    cout << "Date of Arrival: ";
    cout << day << "/" << month << "/" << year << endl << endl;

    // print costs table
    cout << "Subject\t\tCost(for 1)\tNo of adults\tTotal" << endl << endl;

    cout << "Travel\t\t" << Currency(prices.destination_ticket, coin_type) << "\t\t   ";
    cout << this->adults_count << "\t\t" << Currency(this->adults_count * prices.destination_ticket, coin_type) << endl;

    cout << "Class\t\t" << class_cost << "\t\t   " << this->adults_count;
    cout << "\t\t" << Currency(class_cost * this->adults_count, coin_type) << endl;

    // cost of extra expenses
    if (this->pool)
    {
        cout << "\nSwimming Pool\t" << prices.swimming_pool << "\t\t   ";
        cout << this->adults_count << "\t\t" << prices.swimming_pool * this->adults_count << endl;
    }
    if (this->gym)
    {
        cout << "\nGym\t\t" << prices.gym << "\t\t   ";
        cout << this->adults_count << "\t\t" << prices.gym * this->adults_count << endl;
    }
    if (this->sports)
    {
        cout << "\nSports\t\t" << prices.other_sports << "\t\t   ";
        cout << this->adults_count << "\t\t" << prices.other_sports * this->adults_count << endl;
    }
    if (this->salon)
    {
        cout << "\nSalon\t\t" << prices.beauty_salon << "\t\t   ";
        cout << this->adults_count << "\t\t" << prices.beauty_salon * this->adults_count << endl;
    }
    if (this->spa)
    {
        cout << "\nSpa\t\t" << prices.spa << "\t\t   ";
        cout << this->adults_count << "\t\t" << prices.spa * this->adults_count << endl;
    }

    // calculate total cost
    Currency total(0, coin_type);
    total += prices.destination_ticket + class_cost + prices.swimming_pool + prices.gym;
    total += prices.other_sports + prices.beauty_salon + prices.spa;
    total = total * this->adults_count;

    // total cost printing
    cout << "Total cost:  " << total << endl;

    if (dis > 0)
    {
        cout << "\t\t\tEach client is special to us but today you're even more than ever!" << endl;
        cout << "\t\t\tYou will recieve an aditional discount: " << dis << "% off! Thank you for choosing our company!" << endl;
        total -= (total*(float)dis)/100;
    }

    cout << "All Travellers below the age of 5 have not been charged." << endl;
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