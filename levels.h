#ifndef LEVELS_H
#define LEVELS_H
#include <iostream>
#include <vector>
#include "enums.h"

using namespace std;
class Levels
{
	public:
		Levels();

	void getLevel(vector<vector<Tile>> *tile, int levelnum);
	int getLevelX();
	int getLevelY();

	private:
	int X[60];
	int Y[60];
	vector<vector<string>> level= vector<vector<string>>(60);

};

#endif // LEVELS_H
