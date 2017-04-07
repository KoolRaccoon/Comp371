#include "rockTileBuilder.h"


rockTileBuilder::rockTileBuilder(Shader * s, glm::vec3 * p, vector<vector<tile>> * data, int i, int j) :tileBuilder(s, p) 
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
	_tile = new rockTile;
	vector<vector<GLfloat>> * g = new vector<vector<GLfloat>>;
	vector<GLfloat> temp;
	for (int j = 0; j < _size; j++);
	{
		temp.push_back(0.0f);
	}
	for (int i = 0; i < _size; i++)
	{
		g->push_back(temp);
		fill1.push_back(temp);
		fill2.push_back(temp);
	}
	_tile->setGrid(g);
	build();
}

void rockTileBuilder::initializeGrid()
{
	if (_i - 1 >= 0)
		setLeft((*_data)[_i - 1][_j].tileType());
	if (_j + 1 < (*_data)[_i].size())
		setUp((*_data)[_i][_j + 1].tileType());
	if (_i + 1 < (*_data).size())
		setRight((*_data)[_i + 1][_j].tileType());
	if (_j - 1 >= 0)
		setDown((*_data)[_i][_j - 1].tileType());
}

void rockTileBuilder::fillGrid()
{
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	int i = 0;
	int j = 0;
	if ((*grid)[1][_size - 1] != 0)
		j = _size - 1;
	if ((*grid)[_size - 1][1] != 0)
		i = _size - 1;
	if (i == 0 || j == 0)
	{
		fillBottomLeft();
	}
	if (i == 0 || j != 0)
	{
		fillTopLeft();
	}
	if (i != 0 || j == 0)
	{
		fillBottomRight();
	}
	if (i != 0 || j != 0)
	{
		fillTopRight();
	}
}

vector<GLfloat>* rockTileBuilder::convertGrid()
{
	vector<GLfloat> * vertices = new vector<GLfloat>;
	GLfloat offset = 1 / (_size - 1);
	vector<vector<GLfloat>> * grid = _tile->getGrid();
	for (int j = 0; j < _size; j++)
	{
		for (int i = 0; i < _size; i++)
		{
			vertices->push_back(-0.5f + i*offset);
			vertices->push_back((*grid)[i][j]);
			vertices->push_back(-0.5f + j*offset);
			vertices->push_back(0.0f);
			vertices->push_back(0.0f);
			//vertices->push_back(0.0f);
		}
		if (j < _size - 1)
		{
			for (int i = 0; i < _size; i++)
			{
				vertices->push_back(-0.5f + i*offset);
				vertices->push_back((*grid)[i][j + 1]);
				vertices->push_back(-0.5f + (j + 1)*offset); 
				vertices->push_back(0.0f);
				vertices->push_back(0.0f);
				//vertices->push_back(0.0f);
			}
		}
	}
	return vertices;
}

void rockTileBuilder::setUp(unsigned int type)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
		vector<vector<GLfloat>> * upGrid = (*_data)[_i][_j + 1].getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int i = 0; i < _size; i++)
		{
			(*tileGrid)[i][_size - 1] = (*upGrid)[i][0];
		}
		break;
	}
}

void rockTileBuilder::setDown(unsigned int type)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
		vector<vector<GLfloat>> * downGrid = (*_data)[_i][_j - 1].getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int i = 0; i < _size; i++)
		{
			(*tileGrid)[i][0] = (*downGrid)[i][_size - 1];
		}
		break;
	}
}

void rockTileBuilder::setLeft(unsigned int type)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
		vector<vector<GLfloat>> * leftGrid = (*_data)[_i - 1][_j].getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int j = 0; j < _size; j++)
		{
			(*tileGrid)[0][j] = (*leftGrid)[_size - 1][j];
		}
		break;
	}
}

void rockTileBuilder::setRight(unsigned int type)
{
	switch (type)
	{
	case 1:
		break;
	case 2:
		vector<vector<GLfloat>> * rightGrid = (*_data)[_i + 1][_j].getGrid();
		vector<vector<GLfloat>> * tileGrid = _tile->getGrid();
		for (int j = 0; j < _size; j++)
		{
			(*tileGrid)[_size - 1][j] = (*rightGrid)[0][j];
		}
		break;
	}
}

void rockTileBuilder::fillBottomLeft()
{
	for (int k = 1; k < _size - 1; k++)
	{
		for (int l = 1; l < _size - 1; l++)
		{

		}
	}
	for (int l = 1; l < _size - 1; l++)
	{
		for (int k = 1; k < _size - 1; k++)
		{

		}
	}
}

void rockTileBuilder::fillBottomRight()
{
}

void rockTileBuilder::fillTopLeft()
{
}

void rockTileBuilder::fillTopRight()
{
}
