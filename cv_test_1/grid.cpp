#include "grid.h"
#pragma region ��¶����get�����ú���set

void GridCell::setIndex(const int& x, const int& y)
{
	this->_x = x;
	this->_y = y;
}

void GridCell::setBlock(const bool& r)
{
	this->_type.block = r;
}

void GridCell::setStart()
{
	this->_type.start = true;
}

void GridCell::setEnd()
{
	this->_type.end = true;
}

void GridCell::setCost4Way(GridCell* const end)
{
	// GCost
	if (_type.start == true) // ����ǿ�ʼ����
	{
		this->_gCost = 0;
	}
	else // ������ǿ�ʼ����
	{
		this->_gCost = this->_parent->getGCost() + 1;
	}

	// HCost
	int endX, endY;
	std::tie(endX, endY) = end->getIndex();// ��ȡĿ�����������
	_hCost = abs(endX - _x) + abs(endY - _y);// �����پ���

	// FCost
	_fCost = _gCost + _hCost;
}

void GridCell::setParent(GridCell* const parent)
{
	this->_parent = parent;
}

void GridCell::setRoute()
{
	this->_type.route = true;
}
/*
 * @brief ��ȡ��������
 * @note tuple<int, int>��һ��Ԫ�飬�����������ض��ֵ
 * @return std::tuple<int, int> ��������
 */
const std::tuple<int, int> GridCell::getIndex() const
{
	return { this->_x, this->_y };
}

const bool GridCell::isBlock() const
{
	return this->_type.block;
}

const bool GridCell::isStart() const
{
	return this->_type.start;
}

const bool GridCell::isEnd() const
{
	return this->_type.end;
}

const int GridCell::getGCost() const
{
	return this->_gCost;
}

const int GridCell::getHCost() const
{
	return this->_hCost;
}

const int GridCell::getFCost() const
{
	return this->_fCost;
}

GridCell* const GridCell::getParent() const
{
	return this->_parent;
}

const bool GridCell::isRoute() const
{
	return this->_type.route;
}
#pragma endregion

/*
 * @brief ��������ɵ����񻭳���
 * @param img ���ڻ������ͼ��
 * @param grid_size �����ģ��С
 * @param cell_size �������ش�С
 * @param grids ��������
 */
void drawGrid(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids) {
	// ���������͸���
	for (int i = 0; i < grid_size; ++i) {
		for (int j = 0; j < grid_size; ++j) {
			if (grids[i + j * grid_size].isBlock()) {
				cv::rectangle(img, cv::Rect(i * cell_size, j * cell_size, cell_size, cell_size), cv::Scalar(100, 30, 10), cv::FILLED);
			}
			else if (grids[i + j * grid_size].isEnd())
			{
				cv::rectangle(img, cv::Rect(i * cell_size, j * cell_size, cell_size, cell_size), cv::Scalar(0, 255, 0), cv::FILLED);
			}
			else if (grids[i + j * grid_size].isStart())
			{
				cv::rectangle(img, cv::Rect(i * cell_size, j * cell_size, cell_size, cell_size), cv::Scalar(0, 0, 255), cv::FILLED);
			}
			else if (grids[i + j * grid_size].isRoute())
			{
				cv::rectangle(img, cv::Rect(i * cell_size, j * cell_size, cell_size, cell_size), cv::Scalar(0, 120, 120), cv::FILLED);
			}
		}
	}

	// ��������
	for (int i = 1; i < grid_size; ++i) {
		line(img, cv::Point(i * cell_size, 0), cv::Point(i * cell_size, image_size), cv::Scalar(0, 0, 0), 2);
		line(img, cv::Point(0, i * cell_size), cv::Point(image_size, i * cell_size), cv::Scalar(0, 0, 0), 2);
	}
	cv::imshow("Grid", img);//��ʾͼ��
}

// ��������ϰ���
/*
 * @brief ��������ϰ���
 * @note �����ϰ���ĸ���Ϊ25%��ʹ��ʱ���������������
 * @param grids ��������
 */
void generateObstacles(std::vector<GridCell>& grids) {
	srand(static_cast<unsigned>(time(0)));//ʹ��ʱ���������������
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			if (rand() % 100 < 25) {  // ��������ϰ��Լ25%�ĸ���
				grids[i + j * grid_size].setBlock(true);//�����ϰ���
			}
		}
	}
}

/*
 * @brief ��ʼ����������
 * @note ��ʼ��������ȫ��������ΪĬ��ֵ�����grid.h
 * @param grids ��������
 * @param gridsize �����ģ��С
 */
void gridInit(std::vector<GridCell>& grids, const int& gridsize)
{
	std::fill(grids.begin(), grids.end(), GridCell());//ʹ��fill�������grids����grids�е�ÿ��Ԫ�ض���GridCell()��ʼ��
	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			grids[getGridNum(gridsize, i, j)].setIndex(i, j);
		}
	}
}

/*
 * @brief �����������ȡ����(vector�е�)���
 * @note �����Ͻǿ�ʼ��ţ�grids������0~99
 * @param gridsize �����ģ��С
 * @param x ����������
 * @param y ����������
 * @return int ������vector�еı��
 */
const int getGridNum(const int& gridsize, const int& x, const int& y)
{
	return y * gridsize + x;
}

/*
 * @brief ��ʾ·��
 * @note �Ƚ�·��������Ϊroute��Ȼ�󻭳�����tie�����ڽ��Ԫ��
 * @param img ���ڻ������ͼ��
 * @param grid_size �����ģ��С
 * @param cell_size �������ش�С
 * @param grids ��������
 * @param route ·�������ָ������
 */
void showRoute(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids, std::vector<GridCell*> route)
{
	int x, y;
	// �������route
	for (auto routeGrid : route)// range-based-forѭ��������route�е�ÿһ��Ԫ��
	{
		if (!routeGrid->isEnd() && !routeGrid->isStart())
		{
			routeGrid->setRoute();
		}
	}
	// ������ͼ
	for (auto iter = route.begin() + 1; iter != route.end(); iter++)
	{
		std::tie(x, y) = (*iter)->getIndex();// ��ȡ��������
		cv::rectangle(img, cv::Rect(x * cell_size + 3, y * cell_size + 3, cell_size - 5, cell_size - 5), cv::Scalar(0, 120, 120), cv::FILLED);
		cv::imshow("Grid", img);
		cv::waitKey(10);
	}

}
