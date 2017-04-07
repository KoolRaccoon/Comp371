#include "cityTileBuilder.h"


cityTileBuilder::cityTileBuilder(Shader * s, glm::vec3 * p) :tileBuilder(s, p){}

void cityTileBuilder::buildType()
{
	_tile->setTileType(CITY);
}

void cityTileBuilder::buildVertices()
{
	// Creates the floor of the tile with two triangles
	GLfloat vertices[] = {
		//Square
		//Bottom triangle
		// Positions          //Temporary Texture Coords
		0.5f,   0.0f,  0.5f,   1.0f, 1.0f,   // Top Right
		0.5f,  0.0f,   -0.5f,  1.0f, 0.0f,   // Bottom Right
		-0.5f,   0.0f, 0.5f,   0.0f, 1.0f,    // Top Left 

		//Top triangle
		0.5f,  0.0f, -0.5f,    1.0f, 0.0f,   // Bottom Right
		-0.5f,  0.0f, -0.5f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,   0.0f, 0.5f,    0.0f, 1.0f    // Top Left
	};
	//Converts the array into a vector
	vector<GLfloat> * v = new vector<GLfloat>(vertices, vertices + sizeof vertices / sizeof vertices[0]);
	//Sets the vertice matrix of the tile
	_tile->setVertices(v);
}

void cityTileBuilder::buildDrawType()
{
	_tile->setDrawType(GL_TRIANGLES);
}

void cityTileBuilder::buildShader()
{
	_tile->setShader(_shader);
}

void cityTileBuilder::buildPosition()
{
	_tile->setPosition(_position);
}

void cityTileBuilder::createTile()
{
	_tile = new tile;
	build();
}
