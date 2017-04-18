#include "DiscoverySquare.h"
#include <iostream>
#include <vector>

vector<circle*> DiscoverySquare::cities;
//Initializes everything
DiscoverySquare::DiscoverySquare(float xs, float zs, glm::vec3 cam)
{
	xSize = xs;
	zSize = zs;
	for (int i = 0; i < 4; i++)
		cities.push_back(new circle());
		
	usedData = new vector<vector<tile*>>;
	initializeUsedData();
}

DiscoverySquare::~DiscoverySquare()
{
	delete usedData;
	usedData = nullptr;
}
//Updates the square centered around the camera and prints the camera's position
vector<vector<tile*>> * DiscoverySquare::update(glm::vec3 v)
{
	cout << v.x << " " << v.z << " " << endl;
	//cout << data.size() << endl;
	resetUsedData();
	int xZero = (int)v.x - xSize / 2;
	int zZero = (int)v.z - zSize / 2;
	int xFinal = (int)v.x + xSize / 2;
	int zFinal = (int)v.z + zSize / 2;
	for (int i = 0; i < data.size(); i++)
	{
		int x = data[i]->x;
		int z = data[i]->z;
		if (x >= xZero
			&& x <= xFinal
			&& z >= zZero
			&& z <= zFinal)
		{
			//Loads the preexisting tiles
			(*usedData)[x - xZero][z - zZero] = data[i];
		}
	}
	//Creates new tiles
	createTiles(xZero, zZero);

	return usedData;
}

//Resets usedData to contain only empty tiles
void DiscoverySquare::resetUsedData()
{
	tile * tempTile = new tile();
	for (int i = 0; i <= (int)xSize; i++)
	{
		for (int j = 0; j <= (int)zSize; j++)
		{
			(*usedData)[i][j] = tempTile;
		}
	}
}
//Initializes the dynamic container usedData
void DiscoverySquare::initializeUsedData()
{
	tile * tempTile = new tile();
	for (int i = 0; i <= (int)xSize; i++)
	{
		vector<tile*> temp;
		for (int j = 0; j <= (int)zSize; j++)
		{
			temp.push_back(tempTile);
		}
		usedData->push_back(temp);
	}
}

//Checks if theres a collision the movement on each axis and returns the new good position
glm::vec3 DiscoverySquare::checkCollision(glm::vec3 currentPos, glm::vec3 nextPos)
{
	tile * t = findTile(nextPos);

	bool goodx = false;
	bool goody = false;
	bool goodz = false;

	glm::vec3 movex = glm::vec3(nextPos.x, currentPos.y, currentPos.z);
	glm::vec3 movey = glm::vec3(currentPos.x, nextPos.y, currentPos.z);
	glm::vec3 movez = glm::vec3(currentPos.x, currentPos.y, nextPos.z);

	glm::vec3 tilex = toTileCoord(movex, t->getPosition());
	glm::vec3 tiley = toTileCoord(movey, t->getPosition());
	glm::vec3 tilez = toTileCoord(movez, t->getPosition());

	float distx = nextPos.x - currentPos.x;
	float disty = nextPos.y - currentPos.y;
	float distz = nextPos.z - currentPos.z;

	goodx = t->checkCollision(&tilex);
	goody = t->checkCollision(&tiley);
	goodz = t->checkCollision(&tilez);

	//Bump the camera up a bit to avoid blocking
	if ((goodx || goodz) && t->tileType() == ROCK)
		currentPos.y += 0.05f;

	//Only add the movement if there is no collision
	glm::vec3 realPos = glm::vec3
	(!goodx * distx + currentPos.x,
		!goody * disty + currentPos.y,
		!goodz * distz + currentPos.z);
	return realPos;
}

//Similar to update but for the intial camera position
vector<vector<tile*>> * DiscoverySquare::initializeSquare()
{
	createTiles(-(xSize / 2), -(zSize / 2));
	return usedData;
}

//Check if a tile is empty then creates a new one if necessary
void DiscoverySquare::createTiles(int x, int z)
{
	int count = 0;
	for (int i = 0; i < usedData->size(); i++)
	{
		for (int j = 0; j < (*usedData)[i].size(); j++)
		{
			if ((*usedData)[i][j]->tileType() == EMPTY)
			{
				//Increment the data size
				count++;
				//Gets the new tile's position
				glm::vec3 * pos = new glm::vec3(i + x, 0.0f, j + z);
				//Figure out which type of tile needs to be created
				unsigned int type = selectTile(i + x, j + z);
				//Selects the right builder, creates the tile and adds it to usedData and data
				switch (type)
				{
				case 1:
				{
					tileBuilder * ctb = new cityTileBuilder(shaders[CITY], pos);
					ctb->createTile();
					(*usedData)[i][j] = ctb->getTile();
					data.push_back(ctb->getTile());
					delete ctb;
					ctb = nullptr;
					break;
				}
				case 2:
				{
					tileBuilder * rtb = new rockTileBuilder(shaders[ROCK], pos, usedData, i, j);
					rtb->createTile();
					(*usedData)[i][j] = rtb->getTile();
					data.push_back(rtb->getTile());
					delete rtb;
					rtb = nullptr;
					break;
				}
				}
			}
		}
	}
}
//Converts the world coordinates to coordinates bound by -0.5f and 0.5f
glm::vec3 DiscoverySquare::toTileCoord(glm::vec3 wp, glm::vec3 * tp)
{
	return glm::vec3(wp.x-tp->x, wp.y-tp->y, wp.z-tp->z);
}
//Finds which tile the camera's new position is standing on
tile * DiscoverySquare::findTile(glm::vec3 nextCameraPosition)
{
	
	for (int i = 0; i < (*usedData).size(); i++)
		for (int j = 0; j < (*usedData)[i].size(); j++)
			if ((*usedData)[i][j]->getPosition()->x == roundf(nextCameraPosition.x) &&
				(*usedData)[i][j]->getPosition()->z == roundf(nextCameraPosition.z))
				return (*usedData)[i][j];
    return nullptr;
}
//Check if the position is inside one of the city circles
unsigned int DiscoverySquare::selectTile(int x, int z)
{
	bool inside = false;
	for (int i = 0; i < cities.size(); i++)
		inside = inside || cities[i]->checkIfInside(x, z);
	if(inside)
		return (CITY);
	else
		return (ROCK);
}
//Adds a shader to the shader bank
void DiscoverySquare::addShader(Shader * s)
{
	shaders.push_back(s);
}
