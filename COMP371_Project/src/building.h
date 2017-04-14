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

	//Checks if the position(in tile coords) is inside the building
	bool checkIfInside(glm::vec3 * pos)
	{
		if (pos->y <= _height &&
			pos->x <= _center->x + _width / 2 &&
			pos->x >= _center->x - _width / 2 &&
			pos->z <= _center->z + _length / 2 &&
			pos->z >= _center->z + _length / 2)
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