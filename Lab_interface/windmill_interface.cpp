#include <windows.h>
#include "header_interface.h"

extern HDC hdc;

// ������ ��� �������� ��������� ���������� � �� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//----------------------------------------------------
// LOCATION  -----------------------------------------
//----------------------------------------------------

//���������� ������������
Location::Location(int InitX, int InitY)
{
	X = InitX;
	Y = InitY;
} // Location :: Location

//���������� �����������
Location :: ~Location() {}

//���������� �������, ������� �������� ���������� �
int Location::GetX()
{
	return X;
} // Location :: GetX()

//���������� �������, ������� �������� ���������� Y
int Location::GetY()
{
	return Y;
}// Location :: GetY()

void Location::SetX(int InitX)
{
	X = InitX;
}

void Location::SetY(int InitY)
{
	Y = InitY;
}

void Location::Show_Rect(int InitX, int InitY, int InitLength, int InitWidth,
	int InitRed, int InitGreen, int InitBlue)
{
	HPEN Pen = CreatePen(PS_SOLID, 5, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Pen);	//������� ���� ��������

	POINT pen[5] =
	{
		{InitX, InitY},
		{InitX + InitLength, InitY},
		{InitX + InitLength, InitY + InitWidth},
		{InitX, InitY + InitWidth},
		{InitX, InitY}
	};

	Polygon(hdc, pen, 5);           // ������
	DeleteObject(Pen);              // ������� ������

	//------------------����������� ������������--------------------
	HBRUSH Brush = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Brush);

	POINT brush[5] =
	{
		{InitX, InitY},
		{InitX + InitLength, InitY},
		{InitX + InitLength, InitY + InitWidth},
		{InitX, InitY + InitWidth},
		{InitX, InitY}
	};

	Polygon(hdc, brush, 5);           // ������
	DeleteObject(Brush);    // ������� ������
}

void Location::Show_Triangle(int InitX, int InitY, int InitBase, int InitHeight,
	int InitRed, int InitGreen, int InitBlue)
{
	//-------------------������� �� �������-----------------------
	HPEN Pen = CreatePen(PS_SOLID, 5, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Pen);	//������� ���� ��������

	POINT pen[4] =
	{
		{InitX, InitY},
		{InitX + InitBase, InitY},
		{InitX + InitBase / 2, InitY - InitHeight},
		{InitX, InitY}
	};
	Polygon(hdc, pen, 4); // ������
	DeleteObject(Pen);    // ������� ������

	//------------------����������� ������������--------------------
	HBRUSH Brush = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Brush);

	POINT brush[4] =
	{
		{InitX, InitY},
		{InitX + InitBase, InitY},
		{InitX + InitBase / 2, InitY - InitHeight},
		{InitX, InitY}
	};

	Polygon(hdc, brush, 4); // ������
	DeleteObject(Brush);    // ������� ������
	//------------------------------------------------------------------------------
}

//----------------------------------------------------
// POINT  --------------------------------------------
//----------------------------------------------------

//���������� ������������
Point::Point(int InitX, int InitY) : Location(InitX, InitY) {}

