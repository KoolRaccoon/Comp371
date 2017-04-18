#pragma once
#include <random>
#include <math.h>
class circle
{
public:
	circle()
	{
		_r = rand() % 10 + 5;
		_k = -30 + rand() % 60;
		_h = -30 + rand() % 60;
		cout << _k << " " << _h << " " << _r << endl;
	}
	~circle() {}
	bool checkIfInside(int x, int z)
	{
		//(x-h)2 + (y-k)2 = r2
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