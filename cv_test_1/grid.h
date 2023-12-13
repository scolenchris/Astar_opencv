#pragma once
#ifndef _GRID_H_
#define _GRID_H_

#include<opencv2/opencv.hpp>
#include<iostream>
#include <ctime>

// �����������������Ϊ�����Σ�
const int grid_size = 64;//�����ģ��С��xx*xx
const int cell_size = 10;//�������ؿ�ȣ����ڻ����񣬺�����������
const int image_size = grid_size * cell_size;//ͼ���С

// �������ͽṹ��
struct GridType
{
	bool block;
	bool start;
	bool end;
	bool route;
};

// �������ݽṹ��
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

	//���ú���
	void setIndex(const int& x, const int& y);
	void setBlock(const bool& r);
	void setStart();
	void setEnd();
	void setRoute();
	void setCost4Way(GridCell* const end);
	void setParent(GridCell* const parent);

	//��¶����
	const std::tuple<int, int> getIndex() const;//������������index (0,0)~(10,10)
	const bool isBlock() const;
	const bool isStart() const;
	const bool isEnd() const;
	const bool isRoute() const;
	const int getGCost() const;
	const int getHCost() const;
	const int getFCost() const;
	GridCell* const getParent() const;

private:
	// �������
	GridType _type;     // ��������
	int _x;				// ����������
	int _y;				// ����������

	// A*�㷨���ò���
	int _gCost = 0; // ��ʼ���߹����Ĵ���
	int _hCost = 0; // ����Ŀ���ľ���
	int _fCost = 0; // �����ܺ�
	GridCell* _parent = NULL; // ������
};

void drawGrid(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids);
void generateObstacles(std::vector<GridCell>& grids);
void gridInit(std::vector<GridCell>& grids, const int& gridsize);
const int getGridNum(const int& gridsize, const int& x, const int& y);//����������,�����Ͻǿ�ʼ��ţ�grids������0~99
void showRoute(cv::Mat& img, const int gridsize, const int cellsize, std::vector<GridCell>& grids, std::vector<GridCell*> route);

#endif // !_GRID_H

