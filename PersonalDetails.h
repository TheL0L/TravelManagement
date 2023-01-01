#pragma once


/*
fields:
    ID - each travel entry has 'unique' id by which the details can be accessed
    ages[] - array of family member ages
    children_count - number of kids in family
    members_count - total number of family members (adults + kids)
    names[] - array of family member names
    address[] - string containing family address
    phone_number[] - string containing contact phone number for the family
    genders[] - char array containing M/F as gender representaion of family members
    passports[] - array of strings containing passport numbers of family members
    family_name[] - string representing the family name

methods:
    p_input(travel_code) - function gets the TravelCode as arg, and collects family details from input
    p_output() - function prints family details
    adults_count() - Get number of adults
    get_travel_code() - Get TravelCode, which is ID

*/
struct PersonalDetails // class for collecting the personal details
{
    int ID, ages[20], bday[20], bmonth[20], children_count, members_count;
    char names[20][20], address[50], phone_number[15], genders[20], passports[20][9], family_name[30];

    void p_input(int travel_code);
    void p_output();
    int adults_count();
    int get_travel_code();
    int DiscountAvaliablity();
};

