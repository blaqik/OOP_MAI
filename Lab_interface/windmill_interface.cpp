#include <windows.h>
#include "header_interface.h"

extern HDC hdc;

// Макрос для проверки состояния клавиатуры – из ШАБЛОНА
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//----------------------------------------------------
// LOCATION  -----------------------------------------
//----------------------------------------------------

//объявление конструктора
Location::Location(int InitX, int InitY)
{
	X = InitX;
	Y = InitY;
} // Location :: Location

//объявление деструктора
Location :: ~Location() {}

//объявление функции, которая получает координату Х
int Location::GetX()
{
	return X;
} // Location :: GetX()

//объявление функции, которая получает координату Y
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
	SelectObject(hdc, Pen);	//сделаем перо активным

	POINT pen[5] =
	{
		{InitX, InitY},
		{InitX + InitLength, InitY},
		{InitX + InitLength, InitY + InitWidth},
		{InitX, InitY + InitWidth},
		{InitX, InitY}
	};

	Polygon(hdc, pen, 5);           // красим
	DeleteObject(Pen);              // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
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

	Polygon(hdc, brush, 5);           // красим
	DeleteObject(Brush);    // удаляем объект
}

void Location::Show_Triangle(int InitX, int InitY, int InitBase, int InitHeight,
	int InitRed, int InitGreen, int InitBlue)
{
	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen = CreatePen(PS_SOLID, 5, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Pen);	//сделаем перо активным

	POINT pen[4] =
	{
		{InitX, InitY},
		{InitX + InitBase, InitY},
		{InitX + InitBase / 2, InitY - InitHeight},
		{InitX, InitY}
	};
	Polygon(hdc, pen, 4); // красим
	DeleteObject(Pen);    // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HBRUSH Brush = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Brush);

	POINT brush[4] =
	{
		{InitX, InitY},
		{InitX + InitBase, InitY},
		{InitX + InitBase / 2, InitY - InitHeight},
		{InitX, InitY}
	};

	Polygon(hdc, brush, 4); // красим
	DeleteObject(Brush);    // удаляем объект
	//------------------------------------------------------------------------------
}

//----------------------------------------------------
// POINT  --------------------------------------------
//----------------------------------------------------

//объявление конструктора
Point::Point(int InitX, int InitY) : Location(InitX, InitY) {}

//объявление деструктора
Point::~Point() {}
//объявление функции, которая показывает точку
void Point::Show()
{
	SetPixel(hdc, X, Y, RGB(255, 0, 0));	//рисуем красным цветом
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	// 4 точки для удобства
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

//объявление функции, которая скрывает точку
void Point::Hide()
{
	SetPixel(hdc, X, Y, RGB(242, 242, 242));	//рисуем красным цветом
	SetPixel(hdc, X + 1, Y, RGB(242, 242, 242));	// 4 точки для удобства
	SetPixel(hdc, X, Y + 1, RGB(242, 242, 242));
	SetPixel(hdc, X + 1, Y + 1, RGB(242, 242, 242));
}

//объявление функции, которая двигает точку
void Point::MoveTo(int NewX, int NewY)
{
	Hide();
	X = NewX;
	Y = NewY;
	Show();
}

//объявление функции, которая двигает точку 4-мя клавишами
void Point::Drag(int InitStep)
{
	int FigX = GetX();
	int FigY = GetY();

	while (true)
	{
		if (KEY_DOWN(VK_ESCAPE))
			break; // выход из while

		// стрелка влево
		if (KEY_DOWN(37))
		{
			FigX -= InitStep;
			MoveTo(FigX, FigY);
			Sleep(100);
		} // влево

		// стрелка вправо
		if (KEY_DOWN(39))
		{
			FigX += InitStep;
			MoveTo(FigX, FigY);
			Sleep(30);
		} // вправо

		 // стрелка вверх
		if (KEY_DOWN(38))
		{
			FigY -= InitStep;
			MoveTo(FigX, FigY);
			Sleep(30);
		}// вверх

		 // стрелка вниз
		if (KEY_DOWN(40))
		{
			FigY += InitStep;
			MoveTo(FigX, FigY);
			Sleep(30);
		} // вниз
	}
}


//----------------------------------------------------
// WINDMILL ------------------------------------------
//----------------------------------------------------
//объявление конструктора
WindMill::WindMill(int InitX, int InitY) : Point(InitX, InitY)
{
	id = 0;
}

//объявление деструктора
WindMill::~WindMill() {}

// показывает ОСНОВНОЕ ЗДАНИЕ
void WindMill::Main_Building()
{
	// ------------------------------------------Создание ОСНОВНОГО ЗДАНИЯ
	// ------Начальные данные------------
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 189, 120, 29);
}

