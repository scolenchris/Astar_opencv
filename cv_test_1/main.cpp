#include "grid.h"
#include "Astar.h"
#include <iostream>
#include <opencv2/opencv.hpp>

//全局变量
static bool firstClick = true;			  // 是否是第一次点击，用于判断是设置开始点还是结束点
GridCell* startGrid = NULL;               // 开始点
GridCell* endGrid = NULL;                 // 结束点
std::vector<GridCell*> route;             // 路径点
bool isSucess = false;                    // 是否找到路径
cv::Mat image(image_size, image_size, CV_8UC3, cv::Scalar(255, 255, 255)); // 白色背景
std::vector<GridCell> grids(grid_size* grid_size);// 网格数组，相当于点集合，用于存储所有网格


/*
 * @brief 鼠标点击事件回调函数
 * @note 用于实现鼠标点击网格变色，在opencv的事件中可以被调用，下面的形参可以不用管，是opencv的规定
 * @param event 鼠标事件
 * @param x 鼠标点击的x坐标
 * @param y 鼠标点击的y坐标
 * @param flags 鼠标点击的标志
 * @param userdata 用户数据
 */
void onMouse(int event, int x, int y, int flags, void* userdata) {
	static cv::Point startPt, endPt;
	if (firstClick)
	{
		if (event == cv::EVENT_LBUTTONDOWN) //左键点击，设置起点
		{
			// 计算所在网格的行和列
			int row = y / cell_size;
			int col = x / cell_size;

			// 切换网格颜色
			if (!grids[col + row * grid_size].isBlock()) {
				// 通过矩形框填充颜色，而不是直接在网格上填充颜色
				cv::rectangle(image, cv::Rect(col * cell_size, row * cell_size, cell_size, cell_size), cv::Scalar(0, 0, 255), cv::FILLED);
				cv::imshow("Grid", image);
				firstClick = false;
				grids[col + row * grid_size].setStart();
				startGrid = &grids[col + row * grid_size];
			}
		}
	}
	else
	{
		if (event == cv::EVENT_LBUTTONDOWN) //左键点击，设置终点
		{
			// 计算所在网格的行和列,向下取整
			int row = y / cell_size;
			int col = x / cell_size;
			// 切换网格颜色
			if (!grids[col + row * grid_size].isBlock()) {
				// 通过矩形框填充颜色，而不是直接在网格上填充颜色
				cv::rectangle(image, cv::Rect(col * cell_size, row * cell_size, cell_size, cell_size), cv::Scalar(0, 255, 0), cv::FILLED);
				cv::imshow("Grid", image);
				grids[col + row * grid_size].setEnd();
				endGrid = &grids[col + row * grid_size];
				// 关闭鼠标点击变换功能,回调函数关闭
				cv::setMouseCallback("Grid", NULL);
			}
		}
	}
	if (event == cv::EVENT_RBUTTONDOWN)//右键点击，设置障碍物
	{
		int row = y / cell_size;
		int col = x / cell_size;
		if (!grids[col + row * grid_size].isBlock()) {
			cv::rectangle(image, cv::Rect(col * cell_size + 1, row * cell_size + 1, cell_size - 2, cell_size - 2), cv::Scalar(100, 30, 10), cv::FILLED);
			cv::imshow("Grid", image);
			grids[col + row * grid_size].setBlock(true);
		}
		else
		{
			cv::rectangle(image, cv::Rect(col * cell_size + 1, row * cell_size + 1, cell_size - 2, cell_size - 2), cv::Scalar(255, 255, 255), cv::FILLED);
			cv::imshow("Grid", image);
			grids[col + row * grid_size].setBlock(false);
		}
	}
}

int main() {
	gridInit(grids, grid_size);// 初始化网格数组
	generateObstacles(grids);// 随机生成障碍物
	drawGrid(image, grid_size, cell_size, grids);// 画格子

	// 创建窗口并绑定鼠标事件回调函数
	cv::namedWindow("Grid");
	cv::setMouseCallback("Grid", onMouse);

	// 主循环
	while (true)
	{
		char key = cv::waitKey(1);
		if (startGrid && endGrid && isSucess == false)
		{
			isSucess = AStar4Way(startGrid, endGrid, grids, grid_size);//接收是否成功的返回值
			if (isSucess)
			{
				AddAllRouteGridToVector(endGrid, route);//将路径上的所有网格放入route中
				showRoute(image, grid_size, cell_size, grids, route);//输入route，显示路径
			}
		}
		// 按下ESC键退出程序
		if (key == 27) {
			break;
		}
	}
	cv::imshow("Grid", image);
	cv::destroyAllWindows();
	return 0;
}