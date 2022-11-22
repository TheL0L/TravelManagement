#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <fstream>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;
long int code;

#include "PersonalDetails.h"
#include "TravelDetails.h"




void family(int c, int &flag) // to display familyname+to check for record
{
    flag = 0;
    system("cls");
    ifstream ifl("PersonalDetails.txt", ios::binary);
    if (!ifl)
        cout << "\nError";
    ifl.read((char *)&PD, sizeof(PD));
    while (!ifl.eof())
    {
        if (PD.givecode() == c)
        {
            flag = 1;
            break;
        }
        ifl.read((char *)&PD, sizeof(PD));
    }
    if (flag == 1)
    {
        PD.givefam();
        cout << "'s FAMILY DATABASE **";
    }
    else
    {
        cout << "\nError in locating record!!";
    }
    ifl.close();
}

void editp(int c) // to edit persdetails
{
    ofstream ofl2("temp1.txt", ios::binary);
    if (!ofl2)
        cout << "Error While Opening File";
    ifstream ifl4("PersonalDetails.txt", ios::binary);
    if (!ifl4)
        cout << "Error While Opening File";
    ifl4.read((char *)&PD, sizeof(PD));
    while (!ifl4.eof())
    {
        if (PD.givecode() == c)
        {
            system("cls");
            cout << "Please Enter the New details of the record" << endl;
            PD.p_input(c);
            ofl2.write((char *)&PD, sizeof(PD));
            cout << "\nModification Succesful!!!";
            ifl4.read((char *)&PD, sizeof(PD));
        }
        else
        {
            ofl2.write((char *)&PD, sizeof(PD));
            ifl4.read((char *)&PD, sizeof(PD));
        }
    }
    remove("PersonalDetails.txt");
    rename("temp1.txt", "PersonalDetails.txt");
    ifl4.close();
    ofl2.close();
    getch();
}

void editt(int c) // to edit travdetails
{
    ofstream ofl2("temp1.txt", ios::binary);
    if (!ofl2)
        cout << "Error While Opening File";
    ifstream ifl4("TravelDetails.txt", ios::binary);
    if (!ifl4)
        cout << "Error While Opening File";
    ifl4.read((char *)&TD, sizeof(TD));
    while (!ifl4.eof())
    {
        if (TD.gtcode() == c)
        {
            system("cls");
            cout << "Please Enter the New details of the record" << endl;
            TD.t_input(c);
            ofl2.write((char *)&TD, sizeof(TD));
            cout << "\nModification Succesful!!!";
            ifl4.read((char *)&TD, sizeof(TD));
        }
        else
        {
            ofl2.write((char *)&TD, sizeof(TD));
            ifl4.read((char *)&TD, sizeof(TD));
        }
    }
    remove("TravelDetails.txt");
    rename("temp1.txt", "TravelDetails.txt");
    ifl4.close();
    ofl2.close();
    getch();
}

void deletion(int c) // common delete func()
{
    ofstream ofl2("temp1.txt", ios::binary);
    if (!ofl2)
        cout << "Error While Opening File";
    ifstream ifl4("PersonalDetails.txt", ios::binary);
    if (!ifl4)
        cout << "Error While Opening File";
    ifl4.read((char *)&PD, sizeof(PD));
    while (!ifl4.eof())
    {
        if (PD.givecode() != c)
        {
            ofl2.write((char *)&PD, sizeof(PD));
        }
        ifl4.read((char *)&PD, sizeof(PD));
    }
    remove("PersonalDetails.txt");
    rename("temp1.txt", "PersonalDetails.txt");
    ofl2.close();
    ifl4.close();
    ofstream ofl3("temp2.txt", ios::binary);
    if (!ofl3)
        cout << "\nError While Opening File";
    ifstream ifl5("TravelDetails.txt", ios::binary);
    if (!ifl5)
        cout << "\nError While Opening File";
    ifl5.read((char *)&TD, sizeof(TD));
    while (!ifl5.eof())
    {
        if (TD.gtcode() != c)
        {
            ofl3.write((char *)&TD, sizeof(TD));
        }
        ifl5.read((char *)&TD, sizeof(TD));
    }
    ofl3.close();
    ifl5.close();
    remove("TravelDetails.txt");
    rename("temp1.txt", "TravelDetails.txt");
    cout << "\n\nDeletion Completed!";
    getch();
}

