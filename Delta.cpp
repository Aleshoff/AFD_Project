#include "Delta.h"

std::string Delta::getDreapta()
{
    return dreapta;
}

std::string Delta::getStanga()
{
    return stanga;
}

char Delta::getSimbol()
{
    return simbol;
}

void Delta::setDreapta(std::string dreapta)
{
    this->dreapta = dreapta;
}

void Delta::setStanga(std::string stanga)
{
    this->stanga = stanga;
}

void Delta::setSimbol(char simbol)
{
    this->simbol = simbol;
}

void Delta::afisare()
{
    std::cout << stanga << "->" << simbol << "->" << dreapta;
}

bool Delta::operator==(const Delta& delta)
{
    if (stanga == delta.stanga && simbol == delta.simbol)
        return true;
    return false;
}

