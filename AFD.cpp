#include "AFD.h"

void AFD::afisareAutomat()
{
	std::cout << "M=(Q{";
	for (int i = 0; i < stari.size() - 1; ++i)
		std::cout << stari[i] << ",";
	std::cout << stari[stari.size() - 1] << "}, E{";

	for (int i = 0; i < sigma.size() - 1; ++i)
		std::cout << sigma[i] << ",";
	std::cout << sigma[sigma.size() - 1] << "}, d{";

	for (int i = 0; i < delta.size() - 1; ++i)
	{
		delta[i].afisare();
		std::cout << ",";
	}
	delta[delta.size() - 1].afisare();
	std::cout << "}, ";
	std::cout << stareInitiala << ", F{";

	for (int i = 0; i < stariFinale.size() - 1; ++i)
		std::cout << stariFinale[i] << ",";
	std::cout << stariFinale[stariFinale.size() - 1] << "})\n";
	std::cout << std::endl;
}

bool AFD::validare()
{
	if (!validareAlfabet(cuvant))
		return false;
	if (!validareaStarilor())
		return false;
	if(!validareTranzitiilor())
		return false;
	if(!validareStareInitiala())
		return false;
	if(!validareStariFinale())
		return false;
	return true;
}

bool AFD::validareAlfabet(std::string cuvant)
{
	for (int i = 0; i < cuvant.size(); ++i)
	{
		if (std::find(sigma.begin(), sigma.end(), cuvant[i]) == sigma.end())
		{
			std::cout << "Cuvantul are simbolurile care nu apartin vocabularului\n";
			return false;
		}
	}
	
	return true;
}

bool AFD::validareaStarilor()
{
	std::string str = "ab";
	for (int i = 0; i < stari.size(); ++i)
	{
		if (typeid(stari[i]).name() != typeid(str).name())
		{
			std::cout << "Starea nu este string\n";
			return false;
		}
	}

	for (int i = 0; i < stari.size(); ++i)
	{
		int count = 0;
		for (int j = 0; j < stari.size(); ++j)
		{
			if (stari[i] == stari[j])
				count += 1;
			if (count > 1)
			{
				std::cout << "Starile nu sunt distincte\n";
				return false;
			}
		}
	}
	return true;
}

bool AFD::validareTranzitiilor()
{
	for (int i = 0; i < delta.size(); ++i)
	{
		if (std::find(stari.begin(), stari.end(), delta[i].getStanga()) == stari.end())
		{
			std::cout << "Tranzitii contin stari nepermise in partea stanga\n";
			return false;
		}

		if (std::find(sigma.begin(), sigma.end(), delta[i].getSimbol()) == sigma.end())
		{
			std::cout << "Tranzitii contin simboluri care nu sunt in Sigma\n";
			return false;
		}

		if (std::find(stari.begin(), stari.end(), delta[i].getDreapta()) == stari.end() && delta[i].getDreapta() != "&")
		{
			std::cout << "Tranzitii contin stari nepermise in partea dreapta\n";
			return false;
		}
	}
	
	return true;
}

bool AFD::validareStareInitiala()
{
	if (std::find(stari.begin(), stari.end(), stareInitiala) == stari.end())
	{
		std::cout << "Starea initiala nu apartine setului de stari\n";
		return false;
	}

	return true;
}

bool AFD::validareStariFinale()
{
	for (int i = 0; i < stariFinale.size(); ++i)
	{
		if (std::find(stari.begin(), stari.end(), stariFinale[i]) == stari.end())
		{
			std::cout << "Nu toate starile finale apartin setului de stari\n";
			return false;
		}
	}

	return true;
}

std::string AFD::consoleRead()
{
	std::string cuvant;
	std::cout << "Introduceti un cuvant pentru verificare: ";
	std::cin >> cuvant;

	return cuvant;
}

void AFD::citire(std::string fileName)
{
	std::ifstream in(fileName);
	int marimeaVocabularului, numarDeStari, numarDeStariFinale, numarDeTranzitii;

	in >> marimeaVocabularului;

	for (int i = 0; i < marimeaVocabularului; ++i)
	{
		char curent;
		in >> curent;
		sigma.emplace_back(curent);
	}

	in >> numarDeStari;

	for (int i = 0; i < numarDeStari; ++i)
	{
		std::string curent;
		in >> curent;
		stari.emplace_back(curent);
	}

	in >> numarDeStariFinale;

	for (int i = 0; i < numarDeStariFinale; ++i)
	{
		std::string curent;
		in >> curent;
		stariFinale.emplace_back(curent);
	}

	in >> stareInitiala;
	in >> numarDeTranzitii;

	for (int i = 0; i < numarDeTranzitii; ++i)
	{
		Delta curent;
		std::string st, dr;
		char simb;
		in >> st >> simb >> dr;
		curent.setStanga(st);
		curent.setSimbol(simb);
		curent.setDreapta(dr);
		delta.emplace_back(curent);
	}
	in.close();
}


void AFD::verificare()
{
	std::string conditiaDeIesire = "a";

	while (conditiaDeIesire != "n")
	{
		cuvant = consoleRead();
		
		if (!validare())
		{
			std::cout << "Validarea esuata!\n";
			return;
		}
		afisareAutomat();

		std::string stareaCurenta = stareInitiala;
		std::cout << "(" << stareaCurenta << "," << cuvant << ")" << " -> ";
		bool isBlocaj = false;
		for (int i = 0; i < cuvant.size(); ++i)
		{
			Delta curentDelta;
			curentDelta.setStanga(stareaCurenta);
			curentDelta.setSimbol(cuvant[i]);
			if (std::find(delta.begin(), delta.end(), curentDelta) != delta.end())
			{
				std::vector<Delta>::iterator it = std::find(delta.begin(), delta.end(), curentDelta);
				curentDelta = *it;
				stareaCurenta = curentDelta.getDreapta();
				if(cuvant.substr(i + 1) == "")
					std::cout << "(" << stareaCurenta << "," << "&" << ")" << " -> ";
				else 
					std::cout << "(" << stareaCurenta << "," << cuvant.substr(i+1) << ")" << " -> ";
				continue;
			}
			if (std::find(delta.begin(), delta.end(), curentDelta) == delta.end())
			{
				std::cout << "blocaj\n";
				isBlocaj = true;
				break;
			}	
		}
		if (std::find(stariFinale.begin(), stariFinale.end(), stareaCurenta) != stariFinale.end() && !isBlocaj)
			std::cout << "acceptat\n";
		if (std::find(stariFinale.begin(), stariFinale.end(), stareaCurenta) == stariFinale.end() && !isBlocaj)
			std::cout << "respins\n";
		
		std::cout << "Daca vreti sa iesiti apasati litera (n) altfel orice alta litera: ";
		std::cin >> conditiaDeIesire;
		std::cout << std::endl;
	}
}
