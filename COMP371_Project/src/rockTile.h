#pragma once
#include "tile.h"
#include "stdafx.h"

class rockTile : public tile
{
public:
	rockTile():tile(){this->setTileType(ROCK);}
	~rockTile();
	virtual vector<vector<GLfloat>> * getGrid(){return _grid;}
	virtual void setGrid(vector<vector<GLfloat>> * grid) { _grid = grid; }
private:
	vector<vector<GLfloat>> * _grid;
};