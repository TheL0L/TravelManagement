#pragma once
#include <iostream>

enum CurrencyType {USD, Rupee, Shekel, RUB};
const float Rates[] = {1.0f, 82.86f, 3.44f, 64.65};

/* Class for managing currency. */
class Currency
{
private:
    float value;  // amount, always given in USD
    CurrencyType type;  // coin type, used for output formatting

public:
    Currency();
    Currency(float value, CurrencyType type);
    Currency(Currency& other);

    void ChangeType(CurrencyType type);
    float ConvertTo(CurrencyType type) const;

    float operator=(float value);
    float operator+(float operand);
    float operator-(float operand);
    float operator*(float operand);
    float operator/(float operand);

    explicit operator float() const;

    /* allows streaming currency to output streams. */
    friend std::ostream& operator<<(std::ostream& os, const Currency& data);
    /* allows changing value from input streams. */
    friend std::istream& operator>>(std::istream& is, Currency& data);
};

/* Print available currencies, made for settings menu. */
void PrintAvailable();

