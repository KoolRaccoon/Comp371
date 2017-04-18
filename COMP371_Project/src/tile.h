/**
tile.h
Purpose: Contains the necessary data to be drawn on screen.
		Also contains const data to represent tile types

@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/

#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "building.h"
const unsigned int EMPTY = 0;
const unsigned int CITY = 1;
const unsigned int ROCK = 2;

using namespace std;
class tile
{
public:
	//Default constructor with type = EMPTY
	tile();
	//Default destructor
	~tile();

	/*
	*	ACCESSORS
	*/

	//Returns the tile's type which is a const value in tile.h
	unsigned int tileType();
	//Returns the drawtype in GLemun, for example GL_TRIANGLES
	GLenum drawType();
	//Returns a pointer to the vertices
	vector<GLfloat> * getVertices();
	//Returns a pointer to the shader which are all initialized in the main.cpp
	Shader * getShader();
	//Returns a pointer to the position of the tile, you can also use x and z
	glm::vec3 * getPosition();
	//Returns true if the position inside a collision. Calls the right method dynamically
	virtual bool checkCollision(glm::vec3 * position) { return false; }
	//Calls rockTile's getGrid or returns a nullptr
	virtual vector<vector<GLfloat>> * getGrid() { return nullptr; };
	//Calls cityTile's getBuildings or returns a nullptr
	virtual vector<building*> * getBuildings() { return nullptr; };

	/*
	*			MUTATORS
	*	(only used by the builders)
	*/
	void setTileType(unsigned int tileType);
	void setDrawType(GLenum drawType);
	void setShader(Shader * shader);
	void setVertices(vector<GLfloat> * vertices);
	void setPosition(glm::vec3 * position);
	void setTextures(GLuint &t1, GLuint &t2);
	virtual void setGrid(vector<vector<GLfloat>> * grid) {};
	virtual void addBuilding(building * building) {};
	
	//Returns position.x;
	int x;
	//Returns position.z;
	int z;

private:
	vector<GLfloat> * vertices;
	glm::vec3 * position;
	unsigned int type;
	Shader * shader;
	GLenum drawtype;
};