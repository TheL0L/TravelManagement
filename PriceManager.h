#pragma once
#include <iostream>
#include "FileManager.h"
#include "PriceSheet.h"

#define _pricesheets_filename "price_sheets.bin"


/* Utility function for filling a pricesheet. */
void Fill_PriceSheet(PriceSheet& out_sheet);

/* Wrapper for adding a new pricesheet. */
bool Add_PriceSheet(PriceSheet& sheet);

/* Wrapper for editing an existing pricesheet. */
bool Edit_PriceSheet(PriceSheet& sheet);

/* Wrapper for removing an existing pricesheet. */
bool Remove_PriceSheet(PriceSheet& sheet);

/* Wrapper for pulling a pricesheet. */
bool Get_PriceSheet(int sheet_id, PriceSheet& out_sheet);