// показывает КРЫШУ
void WindMill::Roof()
{
	// ------Начальные данные------------
	int Base = 300; //  основание
	int Height = Base / 2; // высота
	int x_tri = X - (Base / 2); // координата Х для строения
	int y_tri = Y; // координата Y для строения 

	Show_Triangle(x_tri, y_tri, Base, Height, 349, 55, 12);
}

// показывает ОСЬ ВРАЩЕНИЯ
void WindMill::Axis()
{
	// -----------------------------------------------Создание ОСИ ВРАЩЕНИЯ
	// ------Начальные данные------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 21, 23, 25);
}

// показывает ЛОПАСТИ
void WindMill::Blades()
{
	// ---------------------------------------------------Создание ЛОПАСТЕЙ
	// ------Начальные данные------------
	int length_blade = 300; // длина лопасти
	int x_b_1 = X; // координата Х для начала строения
	int y_b_1 = Y - 300 / 8; // координата Х для начала строения

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
	//------------------------------------------------------------------------------
}

// показывает ВСЮ МЕЛЬНИЦУ
void WindMill::Show()
{
	Main_Building();
	Roof();
	Axis();
	Blades();
}

//----------------------------------------------------------------------------------
// ---------------------------------------------------------------Скрывает МЕЛЬНИЦУ
void WindMill::Hide()
{
	// ------Начальные данные------------
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);

	// ------Начальные данные------------
	int Base = 300; //  основание
	int Height = Base / 2; // высота
	int x_tri = X - (Base / 2); // координата Х для строения
	int y_tri = Y; // координата Y для строения 

	Show_Triangle(x_tri, y_tri, Base, Height, 242, 242, 242);

	// ------Начальные данные------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 242, 242, 242);

	// ------Начальные данные------------
	int length_blade = 300; // длина лопасти
	int x_b_1 = X; // координата Х для начала строения
	int y_b_1 = Y - 300 / 8; // координата Х для начала строения

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
}
//---------------------------------------------------------------------------------


//----------------------------------------------------
// WINDMILL_3axis_ -----------------------------------
//----------------------------------------------------

//объявление конструктора
WindMill_3axis_::WindMill_3axis_(int InitX, int InitY)
	: WindMill(InitX, InitY) 
{
	id = 1;
}

//объявление деструктора
WindMill_3axis_::~WindMill_3axis_() {}

// показывает ОСНОВНОЕ ЗДАНИЕ
void WindMill_3axis_::Main_Building()
{
	// ------------------------------------------Создание ОСНОВНОГО ЗДАНИЯ
	// ------Начальные данные------------
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 199, 159, 239);
}

// показывает КРЫШУ
void WindMill_3axis_::Roof()
{
	//-------------------------------------------------------Создание КРЫШИ
	// ------Начальные данные------------
	int Base = 300; //  основание
	int Height = Base / 2; // высота
	int x_tri = X - (Base / 2); // координата Х для строения
	int y_tri = Y; // координата Y для строения 

	Show_Triangle(x_tri, y_tri, Base, Height, 18, 25, 16);
}

// показывает ОСЬ ВРАЩЕНИЯ
void WindMill_3axis_::Axis()
{
	// -----------------------------------------------Создание ОСИ ВРАЩЕНИЯ
	// ------Начальные данные------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 0, 47, 85);
}

// показывает ЛОПАСТИ
void WindMill_3axis_::Blades()
{
	// ---------------------------------------------------Создание ЛОПАСТЕЙ
	// ------Начальные данные------------
	int length_blade = 150; // длина лопасти
	int x_b_1 = X; // координата Х для начала строения
	int y_b_1 = Y - 300 / 8; // координата Х для начала строения


	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(23, 114, 69));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

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

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
	//------------------------------------------------------------------------------
}


