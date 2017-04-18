/**
cityTile.h
Purpose: Subclass of Tile.h, adds a building list to it
		and a specific collision detection method

@super Tile.h
@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/

#pragma once

#include "tile.h"
#include "stdafx.h"

class cityTile : public tile
{
public:
	//Default constructor
	cityTile() :tile() 
	{ 
		//sets type as CITY and initializes the list of buildings
		this->setTileType(CITY); 
		_buildings = new vector<building*>;
	}
	//Default destructor
	~cityTile()
	{
		delete _buildings;
		_buildings = nullptr;
	}
	//Returns the list of buildings
	virtual vector<building*> * getBuildings() { return _buildings; }
	
	//Adds a building to the current list
	virtual void addBuilding(building * building) { _buildings->push_back(building); }
	
	/*Scrolls through each building and checks 
	* if position is inside one of them. If it is,
	* the method returns true.*/
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