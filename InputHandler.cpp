#include "InputHandler.h"

/* Read a string with spaces after cin>> inputs.
In case there were no such previous inputs,
the function will wait for two inputs and discard the first. */
void StringInput(char* buffer, int max_length)
{
    // flush input buffer, if empty will wait for input then gobble it
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // write to buffer up to max_length characters or until \n seen
    cin.getline(buffer, max_length, '\n');

    // check for fails, main reason is input_length > max_length
    while (cin.fail())
    {
        cout << "Your input exeeds max length, please keep it shorter than ";
        cout << (max_length - 1) << " characters." << endl;

        cin.clear();  // clear input flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(buffer, max_length, '\n');
    }
}
