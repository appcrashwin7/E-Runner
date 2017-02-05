#include "IOoperator.hpp"
#include <iostream>
#include <string>
#include <sstream>


IOoperator::IOoperator()
{}

IOoperator::~IOoperator()
{}

void IOoperator::loadScoreFromFile()
{
	std::ifstream File;
	File.open(nameOfFile);
	if (File.good() != true)
	{
		std::cout << "file.txt isn't exist!" << std::endl;
		return;
	}
	size_t l = 0;
	while (std::getline(File, rawScores[l]))
	{
		if (l == 10)
		{
			break;
		}
		l++;
	}
	File.close();
}

void IOoperator::insertNewScore(std::string name, int &score)
{
	size_t i = 9;
	while (score > scores[i])
	{
		if (i < 9)
		{
			scores[i + 1] = scores[i];
			names[i + 1] = names[i];
		}
		i--;
		if (i == -1)
		{
			break;
		}
	}
	scores[i + 1] = score;
	names[i + 1] = name;
}

void IOoperator::saveScoreToFile()
{
	std::ofstream File;
	File.open(nameOfFile,std::ios::trunc);

	for (size_t i = 0; i < 10; i++)
	{
		File << names[i] << ":" << scores[i] << std::endl;
	}

	File.close();
}

void IOoperator::divideRawToScoresAndNames()
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < rawScores[i].size(); j++)
		{
			if (rawScores[i][j] == ':')
			{
				names[i] = rawScores[i].substr(0, j);
				std::istringstream sc(rawScores[i].substr(j + 1, rawScores[i].size()));
				sc >> scores[i];
				break;
			}
		}
	}
}

bool IOoperator::thisScoreIsEnough(int score)
{
	if (score > scores[9])
	{
		return true;
	}
	
	return false;
}

std::string IOoperator::getRawData(size_t a)
{
	return rawScores[a];
}
