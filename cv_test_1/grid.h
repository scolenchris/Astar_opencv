#pragma once
#ifndef _GRID_H_
#define _GRID_H_

#include<opencv2/opencv.hpp>
#include<iostream>
#include <ctime>

// 网格参数，网格设置为正方形，
const int grid_size = 64;//网格规模大小，xx*xx
const int cell_size = 10;//网格像素宽度，用于画网格，和推算网格编号
const int image_size = grid_size * cell_size;//图像大小

// 网格类型结构体
struct GridType
{
	bool block;
	bool start;
	bool end;
	bool route;
};

// 网格数据结构体
struct GridCell {
public:
	GridCell()
	{
		_type.block = false;
		_type.end = false;
		_type.start = false;
		_type.route = false;
		_x = 0;
		_y = 0;
	}

	//设置函数
	void setIndex(const int& x, const int& y);
	void setBlock(const bool& r);
	void setStart();
	void setEnd();
	void setRoute();
	void setCost4Way(GridCell* const end);
	void setParent(GridCell* const parent);

	//暴露函数
	const std::tuple<int, int> getIndex() const;//返回网格坐标index (0,0)~(10,10)
	const bool isBlock() const;
	const bool isStart() const;
	const bool isEnd() const;
	const bool isRoute() const;
	const int getGCost() const;
	const int getHCost() const;
	const int getFCost() const;
	GridCell* const getParent() const;

private:
	// 网格参数
	GridType _type;     // 网格类型
	int _x;				// 网格所在行
	int _y;				// 网格所在列

	// A*算法所用参数
	int _gCost = 0; // 开始点走过来的代价
	int _hCost = 0; // 距离目标点的距离
	int _fCost = 0; // 代价总和
	GridCell* _parent = NULL; // 父网格
};

void drawGrid(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids);
void generateObstacles(std::vector<GridCell>& grids);
void gridInit(std::vector<GridCell>& grids, const int& gridsize);
const int getGridNum(const int& gridsize, const int& x, const int& y);//返回网格编号,从左上角开始编号，grids的索引0~99
void showRoute(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids, std::vector<GridCell*> route);

#endif // !_GRID_H

