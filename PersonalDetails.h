#pragma once
#include <iostream>
#include "InputHandler.cpp"
using namespace std;

/*
fields:
    TravelCode - each travel entry has 'unique' id by which the details can be accessed
    age[] - array of family member ages
    num - number of kids in family
    numppl - total number of family members (adults + kids)
    Name[] - array of family member names
    Address[] - string containing family address
    PhoneNumber[] - string containing contact phone number for the family
    gender[] - char array containing M/F as gender representaion of family members
    PassportNum[] - array of strings containing passport numbers (ids) of family members
    FamilyName[] - string representing the family name

methods:
    p_input(cd) - function gets the TravelCode as arg, and collects family details from input
    p_output() - function prints family details
    givefam() - function prints family name
    givecode() - function returns TravelCode
    givenum() - function returns the number of adults (total members - kids)
*/


class PersonalDetails // class for collecting the personal details
{
    int TravelCode, age[20], num, numppl;
    char Name[20][20], Address[50], PhoneNumber[15], gender[20], PassportNum[9][9], FamilyName[30];

public:
    void p_input(int cd)
    {
        TravelCode = cd;
        num = 0;
        cout << "\n\n:::::::::::::::::::::: PERSONAL DETAILS ::::::::::::::::::::::\n";
        cout << "\n* Please fill in the details:\n1.Family Name: ";
        StringInput(FamilyName, 30);
        cout << "\n2.Address: ";
        StringInput(Address, 50);
        cout << "\n3.Contact Number(10 Digit Mobile Number) : ";
        StringInput(PhoneNumber, 15);
        cout << "\nEnter The No of People Travelling: ";
        cin >> numppl;
        system("cls");
        if (numppl > 0)
        {
            cout << "\nPlease Enter The Details of each Member/Members: " << endl;
            for (int i = 0; i < numppl; i++)
            {
                cout << endl << "\nMember " << i + 1;
                cout << "\n~~~~~~~~~~~~~~~";
                cout << "\nFirst Name: ";
                StringInput(Name[i], 20);
                cout << "\nAge: ";
                cin >> age[i];
                cout << "\nSex (M/F): ";
                cin >> gender[i];
                cout << "\nPassport Number: ";
                StringInput(PassportNum[i], 9);
                if (age[i] < 5)
                {
                    num++; // to calculate no of travellers below 5 yrs
                }
            }
        }
    }
    void p_output()
    {
        system("cls");
        cout << "\n\n******* PERSONAL DETAILS *******" << endl;
        cout << "\nFamily Name: " << FamilyName << endl;
        cout << "Address: " << Address << endl;
        cout << "Phone Number: " << PhoneNumber << endl;
        cout << "\nName\t\tAge\t\tSex\t\tPassport Number\n" << endl;
        for (int i = 0; i < numppl; i++)
        {
            cout << "\t" << Name[i] << "\t\t" << age[i] << "\t\t" << gender[i] << "\t\t" << PassportNum[i] << endl;
        }
    }
    void givefam();
    int givecode();
    int givenum();
} PD;
int PersonalDetails::givenum()
{
    return numppl - num;
}
void PersonalDetails::givefam()
{
    cout << FamilyName;
}
int PersonalDetails::givecode()
{
    return TravelCode;
}