#pragma once


/*
fields:
    ID - each travel entry has 'unique' id by which the details can be accessed
    day,month,year - fields represent the date of departure
    boarding_point_id - id of boarding location for ease of managing
    disembarking_point_id - id of disembarking location for ease of managing
    flight_class - flight class id, affects prices and available activities
    adults_count - amount of adults in family
    pool, gym, sports, salon, spa - boolean values of activities

methods:
    t_input(travel_code) - function gets the TravelCode as arg, and collects travel details from input
    t_output() - function prints travel details
    compute_expenses() - function calculates total travel expenses, reservation time, and prints a receipt
    get_travel_code() - Get TravelCode, which is ID
    update_adults(count) - function gets number of adult family members as arg, adults_count
    boarding_name(id) - function gets BoardingPoint as arg, prints name of boarding location
    disembarking_name(id) - function gets DisembarkingPoint as arg, prints name of disembarking location

*/
struct TravelDetails
{
    int ID, boarding_point_id, disembarking_point_id;
    int flight_class, day, month, year, adults_count = 0;
    bool pool = false, gym = false, sports = false, salon = false, spa = false;
    
    void t_input(int travel_code);
    void t_output();
    void compute_expenses();
    int get_travel_code();
    void update_adults(int count);
};

void boarding_name(int id);
void disembarking_name(int id);
