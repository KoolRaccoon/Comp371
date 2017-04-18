/**
DiscoverySquare.h
Purpose: Contains the data of all generated tiles.
		Also creates a square around the camera's
		position where all the tiles that are to be drawn
		are generated. If a tile already exists it gets it
		from its data, if not it creates it using random parameters.
		It uses a factory builder pattern to generate the right 
		tile.

@super tileBuilder.h
@author Keven Presseau-St-Laurent
@version final 2017/04/18
*/

#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <vector>
#include "tile.h"
#include "cityTileBuilder.h"
#include "rockTileBuilder.h"
#include "Shader.h"
#include "Circle.h"
#include <vector>

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
	/*Recieves the camera's current and next hypothetic position
	* then returns a new camera position that is outside terrain/objects*/
	glm::vec3 checkCollision(glm::vec3 currentCameraPos, glm::vec3 nextCameraPosistion);
	//Returns what type of tile is at this position in the world
	static unsigned int selectTile(int worldx, int worldz);


private:
	
	//Creates tiles for each tile of type EMPTY in usedData
	void createTiles(int smallestX, int smallestZ);

	//Converts world coordinates into tile coordinates
	glm::vec3 toTileCoord(glm::vec3 worldPosition, glm::vec3 * tilePosition);
	
	//Returns the tile under the camera's position
	tile * findTile(glm::vec3 nextCameraPosition);

	//Load size
	float xSize;
	float zSize;
	
	//Data of all created tiles
	vector<tile*> data;

	//Data that is actually shown on screen
	vector<vector<tile*>> * usedData;

	vector<Shader*> shaders;

	//List of circles that are cities
	static vector<circle*>  cities;
};