int main()
{
    system("cls");

    ifstream fl("INITIAL.txt", ios::binary); // initialisation of code
    fl.read((char *)&code, sizeof(code));
    fl.close();
    int opt, opt1, opt2, opt3, opt4;
    int acceptcode, flag;
    system("cls");
    do
    {
        system("cls");
        cout << "#######################################\n";
        cout << "#######################################\n";
        cout << "############   MAIN MENU   ############\n";
        cout << "#######################################\n";
        cout << "#######################################\n";

        cout << "\nPlease Register Choice!\n";
        cout << "\n1.New User\n2.Existing User\n3.Exit\n";
        cin >> opt;
        switch (opt)
        {
        case 1:
            do
            {
                system("cls");
                cout << "\n\n    NEW USER\n";
                cout << "*********\n\n";
                cout << "\n\nChoose the type of details you want to enter:";
                cout << "\n\n1.Personal Details\n2.Travel Details\n3.Back\n\n";
                cin >> opt1;
                if (opt1 == 1)
                {
                    code++;
                    PD.p_input(code);
                    ofstream ofl("PersonalDetails.txt", ios::binary | ios::app);
                    if (!ofl)
                        cout << "\n\nSorry.The File Cannot Be Opened For Writing" << endl;
                    ofl.write((char *)&PD, sizeof(PD));
                    ofl.close();
                }
                else if (opt1 == 2)
                {
                    TD.t_input(code);
                    ofstream ofl1("TravelDetails.txt", ios::binary | ios::app);
                    if (!ofl1)
                        cout << "\n\n\t\tSorry.The File Cannot Be Opened For Writing" << endl;
                    ofl1.write((char *)&TD, sizeof(TD));
                    ofl1.close();
                    system("cls");
                    cout << "\n\n\n\n!!!!!Your Details Have Been Registered.Please Make A Note Of This Code: " << code;
                    cout << "\n\n* For modifications,Please visit 'existing user' section in the main screen";
                    getch();
                }
            } while (opt1 != 3);
            break;
        case 2:
            system("cls");
            cout << "\n\n** EXISTING USER **\n\nPlease Enter The Travel Code That Was Given To You\n\n";
            cin >> acceptcode;
            if (acceptcode > code)
            {
                cout << "\nNo such record has been created!";
                break;
            }
            family(acceptcode, flag);
            cout << endl
                 << endl
                 << "\t\t\t\tCode no:" << acceptcode;
            getch();
            if (flag == 1)
            {
                do
                {
                    system("cls");
                    cout << "\n\n@@@@@@@@@Information Centre@@@@@@@@@";
                    cout << "\n~~~~~~~";
                    cout << "\n\nPlease select the type of operation that you would like to perform:";
                    cout << "\n1.View Personal Details\n\n2.View Travel Details\n\n3.Edit Details\n\n4.Compute Bill\n\n5.Back\n";
                    cin >> opt2;
                    if (opt2 == 1)
                    {
                        ifstream ifl("PersonalDetails.txt", ios::binary);
                        if (!ifl)
                            cout << "\nError";
                        ifl.read((char *)&PD, sizeof(PD));
                        while (!ifl.eof())
                        {
                            if (PD.givecode() == acceptcode)
                            {
                                break;
                            }
                            ifl.read((char *)&PD, sizeof(PD));
                        }
                        PD.p_output();
                        ifl.close();
                    }
                    else if (opt2 == 2)
                    {
                        ifstream ifl1("TravelDetails.txt", ios::binary);
                        if (!ifl1)
                            cout << "\nError";
                        ifl1.read((char *)&TD, sizeof(TD));
                        while (!ifl1.eof())
                        {
                            if (TD.gtcode() == acceptcode)
                            {
                                break;
                            }
                            ifl1.read((char *)&TD, sizeof(TD));
                        }
                        TD.t_output();
                        ifl1.close();
                    }
                    else if (opt2 == 3)
                    {
                        do
                        {
                            system("cls");
                            cout << "\n\n\n\t¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬ Edit Details ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬";
                            cout << "\n\n\t\tPlease select from among the editing options:\n\n";
                            cout << "\t\t\t\t1.Modify\n\n\t\t\t\t2.Delete\n\n\t\t\t\t3.Back\n\n\t\t\t\t ";
                            cin >> opt3;
                            switch (opt3)
                            {
                            case 1:
                                do
                                {
                                    system("cls");
                                    cout << "\n\n\t\t Modificaton \n";
                                    cout << "\t\t               ~~~~~";
                                    cout << "\n\n\tChoose The Type Of Details You Want To Modify:\n\n\t\t\t1.Personal Details\n\n\t\t\t2.Travel Details\n\n\t\t\t3.Back\n\n\t\t\t ";
                                    cin >> opt4;
                                    switch (opt4)
                                    {
                                    case 1:
                                        editp(acceptcode);
                                        break;
                                    case 2:
                                        editt(acceptcode);
                                        break;
                                    case 3:
                                        break;
                                    }
                                } while (opt4 != 3);
                                break;
                            case 2:
                                deletion(acceptcode);
                                opt3 = 3;
                                opt2 = 5;
                                break;
                            case 3:
                                break;
                            }
                        } while (opt3 != 3);
                    }
                    else if (opt2 == 4)
                    {
                        ifstream ifl3("PersonalDetails.txt", ios::binary);
                        if (!ifl3)
                            cout << "\nError";
                        ifl3.read((char *)&PD, sizeof(PD));
                        while (!ifl3.eof())
                        {
                            if (PD.givecode() == acceptcode)
                            {
                                break;
                            }
                            ifl3.read((char *)&PD, sizeof(PD));
                        }
                        ifstream ifl2("TravelDetails.txt", ios::binary);
                        if (!ifl2)
                            cout << "\nError";
                        ifl2.read((char *)&TD, sizeof(TD));
                        while (!ifl2.eof())
                        {
                            if (TD.gtcode() == acceptcode)
                            {
                                break;
                            }
                            ifl2.read((char *)&TD, sizeof(TD));
                        }
                        TD.accept(PD.givenum());
                        TD.compute();
                        ifl2.close();
                    }
                    else if (opt2 == 5)
                        break;
                } while (opt3 != 3);
            }
            break;
        case 3:
            ofstream fil("INITIALL.txt", ios::binary); // storing code value
            if (!fil)
                cout << "\nError";
            fil.write((char *)&code, sizeof(code));
            fil.close();
            getch();
            exit(0);
            break;
        }
        getch();
    } while (1); // infinite loop till exit selected
    return 0;
}
