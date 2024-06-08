/*************************************************************************
*                                                                        *
*               ЛАБОРАТОРНАЯ РАБОТА №3 ПО ООП, 4 СЕМЕСТР                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : Source.cpp	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : Вохминова Диана Олеговна, М3О-210Б-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 04.06.2024                                               *
*Comment      : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ. Интерфейсы и АБК			 *
*************************************************************************/

#include <Windows.h>
#include "Header.h"		// файл с объявлениями классов
extern HDC hdc;			// объявление контекста устройства
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*----------------------------------------------------------------------*/
/*                Р Е А Л И З А Ц И Я    М Е Т О Д О В                  */
/*----------------------------------------------------------------------*/
/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Location          */
/*----------------------------------------*/
//конструктор
Location::Location(int InitX, int InitY)
{
	//инициализация закрытых переменных своего класса
	X = InitX;
	Y = InitY;
};//Location::Location()

//деструктор
Location::~Location(void)  //формально пустое тело
{
};//Location::~Location()

//получить X координату точки
int Location::GetX(void)
{
	return X;
};//Location::GetX()	

//получить Y координату точки
int Location::GetY(void)
{
	return Y;
}; //Location::GetY()
/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Point             */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
	//инициализация закрытых переменных своего класса
	Visible = false;
}//Point::Point()

 //деструктор
Point::~Point(void)   //формально пустое тело
{
}//Point::~Point()

 //показать ТОЧКУ
void Point::Show(void)
{
	Visible = true;
	for (int x = 0; x <= 3; x++)
		for (int y = 0; y <= 3; y++)
			SetPixel(hdc, X + x, Y + y, RGB(255, 0, 0));//рисуем красным цветом
}//end Point::Show()

 //скрыть ТОЧКУ
void Point::Hide(void)
{
	Visible = false;
	for (int x = 0; x <= 3; x++)
		for (int y = 0; y <= 3; y++)
			SetPixel(hdc, X, Y, RGB(0, 0, 255));//рисуем синим цветом или фона
}//Point::Hide()

 //узнать про светимость ТОЧКИ
bool Point::IsVisible(void)
{
	return Visible;
};//Point::IsVisible()

//переместить ТОЧКУ
void Point::MoveTo(int NewX, int NewY)
{
	Hide();		//сделать точку невидимой 
	X = NewX;	//поменять координаты ТОЧКИ
	Y = NewY;
	Show();		//показать точку на новом месте
};//Point::MoveTo()

