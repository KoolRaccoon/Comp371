#pragma once
#include "stdafx.h"

class building 
{
public:
	//Parameter constructor
	building(glm::vec3 * center, float height, float width, float length)
	{
		_center = center;
		_height = height;
		_width = width;
		_length = length;
	}
	//Destructor
	~building()
	{
		delete _center;
		_center = nullptr;
	}
	/*
	*
	*		ACCESSORS	
	*
	*/
	float getHeight() { return _height; }
	float getWidth() { return _width; }
	float getLength() { return _length; }
	glm::vec3 * getCenter() { return _center; }

	//Checks if the position(in tile coords) is inside the building
	bool checkIfInside(glm::vec3 * pos)
	{
		
		if (pos->y <= (_height + 0.13f) &&
			pos->x <= (_center->x + _width / 2 + 0.13f) &&
			pos->x >= (_center->x - _width / 2 - 0.13f) &&
			pos->z <= (_center->z + _length / 2 + 0.13f) &&
			pos->z >= (_center->z - _length / 2 - 0.13f))
			return true;
		else
			return false;
	}


private:
	glm::vec3 * _center;
	float _height;
	float _width;
	float _length;
};