void WindMill_3axis_::Hide()
{
	// ------Начальные данные------------
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);

	// ------Начальные данные------------
	int Base = 300; //  основание
	int Height = Base / 2; // высота
	int x_tri = X - (Base / 2); // координата Х для строения
	int y_tri = Y; // координата Y для строения 

	Show_Triangle(x_tri, y_tri, Base, Height, 242, 242, 242);

	// ------Начальные данные------------
	int length_axis = 25;
	int width_axis = 25;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - width_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, width_axis, 242, 242, 242);

	// ------Начальные данные------------
	int length_blade = 150; // длина лопасти
	int x_b_1 = X; // координата Х для начала строения
	int y_b_1 = Y - 300 / 8; // координата Х для начала строения


	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

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

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект

	// ------Начальные данные------------
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

//объявление деструктора
WindMill_wide::~WindMill_wide() {}

// показывает ОСНОВНОЕ ЗДАНИЕ
void WindMill_wide::Main_Building()
{
	// ------------------------------------------Создание ОСНОВНОГО ЗДАНИЯ
	// ------Начальные данные------------
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строенияs

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 199, 159, 239);

	// ------Начальные данные------------
	int length = 300;
	int width = 100;

	int x_ground = X - 150;
	int y_ground = Y + 200;

	Show_Rect(x_ground, y_ground, length, width, 128, 64, 48);
}



//----------------------------------------------------
// WINDMILL_small ------------------------------------
//----------------------------------------------------
//объявление конструктора
WindMill_small::WindMill_small(int InitX, int InitY) 
	: WindMill(InitX, InitY) 
{
	id = 2;
}

//объявление деструктора
WindMill_small::~WindMill_small() {}

// показывает ОСНОВНОЕ ЗДАНИЕ
void WindMill_small::Main_Building()
{
	int k = 2; // коэффициент кратности 
	// ------------------------------------------Создание ОСНОВНОГО ЗДАНИЯ
	int length_m_b = 200 / k; // длина прямоугольника
	int width_m_b = 300 / k; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 255, 216, 0);
}

// показывает КРЫШУ
void WindMill_small::Roof()
{
	int k = 2;
	//-------------------------------------------------------Создание КРЫШИ
	int Base = 300 / k * k; //  основание
	int Height = Base / 2; // высота
	int x_tri = X - (Base / 2); // координата Х для строения
	int y_tri = Y; // координата Y для строения 

	Show_Triangle(x_tri, y_tri, Base, Height, 169, 131, 7);
}

// показывает ОСЬ ВРАЩЕНИЯ
void WindMill_small::Axis()
{
	// -----------------------------------------------Создание ОСИ ВРАЩЕНИЯ
	int k = 2;
	int length_axis = 25 * k ^ 2;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - length_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, length_axis, 89, 53, 31);
}

// показывает ЛОПАСТИ
void WindMill_small::Blades()
{
	int k = 2;
	// ---------------------------------------------------Создание ЛОПАСТЕЙ
	int length_blade = 300 / k; // длина лопасти
	int x_b_1 = X; // координата Х для начала строения
	int y_b_1 = Y - 300 / 8; // координата Х для начала строения

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(121, 68, 59));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
	//------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------
void WindMill_small::Hide()
{
	int k = 2; // коэффициент кратности 
	// ------Начальные данные------------
	int length_m_b = 200 / k; // длина прямоугольника
	int width_m_b = 300 / k; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);

	// ------Начальные данные------------
	int Base = 300 / k * k; //  основание
	int Height = Base / 2; // высота
	int x_tri = X - (Base / 2); // координата Х для строения
	int y_tri = Y; // координата Y для строения 

	Show_Triangle(x_tri, y_tri, Base, Height, 242, 242, 242);

	// ------Начальные данные------------
	int length_axis = 25 * k ^ 2;
	int x_axis = X - (length_axis / 2);
	int y_axis = Y - 300 / 8 - length_axis / 2;

	Show_Rect(x_axis, y_axis, length_axis, length_axis, 242, 242, 242);

	// ------Начальные данные------------
	int length_blade = 300 / k; // длина лопасти
	int x_b_1 = X; // координата Х для начала строения
	int y_b_1 = Y - 300 / 8; // координата Х для начала строения

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1},
		{x_b_1 + length_blade / 2, y_b_1},
		{x_b_1,y_b_1},
		{x_b_1, y_b_1 - length_blade / 2},
		{x_b_1, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
}

//----------------------------------------------------
// WINDMILL_broken ------------------------------------
//----------------------------------------------------