//буксировка ФИГУРЫ
void Point::Drag(int Step)
{
	int figX, figY; //новые координаты фигуры
	figX = GetX(); //получаем начальные координаты фигуры
	figY = GetY();

	//бесконечный цикл буксировки фигуры
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - конец работы
			break;

		//выбор направления движения фигуры
		if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
		{
			figX -= Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
		{
			figX += Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
		{
			figY += Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
		{
			figY -= Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if
	}//while
}//Point::Drag()

Figure::Figure(int InitX, int InitY) : Point(InitX, InitY)
{
}

Figure::~Figure()
{
}// деструктор

int Figure::getIndex() {
	return index;
}

// Получить из protected координату Х (право-низ)
int Figure::get_xRB()
{
	return xRightBottom;
}

// Получить из protected координату Y (право-низ)
int Figure::get_yRB()
{
	return yRightBottom;
}

// Получить из protected координату Х (лево-вверх)
int Figure::get_xLUp()
{
	return xLeftUp;
}

// Получить из protected координату Y (лево-вверх)
int Figure::get_yLUp()
{
	return yLeftUp;
}

/*-----------------------------------------*/
/*        МЕТОДЫ КЛАССА Bicycle            */
/*-----------------------------------------*/
//конструктор
Bicycle::Bicycle(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH) : Figure(InitX, InitY)
{
	handleBarLen = hbL;  // длина руля
	handleBarHeight = hbH; //высота руля
	WheelRad = Rad; // радиус колес
	FrameLen = fL; //длина рамы
	FrameHeight = fH; //высота рамы
	SeatLen = sL;//ширина сиденья
	SeatHeight = sH;//высота сиденья

	index = 0;
}//Bicycle::Bicycle()

//декструктор
Bicycle::~Bicycle() {
	//empty body
}//Bicycle::~Bicycle()


//показать фигуру
void Bicycle::Show()
{
	//if (Visible == true)
	//	return;
	Visible = true;
	makeHitbox();
	Weels();
	Frame();
	Seat();
	HandleBar();
}//Bicycle::Show()

//скрыть фигуру
void Bicycle::Hide()
{
	Visible = false;

	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //ручка цвета фона

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка цвета фона
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//Передняя рама
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//задняя рама
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//перекладина
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//сидение
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//руль


	DeleteObject(pen);
	DeleteObject(penW);
}//Bicycle::Hide()

void Bicycle::Weels()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(0, 0, 0)); //ручка черного цвета

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо
	DeleteObject(penW);
}

void Bicycle::Frame()
{
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //ручка черного цвета
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//Передняя рама
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//задняя рама
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//перекладина

	DeleteObject(pen);
}

void Bicycle::Seat()
{
	
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //ручка черного цвета
	SelectObject(hdc, pen);
	
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//сидение
	
	DeleteObject(pen);
}

void Bicycle::HandleBar()
{
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //ручка черного цвета
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//руль
	DeleteObject(pen);
}

void Bicycle::makeHitbox()
{
	xRightBottom = X + 5 * WheelRad;	// Координата Х (правая)
	yRightBottom = Y + 2 * WheelRad;	// Координата Y (нижняя)
	xLeftUp = X;						// Координата Х (левая)
	yLeftUp = Y;						// Координата Y (верхняя)
}

//буксировка фигуры
void Bicycle::Drag(int Step)
{
	int figX, figY; //новые координаты фигуры

	figX = GetX(); //получаем начальные координаты фигуры
	figY = GetY();
	//выбор направления движения фигуры
	if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
	{
		figX -= Step;
		xLeftUp -= Step;		// Изменение границ фигуры (слева)
		xRightBottom -= Step;	// Изменение границ фигуры (справа)
		MoveTo(figX, figY);
		Sleep(50); //задержка экрана на 500 милисекунд
		return;
	}//if

	if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
	{
		figX += Step;
		xRightBottom += Step;				// Изменение границ фигуры (справа)
		xLeftUp += Step;					// Изменение границ фигуры (слева)
		MoveTo(figX, figY);
		Sleep(50); //задержка экрана на 500 милисекунд
		return;
	}//if

	if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
	{
		figY += Step;
		yRightBottom += Step;		// Изменение границ фигуры (снизу)
		yLeftUp += Step;			// Изменение границ фигуры (сверху)
		MoveTo(figX, figY);
		Sleep(50); //задержка экрана на 500 милисекунд
		return;
	}//if

	if (KEY_DOWN(VK_UP)) //38 стрелка вверх
	{
		figY -= Step;
		yRightBottom -= Step;		// Изменение границ фигуры (снизу)
		yLeftUp -= Step;			// Изменение границ фигуры (сверху)
		MoveTo(figX, figY);
		Sleep(50); //задержка экрана на 500 милисекунд
		return;
	}
}// Bicycle::Drag()

// Получить из protected длину руля
int Bicycle::getHandleBarLen()
{
	return handleBarLen;
}
// Получить из protected высоту руля
int Bicycle::getHandleBarHeight()
{
	return handleBarHeight;
}
// Получить из protected радиус колес
int Bicycle::getWheelRad()
{
	return WheelRad;
}
// Получить из protected длину рамы
int Bicycle::getFrameLen()
{
	return FrameLen;
}
// Получить из protected высоту рамы
int Bicycle::getFrameHeight()
{
	return FrameHeight;
}
// Получить из protected ширину сиденья
int Bicycle::getSeatLen()
{
	return SeatLen;
}
// Получить из protected высоту сиденья
int Bicycle::getSeatHeight()
{
	return SeatHeight;
}
/*----------------------------------------*/
/*      МЕТОДЫ КЛАССА BicycleGreenWheel   */
/*----------------------------------------*/
void BicycleGreenWheel::SetColor(int r, int g, int b)
{
	colorWheelRed = r;
	colorWheelGreen = g;
	colorWheelBlue = b;
}
//конструктор
BicycleGreenWheel::BicycleGreenWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH)
	: Bicycle(InitX, InitY, hbL, hbH, Rad, fL, fH, sL, sH)
{
	index = 1;
}//BicycleGreenWheel::BicycleGreenWheel()

