#include "PriceManager.h"


/* Wrapper for adding a new pricesheet. */
bool Add_PriceSheet(const PriceSheet& sheet)
{
    return FileManager<PriceSheet>().AppendToFile(_filename, sheet);
}

/* Wrapper for editing an existing pricesheet. */
bool Edit_PriceSheet(PriceSheet& sheet)
{
    return FileManager<PriceSheet>().InsertToFile(_filename, sheet, sheet.ID);
}

/* Wrapper for removing an existing pricesheet. */
bool Remove_PriceSheet(const PriceSheet& sheet)
{
    return FileManager<PriceSheet>().DeleteFromFile(_filename, sheet.ID);
}

/* Wrapper for pulling a pricesheet. */
bool Get_PriceSheet(int sheet_id, PriceSheet& out_sheet)
{
    return FileManager<PriceSheet>().ReadFromFile(_filename, sheet_id, out_sheet);
}