//���������� �����������
Point::~Point() {}
//���������� �������, ������� ���������� �����
void Point::Show()
{
	SetPixel(hdc, X, Y, RGB(255, 0, 0));	//������ ������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	// 4 ����� ��� ��������
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

//���������� �������, ������� �������� �����
void Point::Hide()
{
	SetPixel(hdc, X, Y, RGB(242, 242, 242));	//������ ������� ������
	SetPixel(hdc, X + 1, Y, RGB(242, 242, 242));	// 4 ����� ��� ��������
	SetPixel(hdc, X, Y + 1, RGB(242, 242, 242));
	SetPixel(hdc, X + 1, Y + 1, RGB(242, 242, 242));
}

//���������� �������, ������� ������� �����
void Point::MoveTo(int NewX, int NewY)
{
	Hide();
	X = NewX;
	Y = NewY;
	Show();
}

//���������� �������, ������� ������� ����� 4-�� ���������
void Point::Drag(int InitStep)
{
	int FigX = GetX();
	int FigY = GetY();

	while (true)
	{
		if (KEY_DOWN(VK_ESCAPE))
			break; // ����� �� while

		// ������� �����
		if (KEY_DOWN(37))
		{
			FigX -= InitStep;
			MoveTo(FigX, FigY);
			Sleep(100);
		} // �����

		// ������� ������
		if (KEY_DOWN(39))
		{
			FigX += InitStep;
			MoveTo(FigX, FigY);
			Sleep(30);
		} // ������

		 // ������� �����
		if (KEY_DOWN(38))
		{
			FigY -= InitStep;
			MoveTo(FigX, FigY);
			Sleep(30);
		}// �����

		 // ������� ����
		if (KEY_DOWN(40))
		{
			FigY += InitStep;
			MoveTo(FigX, FigY);
			Sleep(30);
		} // ����
	}
}


//----------------------------------------------------
// WINDMILL ------------------------------------------
//----------------------------------------------------
//���������� ������������
WindMill::WindMill(int InitX, int InitY) : Point(InitX, InitY)
{
	id = 0;
}

//���������� �����������
WindMill::~WindMill() {}

// ���������� �������� ������
void WindMill::Main_Building()
{
	// ------------------------------------------�������� ��������� ������
	// ------��������� ������------------
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 189, 120, 29);
}

// ���������� �����
void WindMill::Roof()
{
	// ------��������� ������------------
	int Base = 300; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X - (Base / 2); // ���������� � ��� ��������
	int y_tri = Y; // ���������� Y ��� �������� 

	Show_Triangle(x_tri, y_tri, Base, Height, 349, 55, 12);
}

// ���������� ��� ��������
void WindMill::Axis()
{
	// -----------------------------------------------�������� ��� ��������
	// ------��������� ������------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 21, 23, 25);
}

// ���������� �������
void WindMill::Blades()
{
	// ---------------------------------------------------�������� ��������
	// ------��������� ������------------
	int length_blade = 300; // ����� �������
	int x_b_1 = X; // ���������� � ��� ������ ��������
	int y_b_1 = Y - 300 / 8; // ���������� � ��� ������ ��������

	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
	//------------------------------------------------------------------------------
}

// ���������� ��� ��������
void WindMill::Show()
{
	Main_Building();
	Roof();
	Axis();
	Blades();
}

//----------------------------------------------------------------------------------
// ---------------------------------------------------------------�������� ��������
void WindMill::Hide()
{
	// ------��������� ������------------
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);

	// ------��������� ������------------
	int Base = 300; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X - (Base / 2); // ���������� � ��� ��������
	int y_tri = Y; // ���������� Y ��� �������� 

	Show_Triangle(x_tri, y_tri, Base, Height, 242, 242, 242);

	// ------��������� ������------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 242, 242, 242);

	// ------��������� ������------------
	int length_blade = 300; // ����� �������
	int x_b_1 = X; // ���������� � ��� ������ ��������
	int y_b_1 = Y - 300 / 8; // ���������� � ��� ������ ��������

	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
}
//---------------------------------------------------------------------------------


//----------------------------------------------------
// WINDMILL_3axis_ -----------------------------------
//----------------------------------------------------

//���������� ������������
WindMill_3axis_::WindMill_3axis_(int InitX, int InitY)
	: WindMill(InitX, InitY) 
{
	id = 1;
}

//���������� �����������
WindMill_3axis_::~WindMill_3axis_() {}

// ���������� �������� ������
void WindMill_3axis_::Main_Building()
{
	// ------------------------------------------�������� ��������� ������
	// ------��������� ������------------
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 199, 159, 239);
}

// ���������� �����
void WindMill_3axis_::Roof()
{
	//-------------------------------------------------------�������� �����
	// ------��������� ������------------
	int Base = 300; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X - (Base / 2); // ���������� � ��� ��������
	int y_tri = Y; // ���������� Y ��� �������� 

	Show_Triangle(x_tri, y_tri, Base, Height, 18, 25, 16);
}