//декструктор
BicycleGreenWheel::~BicycleGreenWheel() {
	//empty body
}//BicycleGreenWheel::~BicycleGreenWheel()

//скрыть фигуру
void BicycleGreenWheel::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //ручка цвета фона

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка цвета фона
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//Передняя рама
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//задняя рама
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//перекладина
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//сидение
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//руль


	DeleteObject(pen);
	DeleteObject(penW);
	// Скрыть родителя
	Bicycle::Hide();
}//BicycleGreenWheel::Hide()

void BicycleGreenWheel::Weels()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(colorWheelRed, colorWheelGreen, colorWheelBlue)); //ручка ЗЕЛЕНОГО цвета 

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Ellipse(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо
	DeleteObject(penW);
}

/*----------------------------------------*/
/*      МЕТОДЫ КЛАССА BicycleSquareWheel   */
/*----------------------------------------*/
//конструктор
BicycleSquareWheel::BicycleSquareWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH)
	: Bicycle(InitX, InitY, hbL, hbH, Rad, fL, fH, sL, sH)
{
	index = 2;
}//BicycleGreenWheel::BicycleGreenWheel()

//декструктор
BicycleSquareWheel::~BicycleSquareWheel() {
	//empty body
}//BicycleSquareWheel::~BicycleSquareWheel()

//скрыть фигуру
void BicycleSquareWheel::Hide()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //ручка цвета фона

	SelectObject(hdc, penW);

	Rectangle(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо

	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка цвета фона
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//Передняя рама
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//задняя рама
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//перекладина
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//сидение
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//руль


	DeleteObject(pen);
	DeleteObject(penW);
	Bicycle::Hide();//Скрыли родителя
}//BicycleSquareWheel::Hide()

void BicycleSquareWheel::Weels()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(0, 0, 0)); //ручка ЗЕЛЕНОГО цвета

	SelectObject(hdc, penW);

	Rectangle(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо
	DeleteObject(penW);
}

/*----------------------------------------*/
/*      МЕТОДЫ КЛАССА BicyclePennyFart    */
/*----------------------------------------*/
//конструктор
BicyclePennyFart::BicyclePennyFart(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH)
	: Bicycle(InitX, InitY, hbL, hbH, Rad, fL, fH, sL, sH)
{
	index = 3;

}//BicyclePennyFart::BicyclePennyFart()

//декструктор
BicyclePennyFart::~BicyclePennyFart() {
	//empty body
}//BicyclePennyFart::~BicyclePennyFart()

