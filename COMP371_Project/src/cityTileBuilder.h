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
	void _createBuildings(vector<GLfloat> * vertices);
	void _singleBuilding(vector<GLfloat> * vertices);
	void _dualBuilding(vector<GLfloat> * vertices);
	void _tripleBuilding(vector<GLfloat> * vertices);
	void _quadBuilding(vector<GLfloat> * vertices);
	void _rotateBuilding(vector<glm::vec3> * building);
	void _convertToVertices(vector<GLfloat> * vertices, float height);
	float randHeight();
	float randQuarterSize();
	float randHalfSize();
	float randQuarterQuad(float value, float smallestPosition, float offset);
	float randHalfQuad(float val);
};