// ���������� ��� ��������
void WindMill_3axis_::Axis()
{
	// -----------------------------------------------�������� ��� ��������
	// ------��������� ������------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 0, 47, 85);
}

// ���������� �������
void WindMill_3axis_::Blades()
{
	// ---------------------------------------------------�������� ��������
	// ------��������� ������------------
	int length_blade = 150; // ����� �������
	int x_b_1 = X; // ���������� � ��� ������ ��������
	int y_b_1 = Y - 300 / 8; // ���������� � ��� ������ ��������


	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(23, 114, 69));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[7] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade, y_b_1 - length_blade},
		{x_b_1, y_b_1},
		{x_b_1 + length_blade, y_b_1 - length_blade},
		{x_b_1,y_b_1},
		{x_b_1,  y_b_1 + length_blade},
		{x_b_1, y_b_1}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
	//------------------------------------------------------------------------------
}


void WindMill_3axis_::Hide()
{
	// ------��������� ������------------
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);

	// ------��������� ������------------
	int Base = 300; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X - (Base / 2); // ���������� � ��� ��������
	int y_tri = Y; // ���������� Y ��� �������� 

	Show_Triangle(x_tri, y_tri, Base, Height, 242, 242, 242);

	// ------��������� ������------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 242, 242, 242);

	// ------��������� ������------------
	int length_blade = 150; // ����� �������
	int x_b_1 = X; // ���������� � ��� ������ ��������
	int y_b_1 = Y - 300 / 8; // ���������� � ��� ������ ��������


	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[7] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade, y_b_1 - length_blade},
		{x_b_1, y_b_1},
		{x_b_1 + length_blade, y_b_1 - length_blade},
		{x_b_1,y_b_1},
		{x_b_1,  y_b_1 + length_blade},
		{x_b_1, y_b_1}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������

	// ------��������� ������------------
	int length = 300;
	int width = 100;

	int x_ground = X - 150;
	int y_ground = Y + 200;

	Show_Rect(x_ground, y_ground, length, width, 242, 242, 242);
}

//----------------------------------------------------
// WindMill_wide ------------------------------------
//----------------------------------------------------

WindMill_wide::WindMill_wide(int InitX, int InitY)
	: WindMill_3axis_(InitX, InitY)
{
	id = 1;
}

//���������� �����������
WindMill_wide::~WindMill_wide() {}

// ���������� �������� ������
void WindMill_wide::Main_Building()
{
	// ------------------------------------------�������� ��������� ������
	// ------��������� ������------------
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������s

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 199, 159, 239);

	// ------��������� ������------------
	int length = 300;
	int width = 100;

	int x_ground = X - 150;
	int y_ground = Y + 200;

	Show_Rect(x_ground, y_ground, length, width, 128, 64, 48);
}



//----------------------------------------------------
// WINDMILL_small ------------------------------------
//----------------------------------------------------
//���������� ������������
WindMill_small::WindMill_small(int InitX, int InitY) 
	: WindMill(InitX, InitY) 
{
	id = 2;
}

//���������� �����������
WindMill_small::~WindMill_small() {}

// ���������� �������� ������
void WindMill_small::Main_Building()
{
	int k = 2; // ����������� ��������� 
	// ------------------------------------------�������� ��������� ������
	int length_m_b = 200 / k; // ����� ��������������
	int width_m_b = 300 / k; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 255, 216, 0);
}

// ���������� �����
void WindMill_small::Roof()
{
	int k = 2;
	//-------------------------------------------------------�������� �����
	int Base = 300 / k * k; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X - (Base / 2); // ���������� � ��� ��������
	int y_tri = Y; // ���������� Y ��� �������� 

	Show_Triangle(x_tri, y_tri, Base, Height, 169, 131, 7);
}

// ���������� ��� ��������
void WindMill_small::Axis()
{
	// -----------------------------------------------�������� ��� ��������
	int k = 2;
	int length_axis = 25 * k ^ 2;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - length_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, length_axis, 89, 53, 31);
}

