#include <iostream>
#include <fstream>

#include "Settings.h"
#include "PersonalDetails.h"
#include "TravelDetails.h"
#include "FileManager.h"
#include "Currency.h"
#include "PriceManager.h"

#define _personal_details_filename "personal_details.bin"
#define _travel_details_filename "travel_details.bin"

using namespace std;
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

    cout << "Initialization completed." << endl;
    system("pause");
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
    for (int i = 1; i <= settings.last_travel_code; i++) {
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

        system("cls");
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
        settings.SaveSettings();
        system("pause");
    } while (choice != 5);
    
}

int main()
{
    Initialize();
    PersonalDetails PD;
    TravelDetails TD;

    int main_choice, opt1, opt2, opt3, opt4;
    int acceptcode;
    bool success_flag;
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
                    settings.last_travel_code++;
                    PD.p_input(settings.last_travel_code);
                    TD.t_input(settings.last_travel_code);

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
                    cout << "\n\n\n\n!!!!!Your Details Have Been Registered.Please Make A Note Of This Code: " << settings.last_travel_code;
                    cout << "\n\n* For modifications,Please visit 'existing user' section in the main screen";
                    system("pause");
                }
            } while (opt1 != 2);
            break;
        case 2:
            system("cls");
            cout << "\n\n** EXISTING USER **\n\nPlease Enter The Travel Code That Was Given To You\n\n";
            cin >> acceptcode;
            if (acceptcode > settings.last_travel_code)
            {
                cout << "\nNo such record has been created!";
                system("pause");
                break;
            }

            // load personal details from file and print family name:  _name_'s FAMILY
            success_flag = FileManager<PersonalDetails>().ReadFromFile(_personal_details_filename, acceptcode, PD);
            if (success_flag == false)
            {
                cout << "Couldn't find requested family record." << endl;
                system("pause");
                break;
            }
            cout << PD.family_name << "'s FAMILY DATABASE **" << endl;
            cout << "\t\t\t\tCode no:" << acceptcode << endl;
            system("pause");
            
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
                    // print personal details
                    FileManager<PersonalDetails>().ReadFromFile(_personal_details_filename, acceptcode, PD);
                    PD.p_output();
                }
                else if (opt2 == 2)
                {
                    // print travel details
                    FileManager<TravelDetails>().ReadFromFile(_travel_details_filename, acceptcode, TD);
                    TD.t_output();
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
                                    // edit personal details
                                    PD.p_input(acceptcode);
                                    FileManager<PersonalDetails>().InsertToFile(_personal_details_filename, PD, acceptcode);
                                    break;
                                case 2:
                                    // edit travel details
                                    TD.t_input(acceptcode);
                                    FileManager<TravelDetails>().InsertToFile(_travel_details_filename, TD, acceptcode);
                                    break;
                                }
                            } while (opt4 != 3);
                            break;
                        case 2:
                            // remove record
                            FileManager<PersonalDetails>().DeleteFromFile(_personal_details_filename, acceptcode);
                            FileManager<TravelDetails>().DeleteFromFile(_travel_details_filename, acceptcode);
                            opt3 = 3;
                            opt2 = 5;
                            break;
                        }
                    } while (opt3 != 3);
                }
                else if (opt2 == 4)
                {
                    // print expenses bill
                    FileManager<PersonalDetails>().ReadFromFile(_personal_details_filename, acceptcode, PD);
                    FileManager<TravelDetails>().ReadFromFile(_travel_details_filename, acceptcode, TD);
                    TD.update_adults(PD.adults_count());
                    TD.compute_expenses();
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
            
            break;
        case 3:
            settings_menu();
            break;
        }
    } while (main_choice != 4);

    settings.SaveSettings();
    return 0;
}
