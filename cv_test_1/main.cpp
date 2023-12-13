#include "grid.h"
#include "Astar.h"
#include <iostream>
#include <opencv2/opencv.hpp>

//ȫ�ֱ���
static bool firstClick = true;			  // �Ƿ��ǵ�һ�ε���������ж������ÿ�ʼ�㻹�ǽ�����
GridCell* startGrid = NULL;               // ��ʼ��
GridCell* endGrid = NULL;                 // ������
std::vector<GridCell*> route;             // ·����
bool isSucess = false;                    // �Ƿ��ҵ�·��
cv::Mat image(image_size, image_size, CV_8UC3, cv::Scalar(255, 255, 255)); // ��ɫ����
std::vector<GridCell> grids(grid_size* grid_size);// �������飬�൱�ڵ㼯�ϣ����ڴ洢��������


/*
 * @brief ������¼��ص�����
 * @note ����ʵ������������ɫ����opencv���¼��п��Ա����ã�������βο��Բ��ùܣ���opencv�Ĺ涨
 * @param event ����¼�
 * @param x �������x����
 * @param y �������y����
 * @param flags ������ı�־
 * @param userdata �û�����
 */
void onMouse(int event, int x, int y, int flags, void* userdata) {
	static cv::Point startPt, endPt;
	if (firstClick)
	{
		if (event == cv::EVENT_LBUTTONDOWN) //���������������
		{
			// ��������������к���
			int row = y / cell_size;
			int col = x / cell_size;

			// �л�������ɫ
			if (!grids[col + row * grid_size].isBlock()) {
				// ͨ�����ο������ɫ��������ֱ���������������ɫ
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
		if (event == cv::EVENT_LBUTTONDOWN) //�������������յ�
		{
			// ��������������к���,����ȡ��
			int row = y / cell_size;
			int col = x / cell_size;
			// �л�������ɫ
			if (!grids[col + row * grid_size].isBlock()) {
				// ͨ�����ο������ɫ��������ֱ���������������ɫ
				cv::rectangle(image, cv::Rect(col * cell_size, row * cell_size, cell_size, cell_size), cv::Scalar(0, 255, 0), cv::FILLED);
				cv::imshow("Grid", image);
				grids[col + row * grid_size].setEnd();
				endGrid = &grids[col + row * grid_size];
				// �ر�������任����,�ص������ر�
				cv::setMouseCallback("Grid", NULL);
			}
		}
	}
	if (event == cv::EVENT_RBUTTONDOWN)//�Ҽ�����������ϰ���
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
	gridInit(grids, grid_size);// ��ʼ����������
	generateObstacles(grids);// ��������ϰ���
	drawGrid(image, grid_size, cell_size, grids);// ������

	// �������ڲ�������¼��ص�����
	cv::namedWindow("Grid");
	cv::setMouseCallback("Grid", onMouse);

	// ��ѭ��
	while (true)
	{
		char key = cv::waitKey(1);
		if (startGrid && endGrid && isSucess == false)
		{
			isSucess = AStar4Way(startGrid, endGrid, grids, grid_size);//�����Ƿ�ɹ��ķ���ֵ
			if (isSucess)
			{
				AddAllRouteGridToVector(endGrid, route);//��·���ϵ������������route��
				showRoute(image, grid_size, cell_size, grids, route);//����route����ʾ·��
			}
		}
		// ����ESC���˳�����
		if (key == 27) {
			break;
		}
	}
	cv::imshow("Grid", image);
	cv::destroyAllWindows();
	return 0;
}