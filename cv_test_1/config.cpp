#include "config.h"
#pragma region ��¶���������ú���

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
//		std::cout << "WARNING: ��ȡconfig�ļ�ʧ��" << std::endl;
//		system("pause");
//		exit(0);
//	}
//
//	while (1)
//	{
//		if (file.eof())
//		{
//			std::cout << "WARNING: config�ļ��޽���ָ��\"END\"" << std::endl;
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
//				std::cout << "WARNING: config�����Դ���4WayOr8Way" << std::endl;
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
//				std::cout << "WARNING: config����ʧ���ԣ�ScreenConfig" << std::endl;
//				bSuccess = false;
//			}
//			if (!bReadGridNum)
//			{
//				std::cout << "WARNING: config����ʧ���ԣ�GridNum" << std::endl;
//				bSuccess = false;
//			}
//			if (!bReadGridLineWidth)
//			{
//				std::cout << "WARNING: config����ʧ���ԣ�GridLineWidth" << std::endl;
//				bSuccess = false;
//			}
//			if (!bReadWay)
//			{
//				std::cout << "WARNING: config����ʧ���ԣ�4WayOr8Way" << std::endl;
//				bSuccess = false;
//			}
//
//			if (bSuccess)
//			{
//				std::cout << "��ȡConfig�ļ��ɹ�" << std::endl;
//
//				if (b4Way)
//					std::cout << "����ͨA*Ѱ·" << std::endl;
//				else
//					std::cout << "����ͨA*Ѱ·" << std::endl;
//				std::cout << "��Ļ��ߣ�" << windowWidth << "x" << windowHeight << std::endl;
//				std::cout << "����������" << gridNumX << "x" << gridNumY << std::endl;
//				std::cout << "�����ߴ�ϸ��" << gridLineWidth << std::endl;
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
//			std::cout << "WARNING: config�ļ�����δ֪���ԣ�" << s << std::endl;
//			system("pause");
//			exit(0);
//			break;
//		}
//	}
//	file.close();
//}
#pragma endregion
