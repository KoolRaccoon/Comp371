/**
Circle.h
Purpose: Generates a circle with a random radius,
		a random h and k translation. Also allows to
		check if a 2D position is inside itself

@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/
#pragma once
#include <random>
#include <math.h>
class circle
{
public:
	//Default constructor
	circle()
	{
		//Creates a random circle and prints its position
		_r = rand() % 10 + 5;
		_k = -30 + rand() % 60;
		_h = -30 + rand() % 60;
		cout << _k << " " << _h << " " << _r << endl;
	}
	~circle() {}
	//Checks if the given position is inside itself
	bool checkIfInside(int x, int z)
	{
		//Equation of the area of a circle : (x-h)^2 + (z-k)^2 <= r^2
		if (pow(x - (_h), 2) + pow(z - (_k), 2) <= pow(_r, 2))
			return true;
		else
			return false;
	}

private:
	int _h;
	int _k;
	int _r;
};