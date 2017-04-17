#pragma once
#include "tile.h"
#include "stdafx.h"

class rockTile : public tile
{
public:
	rockTile():tile(){this->setTileType(ROCK);}
	~rockTile()
	{
		delete _grid;
		_grid = nullptr;
	}
	virtual vector<vector<GLfloat>> * getGrid(){return _grid;}
	virtual void setGrid(vector<vector<GLfloat>> * grid) { _grid = grid; }
	virtual bool checkCollision(glm::vec3 * position)
	{
		int posx1 = (int)(position->x + 0.5);
		int posx2 = posx1 + 1;
		int posz1 = (int)(position->z + 0.5);
		int posz2 = posz1 + 1;

		float avgH = (*_grid)[posx1][posz1] +
			(*_grid)[posx1][posz2] +
			(*_grid)[posx2][posz1] +
			(*_grid)[posx2][posz2];
		avgH = avgH / 4;
		if (avgH < position->z)
			return true;
		else
			return false;	
	}
private:
	vector<vector<GLfloat>> * _grid;
};