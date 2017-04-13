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
		-0.5f,  0.0f, -0.5f,   0.0f, 0.0f,   // Bottom Left
		-0.5f,   0.0f, 0.5f,    0.0f, 1.0f,    // Top Left
		0.5f,  0.0f,   -0.5f,  1.0f, 0.0f,   // Bottom Right
		0.5f,   0.0f,  0.5f,   1.0f, 1.0f,   // Top Right
		//Invisible triangle to avoid mesh creation between strips
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		
		/*//Bottom triangle
		// Positions          //Temporary Texture Coords
		
		
		-0.5f,   0.0f, 0.5f,   0.0f, 1.0f,    // Top Left 

		//Top triangle
		0.5f,  0.0f, -0.5f,    1.0f, 0.0f,   // Bottom Right
		*/
		
	};
	//Converts the array into a vector
	vector<GLfloat> * v = new vector<GLfloat>(vertices, vertices + sizeof vertices / sizeof vertices[0]);
	//Sets the vertice matrix of the tile
	_createBuilding(v);
	_tile->setVertices(v);
}

void cityTileBuilder::buildDrawType()
{
	_tile->setDrawType(GL_TRIANGLE_STRIP);
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

void cityTileBuilder::_createBuilding(vector<GLfloat>* v)
{
	//size of one side of the square
	float size = 0.5f;
	//center of the building
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	//random height between 0.01 and 3.00
	float height = (rand() % 300 + 1) / 100.0f;

	/*	top view of the calls
	*		.---------->.
	*		^			|
	*		|			v
	*start->.<----------.
	*/

	//From top view, push bottom left, up and down
	for (int i = 0; i <= 1; i++)
	{
		v->push_back(center.x - size / 2);
		v->push_back( i * height);
		v->push_back(center.z - size / 2);
		//texture coords set to 0.0 for now.
		v->push_back(0.0f);
		v->push_back(0.0f);
	}
	
	//top left
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i <= 1; i++)
		{
			v->push_back(center.x - size / 2);
			v->push_back(i * height);
			v->push_back(center.z + size / 2);
			v->push_back(0.0f);
			v->push_back(0.0f);
		}
	}
	//top right
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i <= 1; i++)
		{
			v->push_back(center.x + size / 2);
			v->push_back(i * height);
			v->push_back(center.z + size / 2);
			v->push_back(0.0f);
			v->push_back(0.0f);
		}
	}
	//bottom right
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i <= 1; i++)
		{
			v->push_back(center.x + size / 2);
			v->push_back(i * height);
			v->push_back(center.z - size / 2);
			v->push_back(0.0f);
			v->push_back(0.0f);
		}
	}
	//push bottom left again
	for (int i = 0; i <= 1; i++)
	{
		v->push_back(center.x - size / 2);
		v->push_back( i * height);
		v->push_back(center.z - size / 2);
		v->push_back(0.0f);
		v->push_back(0.0f);
	}
	//push roof square
	//top view, bottom left
	v->push_back(center.x - size / 2);
	v->push_back(height);
	v->push_back(center.z - size / 2);
	v->push_back(0.0f);
	v->push_back(0.0f);
	//bottom right
	v->push_back(center.x + size / 2);
	v->push_back(height);
	v->push_back(center.z - size / 2);
	v->push_back(0.0f);
	v->push_back(0.0f);
	//top left
	v->push_back(center.x - size / 2);
	v->push_back(height);
	v->push_back(center.z + size / 2);
	v->push_back(0.0f);
	v->push_back(0.0f);
	//top right
	v->push_back(center.x + size / 2);
	v->push_back(height);
	v->push_back(center.z + size / 2);
	v->push_back(0.0f);
	v->push_back(0.0f);


}
