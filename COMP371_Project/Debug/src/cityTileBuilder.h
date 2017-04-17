#pragma once
#include "stdafx.h"
#include "tileBuilder.h"
#include "cityTile.h"

class cityTileBuilder : public tileBuilder
{
public:
    //Parameter constructor, no default constructor, takes an initialized shader and a position
    cityTileBuilder(Shader * shader, glm::vec3 * position);
    /*
     *				BUILDER
     *	(builds each component of a tile)
     */
    virtual void buildType();
    virtual void buildVertices();
    virtual void buildDrawType();
    virtual void buildShader();
    virtual void buildPosition();
    virtual void createTile();
private:
    void _createBuildings(vector<GLfloat> * vertices);
    void _singleBuilding();
    void _dualBuilding();
    void _tripleBuilding();
    void _quadBuilding();
    void _rotateBuilding(vector<glm::vec3> * building);
    void _convertToVertices(vector<GLfloat> * vertices);
    void _convertBuilding(vector<GLfloat> * vertices, building * building);
    void _convertTopHalf(vector<GLfloat> * vertices, building * building);
    void _convertBotHalf(vector<GLfloat> * vertices, building * building);
    float randHeight();
    float randQuarterSize();
    float randHalfSize();
    float randQuarterQuad(float value, float smallestPosition, float offset);
    float randHalfQuad(float val);
    
};