#pragma once
#include "stdafx.h"
#include <vector>
#include "tile.h"
#include "cityTileBuilder.h"
#include "rockTileBuilder.h"
#include "Shader.h"

using namespace std;
//Class used to send a boundary of discovery to load new tiles
class DiscoverySquare {
public:
	/*Parameter constructor, no default constructor, takes the width and length
	* of the square and the position of the camera (usually (0.0, 0.0, 0.0))
	*/
	DiscoverySquare(float xsize, float zsize, glm::vec3 camPos);
	//Default destructor
	~DiscoverySquare();
	//Updates the tiles according to the new camera position
	vector<vector<tile*>> * update(glm::vec3 position);
	//Resets used data to be centered around the new position
	void resetUsedData();
	//Returns the first set of tiles. Is used once to generate the data of the initial tiles
	vector<vector<tile*>> * initializeSquare();
	//Adds a shader, declared in the main, to the list of initialized shaders to used from.
	void addShader(Shader * shader);
	//Creates the initial used data. 
	void initializeUsedData();
	glm::vec3 checkCollision(glm::vec3 currentCameraPos, glm::vec3 nextCameraPosistion);
	static unsigned int selectTile(int worldx, int worldz);


private:
	
	//Creates tiles for each tile of type EMPTY in usedData
	void createTiles(int smallestX, int smallestZ);
	glm::vec3 toTileCoord(glm::vec3 worldPosition, glm::vec3 * tilePosition);
	tile * findTile(glm::vec3 nextCameraPosition);

	float xSize;
	float zSize;
	
	//Data of all created tiles
	vector<tile*> data;

	//Data that is actually shown on screen
	vector<vector<tile*>> * usedData;

	vector<Shader*> shaders;
};