//скрыть фигуру
void BicyclePennyFart::Hide()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(255, 255, 255)); //ручка цвета фона

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо


	HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка цвета фона
	SelectObject(hdc, pen);
	Rectangle(hdc, X + WheelRad - 0.5 * FrameLen, Y - 0.5 * FrameHeight, X + WheelRad + 0.5 * FrameLen, Y + WheelRad);	//Передняя рама
	Rectangle(hdc, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad + 0.5 * FrameLen, Y + WheelRad);//задняя рама
	Rectangle(hdc, X + WheelRad + 0.5 * FrameLen, Y - 0.3 * FrameHeight, X + 4 * WheelRad - 0.5 * FrameLen, Y - 0.3 * FrameHeight + FrameLen);//перекладина
	Rectangle(hdc, X + 4 * WheelRad - 2 * SeatLen, Y - 0.3 * FrameHeight - SeatHeight, X + 4 * WheelRad + 0.5 * FrameLen - SeatLen, Y - 0.3 * FrameHeight);//сидение
	Rectangle(hdc, X + WheelRad - 0.3 * handleBarLen, Y - 0.5 * FrameHeight - handleBarHeight, X + WheelRad + 0.6 * handleBarLen, Y - 0.5 * FrameHeight);//руль


	DeleteObject(pen);
	DeleteObject(penW);
	Bicycle::Hide();//Скрыть родителя
}//BicyclePennyFart::Hide()

void BicyclePennyFart::Weels()
{
	HPEN penW = CreatePen(PS_SOLID, 11, RGB(0, 0, 0)); //ручка черного цвета

	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * WheelRad, Y + 2 * WheelRad);//переднее колесо
	Rectangle(hdc, X + 3 * WheelRad, Y, X + 5 * WheelRad, Y + 2 * WheelRad);//заднее колесо
	DeleteObject(penW);
}


/*----------------------------------------*/
/*      МЕТОДЫ КЛАССА Bucket			  */
/*----------------------------------------*/
//конструктор
Bucket::Bucket(int InitX, int InitY, int lB, int hB) : Figure(InitX, InitY)
{
	LenBucket = lB;
	HeightBucket = hB;

	index = 4;
}

//деструктор
Bucket::~Bucket() {}//Bucket::~Bucket()

//показать фигуру
void Bucket::Show()
{
	Visible = true;
	makeHitbox();
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //ручка черного цвета
	SelectObject(hdc, penW);

	//стенки ведра
	Rectangle(hdc, X, Y, X + LenBucket, Y + HeightBucket);

	DeleteObject(penW);
}//Bucket::Show()

//скрыть фигуру
void Bucket::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка цвета фона
	SelectObject(hdc, penW);

	Rectangle(hdc, X, Y, X + LenBucket, Y + HeightBucket);

	DeleteObject(penW);

}//Bucket::Hide()

void Bucket::makeHitbox()
{
	xLeftUp = X;
	yLeftUp = Y;
	xRightBottom = xLeftUp + LenBucket;
	yRightBottom = yLeftUp + HeightBucket;
}

/*----------------------------------------*/
/*       МЕТОДЫ КЛАССА Stone		      */
/*----------------------------------------*/
//конструктор
Stone::Stone(int InitX, int InitY, int rS) : Figure(InitX, InitY)
{
	RadiusStone = rS;
	index = 5;
}
//деструктор
Stone::~Stone()
{
	//empty body
}//Bucket::~Bucket()

//показать фигуру
void Stone::Show()
{
	Visible = true;
	makeHitbox();

	HPEN penW = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //ручка черного цвета
	SelectObject(hdc, penW);

	Ellipse(hdc, X, Y, X + 2 * RadiusStone, Y + RadiusStone);

	DeleteObject(penW);
}//Stone::Show()

//скрыть фигуру
void Stone::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка черного цвета
	SelectObject(hdc, penW);

	Ellipse(hdc, X - RadiusStone, Y - 0.5 * RadiusStone, X + RadiusStone, Y + 0.5 * RadiusStone);

	DeleteObject(penW);

}//Stone::Hide()

void Stone::makeHitbox()
{
	xLeftUp = X;
	yLeftUp = Y;
	xRightBottom = xLeftUp + 2 * RadiusStone;
	yRightBottom = yLeftUp + RadiusStone;
}

