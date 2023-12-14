#include "Astar.h"

/**
 * @brief �ж��������Ƿ����Ԫ��
 *
 * @param vector ��Ҫ�жϵ�����
 * @param item ����Ԫ��
 * @return true ��
 * @return false ��
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
 * @brief ����ͨA*�㷨����
 * @note �����ͨA*�㷨��ͬ���ǣ�����ͨA*�㷨ֻ�����������ƶ�
 * @param startGrid ��ʼ������
 * @param endGrid ����������
 * @param grids �ܵ���������
 * @param gridsize �����ģ��С
 * @return true �ɹ�
 * @return false ʧ��
 *
*/
bool AStar4Way(GridCell* startGrid, GridCell* endGrid, std::vector<GridCell>& grids, const int& gridsize)
{
	// A*�㷨�������
	std::vector<GridCell*> openGrid;   // openList
	std::vector<GridCell*> closeGrid;  // closeList
	GridCell* current = NULL;          // ���ڼ���Ľڵ�

	std::cout << "��ʼ����ͨѰ·" << std::endl;
	clock_t start = clock();// ��ʱ��ʼ

	// ����ʼ�ڵ����Open List
	startGrid->setCost4Way(endGrid);
	openGrid.push_back(startGrid);

	// ��Open List����Ԫ�ص�ʱ�����ѭ��
	while (openGrid.size() > 0)
	{
		// ��current�������ó�Open List��FCost��С�ģ����FCostһ���Ļ����ó�HCost��С��
		int minFCost = std::numeric_limits<int>::max();
		int currentNum = 0;
		int i = 0;
		for (auto grid : openGrid)
		{
			if (grid->getFCost() < minFCost)
			{
				current = grid;
				minFCost = grid->getFCost();// ���ڱȽϵ�FCost
				currentNum = i;
			}
			else if (grid->getFCost() == minFCost && current)// ���FCostһ���Ļ����ó�HCost��С��
			{
				if (grid->getHCost() < current->getHCost())
				{
					current = grid;
					currentNum = i;
				}
			}
			i++;
		}

		// ��current��open list���Ƴ������뵽close list��
		openGrid.erase(openGrid.begin() + currentNum);
		closeGrid.push_back(current);

		// ���current��Ŀ�����Ѱ·�ɹ�
		if (current && current->isEnd())
		{
			clock_t end = clock();// ��ʱ����
			std::cout << "Ѱ·�ɹ�����ʱ��" << end - start << "����" << std::endl;
			return true;
		}

		// ����ÿһ���ھ�����
		auto neighbors = FindAllNeighbors4Way(current, grids, gridsize);// ��ȡ��ǰһ������������ھ�
		for (auto neighbor : neighbors)
		{
			// �����open��close list�л�����ǽ����������ͬʱҪ�ж��Ƿ���Ԫ�أ���ֹԽ��
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
	std::cout << "Ѱ·ʧ��" << std::endl;
	system("pause");
	exit(0);
	return false;
}

/*
 * @brief ��ȡ��ǰ����������ھ�
 * @note �����ͨA*�㷨��ͬ���ǣ�����ͨA*�㷨ֻ�����������ƶ������ֻ���ĸ��ھ�
 * @param current ��ǰ����
 * @param grids �ܵ���������
 * @param gridsize �����ģ��С
 * @return std::vector<GridCell*> ��ǰ����������ھӵ�ָ��
 *
 */
std::vector<GridCell*> FindAllNeighbors4Way(GridCell* const current, std::vector<GridCell>& grids, const int& gridsize)
{
	std::vector<GridCell*> neighbors;
	int currentX, currentY;
	std::tie(currentX, currentY) = current->getIndex();
	// ��
	if (currentY > 0)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX, currentY - 1)];
		neighbors.push_back(neighbor);// ʹ��push_back�������ھӷ���vector������Ҳһ��
	}

	// ��
	if (currentY < gridsize - 1)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX, currentY + 1)];
		neighbors.push_back(neighbor);
	}

	// ��
	if (currentX > 0)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX - 1, currentY)];
		neighbors.push_back(neighbor);
	}

	// ��
	if (currentX < gridsize - 1)
	{
		GridCell* neighbor = &grids[getGridNum(gridsize, currentX + 1, currentY)];
		neighbors.push_back(neighbor);
	}
	return neighbors;
}

/*
 * @brief �ݹ��������·���ڵ㣬������vector�������ʾ
 * @param grid ��ǰ����
 * @param result ���ڴ���·����vector
 *
 */
void AddAllRouteGridToVector(GridCell* const grid, std::vector<GridCell*>& result)
{
	if (grid->getParent())
	{
		result.push_back(grid);
		AddAllRouteGridToVector(grid->getParent(), result);// �ݹ���ݣ�ֱ�����ڵ�Ϊ�գ��൱�����ϲ��ң������ݽṹ���Կ�������
	}
	else
	{
		return;
	}
}