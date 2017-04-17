#pragma once

#include "tile.h"
#include "stdafx.h"

class cityTile : public tile
{
public:
	cityTile() :tile() 
	{ 
		this->setTileType(CITY); 
		_buildings = new vector<building*>;
	}
	~cityTile()
	{
		delete _buildings;
		_buildings = nullptr;
	}
	virtual vector<building*> * getBuildings() { return _buildings; }
	virtual void addBuilding(building * building) { _buildings->push_back(building); }
	virtual bool checkCollision(glm::vec3 * position) 
	{
		bool inside = false;
		for (int i = 0; i < _buildings->size(); i++)
			inside = inside || (*_buildings)[i]->checkIfInside(position);
		if (position->y <= 0.18f)
			inside = true;
		return inside;
	}
private:
	vector<building*> * _buildings;
};