//объявление конструктора
WindMill_broken::WindMill_broken(int InitX, int InitY) : WindMill(InitX, InitY)
{
	id = 3;
}

//объявление деструктора
WindMill_broken::~WindMill_broken() {}

void WindMill_broken::Main_Building()
{
	// ------------------------------------------Создание ОСНОВНОГО ЗДАНИЯ
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 189, 120, 29);
	

	// рисуем огонь на мельнице

	int base_fire = length_m_b / 4; // длина огня
	int height_fire = width_m_b / 8; // ширина огня

	// ------------------------------ПЕРВЫЙ огонёк
	int x_fire_1 = X - (length_m_b / 2); // координата Х для начала строения
	int y_fire_1 = Y; // координата Х для начала строения
		
	Show_Triangle(x_fire_1, y_fire_1, base_fire, height_fire, 255, 255, 29);
	
	// ------------------------------ВТОРОЙ огонёк
	int x_fire_2 = x_fire_1 + base_fire; // координата Х для начала строения
	int y_fire_2 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_2, y_fire_2, base_fire, height_fire, 255, 255, 29);

	// ------------------------------ТРЕТИЙ огонёк
	int x_fire_3 = x_fire_2 + base_fire; // координата Х для начала строения
	int y_fire_3 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_3, y_fire_3, base_fire, height_fire, 255, 255, 29);

	// ------------------------------ЧЕТВЁРТЫЙ огонёк
	int x_fire_4 = x_fire_3 + base_fire; // координата Х для начала строения
	int y_fire_4 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_4, y_fire_4, base_fire, height_fire, 255, 255, 29);
}

void WindMill_broken::Roof()
{
	//-------------------------------------------------------Создание КРЫШИ
	int Base = 300; //  основание
	int Height = Base / 2; // высота
	int x_tri = X + 50; // координата Х для строения
	int y_tri = Y + 350; // координата Y для строения 

	//Show_Triangle(x_tri, y_tri, Base, Height, 349, 55, 12);

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_ROOF = CreatePen(PS_SOLID, 5, RGB(349, 55, 12));
	SelectObject(hdc, Pen_ROOF);	//сделаем перо активным

	POINT pen_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};
	Polygon(hdc, pen_roof, 4); // красим
	DeleteObject(Pen_ROOF);    // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HBRUSH Brush_Roof = CreateSolidBrush(RGB(349, 55, 12));
	SelectObject(hdc, Brush_Roof);

	POINT brush_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};

	Polygon(hdc, brush_roof, 4); // красим
	DeleteObject(Brush_Roof);    // удаляем объект
	//------------------------------------------------------------------------------
}

void WindMill_broken::Axis()
{
	// -----------------------------------------------Создание ОСИ ВРАЩЕНИЯ

	int length_axis = 25;
	int x_axis = X + 150;
	int y_axis = Y + 300;

	//Show_Rect(x_axis, y_axis, length_axis, length_axis, 21, 23, 25);

	HBRUSH Brush_AXIS = CreateSolidBrush(RGB(21, 23, 25));
	SelectObject(hdc, Brush_AXIS);  //сделаем перо активным

	POINT brush_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, brush_axis, 5); // красим
	DeleteObject(Brush_AXIS);    // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HPEN Pen_AXIS = CreatePen(PS_SOLID, 5, RGB(21, 23, 25));
	SelectObject(hdc, Pen_AXIS);	//сделаем перо активным

	POINT pen_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, pen_axis, 5); // красим
	DeleteObject(Pen_AXIS);    // удаляем объект

	//------------------------------------------------------------------------------
}

void WindMill_broken::Blades()
{
	// ---------------------------------------------------Создание ЛОПАСТЕЙ
	int length_blade = 200; // длина лопасти
	int x_b_1 = X + 150 + 25 / 2; // координата Х для начала строения
	int y_b_1 = Y + 300 + 25 / 2; // координата Х для начала строения

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 + length_blade / 2, y_b_1 + length_blade / 2},
		{x_b_1,y_b_1},
		{x_b_1 + length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 - length_blade / 2, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
}


