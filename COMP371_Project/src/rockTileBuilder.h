#pragma once
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
	void initializeGrid();
	void fillGrid();
	vector<GLfloat> * convertGrid();
	void setUp(unsigned int type);
	void setDown(unsigned int type);
	void setLeft(unsigned int type);
	void setRight(unsigned int type);

	void fillBottomLeft();
	void fillBottomRight();
	void fillTopLeft();
	void fillTopRight();

	vector<vector<tile*>> * _data;
	int _i, _j;
	vector<vector<GLfloat>> fill1, fill2;
	const int _size = 5;
};