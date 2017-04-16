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
	
private:
	vector<building*> * _buildings;
};