//----------------------------------------------------------------------------------
void WindMill_broken::Hide()
{
	// ------------------------------------------Создание ОСНОВНОГО ЗДАНИЯ
	// ------Начальные данные------------
	int length_m_b = 200; // длина прямоугольника
	int width_m_b = 300; // ширина 
	int x_m_b = X - (length_m_b / 2); // координата Х для начала строения
	int y_m_b = Y; // координата Х для начала строения

	Show_Rect(x_m_b, y_m_b, length_m_b, width_m_b, 242, 242, 242);


	// рисуем огонь на мельнице

	int base_fire = length_m_b / 4; // длина огня
	int height_fire = width_m_b / 8; // ширина огня

	// ------------------------------ПЕРВЫЙ огонёк
	int x_fire_1 = X - (length_m_b / 2); // координата Х для начала строения
	int y_fire_1 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_1, y_fire_1, base_fire, height_fire, 242, 242, 242);

	// ------------------------------ВТОРОЙ огонёк
	int x_fire_2 = x_fire_1 + base_fire; // координата Х для начала строения
	int y_fire_2 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_2, y_fire_2, base_fire, height_fire, 242, 242, 242);

	// ------------------------------ТРЕТИЙ огонёк
	int x_fire_3 = x_fire_2 + base_fire; // координата Х для начала строения
	int y_fire_3 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_3, y_fire_3, base_fire, height_fire, 242, 242, 242);

	// ------------------------------ЧЕТВЁРТЫЙ огонёк
	int x_fire_4 = x_fire_3 + base_fire; // координата Х для начала строения
	int y_fire_4 = Y; // координата Х для начала строения

	Show_Triangle(x_fire_4, y_fire_4, base_fire, height_fire, 242, 242, 242);


	//-----------------------------------------------------------
	int Base = 300; //  основание
	int Height = Base / 2; // высота
	int x_tri = X + 50; // координата Х для строения
	int y_tri = Y + 350; // координата Y для строения 


	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_ROOF = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_ROOF);	//сделаем перо активным

	POINT pen_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};
	Polygon(hdc, pen_roof, 4); // красим
	DeleteObject(Pen_ROOF);    // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HBRUSH Brush_Roof = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_Roof);

	POINT brush_roof[4] =
	{
		{x_tri, y_tri},
		{x_tri + Height, y_tri},
		{x_tri + Height, y_tri - Height},
		{x_tri, y_tri}
	};

	Polygon(hdc, brush_roof, 4); // красим
	DeleteObject(Brush_Roof);    // удаляем объект

	// -----------------------------------------------Создание ОСИ ВРАЩЕНИЯ

	int length_axis = 25;
	int x_axis = X + 150;
	int y_axis = Y + 300;

	HBRUSH Brush_AXIS = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_AXIS);  //сделаем перо активным

	POINT brush_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, brush_axis, 5); // красим
	DeleteObject(Brush_AXIS);    // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HPEN Pen_AXIS = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_AXIS);	//сделаем перо активным

	POINT pen_axis[5] =
	{
		{x_axis, y_axis},
		{x_axis + length_axis, y_axis},
		{x_axis + length_axis, y_axis + length_axis},
		{x_axis, y_axis + length_axis},
		{x_axis, y_axis}
	};

	Polygon(hdc, pen_axis, 5); // красим
	DeleteObject(Pen_AXIS);    // удаляем объект

	//------------------------------------------------------------------------------

	// ---------------------------------------------------Создание ЛОПАСТЕЙ
	int length_blade = 200; // длина лопасти
	int x_b_1 = X + 150 + 25 / 2; // координата Х для начала строения
	int y_b_1 = Y + 300 + 25 / 2; // координата Х для начала строения

	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_BLADE = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));
	SelectObject(hdc, Pen_BLADE);	//сделаем перо активным

	POINT pen_blade[6] =
	{
		{x_b_1, y_b_1},
		{x_b_1 - length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 + length_blade / 2, y_b_1 + length_blade / 2},
		{x_b_1,y_b_1},
		{x_b_1 + length_blade / 2, y_b_1 - length_blade / 2},
		{x_b_1 - length_blade / 2, y_b_1 + length_blade / 2}
	};

	Polygon(hdc, pen_blade, 6); // красим
	DeleteObject(Pen_BLADE);    // удаляем объект
}


//----------------------------------------------------
// OCONFLICT -----------------------------------------
//----------------------------------------------------
//объявление конструктора
OConflict_abstract::OConflict_abstract(int InitX, int InitY, int InitRad) : Point(InitX, InitY)
{
	Rad0 = InitRad;
	id = -1;
}
//объявление деструктора
OConflict_abstract::~OConflict_abstract() {}

