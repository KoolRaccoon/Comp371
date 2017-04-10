#include "DiscoverySquare.h"
#include <iostream>

DiscoverySquare::DiscoverySquare(float xs, float zs, glm::vec3 cam)
{
	xSize = xs;
	zSize = zs;
	usedData = new vector<vector<tile*>>;
	initializeUsedData();
}

DiscoverySquare::~DiscoverySquare()
{
	delete usedData;
	usedData = nullptr;
}

vector<vector<tile*>> * DiscoverySquare::update(glm::vec3 v)
{
	//cout << v.x << " " << v.z << " " << endl;
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
			(*usedData)[x - xZero][z - zZero] = data[i];
		}
	}
	createTiles(xZero, zZero);

	return usedData;
}
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
		usedData->emplace_back(temp);
	}
}

vector<vector<tile*>> * DiscoverySquare::initializeSquare()
{
	createTiles(-(xSize / 2), -(zSize / 2));
	return usedData;
}

void DiscoverySquare::createTiles(int x, int z)
{
	int count = 0;
	for (int i = 0; i < usedData->size(); i++)
	{
		for (int j = 0; j < (*usedData)[i].size(); j++)
		{
			if ((*usedData)[i][j]->tileType() == EMPTY)
			{
				count++;
				glm::vec3 * pos = new glm::vec3(i + x, 0.0f, j + z);
				//tileBuilder * rtb = new rockTileBuilder(shaders[ROCK], pos, usedData, i, j);
				if ((i + x) <= 25 && 
					(i + x) >= -25 &&
					(j + z) <= 25 &&
					(j + z) >= -25)
				{
					tileBuilder * ctb = new cityTileBuilder(shaders[CITY], pos);
					ctb->createTile();
					(*usedData)[i][j] = ctb->getTile();
					data.push_back(ctb->getTile());
					delete ctb;
					ctb = nullptr;
				}
				else
				{
					tileBuilder * rtb = new rockTileBuilder(shaders[ROCK], pos, usedData, i, j);
					rtb->createTile();
					(*usedData)[i][j] = rtb->getTile();
					data.push_back(rtb->getTile());
					delete rtb;
					rtb = nullptr;
					//cout << "Creating rock tile" << endl;
				}
			}
		}
	}
}
void DiscoverySquare::addShader(Shader * s)
{
	shaders.push_back(s);
}
/*
std::vector<glm::vec3> DiscoverySquare::getTransl(glm::vec3 v)
{
	std::vector<glm::vec3> transl;
	//Checks where the camera has stepped out and then
	//creates a new line of tiles on the side where the camera
	//has stepped out.
	if (v.x < _minX)
	{
		_minX --;
		
		for (float i = _shownMinZ; i <= _shownMaxZ; i++)
		{
			transl.push_back(glm::vec3(_shownMinX, 0.0f, i));
		}
		_shownMinX--;
	}
	if (v.x > _maxX)
	{
		_maxX ++;
		
		for (float i = _shownMinZ; i <= _shownMaxZ; i++)
		{
			transl.push_back(glm::vec3(_shownMaxX, 0.0f, i));
		}
		_shownMaxX++;
	}
	if (v.z < _minZ)
	{
		_minZ --;
		
		for (float i = _shownMinX; i <= _shownMaxX; i++)
		{
			transl.push_back(glm::vec3(i, 0.0f, _shownMinZ));
		}
		_shownMinZ--;
	}
	if (v.z > _maxZ)
	{
		_maxZ ++;
		
		for (float i = _shownMinX; i <= _shownMaxX; i++)
		{
			transl.push_back(glm::vec3(i, 0.0f, _shownMaxZ));
		}
		_shownMaxZ++;
	}
	return transl;
}*/
