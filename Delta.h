#pragma once
#include<string>
#include <iostream>
class Delta
{
private:
	std::string dreapta, stanga;
	char simbol;

public:
	std::string getDreapta();
	std::string getStanga();
	char getSimbol();
	void setDreapta(std::string);
	void setStanga(std::string);
	void setSimbol(char);
	void afisare();
	bool operator ==(const Delta& delta);
};