// ���������� �������
void WindMill_small::Blades()
{
	int k = 2;
	// ---------------------------------------------------�������� ��������
	int length_blade = 300 / k; // ����� �������
	int x_b_1 = X; // ���������� � ��� ������ ��������
	int y_b_1 = Y - 300 / 8; // ���������� � ��� ������ ��������

	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(121, 68, 59));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
	//------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------
void WindMill_small::Hide()
{
	int k = 2; // ����������� ��������� 
	// ------��������� ������------------
	int length_m_b = 200 / k; // ����� ��������������
	int width_m_b = 300 / k; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);

	// ------��������� ������------------
	int Base = 300 / k * k; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X - (Base / 2); // ���������� � ��� ��������
	int y_tri = Y; // ���������� Y ��� �������� 

	Show_Triangle(x_tri, y_tri, Base, Height, 242, 242, 242);

	// ------��������� ������------------
	int length_axis = 25 * k ^ 2;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - length_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, length_axis, 242, 242, 242);

	// ------��������� ������------------
	int length_blade = 300 / k; // ����� �������
	int x_b_1 = X; // ���������� � ��� ������ ��������
	int y_b_1 = Y - 300 / 8; // ���������� � ��� ������ ��������

	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
}

//----------------------------------------------------
// WINDMILL_broken ------------------------------------
//----------------------------------------------------

//���������� ������������
WindMill_broken::WindMill_broken(int InitX, int InitY) : WindMill(InitX, InitY)
{
	id = 3;
}

//���������� �����������
WindMill_broken::~WindMill_broken() {}

void WindMill_broken::Main_Building()
{
	// ------------------------------------------�������� ��������� ������
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 189, 120, 29);
	

	// ������ ����� �� ��������

	int base_fire = length_m_b / 4; // ����� ����
	int height_fire = width_m_b / 8; // ������ ����

	// ------------------------------������ �����
	int x_fire_1 = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_fire_1 = Y; // ���������� � ��� ������ ��������
		
	Show_Triangle(x_fire_1, y_fire_1, base_fire, height_fire, 255, 255, 29);
	
	// ------------------------------������ �����
	int x_fire_2 = x_fire_1 + base_fire; // ���������� � ��� ������ ��������
	int y_fire_2 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_2, y_fire_2, base_fire, height_fire, 255, 255, 29);

	// ------------------------------������ �����
	int x_fire_3 = x_fire_2 + base_fire; // ���������� � ��� ������ ��������
	int y_fire_3 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_3, y_fire_3, base_fire, height_fire, 255, 255, 29);

	// ------------------------------���¨���� �����
	int x_fire_4 = x_fire_3 + base_fire; // ���������� � ��� ������ ��������
	int y_fire_4 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_4, y_fire_4, base_fire, height_fire, 255, 255, 29);
}

void WindMill_broken::Roof()
{
	//-------------------------------------------------------�������� �����
	int Base = 300; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X + 50; // ���������� � ��� ��������
	int y_tri = Y + 350; // ���������� Y ��� �������� 

	//Show_Triangle(x_tri, y_tri, Base, Height, 349, 55, 12);

	//-------------------������� �� �������-----------------------
	HPEN Pen_ROOF = CreatePen(PS_SOLID, 5, RGB(349, 55, 12));
	SelectObject(hdc, Pen_ROOF);	//������� ���� ��������

	POINT pen_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};
	Polygon(hdc, pen_roof, 4); // ������
	DeleteObject(Pen_ROOF);    // ������� ������

	//------------------����������� ������������--------------------
	HBRUSH Brush_Roof = CreateSolidBrush(RGB(349, 55, 12));
	SelectObject(hdc, Brush_Roof);

	POINT brush_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};

	Polygon(hdc, brush_roof, 4); // ������
	DeleteObject(Brush_Roof);    // ������� ������
	//------------------------------------------------------------------------------
}

