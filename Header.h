#pragma once
/*************************************************************************
*                                                                        *
*               ������������ ������ �3 �� ���, 4 �������                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP_Bicycle		                                         *
*File name    : Header.h	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : ��������� ����� ��������, �3�-210�-22	                 *
*Modified by  :                                                          *
*Created      : 14.04.2024                                               *
*Last revision: 04.06.2024                                               *
*Comment      : ���������� �������� �������. ���������� � ���			 *
*************************************************************************/

/*----------------------------------------------------------------------*/
/*                        � � � �    � � � � � �                        */
/*----------------------------------------------------------------------*/

 /*----------------------  ����� �������������� ------------------------*/
class Location
{
protected:		//������������� ����������� �������� (������������
	//������) ����� ������ � ������� ������
	int X;		//���������� �
	int Y;		//���������� Y

public:			//��� ������ �������� ����� ���� � ���������
	Location(int InitX, int InitY);	//�����������
	~Location();					//����������
	int GetX();						//�������� � ���������� �����
	int GetY();						//�������� Y ���������� �����
};//class Location

/*-----------------------  ����� ����� ---------------------------------*/

// Point - ����������� ����� �� Location
class Point : public Location
{
protected:							//�������, ����������� �� Point, ����������� ������ public
	bool Visible;					//���������� �����

public:
	Point(int InitX, int InitY);	//����������� ������
	~Point();						//����������
	bool IsVisible();				//������ ��� ���������� �����
	void MoveTo(int NewX, int NewY);//����������� ������
	void Drag(int Step);			//���������� ������

	//����������� ������ (����� ����������)
	//void Show();					//
	//void Hide();					//

	//����������� ������ (������� ����������)
	virtual void Show();			// �������� ������ �����
	virtual void Hide();			// ������ ������ �����
};

class Figure : public Point
{
protected:
	int xRightBottom;				// ���������� � (�����-���)
	int yRightBottom;				// ���������� Y (�����-���)
	int xLeftUp;					// ���������� � (����-����)
	int yLeftUp;					// ���������� Y (����-����)
	int index;						// ������ ������� ��������
public:
	Figure(int InitX = 0, int InitY = 0);	// �����������
	~Figure();								// ����������
	int getIndex();							// �������� ������ �� protected
	int get_xRB();			// �������� �� protected ���������� � (�����-���)
	int get_yRB();			// �������� �� protected ���������� Y (�����-���)
	int get_xLUp();			// �������� �� protected ���������� � (����-�����)	
	int get_yLUp();			// �������� �� protected ���������� Y (����-�����)
	virtual void makeHitbox() = 0;
};

class IBicycle
{
	virtual void Weels() = 0;//������
	virtual void Frame() = 0;//����
	virtual void Seat() = 0;//�������
	virtual void HandleBar() = 0; //����
};

/*-----------------------  ����� ��������� --------------------------------*/
class Bicycle : public Figure, IBicycle
{
protected:

	int handleBarLen;				// ����� ����
	int handleBarHeight;			//������ ����
	int WheelRad;					// ������ �����
	int FrameLen;					//����� ����
	int FrameHeight;				//������ ����
	int SeatLen;					//������ �������
	int SeatHeight;					//������ �������
	
public:
	Bicycle(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //�����������
	~Bicycle(); //�����������

	virtual void Drag(int step); //����������� ������
	virtual void Show(); //�������� ������
	virtual void Hide(); //������ ������

	int getHandleBarLen();  // �������� �� protected ����� ����
	int getHandleBarHeight(); // �������� �� protected ������ ����
	int getWheelRad();		// �������� �� protected ������ �����
	int getFrameLen();		// �������� �� protected ����� ����
	int getFrameHeight();	// �������� �� protected ������ ����
	int getSeatLen();		// �������� �� protected ������ �������
	int getSeatHeight();	// �������� �� protected ������ �������
	virtual void Weels();//������
	virtual void Frame();//����
	virtual void Seat();//�������
	virtual void HandleBar(); //����
	virtual void makeHitbox();

};//class Bicycle
/*-----------------------  ����� ��������� - ������� ������ ----------------------------------*/
class BicycleGreenWheel : public Bicycle
{
protected:
	int colorWheelRed; //���� �����
	int colorWheelGreen; //���� �����
	int colorWheelBlue; //���� �����

public:
	BicycleGreenWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //�����������
	~BicycleGreenWheel(); //�����������

	void SetColor(int r, int g, int b); //��������� ����� ������

	virtual void Hide(); //������ ������
	virtual void Weels();//������

};//class BycicleGreenWheel
/*-----------------------  ����� ��������� - ���������� ������ ----------------------------------*/
class BicycleSquareWheel : public Bicycle
{
protected:
	int RadiusSquareWheel; //������ ����������� ������

public:
	BicycleSquareWheel(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //�����������
	~BicycleSquareWheel(); //�����������

	virtual void Hide(); //������ ������
	virtual void Weels();//������

};//class BicycleSquareWheel
/*-----------------------  ����� ��������� - ������� � ��������� ������ ----------------------------------*/
class BicyclePennyFart : public Bicycle
{
protected:
	int RadiusFirstWheel; //������ ������� ������
	int RadiusSecondWheel; //������ ������� ������

public:
	BicyclePennyFart(int InitX, int InitY, int hbL, int hbH, int Rad, int fL, int fH, int sL, int sH); //�����������
	~BicyclePennyFart(); //�����������

	virtual void Hide(); //������ ������

	virtual void Weels();//������

};//class BicyclePennyFart

/*-----------------------------------  ������������� �������  ------------------------------------*/

// -------------------�����---------------------
class Bucket : public Figure
{
protected:
	int LenBucket; // ������ �����
	int HeightBucket; //������ �����
public:
	Bucket(int InitX, int InitY, int lB, int hB);
	~Bucket(); //����������

	virtual void Show();
	virtual void Hide();
	virtual void makeHitbox();
}; //class Bucket

// -------------------������---------------------
class Stone : public Figure
{
protected:
	int RadiusStone; // ������ �����
public:
	Stone(int InitX, int InitY, int rS);
	~Stone(); //����������

	virtual void Show();
	virtual void Hide();
	virtual void makeHitbox();

}; //class Stone
// -------------------�������---------------------
class Hammer :public Figure
{
protected:
	int StickLen; // ����� �����
	int StickW; //������� �����

	int HeadLen;//����� ������ �������
	int HeadW; // ������ ������ �������
public:
	Hammer(int InitX, int InitY, int sL, int sW, int hL, int hW);
	~Hammer(); //����������

	virtual void Show();
	virtual void Hide();
	virtual void makeHitbox();

};// class Hammer

bool Collision(Figure& obj1, Figure& obj2);