/*----------------------------------------*/
/*       МЕТОДЫ КЛАССА Hammer		     */
/*----------------------------------------*/
//конструктор
Hammer::Hammer(int InitX, int InitY, int sL, int sW, int hL, int hW) : Figure(InitX, InitY)
{
	StickLen = sL;
	StickW = sW;

	HeadLen = hL;
	HeadW = hW;

	index = 6;
}
//деструктор
Hammer::~Hammer() {}//Hammer::~Hammer()

//показать фигуру
void Hammer::Show()
{
	Visible = true;
	makeHitbox();
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(0, 0, 0)); //ручка черного цвета
	SelectObject(hdc, penW);

	LineTo(hdc, X + HeadLen, Y);
	LineTo(hdc, X + 1.5 * HeadLen, Y + HeadW);
	LineTo(hdc, X, Y + HeadW);
	LineTo(hdc, X, Y);
	Rectangle(hdc, X + 0.5 * HeadLen, Y + HeadW, X + 0.5 * HeadLen + StickW, Y + HeadW + StickLen);

	DeleteObject(penW);
}//Hammer::Show()

//скрыть фигуру
void Hammer::Hide()
{
	Visible = false;
	HPEN penW = CreatePen(PS_SOLID, 5, RGB(255, 255, 255)); //ручка черного цвета
	SelectObject(hdc, penW);

	LineTo(hdc, X + HeadLen, Y);
	LineTo(hdc, X + 1.5 * HeadLen, Y + HeadW);
	LineTo(hdc, X, Y + HeadW);
	LineTo(hdc, X, Y);
	Rectangle(hdc, X + 0.5 * HeadLen, Y + HeadW, X + 0.5 * HeadLen + StickW, Y + HeadW + StickLen);

	DeleteObject(penW);

}//Hammer::Hide()

void Hammer::makeHitbox()
{
	xLeftUp = X;
	yLeftUp = Y;
	xRightBottom = xLeftUp + 1.5 * HeadLen;
	yRightBottom = yLeftUp + +HeadW + StickLen;
}

bool Collision(Figure& obj1, Figure& obj2)
{
	// Определение столкновения слева
	bool left = obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xRB() >= obj1.get_xRB()
		&& (obj2.get_yLUp() <= obj1.get_yRB() && obj2.get_yLUp() >= obj1.get_yLUp()
			|| obj2.get_yRB() >= obj1.get_yLUp() && obj2.get_yRB() <= obj1.get_yRB());
	// Определение столкновений справа
	bool right = obj2.get_xRB() >= obj1.get_xLUp() && obj2.get_xLUp() <= obj1.get_xLUp()
		&& (obj2.get_yLUp() <= obj1.get_yRB() && obj2.get_yLUp() >= obj1.get_yLUp()
			|| obj2.get_yRB() >= obj1.get_yLUp() && obj2.get_yRB() <= obj1.get_yRB());
	// Определение столкновений сверху
	bool top = obj2.get_yLUp() <= obj1.get_yLUp() && obj2.get_yRB() >= obj1.get_yLUp()
		&& (obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xLUp() >= obj1.get_xLUp()
			|| obj2.get_xLUp() >= obj1.get_xLUp() && obj2.get_xRB() <= obj1.get_xRB());
	// Определение столкновений снизу
	bool bottom = obj2.get_yRB() >= obj1.get_yRB() && obj2.get_yLUp() <= obj1.get_yRB()
		&& (obj2.get_xLUp() <= obj1.get_xRB() && obj2.get_xLUp() >= obj1.get_xLUp()
			|| obj2.get_xRB() >= obj1.get_xLUp() && obj2.get_xRB() <= obj1.get_xRB());
	// Определение того, находится ли препятствие "внутри" фигуры
	bool inside = obj2.get_xLUp() >= obj1.get_xLUp() && obj2.get_yLUp() >= obj1.get_yLUp() &&
		obj2.get_xRB() <= obj1.get_xRB() && obj2.get_yRB() <= obj1.get_yRB();
	// Если хоть одно условие выполняется, то столкновение есть
	return left || right || top || bottom || inside; 
}