void WindMill_broken::Axis()
{
	// -----------------------------------------------�������� ��� ��������

	int length_axis = 25;
	int x_axis = X + 150;
	int y_axis = Y + 300;

	//Show_Rect(x_axis, y_axis, length_axis, length_axis, 21, 23, 25);

	HBRUSH Brush_AXIS = CreateSolidBrush(RGB(21, 23, 25));
	SelectObject(hdc, Brush_AXIS);  //������� ���� ��������

	POINT brush_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, brush_axis, 5); // ������
	DeleteObject(Brush_AXIS);    // ������� ������

	//------------------����������� ������������--------------------
	HPEN Pen_AXIS = CreatePen(PS_SOLID, 5, RGB(21, 23, 25));
	SelectObject(hdc, Pen_AXIS);	//������� ���� ��������

	POINT pen_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, pen_axis, 5); // ������
	DeleteObject(Pen_AXIS);    // ������� ������

	//------------------------------------------------------------------------------
}

void WindMill_broken::Blades()
{
	// ---------------------------------------------------�������� ��������
	int length_blade = 200; // ����� �������
	int x_b_1 = X + 150 + 25 / 2; // ���������� � ��� ������ ��������
	int y_b_1 = Y + 300 + 25 / 2; // ���������� � ��� ������ ��������

	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 + length_blade / 2, y_b_1 + length_blade / 2},
		{x_b_1,y_b_1},
		{x_b_1 + length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 - length_blade / 2, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
}


//----------------------------------------------------------------------------------
void WindMill_broken::Hide()
{
	// ------------------------------------------�������� ��������� ������
	// ------��������� ������------------
	int length_m_b = 200; // ����� ��������������
	int width_m_b = 300; // ������ 
	int x_m_b = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_m_b = Y; // ���������� � ��� ������ ��������

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);


	// ������ ����� �� ��������

	int base_fire = length_m_b / 4; // ����� ����
	int height_fire = width_m_b / 8; // ������ ����

	// ------------------------------������ �����
	int x_fire_1 = X - (length_m_b / 2); // ���������� � ��� ������ ��������
	int y_fire_1 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_1, y_fire_1, base_fire, height_fire, 242, 242, 242);

	// ------------------------------������ �����
	int x_fire_2 = x_fire_1 + base_fire; // ���������� � ��� ������ ��������
	int y_fire_2 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_2, y_fire_2, base_fire, height_fire, 242, 242, 242);

	// ------------------------------������ �����
	int x_fire_3 = x_fire_2 + base_fire; // ���������� � ��� ������ ��������
	int y_fire_3 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_3, y_fire_3, base_fire, height_fire, 242, 242, 242);

	// ------------------------------���¨���� �����
	int x_fire_4 = x_fire_3 + base_fire; // ���������� � ��� ������ ��������
	int y_fire_4 = Y; // ���������� � ��� ������ ��������

	Show_Triangle(x_fire_4, y_fire_4, base_fire, height_fire, 242, 242, 242);


	//-----------------------------------------------------------
	int Base = 300; //  ���������
	int Height = Base / 2; // ������
	int x_tri = X + 50; // ���������� � ��� ��������
	int y_tri = Y + 350; // ���������� Y ��� �������� 


	//-------------------������� �� �������-----------------------
	HPEN Pen_ROOF = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_ROOF);	//������� ���� ��������

	POINT pen_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};
	Polygon(hdc, pen_roof, 4); // ������
	DeleteObject(Pen_ROOF);    // ������� ������

	//------------------����������� ������������--------------------
	HBRUSH Brush_Roof = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_Roof);

	POINT brush_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};

	Polygon(hdc, brush_roof, 4); // ������
	DeleteObject(Brush_Roof);    // ������� ������

	// -----------------------------------------------�������� ��� ��������

	int length_axis = 25;
	int x_axis = X + 150;
	int y_axis = Y + 300;

	HBRUSH Brush_AXIS = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_AXIS);  //������� ���� ��������

	POINT brush_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, brush_axis, 5); // ������
	DeleteObject(Brush_AXIS);    // ������� ������

	//------------------����������� ������������--------------------
	HPEN Pen_AXIS = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_AXIS);	//������� ���� ��������

	POINT pen_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, pen_axis, 5); // ������
	DeleteObject(Pen_AXIS);    // ������� ������

	//------------------------------------------------------------------------------

	// ---------------------------------------------------�������� ��������
	int length_blade = 200; // ����� �������
	int x_b_1 = X + 150 + 25 / 2; // ���������� � ��� ������ ��������
	int y_b_1 = Y + 300 + 25 / 2; // ���������� � ��� ������ ��������

	//-------------------������� �� �������-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//������� ���� ��������

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 + length_blade / 2, y_b_1 + length_blade / 2},
		{x_b_1,y_b_1},
		{x_b_1 + length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 - length_blade / 2, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // ������
	DeleteObject(Pen_BLADE);    // ������� ������
}


