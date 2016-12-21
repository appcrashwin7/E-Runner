#include "IOoperator.hpp"

#include <fstream>

IOoperator::IOoperator()
{}

IOoperator::~IOoperator()
{
}

void IOoperator::getScoreFromFile(std::string score[10])
{
	std::fstream file;
	file.open("bestRaces.txt", std::ios::in);
	if (file.good() == false)
	{
	}
	else
	{
		int num = 0;
		while (!file.eof())
		{
			std::getline(file, score[num]);
			num++;
		}
	}
}
