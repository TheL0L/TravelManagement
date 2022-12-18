#include <iostream>
#include <fstream>

#include "Settings.h"
#include "PersonalDetails.h"
#include "TravelDetails.h"
#include "FileManager.h"
#include "Currency.h"
#include "PriceManager.h"

using namespace std;
long int latest_travel_code;
Settings settings;

/* Load settings and set initial fields. */
void Initialize()
{
    system("cls");

    // try to load settings from file
    if (settings.LoadSettings() == false)
    {
        cout << endl << "Trying to create file..." << endl;
        // if failed, check if file exists, otherwise create it
        ifstream check_handle(_settings_filename);
        if (check_handle.good() == false)
            FileManager<Settings>().CreateEmpty(_settings_filename);
        check_handle.close();

        settings.SaveSettings();
    }

    latest_travel_code = settings.last_travel_code;

    cout << "Initialization completed." << endl;
    system("pause");
}

void family(int c, int &flag) // to display familyname+to check for record
{
    PersonalDetails PD;

    flag = 0;
    system("cls");
    ifstream ifl("personal_details.bin", ios::binary);
    if (!ifl)
        cout << "\nError";
    ifl.read((char *)&PD, sizeof(PD));
    do
    {
        if (PD.get_travel_code() == c)
        {
            flag = 1;
            break;
        }
        ifl.read((char *)&PD, sizeof(PD));
    } while (!ifl.eof());
    if (flag == 1)
    {
        cout << PD.family_name << "'s FAMILY DATABASE **";
    }
    else
    {
        cout << "\nError in locating record!!";
    }
    ifl.close();
}

