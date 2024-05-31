#include "AFD.h"

int main()
{
    std::string fileName = "Data.txt";
    AFD afd;
    afd.citire(fileName);
    afd.verificare();
}
