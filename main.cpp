/*************************************************************************
*                                                                        *
*               ЛАБОРАТОРНАЯ РАБОТА №3 ПО ООП, 4 СЕМЕСТР                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : main.cpp	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : Вохминова Диана Олеговна, М3О-210Б-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 04.06.2024                                               *
*Comment      : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ. Интерфейсы и АБК			 *
*************************************************************************/

#include <iostream>
#include <windows.h>
#include "Header.h"
using namespace std;

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*++*/
/*   Г Л О Б А Л Ь Н Ы Е   П Е Р Е М Е Н Н Ы Е  И  К О Н С Т А Н Т Ы    */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*+*/
HDC hdc;
HWND GetConcolWindow(); //указатель на консольное окно

// Матрица перехода (по строкам конфликтные объекты, по столбцам велосипеды)

const int ArrSize = 4;

int transitionMatrix[2*ArrSize][ArrSize]
{
	{ 0, 0, 0, 0 },		// Просто велик
	{ 1, 0, 1, 1 },		// Велик халк
	{ 2, 2, 0, 2 },    	// Велик из майнкрафта
	{ 3, 3, 3, 3 },		// Велик неудобный
	{ 2, 2, 0, 2 },		// Букет (ведро)
	{ 2, 3, 0, 3 },		// Камень
	{ 3, 2, 3, 2 },		// Молот тора

};
/************************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                   */
/************************************************************************/

int main()
{
	system("color F0");
	HWND hwnd = GetConcolWindow(); //получим дескриптор консольного окна 

	if (hwnd != NULL) //если дескриптор существует 
	{
		hdc = GetWindowDC(hwnd); //получим контекст устройства для консольного окна 

		if (hdc != NULL)
		{
			int x = 350; //начальные координаты
			int y = 350;
			int handleBarLen = 70; //длина руля
			int handleBarHeight = 10;//высота руля
			int WheelRad = 50; //радиус колес
			int FrameLen = 10; //длина рамы
			int FrameHeight = 100; //высота рамы
			int SeatLen = 30;//длина сиденья
			int SeatHeight = 10;//высота сиденья

			// Экземпляры вылосипедов
			//обычный велосипед
			Bicycle ABicycle(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			//велосипед с зелеными колесами
			BicycleGreenWheel ABicycleGreenWheel(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			ABicycleGreenWheel.SetColor(80, 220, 100); //устанавливаем цвет колес на зеленый
			//велосипед с квадратными колесами
			BicycleSquareWheel ABicycleSquareWheel(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			//Велосипед с большим и маленьким колесами
			BicyclePennyFart ABicyclePennyFart(x, y, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);


			Bicycle* bicycles[ArrSize] = { &ABicycle, &ABicycleGreenWheel, &ABicycleSquareWheel, &ABicyclePennyFart };

			// Конфликтные объекты
			Bucket ABucket(200, 270, 60, 80);
			Stone AStone(900, 400, 30);
			int x1 = 200; int y1 = 700;
			Hammer AHammer(x1, y1, 100, 20, 50, 30);
			MoveToEx(hdc, x1, y1, NULL);
			BicycleGreenWheel ConflictBike(1100, 600, handleBarLen, handleBarHeight, WheelRad, FrameLen, FrameHeight, SeatLen, SeatHeight);
			ConflictBike.SetColor(80, 220, 100); //устанавливаем цвет колес на зеленый)


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
						pBicycle->MoveTo(x, y);	// переход в начальную точку 
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
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}//end GetConcolWindow()