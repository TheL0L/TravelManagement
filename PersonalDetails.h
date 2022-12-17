#pragma once


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


struct PersonalDetails // class for collecting the personal details
{
    int TravelCode, age[20], num, numppl;
    char Name[20][20], Address[50], PhoneNumber[15], gender[20], PassportNum[9][9], FamilyName[30];

    void p_input(int cd);
    void p_output();
    void givefam();
    int givecode();
    int givenum();
};

