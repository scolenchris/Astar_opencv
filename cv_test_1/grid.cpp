#include "grid.h"
#pragma region 暴露函数get和设置函数set

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
	if (_type.start == true) // 如果是开始网格
	{
		this->_gCost = 0;
	}
	else // 如果不是开始网格
	{
		this->_gCost = this->_parent->getGCost() + 1;
	}

	// HCost
	int endX, endY;
	std::tie(endX, endY) = end->getIndex();// 获取目标网格的坐标
	_hCost = abs(endX - _x) + abs(endY - _y);// 曼哈顿距离

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
 * @brief 获取网格坐标
 * @note tuple<int, int>是一个元组，可以用来返回多个值
 * @return std::tuple<int, int> 网格坐标
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
 * @brief 将随机生成的网格画出来
 * @param img 用于画网格的图像
 * @param grid_size 网格规模大小
 * @param cell_size 网格像素大小
 * @param grids 网格数组
 */
void drawGrid(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids) {
	// 画四种类型格子
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

	// 画网格线
	for (int i = 1; i < grid_size; ++i) {
		line(img, cv::Point(i * cell_size, 0), cv::Point(i * cell_size, image_size), cv::Scalar(0, 0, 0), 2);
		line(img, cv::Point(0, i * cell_size), cv::Point(image_size, i * cell_size), cv::Scalar(0, 0, 0), 2);
	}
	cv::imshow("Grid", img);//显示图像
}

// 随机生成障碍物
/*
 * @brief 随机生成障碍物
 * @note 生成障碍物的概率为25%，使用时间种子生成随机数
 * @param grids 网格数组
 */
void generateObstacles(std::vector<GridCell>& grids) {
	srand(static_cast<unsigned>(time(0)));//使用时间种子生成随机数
	for (int i = 0; i < grid_size; i++) {
		for (int j = 0; j < grid_size; j++) {
			if (rand() % 100 < 25) {  // 随机生成障碍物，约25%的概率
				grids[i + j * grid_size].setBlock(true);//设置障碍物
			}
		}
	}
}

/*
 * @brief 初始化网格数组
 * @note 初始化的网格全部属性设为默认值，详见grid.h
 * @param grids 网格数组
 * @param gridsize 网格规模大小
 */
void gridInit(std::vector<GridCell>& grids, const int& gridsize)
{
	std::fill(grids.begin(), grids.end(), GridCell());//使用fill函数填充grids，将grids中的每个元素都用GridCell()初始化
	for (int i = 0; i < gridsize; i++)
	{
		for (int j = 0; j < gridsize; j++)
		{
			grids[getGridNum(gridsize, i, j)].setIndex(i, j);
		}
	}
}

/*
 * @brief 从网格坐标获取网格(vector中的)编号
 * @note 从左上角开始编号，grids的索引0~99
 * @param gridsize 网格规模大小
 * @param x 网格所在行
 * @param y 网格所在列
 * @return int 网格在vector中的编号
 */
const int getGridNum(const int& gridsize, const int& x, const int& y)
{
	return y * gridsize + x;
}

/*
 * @brief 显示路径
 * @note 先将路径网格标记为route，然后画出来，tie可用于解包元组
 * @param img 用于画网格的图像
 * @param grid_size 网格规模大小
 * @param cell_size 网格像素大小
 * @param grids 网格数组
 * @param route 路径网格的指针数组
 */
void showRoute(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids, std::vector<GridCell*> route)
{
	int x, y;
	// 遍历标记route
	for (auto routeGrid : route)// range-based-for循环，遍历route中的每一个元素
	{
		if (!routeGrid->isEnd() && !routeGrid->isStart())
		{
			routeGrid->setRoute();
		}
	}
	// 遍历画图
	for (auto iter = route.begin() + 1; iter != route.end(); iter++)
	{
		std::tie(x, y) = (*iter)->getIndex();// 获取网格坐标
		cv::rectangle(img, cv::Rect(x * cell_size + 3, y * cell_size + 3, cell_size - 5, cell_size - 5), cv::Scalar(0, 120, 120), cv::FILLED);
		cv::imshow("Grid", img);
		cv::waitKey(10);
	}

}
