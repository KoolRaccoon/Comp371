/**
rockTile.h
Purpose: Subclass of tile.h, adds a grid of height
		that represents terrain at each point of the grid
		inside the tile. Also contains the method to check
		if the position is over its terrain

@super tile.h
@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/

#pragma once
#include "tile.h"
#include "stdafx.h"

class rockTile : public tile
{
public:
	//Defaut Constructor
	rockTile():tile(){this->setTileType(ROCK);}

	//Default Destructor
	~rockTile()
	{
		delete _grid;
		_grid = nullptr;
	}
	// *Accessor* Returns a pointer to its grid
	virtual vector<vector<GLfloat>> * getGrid(){return _grid;}
	
	// *Mutator* Sets the grid as the parameter
	virtual void setGrid(vector<vector<GLfloat>> * grid) { _grid = grid; }
	
	//Returns true if the position is under the terrain
	virtual bool checkCollision(glm::vec3 * position)
	{
		//Finds the square around the position
		int posx1 = (int)(position->x + 0.5);
		int posx2 = posx1 + 1;
		int posz1 = (int)(position->z + 0.5);
		int posz2 = posz1 + 1;

		//Calculates the average height at that square
		float avgH = (*_grid)[posx1][posz1] +
			(*_grid)[posx1][posz2] +
			(*_grid)[posx2][posz1] +
			(*_grid)[posx2][posz2];
		avgH = avgH / 4;

		//Returns true if the position is under the average + an offset
		if ((avgH + 0.8f) > position->y)
			return true;
		else
			return false;	
	}
private:
	vector<vector<GLfloat>> * _grid;
};