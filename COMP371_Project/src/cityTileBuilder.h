/**
cityTileBuilder.h
Purpose: Subclass of tileBuilder.h, builds a tile of
		type CITY and sets its parameters randomly
		and then calculates all the resulting vertices.

@super tileBuilder.h
@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/

#pragma once
#include "stdafx.h"
#include "tileBuilder.h"
#include "cityTile.h"

class cityTileBuilder : public tileBuilder
{
public:
	//Parameter constructor, no default constructor, takes an initialized shader and a position
	cityTileBuilder(Shader * shader, glm::vec3 * position);
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
	/*
	*				BUILDING CREATORS
	*		(builds one of four building setups)
	*/
	void _createBuildings(vector<GLfloat> * vertices);
	void _singleBuilding();
	void _dualBuilding();
	void _tripleBuilding();
	void _quadBuilding();

	//Was not implemented
	void _rotateBuilding(vector<glm::vec3> * building);

	//Converts the tile's buildings to vertices
	void _convertToVertices(vector<GLfloat> * vertices);
	//Converts a building and pushes the vertices to tile's vertices vector
	void _convertBuilding(vector<GLfloat> * vertices, building * building);
	//Converts the top half of the tile
	void _convertTopHalf(vector<GLfloat> * vertices, building * building);
	//Converts the bottom half of the tile
	void _convertBotHalf(vector<GLfloat> * vertices, building * building);
	//Returns a random height
	float randHeight();
	//Returns a size that fits inside a quarter of a tile
	float randQuarterSize();
	//Returns a size that fits inside half of a tile
	float randHalfSize();
	//Returns a 1D position that fits inside a quarter of a tile
	float randQuarterQuad(float value, float smallestPosition, float offset);
	//Returns a 1D position that fits inside half of a tile
	float randHalfQuad(float val);
	
};