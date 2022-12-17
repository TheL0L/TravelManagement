#pragma once
#include <iostream>
#include "FileManager.h"
#include "PriceSheet.h"

#define _filename "price_sheets.bin"


/* Wrapper for adding a new pricesheet. */
bool Add_PriceSheet(const PriceSheet& sheet);

/* Wrapper for editing an existing pricesheet. */
bool Edit_PriceSheet(const PriceSheet& sheet);

/* Wrapper for removing an existing pricesheet. */
bool Remove_PriceSheet(const PriceSheet& sheet);

/* Wrapper for pulling a pricesheet. */
bool Get_PriceSheet(int sheet_id, PriceSheet& out_sheet);
