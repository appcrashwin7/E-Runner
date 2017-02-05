#pragma once
#include <fstream>

class IOoperator
{
	const std::string nameOfFile = "bestRaces.txt";
	std::string rawScores[10]={""};

	int scores[10] = {0};
	std::string names[10] = {""};

public:
	IOoperator();
	~IOoperator();

	void loadScoreFromFile();
	void insertNewScore(std::string name,int &score);
	void saveScoreToFile();
	void divideRawToScoresAndNames();

	bool thisScoreIsEnough(int score);

	std::string getRawData(size_t a);
};