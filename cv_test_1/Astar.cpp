#include "Astar.h"

/**
 * @brief 判断向量中是否包含元素
 *
 * @param vector 需要判断的向量
 * @param item 包含元素
 * @return true 有
 * @return false 无
 *
*/
bool VectorContainItem(std::vector<GridCell*> vector, GridCell* const item)
{
	for (auto _item : vector)
	{
		if (_item == item)
			return true;
	}
	return false;
}

/**
 * @brief 四连通A*算法本体
 * @note 与八连通A*算法不同的是，四连通A*算法只能上下左右移动
 * @param startGrid 开始的网格
 * @param endGrid 结束的网格
 * @param grids 总的网格数组
 * @param gridsize 网格规模大小
 * @return true 成功
 * @return false 失败
 *
*/
bool AStar4Way(GridCell* startGrid, GridCell* endGrid, std::vector<GridCell>& grids, const int& gridsize)
{
	// A*算法所需变量
	std::vector<GridCell*> openGrid;   // openList
	std::vector<GridCell*> closeGrid;  // closeList
	GridCell* current = NULL;          // 现在计算的节点

	std::cout << "开始四连通寻路" << std::endl;
	clock_t start = clock();// 计时开始

	// 将开始节点放入Open List
	startGrid->setCost4Way(endGrid);
	openGrid.push_back(startGrid);

	// 在Open List中有元素的时候进行循环
	while (openGrid.size() > 0)
	{
		// 将current网格设置成Open List中FCost最小的，如果FCost一样的话设置成HCost最小的
		int minFCost = std::numeric_limits<int>::max();
		int currentNum = 0;
		int i = 0;
		for (auto grid : openGrid)
		{
			if (grid->getFCost() < minFCost)
			{
				current = grid;
				minFCost = grid->getFCost();// 用于比较的FCost
				currentNum = i;
			}
			else if (grid->getFCost() == minFCost && current)// 如果FCost一样的话设置成HCost最小的
			{
				if (grid->getHCost() < current->getHCost())
				{
					current = grid;
					currentNum = i;
				}
			}
			i++;
		}

		// 将current从open list中移除，加入到close list中
		openGrid.erase(openGrid.begin() + currentNum);
		closeGrid.push_back(current);

		// 如果current是目标点则寻路成功
		if (current && current->isEnd())
		{
			clock_t end = clock();// 计时结束
			std::cout << "寻路成功，用时：" << end - start << "毫秒" << std::endl;
			return true;
		}

		// 对于每一个邻居网格
		auto neighbors = FindAllNeighbors4Way(current, grids, gridsize);// 获取当前一个网格的所有邻居
		for (auto neighbor : neighbors)
		{
			// 如果在open和close list中或者是墙，则跳过，同时要判断是否有元素，防止越界
			if (neighbor->isBlock() || VectorContainItem(closeGrid, neighbor) || VectorContainItem(openGrid, neighbor))
				continue;
			else
			{
				neighbor->setParent(current);
				neighbor->setCost4Way(endGrid);
				openGrid.push_back(neighbor);
			}
		}
	}
	std::cout << "寻路失败" << std::endl;
	system("pause");
	exit(0);
	return false;
}

/*
 * @brief 获取当前网格的所有邻居
 * @note 与八连通A*算法不同的是，四连通A*算法只能上下左右移动，因此只有四个邻居
 * @param current 当前网格
 * @param grids 总的网格数组
 * @param gridsize 网格规模大小
 * @return std::vector<GridCell*> 当前网格的所有邻居的指针
 *
 */
std::vector<GridCell*> FindAllNeighbors4Way(GridCell* const current, std::vector<GridCell>& grids, const int& gridsize)
{
	std::vector<GridCell*> neighbors;
	int currentX, currentY;
	std::tie(currentX, currentY) = current->getIndex();
	// 上
	if (currentY > 0)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX, currentY - 1)];
		neighbors.push_back(neighbor);// 使用push_back方法将邻居放入vector，后面也一样
	}

	// 下
	if (currentY < gridsize - 1)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX, currentY + 1)];
		neighbors.push_back(neighbor);
	}

	// 左
	if (currentX > 0)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX - 1, currentY)];
		neighbors.push_back(neighbor);
	}

	// 右
	if (currentX < gridsize - 1)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX + 1, currentY)];
		neighbors.push_back(neighbor);
	}
	return neighbors;
}

/*
 * @brief 递归回溯所有路径节点，储存在vector里，用于显示
 * @param grid 当前网格
 * @param result 用于储存路径的vector
 *
 */
void AddAllRouteGridToVector(GridCell* const grid, std::vector<GridCell*>& result)
{
	if (grid->getParent())
	{
		result.push_back(grid);
		AddAllRouteGridToVector(grid->getParent(), result);// 递归回溯，直到父节点为空（相当于向上查找，从数据结构可以看出来）
	}
	else
	{
		return;
	}
}