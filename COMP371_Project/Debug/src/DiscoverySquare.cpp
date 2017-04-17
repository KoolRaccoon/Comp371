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
    cout << v.x << " " << v.z << " " << endl;
    cout << data.size() << endl;
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
    
    if ((goodx || goodz) && t->tileType() == ROCK)
        currentPos.y += 0.05f;
    
    glm::vec3 realPos = glm::vec3
    (!goodx * distx + currentPos.x,
     !goody * disty + currentPos.y,
     !goodz * distz + currentPos.z);
    return realPos;
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
                unsigned int type = selectTile(i + x, j + z);
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
                        //cout << "Creating rock tile" << endl;
                        break;
                    }
                }
            }
        }
    }
}
glm::vec3 DiscoverySquare::toTileCoord(glm::vec3 wp, glm::vec3 * tp)
{
    return glm::vec3(wp.x-tp->x, wp.y-tp->y, wp.z-tp->z);
}


tile * DiscoverySquare::findTile(glm::vec3 nextCameraPosition)
{
    
    for (int i = 0; i < (*usedData).size(); i++)
        for (int j = 0; j < (*usedData)[i].size(); j++)
            if ((*usedData)[i][j]->getPosition()->x == roundf(nextCameraPosition.x) &&
                (*usedData)[i][j]->getPosition()->z == roundf(nextCameraPosition.z))
                return (*usedData)[i][j];

    return NULL;
}


unsigned int DiscoverySquare::selectTile(int x, int z)
{
    if ((x) <= 25 &&
        (x) >= -25 &&
        (z) <= 25 &&
        (z) >= -25)
        return (CITY);
    else
        return (ROCK);
}
void DiscoverySquare::addShader(Shader * s)
{
    shaders.push_back(s);
}

