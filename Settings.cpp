#include "Settings.h"
#include "FileManager.h"


Settings::Settings()
{
	this->last_travel_code = 0;
	this->default_currency = 1;
}

/* Save settings to file. */
bool Settings::LoadSettings()
{
	return FileManager<Settings>().ReadFromFile_at_offset(_settings_filename, 0, *this);
}

/* Load settings from file. */
bool Settings::SaveSettings()
{
	return FileManager<Settings>().InsertToFile_at_offset(_settings_filename, *this, 0);
}

/* Load ONLY travel code. */
void Settings::LoadTravelCode()
{
	Settings buffer;
	buffer.LoadSettings();
	this->last_travel_code = buffer.last_travel_code;
}

/* Save ONLY travel code. */
void Settings::SaveTravelCode()
{
	Settings buffer;
	buffer.last_travel_code = this->last_travel_code;
	buffer.SaveSettings();
}

