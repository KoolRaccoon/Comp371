#include "DiscoverySquare.h"
#include <iostream>

DiscoverySquare::DiscoverySquare(float minx, float maxx, float minz, float maxz)
{
	//Initially sets the discovery box to half the initial shown square
	_minX = minx/2;
	_maxX = maxx/2;
	_minZ = minz/2;
	_maxZ = maxz/2;

	//Initial shown square
	_shownMinX = minx;
	_shownMaxX = maxx;
	_shownMinZ = minz;
	_shownMaxZ = maxz;
}

DiscoverySquare::~DiscoverySquare()
{
}

bool DiscoverySquare::needUpdate(glm::vec3 v)
{
	//std::cout << v.z << " " << _minZ << " " << _maxZ << _shownMinZ << " " << _shownMaxZ <<  std::endl;
	//Tests to see if the camera is outside the boundary
	if (v.x < _minX
		|| v.x > _maxX
		|| v.z < _minZ
		|| v.z > _maxZ)
		return true;
	else
		return false;
}

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
}
