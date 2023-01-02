#include <iostream>
#include <fstream>
#include <iomanip>

#include "Settings.h"
#include "PersonalDetails.h"
#include "TravelDetails.h"
#include "FileManager.h"
#include "Currency.h"
#include "PriceManager.h"

struct date_pack { int day = 1, month = 1, year = 1970; };

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

int* Statistics()// get the amounts of travelers to the same destination
{
    TravelDetails TD;
    FileManager<TravelDetails> fm;
    int last_code = settings.last_travel_code;
    int stats[15] = { 0 };

    for (int i = 1; i <= last_code; i++)
    {
        fm.ReadFromFile(_travel_details_filename, i, TD);
        stats[TD.disembarking_point_id - 1]++;
    }
    return stats;
}

void printStats(int* stats)// print the hotest and least hotest locations
{
    int maxIndex = 0, minIndex = 0;
    for (int i = 1; i < 15; i++)
    {
        if (stats[i] > stats[maxIndex])
            maxIndex = i;
        if (stats[i] < stats[minIndex])
            minIndex = i;
    }
    cout << " Amount | Destination" << endl;
    cout << "______________________" << endl << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << std::setw(7) << stats[i];
        cout << " | ";
        disembarking_name(i + 1);
        cout << endl;
    }
    cout << endl;
    cout << "The hottest destination today is: "; disembarking_name(maxIndex + 1);
    cout << endl;
    cout << "The least hottest destination today is: "; disembarking_name(minIndex + 1);
    cout << endl << endl;
}

void get_date(date_pack& date)
{
    bool invalid = true;

    do  // validity check
    {
        cin >> date.day >> date.month >> date.year;
        
        if (date.day < 1 || date.month < 1 || date.year < 1970)
        {
            invalid = true;
        }
        else if (date.day > 31 || date.month > 12 || date.year > 2300)
        {
            invalid = true;
        }

        // if we got here, then year & month are valid.
        // procced to check day

        else if (date.month == 2)
        {
            if (date.day <= 28)
                invalid = false;
        }
        else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
        {
            if (date.day <= 30)
                invalid = false;
        }
        else
        {
            invalid = false;
        }

    } while (invalid);
    
}

void get_dest(int& dest)
{
    bool invalid;
    do
    {
        system("cls");
        cout << "\n*** Select Destination ***" << endl;
        cout << "1.New York\t\t6.Dubai\t\t\t11.Antananariv";
        cout << "\n2.Miami\t\t\t7.Lisbon\t\t12.Cairo";
        cout << "\n3.Rio De Janeiro\t8.London\t\t13.Perth";
        cout << "\n4.Colombo\t\t9.Copenhagen\t\t14.Sydney";
        cout << "\n5.Hong Kong\t\t10.Cape Town\t\t15.Wellington" << endl;
        
        cin >> dest;
        if (dest >= 1 || dest <= 15)
        {
            invalid = false;
        }
    } while (invalid);
}

bool check_time_span(date_pack min, date_pack max, date_pack date)
{
    // check min
    if (date.year < min.year)
        return false;
    else if (date.year == min.year)
    {
        if (date.month < min.month)
            return false;
        else if (date.month == min.month)
        {
            if (date.day < min.day )
                return false;
        }
    }
    
    // check max
    if (date.year > max.year)
        return false;
    else if (date.year == max.year)
    {
        if (date.month > max.month)
            return false;
        else if (date.month == max.month)
        {
            if (date.day > max.day)
                return false;
        }
    }
    return true;
}