//----------------------------------------------------
// OCONFLICT -----------------------------------------
//----------------------------------------------------
//���������� ������������
OConflict_abstract::OConflict_abstract(int InitX, int InitY, int InitRad) : Point(InitX, InitY)
{
	Rad0 = InitRad;
	id = -1;
}
//���������� �����������
OConflict_abstract::~OConflict_abstract() {}

// ----------------------------------------------------------���������� ���������
void OConflict_abstract::Show()
{
	//-------------------������� �� �������-----------------------
	HPEN Pen_OConflict = CreatePen(PS_SOLID, 5, RGB(120, 100, 50));

	SelectObject(hdc, Pen_OConflict);	//������� ���� ��������
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Pen_OConflict);              // ������� ������

	//------------------����������� ������������--------------------
	HBRUSH Brush_OConflict = CreateSolidBrush(RGB(120, 100, 50));
	SelectObject(hdc, Brush_OConflict);
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Brush_OConflict);    // ������� ������
}
//-------------------------------------------------------------------------------
// -----------------------------------------------------------�������� ���������
void OConflict_abstract::Hide()
{
	//-------------------������� �� �������-----------------------
	HPEN Pen_OConflict = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));

	SelectObject(hdc, Pen_OConflict);	//������� ���� ��������
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Pen_OConflict);              // ������� ������

	//------------------����������� ������������--------------------
	HBRUSH Brush_OConflict = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_OConflict);
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Brush_OConflict);    // ������� ������
}
//------------------------------------------------------------------------------
// ������ �������
int OConflict_abstract::GetRad()
{
	return Rad0;
}

// ��������� �������
void OConflict_abstract::SetRad(int InitRad)
{
	Rad0 = InitRad;
}


//----------------------------------------------------
// OCONFLICT : GREENCIRCLE ---------------------------
//----------------------------------------------------

GreenCircle::GreenCircle(int InitX, int InitY, int InitRad)
	: OConflict_abstract(InitX, InitY, InitRad)
{
	id = 1;
}
GreenCircle::~GreenCircle() {}

void GreenCircle::edge_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	//-------------------������� �� �������-----------------------
	HPEN Pen_OConflict = CreatePen(PS_SOLID, 5, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Pen_OConflict);	//������� ���� ��������
	Ellipse(hdc, X - InitRad / 4, Y - InitRad / 4, X + InitRad / 4, Y + InitRad / 4);
	DeleteObject(Pen_OConflict);              // ������� ������
}

void GreenCircle::inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	//------------------����������� ������������--------------------
	HBRUSH Brush_OConflict = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Brush_OConflict);
	Ellipse(hdc, X - InitRad / 4, Y - InitRad / 4, X + InitRad / 4, Y + InitRad / 4);
	DeleteObject(Brush_OConflict);    // ������� ������
}

void GreenCircle::Show()
{
	edge_Circle(Rad0, 120, 100, 50);
	inside_Circle(Rad0, 120, 100, 50);
}

void GreenCircle::Hide()
{
	edge_Circle(Rad0, 242, 242, 242);
	inside_Circle(Rad0, 242, 242, 242);
}


//----------------------------------------------------
// CLOUD ---------------------------------------------
//----------------------------------------------------

//���������� ������������
Cloud::Cloud(int InitX, int InitY, int InitRad)
	: OConflict_abstract(InitX, InitY, InitRad)
{
	id = 2;
}
//���������� �����������
Cloud::~Cloud() {}

