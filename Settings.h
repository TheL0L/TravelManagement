#pragma once

#define _settings_filename "settings.bin"


struct Settings
{
    int last_travel_code;
    int default_currency;

    Settings();
    /* Save settings to file. */
    void LoadSettings();
    /* Load settings from file. */
    void SaveSettings();
    /* Load ONLY travel code. */
    void LoadTravelCode();
    /* Save ONLY travel code. */
    void SaveTravelCode();
};

