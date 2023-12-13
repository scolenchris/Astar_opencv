#include "config.h"
#pragma region 暴露函数和设置函数

//void ConfigClass::readConfig()
//{
//	bool bReadScreenConfig = false;
//	bool bReadGridNum = false;
//	bool bReadGridLineWidth = false;
//	bool bReadWay = false;
//	bool b4Way;
//
//	std::ifstream file("config.txt", std::ios::in);
//	if (!file)
//	{
//		std::cout << "WARNING: 读取config文件失败" << std::endl;
//		system("pause");
//		exit(0);
//	}
//
//	while (1)
//	{
//		if (file.eof())
//		{
//			std::cout << "WARNING: config文件无结束指令\"END\"" << std::endl;
//			system("pause");
//			exit(0);
//		}
//
//		std::string s;
//		file >> s;
//		if (s.compare("4WayOr8Way") == 0)
//		{
//			int i;
//			file >> i;
//			if (i == 4)
//			{
//				aStarFunc = AStar4Way;
//				b4Way = true;
//			}
//			if (i == 8)
//			{
//				aStarFunc = AStar8Way;
//				b4Way = false;
//			}
//			if (i != 4 && i != 8)
//			{
//				std::cout << "WARNING: config：属性错误：4WayOr8Way" << std::endl;
//				system("pause");
//				exit(0);
//			}
//			bReadWay = true;
//		}
//		else if (s.compare("ScreenConfig(256-2048)") == 0)
//		{
//			file >> windowHeight >> windowWidth;
//			bReadScreenConfig = true;
//		}
//		else if (s.compare("GridNum(5-64)") == 0)
//		{
//			file >> gridNumX >> gridNumY;
//			bReadGridNum = true;
//		}
//		else if (s.compare("GridLineWidth(1-3)") == 0)
//		{
//			file >> gridLineWidth;
//			bReadGridLineWidth = true;
//		}
//		else if (s.compare("End") == 0)
//		{
//			bool bSuccess = true;
//			if (!bReadScreenConfig)
//			{
//				std::cout << "WARNING: config：丢失属性：ScreenConfig" << std::endl;
//				bSuccess = false;
//			}
//			if (!bReadGridNum)
//			{
//				std::cout << "WARNING: config：丢失属性：GridNum" << std::endl;
//				bSuccess = false;
//			}
//			if (!bReadGridLineWidth)
//			{
//				std::cout << "WARNING: config：丢失属性：GridLineWidth" << std::endl;
//				bSuccess = false;
//			}
//			if (!bReadWay)
//			{
//				std::cout << "WARNING: config：丢失属性：4WayOr8Way" << std::endl;
//				bSuccess = false;
//			}
//
//			if (bSuccess)
//			{
//				std::cout << "读取Config文件成功" << std::endl;
//
//				if (b4Way)
//					std::cout << "四连通A*寻路" << std::endl;
//				else
//					std::cout << "八连通A*寻路" << std::endl;
//				std::cout << "屏幕宽高：" << windowWidth << "x" << windowHeight << std::endl;
//				std::cout << "网格数量：" << gridNumX << "x" << gridNumY << std::endl;
//				std::cout << "网格线粗细：" << gridLineWidth << std::endl;
//				std::cout << "======================================" << std::endl;
//				break;
//			}
//			else
//			{
//				system("pause");
//				exit(0);
//			}
//		}
//		else
//		{
//			std::cout << "WARNING: config文件中有未知属性：" << s << std::endl;
//			system("pause");
//			exit(0);
//			break;
//		}
//	}
//	file.close();
//}
#pragma endregion
