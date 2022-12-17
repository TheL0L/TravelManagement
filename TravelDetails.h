#pragma once
#include <iostream>
using namespace std;

/*
fields:
    TravelCode - each travel entry has 'unique' id by which the details can be accessed
    day,month,year - fields represent the date of departure
    num1 - number of adult family members
    BoardingPoint - id of boarding location for ease of managing
    DisembarkingPoint - id of disembarking location for ease of managing
    Class - flight class id, affects prices and available activities
    pool, gym, sports, salon, spa - boolean values of activities

methods:
    initial() - function resets the boolean fields to 0
    t_input(cd) - function gets the TravelCode as arg, and collects travel details from input
    t_output() - function prints travel details
    compute() - function calculates total travel expenses, reservation time, and prints a receipt
    gtcode() - function returns TravelCode
    accept(c) - function gets number of adult family members as arg, and assigns value to num1
    boardpt(c) - function gets BoardingPoint as arg, prints name of boarding location
    dest(d) - function gets DisembarkingPoint as arg, prints name of disembarking location

*/

void boardpt(int c);
void dest(int d);

class TravelDetails
{
    int TravelCode, day, month, year, num1, BoardingPoint, DisembarkingPoint;
    int Class, pool, gym, sports, salon, spa;

public:
    void initial();
    void t_input(int cd);
    void t_output();
    void compute();
    int gtcode();
    void accept(int);
} TD;

