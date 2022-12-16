#include <iostream>
#include "FileManager.cpp"
#include "PriceSheet.h"

#define _filename "price_sheets.bin"
using namespace std;

bool Add_PriceSheet(const PriceSheet& sheet)
{
    return FileManager<PriceSheet>().AppendToFile(_filename, sheet);
}

bool Edit_PriceSheet(const PriceSheet& sheet)
{
    return FileManager<PriceSheet>().InsertToFile(_filename, sheet, sheet.ID);
}

bool Remove_PriceSheet(const PriceSheet& sheet)
{
    return FileManager<PriceSheet>().DeleteFromFile(_filename, sheet.ID);
}

bool Get_PriceSheet(int sheet_id, PriceSheet& out_sheet)
{
    return FileManager<PriceSheet>().ReadFromFile(_filename, sheet_id, out_sheet);
}
