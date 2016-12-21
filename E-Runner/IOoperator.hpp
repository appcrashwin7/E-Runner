#pragma once

#include <string>

class IOoperator
{
public:
	IOoperator();
	~IOoperator();

	void getScoreFromFile(std::string score[10]);
	void SaveScore(std::string newSc[10]);
};