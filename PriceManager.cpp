#include "PriceManager.h"


/* Utility function for filling a pricesheet. */
void Fill_PriceSheet(PriceSheet& out_sheet)
{
    cout << "Please enter only numeric values, no checks are implemented!" << endl << endl;

    cout << "Destination ID: ";
    std::cin >> out_sheet.ID;

    cout << "Destination Ticket Base Price: ";
    std::cin >> out_sheet.destination_ticket;

    cout << "Reservation Period: ";
    std::cin >> out_sheet.reservation_period;

    cout << "Swimming Pool: ";
    std::cin >> out_sheet.swimming_pool;

    cout << "Gym: ";
    std::cin >> out_sheet.gym;

    cout << "Sport Facilities: ";
    std::cin >> out_sheet.other_sports;

    cout << "Spa Salon: ";
    std::cin >> out_sheet.spa;

    cout << "Beauty Salon: ";
    std::cin >> out_sheet.beauty_salon;

    cout << endl << endl;
}

/* Wrapper for adding a new pricesheet. */
bool Add_PriceSheet(PriceSheet& sheet)
{
    return FileManager<PriceSheet>().AppendToFile(_pricesheets_filename, sheet);
}

/* Wrapper for editing an existing pricesheet. */
bool Edit_PriceSheet(PriceSheet& sheet)
{
    return FileManager<PriceSheet>().InsertToFile(_pricesheets_filename, sheet, sheet.ID);
}

/* Wrapper for removing an existing pricesheet. */
bool Remove_PriceSheet(PriceSheet& sheet)
{
    return FileManager<PriceSheet>().DeleteFromFile(_pricesheets_filename, sheet.ID);
}

/* Wrapper for pulling a pricesheet. */
bool Get_PriceSheet(int sheet_id, PriceSheet& out_sheet)
{
    return FileManager<PriceSheet>().ReadFromFile(_pricesheets_filename, sheet_id, out_sheet);
}
