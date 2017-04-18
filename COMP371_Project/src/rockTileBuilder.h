/**
rockTileBuilder.h
Purpose: Subclass of rockBuilder.h, builds a tile of
type ROCK and sets its parameters randomly
and then calculates all the resulting vertices.

@super tileBuilder.h
@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/
#pragma once
#include "stdafx.h"
#include "tileBuilder.h"
#include "rockTile.h"
class rockTileBuilder : public tileBuilder
{
public:
	//Parameter constructor, no default constructor, takes an initialized shader and a position
	rockTileBuilder(Shader * shader, glm::vec3 * position, vector<vector<tile*>> * data, int i, int j);
	/*
	*				BUILDER
	*	(builds each component of a tile)
	*/
	virtual void buildType();
	virtual void buildVertices();
	virtual void buildDrawType();
	virtual void buildShader();
	virtual void buildPosition();
	virtual void createTile();

private:
	//Initializes by checking the tiles around it and setting the right heights at its borders
	void initializeGrid();
	//Fills the tiles in the grid that needs to be filled by doing an up/down and left/right pass
	void fillGrid();
	//Transforms the grid into a vertices matrix by creating a long strip that coils and creates the terrain
	vector<GLfloat> * convertGrid();

	/*
	*				SETTERS
	*	(Methods to set all the necessary borders
	*	of the grid by checking the surrounding tiles)
	*/
	void setUp(unsigned int type);
	void setDown(unsigned int type);
	void setLeft(unsigned int type);
	void setRight(unsigned int type);

	/*
	*				FILLERS
	*	(Methods to fill the grid by doing the necessary
	*	passes. (at least one up/down and left/right)
	*/
	void fillLeft();
	void fillRight();
	void fillUp();
	void fillDown();
	void fillLeftRight();
	void fillUpDown();

	/*Formula to generate a random value with a 50% chance 
	* of being positive. It is later added to the previous 
	* height for proper continuity*/
	float random();
	
	//usedData
	vector<vector<tile*>> * _data;
	//Position in usedData
	int _i, _j;
	//up/down and left/right fill grids
	vector<vector<GLfloat>> fillUD, fillLR;
	//bool values to know which pass to do
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	//Grid size (low value = less weaving)
	const int _size = 4;
};