#include "PersonalDetails.h"
#include <iostream>
#include "InputHandler.h"
using namespace std;

/* Prompt to fill PersonalDetails from inputs. */
void PersonalDetails::p_input(int travel_code)
{
    this->ID = travel_code;
    this->children_count = 0;
    cout << ":::::::::::::::::::::: PERSONAL DETAILS ::::::::::::::::::::::" << endl;
    cout << "* Please fill in the details:" << endl << "1.Family Name: ";
    StringInput_no_flushing(this->family_name, 30);
    cout << endl << "2.Address: ";
    StringInput_no_flushing(this->address, 50);
    cout << endl << "3.Contact Number(10 Digit Mobile Number) : ";
    StringInput_no_flushing(this->phone_number, 15);
    cout << endl << "Enter The No of People Travelling: ";
    cin >> this->members_count;
    system("cls");
    if (this->members_count > 0)
    {
        cout << "Please Enter The Details of each Member/Members: " << endl;
        for (int i = 0; i < this->members_count; i++)
        {
            cout << endl << "Member " << i + 1 << endl;
            cout << "~~~~~~~~~~~~~~~" << endl;
            cout << "First Name: ";
            StringInput(this->names[i], 20);
            cout << "Age: ";
            cin >> this->ages[i];
            cout << "Birthday (day and month): ";
            cin >> this->bday[i] >> this->bmonth[i];
            cout << "Sex (M/F): ";
            cin >> this->genders[i];
            cout << "Passport Number: ";
            StringInput(this->passports[i], 9);
            if (this->ages[i] < 5)
            {
                children_count++; // to calculate no of travellers below 5 yrs
            }
        }
    }
}

/* Print all PersonalDetails. */
void PersonalDetails::p_output()
{
    system("cls");
    cout << "******* PERSONAL DETAILS *******" << endl << endl;
    cout << "Family Name: " << this->family_name << endl;
    cout << "Address: " << this->address << endl;
    cout << "Phone Number: " << this->phone_number << endl;
    cout << "\nName\t\tAge\t\tSex\t\tPassport Number\n" << endl;
    for (int i = 0; i < this->members_count; i++)
    {
        cout << "\t" << this->names[i] << "\t\t" << this->ages[i] << "\t\t" << this->genders[i] << "\t\t" << this->passports[i] << endl;
    }
}

/* Get number of adults. */
int PersonalDetails::adults_count()
{
    return this->members_count - this->children_count;
}

/* Get travel code, which is the same as ID. */
int PersonalDetails::get_travel_code()
{
    return this->ID;
}

/* Calculates a discount a family may get in certein creterias */
int PersonalDetails::DiscountAvaliablity()
{
    int discount = 0;
    bool flag = false;

    struct tm date;
    time_t current_time = time(0);
    localtime_s(&date, &current_time);
    int day = date.tm_mday;
    int month = date.tm_mon + 1;

    //Big families will recieve a 1% discount per member up to 5%
    if (this->members_count >= 3 && this->members_count <= 5)
        discount += members_count;

    else if (this->members_count > 5)
        discount += 5;

    //Elderly discount - a family member older than 50 will recieve additional 1% discount
    for (int i = 0; i < members_count && !flag; i++)
    {
        if (ages[i] >= 50)
        {
            discount += 1;
            flag = true;
        }
    }

    //Group of more than 2 members will recieve a discount based on the creterias:
    if (members_count > 1)
    {

        //Birthday - family member which celebrates birthday will recieve 2% discount
        flag = false;
        for (int i = 0; i < members_count && !flag; i++)
        {
            if (day == this->bday[i] && month == this->bmonth[i])
            {
                discount += 2;
                flag = true;
            }
        }

        //Women's day discount - during 8 of March a female family member will recieve 1% discount
        flag = false;
        if (day == 8 && month == 3)
            for (int i = 0; i < members_count && !flag; i++)
            {
                if (this->genders[i] == 'F')
                {
                    discount += 2;
                    flag = true;
                }
            }
    }
    return discount;
}