void editp(int c) // to edit persdetails
{
    PersonalDetails PD;

    ofstream ofl2("temp1.txt", ios::binary);
    if (!ofl2)
        cout << "Error While Opening File";
    ifstream ifl4("personal_details.bin", ios::binary);
    if (!ifl4)
        cout << "Error While Opening File";
    ifl4.read((char *)&PD, sizeof(PD));
    while (!ifl4.eof())
    {
        if (PD.get_travel_code() == c)
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
    remove("personal_details.bin");
    rename("temp1.txt", "personal_details.bin");
    ifl4.close();
    ofl2.close();
}

void editt(int c) // to edit travdetails
{
    TravelDetails TD;

    ofstream ofl2("temp1.txt", ios::binary);
    if (!ofl2)
        cout << "Error While Opening File";
    ifstream ifl4("travel_details.bin", ios::binary);
    if (!ifl4)
        cout << "Error While Opening File";
    ifl4.read((char *)&TD, sizeof(TD));
    while (!ifl4.eof())
    {
        if (TD.get_travel_code() == c)
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
    remove("travel_details.bin");
    rename("temp1.txt", "travel_details.bin");
    ifl4.close();
    ofl2.close();
}

void deletion(int c) // common delete func()
{
    PersonalDetails PD;
    TravelDetails TD;

    ofstream ofl2("temp1.txt", ios::binary);
    if (!ofl2)
        cout << "Error While Opening File";
    ifstream ifl4("personal_details.bin", ios::binary);
    if (!ifl4)
        cout << "Error While Opening File";
    ifl4.read((char *)&PD, sizeof(PD));
    while (!ifl4.eof())
    {
        if (PD.get_travel_code() != c)
        {
            ofl2.write((char *)&PD, sizeof(PD));
        }
        ifl4.read((char *)&PD, sizeof(PD));
    }
    remove("personal_details.bin");
    rename("temp1.txt", "personal_details.bin");
    ofl2.close();
    ifl4.close();
    ofstream ofl3("temp2.txt", ios::binary);
    if (!ofl3)
        cout << "\nError While Opening File";
    ifstream ifl5("travel_details.bin", ios::binary);
    if (!ifl5)
        cout << "\nError While Opening File";
    ifl5.read((char *)&TD, sizeof(TD));
    while (!ifl5.eof())
    {
        if (TD.get_travel_code() != c)
        {
            ofl3.write((char *)&TD, sizeof(TD));
        }
        ifl5.read((char *)&TD, sizeof(TD));
    }
    ofl3.close();
    ifl5.close();
    remove("travel_details.bin");
    rename("temp1.txt", "travel_details.bin");
    cout << "\n\nDeletion Completed!";
}

void print_same_destination_implement(int tc) {
    bool success_flag;
    //we get a travel code and read from the file the data of the user that corresponds with the travel code//
    TravelDetails data;
    PersonalDetails p_data;
    success_flag=FileManager<TravelDetails>().ReadFromFile("travel_details.bin", tc, data);
    if (success_flag == false) {
        return;
    }

    //we take the destination with data.disembarking_point_id and we'll give it to a temporary arguemnt//
    int dest = data.disembarking_point_id;

    //we check the disembarking point for each travel code (user) on the file and if it matches with the x (the user who we took his disembarking point) and print family names that fly there as well//
    cout << "The families that fly to the same destination are:" << endl;
    for (int i = 1; i <= latest_travel_code; i++) {
        success_flag=FileManager<TravelDetails>().ReadFromFile("travel_details.bin", i, data);

        if (success_flag == false) {
            continue;
        }

        if (dest == data.disembarking_point_id) {
            success_flag=FileManager<PersonalDetails>().ReadFromFile("personal_details.bin", data.ID, p_data);
            if (success_flag == false) {
                continue;
            }
            //print the family name somehow//
            cout<<p_data.family_name<<endl;
        }
    }
}

void settings_menu()
{
    PriceSheet sheet;
    int choice;
    do
    {
        system("cls");
        cout << "#############   SETTINGS   ############" << endl;
        cout << "1. Display Currency" << endl;
        cout << "2. Edit Existing PriceSheets" << endl;
        cout << endl;  // "3. Add New Destinations" << endl;  // an idea
        cout << endl;  // "4. Remove Destinations" << endl;  // an idea
        cout << "5. Back" << endl;

        cin >> choice;
        cin.ignore();  // in case a non numeric input is recieved

        switch (choice)
        {
        case 1:
            settings.default_currency = PickAvailableCurrency();
            break;
        case 2:
            Fill_PriceSheet(sheet);
            Edit_PriceSheet(sheet);
            break;
        }
        system("pause");
    } while (choice != 5);
    
}

int main()
{
    Initialize();
    PersonalDetails PD;
    TravelDetails TD;

    int main_choice, opt1, opt2, opt3, opt4;
    int acceptcode, flag;
    do
    {
        system("cls");
        cout << "#######################################\n";
        cout << "#######################################\n";
        cout << "############   MAIN MENU   ############\n";
        cout << "#######################################\n";
        cout << "#######################################\n";

        cout << "\nPlease select an option:\n";
        cout << "\n1.New User\n2.Existing User\n\n3.Settings\n4.Exit" << endl;
        cin >> main_choice;
        cin.ignore();

        switch (main_choice)
        {
        case 1:
            do
            {
                system("cls");
                cout << "\n\n    NEW USER\n";
                cout << "*********\n\n";
                cout << "\n\nChoose an action:";
                cout << "\n\n1.Enter Personal and Travel Details\n2.Back\n\n";
                cin >> opt1;
                cin.ignore();  // in case a non numeric input is recieved
                if (opt1 == 1)
                {
                    latest_travel_code++;
                    PD.p_input(latest_travel_code);
                    TD.t_input(latest_travel_code);

                    /* update latest travel code */
                    settings.SaveTravelCode();

                    /* save personal */
                    ofstream ofl("personal_details.bin", ios::binary | ios::app);
                    if (!ofl)
                        cout << "\n\nSorry.The File Cannot Be Opened For Writing" << endl;
                    ofl.write((char *)&PD, sizeof(PD));
                    ofl.close();

                    /* save travel */
                    ofstream ofl1("travel_details.bin", ios::binary | ios::app);
                    if (!ofl1)
                        cout << "\n\n\t\tSorry.The File Cannot Be Opened For Writing" << endl;
                    ofl1.write((char *)&TD, sizeof(TD));
                    ofl1.close();


                    system("cls");
                    cout << "\n\n\n\n!!!!!Your Details Have Been Registered.Please Make A Note Of This Code: " << latest_travel_code;
                    cout << "\n\n* For modifications,Please visit 'existing user' section in the main screen";
                    system("pause");
                }
            } while (opt1 != 2);
            break;
        case 2:
            system("cls");
            cout << "\n\n** EXISTING USER **\n\nPlease Enter The Travel Code That Was Given To You\n\n";
            cin >> acceptcode;
            if (acceptcode > latest_travel_code)
            {
                cout << "\nNo such record has been created!";
                system("pause");
                break;
            }
            family(acceptcode, flag);
            cout << endl << endl << "\t\t\t\tCode no:" << acceptcode;
            if (flag == 1)
            {
                do
                {
                    system("cls");
                    cout << "\n\n@@@@@@@@@Information Centre@@@@@@@@@";
                    cout << "\n~~~~~~~";
                    cout << "\n\nPlease select the type of operation that you would like to perform:";
                    cout << "\n1.View Personal Details\n2.View Travel Details\n3.Edit Details" << endl;
                    cout << "4.Compute Bill\n\n5.Print all families with similar destination\n\n6.Back" << endl;
                    cin >> opt2;
                    if (opt2 == 1)
                    {
                        ifstream ifl("personal_details.bin", ios::binary);
                        if (!ifl)
                            cout << "\nError";
                        ifl.read((char *)&PD, sizeof(PD));
                        while (!ifl.eof())
                        {
                            if (PD.get_travel_code() == acceptcode)
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
                        ifstream ifl1("travel_details.bin", ios::binary);
                        if (!ifl1)
                            cout << "\nError";
                        ifl1.read((char *)&TD, sizeof(TD));
                        while (!ifl1.eof())
                        {
                            if (TD.get_travel_code() == acceptcode)
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
                        ifstream ifl3("personal_details.bin", ios::binary);
                        if (!ifl3)
                            cout << "\nError";
                        ifl3.read((char *)&PD, sizeof(PD));
                        while (!ifl3.eof())
                        {
                            if (PD.get_travel_code() == acceptcode)
                            {
                                break;
                            }
                            ifl3.read((char *)&PD, sizeof(PD));
                        }
                        ifstream ifl2("travel_details.bin", ios::binary);
                        if (!ifl2)
                            cout << "\nError";
                        ifl2.read((char *)&TD, sizeof(TD));
                        while (!ifl2.eof())
                        {
                            if (TD.get_travel_code() == acceptcode)
                            {
                                break;
                            }
                            ifl2.read((char *)&TD, sizeof(TD));
                        }
                        TD.update_adults(PD.adults_count());
                        TD.AddDiscount(PD.DiscountAvaliablity());
                        TD.compute_expenses();

                        ifl2.close();
                    }
                    else if (opt2 == 5) 
                    {
                        system("cls");
                        print_same_destination_implement(acceptcode);
                    }
                    else if (opt2 == 6)
                    {
                        break;
                    }
                    system("pause");
                } while (main_choice != 3);
            }
            break;
        case 3:
            settings_menu();
            break;
        }
    } while (main_choice != 4);

    return 0;
}