// ----------------------------------------------------------Показывает КОНФПЛИКТ
void OConflict_abstract::Show()
{
	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_OConflict = CreatePen(PS_SOLID, 5, RGB(120, 100, 50));

	SelectObject(hdc, Pen_OConflict);	//сделаем перо активным
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Pen_OConflict);              // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HBRUSH Brush_OConflict = CreateSolidBrush(RGB(120, 100, 50));
	SelectObject(hdc, Brush_OConflict);
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Brush_OConflict);    // удаляем объект
}
//-------------------------------------------------------------------------------
// -----------------------------------------------------------Скрывает КОНФПЛИКТ
void OConflict_abstract::Hide()
{
	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_OConflict = CreatePen(PS_SOLID, 5, RGB(242, 242, 242));

	SelectObject(hdc, Pen_OConflict);	//сделаем перо активным
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Pen_OConflict);              // удаляем объект

	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HBRUSH Brush_OConflict = CreateSolidBrush(RGB(242, 242, 242));
	SelectObject(hdc, Brush_OConflict);
	Ellipse(hdc, X - Rad0, Y - Rad0, X + Rad0, Y + Rad0);
	DeleteObject(Brush_OConflict);    // удаляем объект
}
//------------------------------------------------------------------------------
// Вызова радиуса
int OConflict_abstract::GetRad()
{
	return Rad0;
}

// Установка радиуса
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
	//-------------------обводим по КОНТУРУ-----------------------
	HPEN Pen_OConflict = CreatePen(PS_SOLID, 5, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Pen_OConflict);	//сделаем перо активным
	Ellipse(hdc, X - InitRad / 4, Y - InitRad / 4, X + InitRad / 4, Y + InitRad / 4);
	DeleteObject(Pen_OConflict);              // удаляем объект
}

void GreenCircle::inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	//------------------закрашиваем ПРОСТРАНСТВО--------------------
	HBRUSH Brush_OConflict = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, Brush_OConflict);
	Ellipse(hdc, X - InitRad / 4, Y - InitRad / 4, X + InitRad / 4, Y + InitRad / 4);
	DeleteObject(Brush_OConflict);    // удаляем объект
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

//объявление конструктора
Cloud::Cloud(int InitX, int InitY, int InitRad)
	: OConflict_abstract(InitX, InitY, InitRad)
{
	id = 2;
}
//объявление деструктора
Cloud::~Cloud() {}

void Cloud::edge_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	//-------------------обводим по КОНТУРУ-----------------------
	HPEN PenCloud = CreatePen(PS_SOLID, 2, RGB(InitRed, InitGreen, InitBlue));
	SelectObject(hdc, PenCloud);	//сделаем ПЕРО активным
	Ellipse(hdc, X - InitRad, Y - InitRad / 2, X + InitRad, Y + InitRad / 2); // рисуем облако
	DeleteObject(PenCloud); // удаляем перо
}


 void Cloud::inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue)
{
	 //------------------закрашиваем ПРОСТРАНСТВО--------------------
	 HBRUSH hBrush = CreateSolidBrush(RGB(InitRed, InitGreen, InitBlue));
	 SelectObject(hdc, hBrush); 	//сделаем КИСТЬ активной
	 Ellipse(hdc, X - InitRad, Y - InitRad/2, X + InitRad, Y + InitRad/2);// закрашиваем облако
	 DeleteObject(hBrush); // удаляем кисть
}


// --------------------------------------------------------------Показывает ОБЛАКО
void Cloud::Show()
{
	edge_Circle(Rad0, 0, 0, 0);
	inside_Circle(Rad0, 255, 255, 255);
} //Show()
//--------------------------------------------------------------------------------
// ----------------------------------------------------------------Скрывает ОБЛАКО
void Cloud::Hide()
{
	edge_Circle(Rad0, 242, 242, 242);
	inside_Circle(Rad0, 242, 242, 242);
} //Show()
//--------------------------------------------------------------------------------

//----------------------------------------------------
// LIGHTNING -----------------------------------------
//----------------------------------------------------

// объявление конструктора
Thunderstorm::Thunderstorm(int InitX, int InitY, int InitRad)
	: Cloud(InitX, InitY, InitRad)
{
	id = 0;
}
// объявление деструктора
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