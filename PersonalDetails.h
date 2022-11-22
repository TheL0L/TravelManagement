#pragma once
#include <iostream>
using namespace std;


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
        cin.ignore();
        cin.getline(FamilyName, 30);
        cout << "\n2.Address: ";
        cin.ignore();
        cin.getline(Address, 50);
        cout << "\n3.Contact Number(10 Digit Mobile Number) : ";
        cin.ignore();
        cin.getline(PhoneNumber, 15);
        cout << "\nEnter The No of People Travelling: ";
        cin >> numppl;
        system("cls");
        if (numppl > 0)
        {
            cout << "\nPlease Enter The Details of each Member/Members: " << endl;
            for (int i = 0; i < numppl; i++)
            {
                cout << endl
                     << "\nMember " << i + 1;
                cout << "\n~~~~~~~~~~~~~~~";
                cout << "\nFirst Name: ";
                cin.ignore();
                cin.getline(Name[i], 20);
                cout << "\nAge: ";
                cin >> age[i];
                cout << "\nSex (M/F): ";
                cin >> gender[i];
                cout << "\nPassport Number: ";
                cin.ignore();
                cin.getline(PassportNum[i], 9);
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
        cout << "\nName\t\tAge\t\tSex\t\tPassport Number\n"
             << endl;
        for (int i = 0; i < numppl; i++)
        {
            cout << "\t" << Name[i] << "\t\t" << age[i] << "\t\t" << gender[i] << "\t\t" << PassportNum[i] << endl;
        }
        getch();
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