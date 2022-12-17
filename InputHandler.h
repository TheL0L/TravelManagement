#pragma once
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;

/* Read a string with spaces after cin>> inputs.
In case there were no such previous inputs,
the function will wait for two inputs and discard the first. */
void StringInput(char* buffer, int max_length);
void StringInput_no_flushing(char* buffer, int max_length);
