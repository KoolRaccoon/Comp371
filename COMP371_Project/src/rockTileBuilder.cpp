#include "rockTileBuilder.h"
#include "DiscoverySquare.h"


rockTileBuilder::rockTileBuilder(Shader * s, glm::vec3 * p, vector<vector<tile*>> * data, int i, int j) :tileBuilder(s, p) 
{
	_data = data;
	_i = i;
	_j = j;
}

void rockTileBuilder::buildType()
{
	_tile->setTileType(ROCK);
}

void rockTileBuilder::buildVertices()
{
	initializeGrid();
	fillGrid();
	vector<GLfloat> * v = convertGrid();
	_tile->setVertices(v);
}

void rockTileBuilder::buildDrawType()
{
	_tile->setDrawType(GL_TRIANGLE_STRIP);
}

void rockTileBuilder::buildShader()
{
	_tile->setShader(_shader);
}

void rockTileBuilder::buildPosition()
{
	_tile->setPosition(_position);
}

void rockTileBuilder::createTile()
{
	//Creates tile and initializes its grid and the builder's two grids
	_tile = new rockTile;
	vector<vector<GLfloat>> * g = new vector<vector<GLfloat>>;
	vector<GLfloat> temp;
	for (int i = 0; i < _size; i++)
	{
		temp.push_back(0.0f);
	}
	for (int i = 0; i < _size; i++)
	{
		g->push_back(temp);
		fillUD.push_back(temp);
		fillLR.push_back(temp);
	}
	_tile->setGrid(g);
	build();
}

void rockTileBuilder::initializeGrid()
{
	float x = _position->x;
	float z = _position->z;
	//Checks to see if a tile exists left right down or up 
	//of the current tile and sets the grids accordingly
	if ((_i - 1) >= 0)
	{
		setLeft((*_data)[_i - 1][_j]->tileType());
		//cout << "setLeft" << endl;
	}
 	else if((DiscoverySquare::selectTile(x - 1, z)) == CITY)
	{
		setLeft(CITY);
	}
		
	if ((_i + 1) < (*_data).size())
	{
		setRight((*_data)[_i + 1][_j]->tileType());
		//cout << "setRight" << endl;
	}
	else if ((DiscoverySquare::selectTile(x + 1, z)) == CITY)
	{
		setRight(CITY);
	}
	if ((_j + 1) < (*_data)[_i].size())
	{
		setUp((*_data)[_i][_j + 1]->tileType()); 
		//cout << "setUp" << endl;
	}
	else if ((DiscoverySquare::selectTile(x, z + 1)) == CITY)
	{
		setUp(CITY);
	}
	if ((_j - 1) >= 0)
	{
		setDown((*_data)[_i][_j - 1]->tileType()); 
		//cout << "setDown" << endl;
	}
	else if ((DiscoverySquare::selectTile(x, z - 1)) == CITY)
	{
		setDown(CITY);
	}
	fillUD = fillLR = (*(_tile->getGrid()));
}

void rockTileBuilder::fillGrid()
{
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	//Checks which pass is needed to fill the grid the applies them
	if (up && down)
		fillUpDown();
	else if (up)
		fillUp();
	else if (down)
		fillDown();
	if (left && right)
		fillLeftRight();
	else if (left)
		fillLeft();
	else if (right)
		fillRight();
	//Div = amount of passes
	float div = ((float)(up | down) + (float)(left | right));
	//No divisions by zero pls (just in case, but shouldnt happen)
	if (div == 0)
		div = 1;
	//Averages the heights and sets the in the tile's grid
	for (int k = 0; k < _size; k++)
	{
		for (int l = 0; l < _size; l++)
		{
			if((*grid)[k][l] == 0 )
				(*grid)[k][l] = (fillUD[k][l] + fillLR[k][l]) / div;
		}
	}
}

vector<GLfloat>* rockTileBuilder::convertGrid()
{
	vector<GLfloat> * vertices = new vector<GLfloat>;
	GLfloat offset = 1 / (float)(_size - 1);
	vector<vector<GLfloat>> * grid = _tile->getGrid();

	/*Creates one strip starting at the bottom left,
	* ending at the top right; doing a spiral while 
	* fitting on the terrain
	*/
	for (int i = 0; i < _size - 1; i++)
	{
		
		vertices->push_back(-0.5f + (i + 1)*offset);
		vertices->push_back(0);
		vertices->push_back(-0.5f);
		vertices->push_back(0.0f);
		vertices->push_back(0.0f);


		vertices->push_back(-0.5f + i*offset);
		vertices->push_back(0);
		vertices->push_back(-0.5f);
		vertices->push_back(0.0f);
		vertices->push_back(0.0f);

		for (int j = 0; j < _size; j++)
		{
			
			vertices->push_back(-0.5f + (i + 1)*offset);
			vertices->push_back((*grid)[i+1][j]);
			vertices->push_back(-0.5f + j*offset);
			vertices->push_back(0.0f);
			vertices->push_back(0.0f);
			//vertices->push_back(0.0f);
			//cout << (*grid)[i][j] << " ";
			vertices->push_back(-0.5f + i*offset);
			vertices->push_back((*grid)[i][j]);
			vertices->push_back(-0.5f + (j)*offset);
			vertices->push_back(0.0f);
			vertices->push_back(0.0f);
			//vertices->push_back(0.0f);
			//cout << (*grid)[i][j + 1];

			if (j == _size - 1)
			{
				vertices->push_back(-0.5f + (i+1)*offset);
				vertices->push_back(0);
				vertices->push_back(-0.5f + (j)*offset);
				vertices->push_back(0.0f);
				vertices->push_back(0.0f);
				vertices->push_back(-0.5f + (i)*offset);
				vertices->push_back(0);
				vertices->push_back(-0.5f + (j)*offset);
				vertices->push_back(0.0f);
				vertices->push_back(0.0f);
			}
			//cout << endl;
		}

	}

	return vertices;
}

