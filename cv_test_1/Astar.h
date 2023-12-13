#pragma once
#ifndef _ASTAR_H_
#define _ASTAR_H_

#include <iostream>
#include "grid.h"

bool VectorContainItem(std::vector<GridCell*> vector, GridCell* const item);
bool AStar4Way(GridCell* startGrid, GridCell* endGrid, std::vector<GridCell>& grids, const int& gridsize);
std::vector<GridCell*> FindAllNeighbors4Way(GridCell* const current, std::vector<GridCell>& grids, const int& gridsize);
void AddAllRouteGridToVector(GridCell* const grid, std::vector<GridCell*>& route);

#endif


