#include "Currency.h"

Currency::Currency()
{
    this->value = 0;
    this->type = CurrencyType::USD;
}

Currency::Currency(float value, CurrencyType type = CurrencyType::USD)
{
    this->value = value;
    this->type = type;
}

Currency::Currency(Currency& other)
{
    this->value = other.value;
    this->type = other.type;
}

void Currency::ChangeType(CurrencyType type)
{
    this->type = type;
}

float Currency::ConvertTo(CurrencyType type) const
{
    return this->value * Rates[type - 1];
}

float Currency::operator=(float value)
{
    return (this->value = value);
}

float Currency::operator+(float operand)
{
    return this->value + operand;
}

float Currency::operator-(float operand)
{
    return this->value - operand;
}

float Currency::operator*(float operand)
{
    return this->value * operand;
}

float Currency::operator/(float operand)
{
    /* instead of throwing errors, return obviously wrong value. */
    if (operand == 0)
        return 1;
    
    return this->value / operand;
}

void Currency::operator+=(float value)
{
    this->value += value;
}

void Currency::operator-=(float value)
{
    this->value -= value;
}

std::ostream& operator<<(std::ostream& os, const Currency& data)
{
    os << data.ConvertTo(data.type);

    switch (data.type)
    {
    case CurrencyType::USD:
        os << " USD";
        break;
    case CurrencyType::Rupee:
        os << " Rupee";
        break;
    case CurrencyType::Shekel:
        os << " Shekel";
        break;
    case CurrencyType::RUB:
        os << " RUB";
        break;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Currency& data)
{
    return is >> data.value;
}

Currency::operator float() const
{
    return this->value;
}

int PickAvailableCurrency()
{
    int choice;
    do
    {
        std::cout << "1. USD" << std::endl;
        std::cout << "2. Rupee" << std::endl;
        std::cout << "3. Shekel" << std::endl;
        std::cout << "4. RUB" << std::endl;

        std::cin >> choice;
        std::cin.ignore();  // in case a non numeric input is recieved

        if (1 <= choice && choice <= 4)
            break;
    } while (true);
    
    return choice;
}

