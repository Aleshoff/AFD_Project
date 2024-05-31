#pragma once
#include"Delta.h"
#include <iostream>
#include<vector>
#include<fstream>
#include <typeinfo>

class AFD
{
private:
	std::string stareInitiala, cuvant;
	std::vector<std::string> stari, stariFinale;
	std::vector<char> sigma;
	std::vector<Delta> delta;

	void afisareAutomat();
	bool validare();
	bool validareAlfabet(std::string);
	bool validareaStarilor();
	bool validareTranzitiilor();
	bool validareStareInitiala();
	bool validareStariFinale();
	std::string consoleRead();

public:
	void citire(std::string);
	void verificare();
	
};

