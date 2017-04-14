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
	_createBuildings(v);
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

void cityTileBuilder::_createBuildings(vector<GLfloat>* v)
{
	switch (1)
	{
	case 1:
		_singleBuilding(v);
		break;
	case 2:
		_dualBuilding(v);
		break;
	case 3:
		_tripleBuilding(v);
		break;
	case 4:
		_quadBuilding(v);
		break;
	}
}

void cityTileBuilder::_singleBuilding(vector<GLfloat> * v)
{
	//size of one side of the square
	float size = (float)(rand()%4 + 4)/(float)10;
	//center of the building
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	//random height between 0.01 and 3.00
	float height = (rand() % 200 + 100) / 100.0f;

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
		v->push_back(i * height);
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
		v->push_back(i * height);
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

void cityTileBuilder::_dualBuilding(vector<GLfloat>* vertices)
{
	//size of one side of the square
	
	float widthUp = randHalfSize();
	float lengthUp = randQuarterSize();

	float widthDown = randHalfSize();
	float lengthDown = randQuarterSize();

	float centerUpx = randHalfQuad(widthUp); 
	float centerUpz = randQuarterQuad(lengthUp, 0.0f, 0.0f);
	
	float centerDownx = randHalfQuad(widthDown);
	float centerDownz = randQuarterQuad(lengthUp, -0.5f, 0.1f);


	float heightUp = randHeight();
	float heightDown = randHeight();

	glm::vec3 * centerUp = new glm::vec3(centerUpx, 0.0f, centerUpz);
	glm::vec3 * centerDown = new glm::vec3(centerDownx, 0.0f, centerDownz);


	building * b1 = new building(centerUp, heightUp, widthUp, lengthUp);
	building * b2 = new building(centerDown, heightDown, widthDown, lengthDown);


	_tile->addBuilding(b1);
	_tile->addBuilding(b2);
	
}

void cityTileBuilder::_tripleBuilding(vector<GLfloat>* vertices)
{
	//size of one side of the square

	float widthUp1 = randQuarterSize();
	float lengthUp1 = randQuarterSize();
		
	float widthUp2 = randQuarterSize();
	float lengthUp2 = randQuarterSize();

	float widthDown = randHalfSize();
	float lengthDown = randQuarterSize();

	float centerUp1x = randQuarterQuad(widthUp1, -0.5f, 0.1f);
	float centerUp1z = randQuarterQuad(lengthUp1, 0.0f, 0.0f);

	float centerUp2x = randQuarterQuad(widthUp1, 0.0f, 0.0f);
	float centerUp2z = randQuarterQuad(lengthUp1, 0.0f, 0.0f);


	float centerDownx = randHalfQuad(widthDown);
	float centerDownz = randQuarterQuad(lengthDown, 0.0f, 0.0f);


	float heightUp1 = randHeight();
	float heightUp2 = randHeight();
	float heightDown = randHeight();

	glm::vec3 * centerUp1 = new glm::vec3(centerUp1x, 0.0f, centerUp1z);
	glm::vec3 * centerUp2 = new glm::vec3(centerUp2x, 0.0f, centerUp2z);
	glm::vec3 * centerDown = new glm::vec3(centerDownx, 0.0f, centerDownz);


	building * b1 = new building(centerUp1, heightUp1, widthUp1, lengthUp1);
	building * b2 = new building(centerUp2, heightUp2, widthUp2, lengthUp2);
	building * b3 = new building(centerDown, heightDown, widthDown, lengthDown);


	_tile->addBuilding(b1);
	_tile->addBuilding(b2);
	_tile->addBuilding(b3);
}

void cityTileBuilder::_quadBuilding(vector<GLfloat>* vertices)
{
	float widthUp1 = randQuarterSize();
	float lengthUp1 = randQuarterSize();

	float widthUp2 = randQuarterSize();
	float lengthUp2 = randQuarterSize();

	float widthDown1 = randQuarterSize();
	float lengthDown1 = randQuarterSize();

	float widthDown2 = randQuarterSize();
	float lengthDown2 = randQuarterSize();

	float centerUp1x = randQuarterQuad(widthUp1, -0.5f, 0.1f);
	float centerUp1z = randQuarterQuad(lengthUp1, 0.0f, 0.0f);

	float centerUp2x = randQuarterQuad(widthUp1, 0.0f, 0.0f);
	float centerUp2z = randQuarterQuad(lengthUp1, 0.0f, 0.0f);

	float centerDown1x = randQuarterQuad(widthDown1, -0.5f, 0.1f);
	float centerDown1z = randQuarterQuad(lengthDown1, 0.0f, 0.0f);

	float centerDown2x = randQuarterQuad(widthDown1, 0.0f, 0.0f);
	float centerDown2z = randQuarterQuad(lengthDown1, 0.0f, 0.0f);
	


	float heightUp1 = randHeight();
	float heightUp2 = randHeight();
	float heightDown1 = randHeight();
	float heightDown2 = randHeight();

	glm::vec3 * centerUp1 = new glm::vec3(centerUp1x, 0.0f, centerUp1z);
	glm::vec3 * centerUp2 = new glm::vec3(centerUp2x, 0.0f, centerUp2z);
	glm::vec3 * centerDown1 = new glm::vec3(centerDown1x, 0.0f, centerDown1z);
	glm::vec3 * centerDown2 = new glm::vec3(centerDown2x, 0.0f, centerDown2z);

	building * b1 = new building(centerUp1, heightUp1, widthUp1, lengthUp1);
	building * b2 = new building(centerUp2, heightUp2, widthUp2, lengthUp2);
	building * b3 = new building(centerDown1, heightDown1, widthDown1, lengthDown1);
	building * b4 = new building(centerDown2, heightDown2, widthDown2, lengthDown2);


	_tile->addBuilding(b1);
	_tile->addBuilding(b2);
	_tile->addBuilding(b3);
	_tile->addBuilding(b4);
}

void cityTileBuilder::_rotateBuilding(vector<glm::vec3>* b)
{
}

void cityTileBuilder::_convertToVertices(vector<GLfloat>* v, float h)
{
}

float cityTileBuilder::randHeight()
{
	return (rand() % 200 + 100) / 100.0f;
}

float cityTileBuilder::randQuarterSize()
{
	return (float)(rand() % 2 + 2) / (float)10;
}

float cityTileBuilder::randHalfSize()
{
	return (float)(rand() % 6 + 2) / (float)10;
}

float cityTileBuilder::randQuarterQuad(float val, float init, float offset)
{
	return init + offset + val / 2 +
		(float)(rand() % (int)((0.5f - 0.1f - val) * 10)) / (float)10;
}

float cityTileBuilder::randHalfQuad(float val)
{
	return -0.5f + 0.1f + val / 2 +
		(float)(rand() % (int)((1.0f - 0.2f - val) * 10)) / (float)10;
}
