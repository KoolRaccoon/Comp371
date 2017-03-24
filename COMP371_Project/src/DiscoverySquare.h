#pragma once
#include "..\glm/glm.hpp"
#include "..\glm/gtc/matrix_transform.hpp"
#include "..\glm/gtc/type_ptr.hpp"
#include <vector>

//Class used to send a boundary of discovery to load new tiles
class DiscoverySquare {
public:
	//Recieves the current shown tiles as parameters
	DiscoverySquare(float minx, float maxx, float minz, float maxz);
	~DiscoverySquare();
	//Returns true if the camera is stepping outside the discovery square
	bool needUpdate(glm::vec3 v);
	//Returns a vector containing all the translations to fill the new line of tiles
	std::vector<glm::vec3> getTransl(glm::vec3 v);

private:
	float _minX;
	float _maxX;
	float _minZ;
	float _maxZ;

	float _shownMinX;
	float _shownMaxX;
	float _shownMinZ;
	float _shownMaxZ;
};