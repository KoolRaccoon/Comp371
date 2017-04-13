#pragma once
#include "stdafx.h"
#include "tileBuilder.h"
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
	void _createBuilding(vector<GLfloat> * vertices);
};