void rockTileBuilder::setUp(unsigned int type)
{
	
	switch (type)
	{
	case 1:
		up = true;
		break;
	case 2:
		vector<vector<GLfloat>> * upGrid = (*_data)[_i][_j + 1]->getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int i = 0; i < _size; i++)
		{
			(*tileGrid)[i][_size - 1] = (*upGrid)[i][0];
		}
		up = true;
		break;
	}
}

void rockTileBuilder::setDown(unsigned int type)
{
	
	switch (type)
	{
	case 1:
		down = true;
		break;
	case 2:
		vector<vector<GLfloat>> * downGrid = (*_data)[_i][_j - 1]->getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int i = 0; i < _size; i++)
		{
			(*tileGrid)[i][0] = (*downGrid)[i][_size - 1];
		}
		down = true;
		break;
	}
}

void rockTileBuilder::setLeft(unsigned int type)
{
	
	switch (type)
	{
	case 1:
		left = true;
		break;
	case 2:
		vector<vector<GLfloat>> * leftGrid = (*_data)[_i - 1][_j]->getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int j = 0; j < _size; j++)
		{
			(*tileGrid)[0][j] = (*leftGrid)[_size - 1][j];
		}
		left = true;
		break;
	}
}

void rockTileBuilder::setRight(unsigned int type)
{
	
	switch (type)
	{
	case 1:
		right = true;
		break;
	case 2:
		vector<vector<GLfloat>> * rightGrid = (*_data)[_i + 1][_j]->getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int j = 0; j < _size; j++)
		{
			(*tileGrid)[_size - 1][j] = (*rightGrid)[0][j];
		}
		right = true;
		break;
	}
}

void rockTileBuilder::fillLeft()
{
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	float height;

	for (int i = left; i < _size - right; i++)
	{
		for (int j = down; j < _size - up; j++)
		{
			height = (fillLR)[i - 1][j] + random();
			if (height < 0)
				height = 0;
			fillLR[i][j] += height;
			//fillLR[i][j] = random();
		}
	}
}

void rockTileBuilder::fillRight()
{
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	float height;

	for (int i = _size - 1 - right; i >= left; i--)
	{
		for (int j = down; j < _size - up; j++)
		{
			height = (fillLR)[i + 1][j] + random();
			if (height < 0)
				height = 0;
			fillLR[i][j] += height;
			//fillLR[i][j] = random();
		}
	}
}

void rockTileBuilder::fillUp()
{
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	float height;

	for (int i = left; i < _size - right; i++)
	{
		for (int j = _size - up - 1; j >= down; j--)
		{
			height = (fillUD)[i][j + 1] + random();
			if (height < 0)
				height = 0;
			fillUD[i][j] += height;
			//fillUD[i][j] = random();
		}
	}
}

void rockTileBuilder::fillDown()
{
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	float height;

	for (int i = left; i < _size - right; i++)
	{
		for (int j = down; j < _size - up; j++)
		{
			height = (fillUD)[i][j - 1] + random();
			if (height < 0)
				height = 0;
			fillUD[i][j] += height;
			//fillUD[i][j] = random();
		}
	}
}

void rockTileBuilder::fillLeftRight()
{
	cout << "LeftRight" << endl;
	fillLeft();
	fillRight();
	for (int i = left; i < _size - right; i++)
	{
		for (int j = down; j < _size - up; j++)
		{
			fillLR[i][j] = fillLR[i][j]/2;
		}
	}
}

void rockTileBuilder::fillUpDown()
{
	cout << "UpDown" << endl;
	fillUp();
	fillDown();
	for (int i = left; i < _size - right; i++)
	{
		for (int j = down; j < _size - up; j++)
		{
			fillUD[i][j] = fillUD[i][j] / 2;
		}
	}
}

float rockTileBuilder::random()
{
	float rnd = (float)-0.2 + ((rand() % 101) / (float)265.0);
	//float rnd = (rand() % 101) / (float)100.0;
	//float rnd = (-1 + rand() % 4) * 0.01f;
	return rnd;
}