void print_same_destination_implement()
{
    /*
        we ask the user to enter a dates range, and a locataion by ID.
            validate the dates.
        we got over the database and find entries that match.
        as we find them we print them in a list.
    */

    // ask user to enter dates range
    date_pack min_date, max_date;
    
    system("cls");
    cout << "Please enter the dates range:" << endl;
    cout << "from: (dd mm yyyy)   ";
    get_date(min_date);
    cout << endl;
    cout << "to: (dd mm yyyy)     ";
    get_date(max_date);


    // ask user for a destintaion
    int dest;
    get_dest(dest);
    

    // print chosen details
    cout << "from --> (" << min_date.day << "/" << min_date.month << "/" << min_date.year << ")";
    cout << " to--> (" << max_date.day << "/" << max_date.month << "/" << max_date.year << ")" << endl;
    cout << "Destintaion: ";
    disembarking_name(dest);
    cout << endl << endl;
    cout << "The families that fly to the same destination are:" << endl;


    bool success_flag;
    TravelDetails t_data;
    PersonalDetails p_data;
    date_pack family_date;
    // go over database and check which families travel to chosen destination and in given time span
    for (int i = 1; i <= settings.last_travel_code; i++)
    {
        success_flag = FileManager<TravelDetails>().ReadFromFile("travel_details.bin", i, t_data);
        if (success_flag == false)
            continue;

        if (dest == t_data.disembarking_point_id)
        {
            success_flag = FileManager<PersonalDetails>().ReadFromFile("personal_details.bin", t_data.ID, p_data);
            if (success_flag == false)
                continue;
            
            /* CHECK DATE RANGE */
            family_date.year = t_data.year;
            family_date.month = t_data.month;
            family_date.day = t_data.day;
            success_flag = check_time_span(min_date, max_date, family_date);
            if (success_flag == false)
                continue;

            // print the family name
            cout << p_data.family_name << endl;
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
        cout << "3. Back" << endl;

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
        if(!settings.SaveSettings())
            system("pause");
    } while (choice != 3);
    
}

int main()
{
    Initialize();
    PersonalDetails PD;
    TravelDetails TD;

    int main_choice, opt1, opt2, opt3, opt4, *stats;
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
        cout << "\n1.New User\n2.Existing User\n\n3.Statistics\n4.Print Travels of Destination in timespan\n\n5.Settings\n6.Exit" << endl;
        cin >> main_choice;
        cin.ignore();

        switch (main_choice)
        {
        case 1:
            do
            {
                system("cls");
                cout << "\n\nNEW USER\n";
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

                    /* save personal details */
                    FileManager<PersonalDetails>().AppendToFile(_personal_details_filename, PD);

                    /* save travel details */
                    FileManager<TravelDetails>().AppendToFile(_travel_details_filename, TD);

                    system("cls");
                    cout << "\n\n\n\nYour details have been registered. please make a note of this code: " << settings.last_travel_code;
                    cout << "\n* For modifications, please see [Existing User] section in the main menu." << endl << endl;
                    system("pause");
                }
            } while (opt1 != 2);
            break;
        case 2:
            system("cls");
            cout << "\n\n** EXISTING USER **\n\nPlease enter a travel code >> ";
            cin >> acceptcode;
            if (acceptcode > settings.last_travel_code)
            {
                cout << "\nNo such record has been created." << endl << endl;
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
            cout << endl << PD.family_name << "'s FAMILY DATABASE **" << endl;
            cout << "\t\tTravel Code: " << acceptcode << endl << endl;
            system("pause");
            
            do
            {
                system("cls");
                cout << "\n\n############  Information Center  ############";
                cout << "\n\nPlease select the type of operation that you would like to perform:";
                cout << "\n1.View Personal Details\n2.View Travel Details\n3.Edit Details" << endl;
                cout << "4.Compute Bill\n\n5.Back" << endl;
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
                        cout << "\n\n\n############  Edit Details  ############";
                        cout << "\n\nPlease select from among the editing options:\n\n";
                        cout << "1.Modify\n2.Delete\n3.Back\n" << endl;
                        cin >> opt3;
                        switch (opt3)
                        {
                        case 1:
                            do
                            {
                                system("cls");
                                cout << "\n\nModificaton\n";
                                cout << "***********";
                                cout << "\n\nChoose which details you want to modify:\n1.Personal Details\n2.Travel Details\n3.Back\n" << endl;
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
                    TD.compute_expenses(PD.DiscountAvaliablity());  // check for discount and pass it further
                }
                else if (opt2 == 5)
                {
                    break;
                }
                system("pause");
            } while (main_choice != 3);
            
            break;
        case 3:
            system("cls");
			stats = Statistics();
			printStats(stats);
			system("pause");
            break;
        case 4:
            system("cls");
            print_same_destination_implement();
            system("pause");
            break;
        case 5:
            settings_menu();
            break;
        }
    } while (main_choice != 6);
    
    settings.SaveSettings();
    return 0;
}
