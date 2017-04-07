#include "rockTile.h"

rockTile::~rockTile()
{
	delete _grid;
	_grid = nullptr;
}
