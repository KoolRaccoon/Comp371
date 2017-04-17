#include "tile.h"

tile::tile()
{
	type = EMPTY;
}


tile::~tile()
{
	delete vertices;
	delete position;
	delete shader;
	vertices = nullptr;
	position = nullptr;
	shader = nullptr;
}

unsigned int tile::tileType()
{
	return type;
}

GLenum tile::drawType()
{
	return drawtype;
}


vector<GLfloat> * tile::getVertices()
{
	return vertices;
}

Shader * tile::getShader()
{
	return shader;
}

glm::vec3 * tile::getPosition()
{
	return position;
}


void tile::setTileType(unsigned int t)
{
	type = t;
}

void tile::setDrawType(GLenum dt)
{
	drawtype = dt;
}

void tile::setShader(Shader * sp)
{
	shader = sp;
}

void tile::setVertices(vector<GLfloat> * v)
{
	vertices = v;
}

void tile::setPosition(glm::vec3 * pos)
{
	position = pos;
	x = pos->x;
	z = pos->z;
}

void tile::setTextures(GLuint &texture1, GLuint &texture2)
{
	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shader->Program, "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(shader->Program, "ourTexture2"), 1);
}
