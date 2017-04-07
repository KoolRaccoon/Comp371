#pragma once
#include "tile.h"

class tileBuilder
{
public:
	tileBuilder(Shader * s, glm::vec3 * pos)
	{
		_shader = s;
		_position = pos;
	}
	//Accessor
	tile * getTile()
	{
		return _tile;
	}
	//Single call to create a tile
	virtual void createTile() = 0;
	virtual void buildType() = 0;
	virtual void buildVertices() = 0;
	virtual void buildDrawType() = 0;
	virtual void buildShader() = 0;
	virtual void buildPosition() = 0;
	void build()
	{
		buildType();
		buildVertices();
		buildDrawType();
		buildShader();
		buildPosition();
	}

protected:
	tile * _tile;
	Shader * _shader;
	glm::vec3 * _position;

};