void Cloud::edge_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	//-------------------������� �� �������-----------------------
	HPEN PenCloud = CreatePen(PS_SOLID, 2, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, PenCloud);	//������� ���� ��������
	Ellipse(hdc, X - InitRad, Y - InitRad / 2, X + InitRad, Y + InitRad / 2); // ������ ������
	DeleteObject(PenCloud); // ������� ����
}


 void Cloud::inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	 //------------------����������� ������������--------------------
	 HBRUSH hBrush = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	 SelectObject(hdc, hBrush); 	//������� ����� ��������
	 Ellipse(hdc, X - InitRad, Y - InitRad/2, X + InitRad, Y + InitRad/2);// ����������� ������
	 DeleteObject(hBrush); // ������� �����
}


// --------------------------------------------------------------���������� ������
void Cloud::Show()
{
	edge_Circle(Rad0, 0, 0, 0);
	inside_Circle(Rad0, 255, 255, 255);
} //Show()
//--------------------------------------------------------------------------------
// ----------------------------------------------------------------�������� ������
void Cloud::Hide()
{
	edge_Circle(Rad0, 242, 242, 242);
	inside_Circle(Rad0, 242, 242, 242);
} //Show()
//--------------------------------------------------------------------------------

//----------------------------------------------------
// LIGHTNING -----------------------------------------
//----------------------------------------------------

// ���������� ������������
Thunderstorm::Thunderstorm(int InitX, int InitY, int InitRad)
	: Cloud(InitX, InitY, InitRad)
{
	id = 0;
}
// ���������� �����������
Thunderstorm::~Thunderstorm() {}

void Thunderstorm::Show()
{
	edge_Circle(Rad0, 0, 0, 0);
	inside_Circle(Rad0, 128, 128, 128);

	int x_light = X;
	int y_light = Y + Rad0 / 2;
	int width_light = 20;

	HBRUSH Brush_LIGHTNING = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Brush_LIGHTNING);

	POINT brush_lightning[7] =
	{
		{x_light, y_light},
		{x_light - 2 * width_light, y_light + 4 * width_light},
		{x_light + width_light, y_light + 4 * width_light},
		{x_light - width_light, y_light + 9 * width_light},
		{ x_light + 4 * width_light, y_light + 2 * width_light},
		{x_light + width_light, y_light + 2 * width_light},
		{x_light + 2 * width_light, y_light}
	};
	Polygon(hdc, brush_lightning, 7);
	DeleteObject(Brush_LIGHTNING);
}

void Thunderstorm::Hide()
{
	edge_Circle(Rad0, 242, 242, 242);
	inside_Circle(Rad0, 242, 242, 242);

	int x_light = X;
	int y_light = Y + Rad0 / 2;
	int width_light = 20;

	HBRUSH Brush_LIGHTNING = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_LIGHTNING);

	POINT brush_lightning[7] =
	{
		{x_light, y_light},
		{x_light - 2 * width_light, y_light + 4 * width_light},
		{x_light + width_light, y_light + 4 * width_light},
		{x_light - width_light, y_light + 9 * width_light},
		{ x_light + 4 * width_light, y_light + 2 * width_light},
		{x_light + width_light, y_light + 2 * width_light},
		{x_light + 2 * width_light, y_light}
	};
	Polygon(hdc, brush_lightning, 7);
	DeleteObject(Brush_LIGHTNING);

	HPEN Pen_LIGHTNING = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));
	SelectObject(hdc, Pen_LIGHTNING);

	POINT pen_lightning[7] =
	{
		{x_light, y_light},
		{x_light - 2 * width_light, y_light + 4 * width_light},
		{x_light + width_light, y_light + 4 * width_light},
		{x_light - width_light, y_light + 9 * width_light},
		{ x_light + 4 * width_light, y_light + 2 * width_light},
		{x_light + width_light, y_light + 2 * width_light},
		{x_light + 2 * width_light, y_light}
	};
	Polygon(hdc, pen_lightning, 7);
	DeleteObject(Pen_LIGHTNING);
}



int WindMill::GetId()
{
	return id;
}

int OConflict_abstract::GetId()
{
	return id;
}