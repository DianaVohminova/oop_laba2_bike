/*************************************************************************
*                                                                        *
*               ������������ ������ �3 �� ���, 4 �������                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : main.cpp	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : ��������� ����� ��������, �3�-210�-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 04.06.2024                                               *
*Comment      : ���������� �������� �������. ���������� � ���			 *
*************************************************************************/

#include <iostream>
#include <windows.h>
#include "Header.h"
using namespace std;

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*++*/
/*   � � � � � � � � � �   � � � � � � � � � �  �  � � � � � � � � �    */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*+*/
HDC hdc;
HWND GetConcolWindow(); //��������� �� ���������� ����

// ������� �������� (�� ������� ����������� �������, �� �������� ����������)

const int ArrSize = 4;

int transitionMatrix[2*ArrSize][ArrSize]
{
	{ 0, 0, 0, 0 },		// ������ �����
	{ 1, 0, 1, 1 },		// ����� ����
	{ 2, 2, 0, 2 },    	// ����� �� ����������
	{ 3, 3, 3, 3 },		// ����� ���������
	{ 2, 2, 0, 2 },		// ����� (�����)
	{ 2, 3, 0, 3 },		// ������
	{ 3, 2, 3, 2 },		// ����� ����

};
/************************************************************************/
/*               � � � � � � � �    � � � � � � � � �                   */
/************************************************************************/

int main()
{
	system("color F0");
	HWND hwnd = GetConcolWindow(); //������� ���������� ����������� ���� 

	if (hwnd != NULL) //���� ���������� ���������� 
	{
		hdc = GetWindowDC(hwnd); //������� �������� ���������� ��� ����������� ���� 

		if (hdc != NULL)
		{
			int x = 350; //��������� ����������
			int y = 350;
			int handleBarLen = 70; //����� ����
			int handleBarHeight = 10;//������ ����
			int WheelRad = 50; //������ �����
			int FrameLen = 10; //����� ����
			int FrameHeight = 100; //������ ����
			int SeatLen = 30;//����� �������
			int SeatHeight = 10;//������ �������

			// ���������� �����������
			//������� ���������
			Bicycle ABicycle(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			//��������� � �������� ��������
			BicycleGreenWheel ABicycleGreenWheel(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			ABicycleGreenWheel.SetColor(80, 220, 100); //������������� ���� ����� �� �������
			//��������� � ����������� ��������
			BicycleSquareWheel ABicycleSquareWheel(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			//��������� � ������� � ��������� ��������
			BicyclePennyFart ABicyclePennyFart(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);


			Bicycle* bicycles[ArrSize] = { &ABicycle, &ABicycleGreenWheel, &ABicycleSquareWheel, &ABicyclePennyFart };

			// ����������� �������
			Bucket ABucket(200, 270, 60, 80);
			Stone AStone(900, 400, 30);
			int x1 = 200; int y1 = 700;
			Hammer AHammer(x1, y1, 100, 20, 50, 30);
			MoveToEx(hdc, x1, y1, NULL);
			BicycleGreenWheel ConflictBike(1100, 600, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			ConflictBike.SetColor(80, 220, 100); //������������� ���� ����� �� �������)


			Figure* objects[ArrSize] = { &ABucket, &AStone, &AHammer, &ConflictBike };

			Bicycle* pBicycle = &ABicycle;
			pBicycle->Show();

			for (int i = 0; i < 4; i++) { objects[i]->Show(); }

			while (true)
			{
				pBicycle->Drag(20);
				for (int i = 0; i < 4; i++) { objects[i]->Show(); }
				for (int i = 0; i < 4; i++)
				{
					if (Collision(*pBicycle, *objects[i]))
					{
						pBicycle->MoveTo(x, y);	// ������� � ��������� ����� 
						pBicycle->Hide();
						pBicycle = bicycles[transitionMatrix[objects[i]->getIndex()][pBicycle->getIndex()]];
						pBicycle->Show();
						for (int i = 0; i < 3; i++) { objects[i]->Show(); }
						break;
					}//if
				}
				for (int i = 0; i < 4; i++) { objects[i]->Show(); }
				Sleep(20);
			}
		}
	}
	return 0;
}//main()

HWND GetConcolWindow()
{

	char str[128];
	//char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//����� ������ Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // �������� ��������� ����
	SetConsoleTitle(title);						// ���������� ����� ��������� ����
	Sleep(100);									// ���� ����� ��������� ���� (100 ��);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// ���������� ���������� ����
	SetConsoleTitle((LPWSTR)str);				//���������� ������� ���������

	return hwnd;//������� ���������� ����
}//end GetConcolWindow()