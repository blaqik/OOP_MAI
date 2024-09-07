#pragma once
// класс ЛОКАЦИЯ
class Location
{
protected:
	int X; // координаты X
	int Y; // координаты Y
public:
	Location(int InitX, int InitY); // контруктор
	~Location(); // деструктор

	int GetX(); // получение координаты Х
	int GetY(); // получение координаты Y
	void SetX(int InitX); // задача координаты X
	void SetY(int InitY); // задать коориднаты Y

	// создание функций для рисования основных геом фигур
	void Show_Rect(int InitX, int InitY, int InitLength, int InitWidth,
		int InitRed, int InitGreen, int InitBlue);
	void Show_Triangle(int InitX, int InitY, int InitBase, int InitHeight,
		int InitRed, int InitGreen, int InitBlue);
};

// класс ТОЧКА
class Point : public Location
{
public:
	Point(int InitX, int InitY); // контруктор
	~Point();  // деструктор

	virtual void Show(); // функция, которая показывает точку
	virtual void Hide(); // функция, которая скрывает точку
	void MoveTo(int NewX, int NewY); // функция, которая двигает точку
	void Drag(int InitStep); // функция, которая двигает точки 4-мя клавишами
};

// класс ИНТЕРФЕЙС
class WindMill_interface
{
public:
	virtual void Main_Building() = 0;
	virtual void Roof() = 0;
	virtual void Axis() = 0;
	virtual void Blades() = 0;
};

// класс МЕЛЬНИЦА
class WindMill : public Point, public WindMill_interface
{
public:
	int id;
	WindMill(int InitX, int InitY);
	~WindMill();
	int GetId();
	virtual void Main_Building();
	virtual void Roof();
	virtual void Axis();
	virtual void Blades();

	virtual void Show();
	virtual void Hide();

	
};

// класс МЕЛЬНИЦА с тремя лопастями
class WindMill_3axis_ : public WindMill
{
public:
	WindMill_3axis_(int InitX, int InitY);  // контруктор
	~WindMill_3axis_();                     // деструктор

	virtual void Main_Building();
	virtual void Roof();
	virtual void Axis();
	virtual void Blades();

	virtual void Hide();
};

class WindMill_wide : public WindMill_3axis_
{
public:
	WindMill_wide(int InitX, int InitY);
	~WindMill_wide();

	virtual void Main_Building();

};

// класс МЕЛЬНИЦА в уменьшенных размерах
class WindMill_small : public WindMill
{
public:
	WindMill_small(int InitX, int InitY);  // контруктор
	~WindMill_small();                     // деструктор

	virtual void Main_Building();
	virtual void Roof();
	virtual void Axis();
	virtual void Blades();

	virtual void Hide();
};

// класс МЕЛЬНИЦА, после последствий с облаком
class WindMill_broken : public WindMill
{
public:
	WindMill_broken(int InitX, int InitY);  // контруктор
	~WindMill_broken();                     // деструктор

	virtual void Main_Building();
	virtual void Roof();
	virtual void Axis();
	virtual void Blades();

	virtual void Hide();
};


//-------------КЛАССЫ-КОНФПЛИКТЫ-------------------

// класс
class OConflict_abstract : public Point
{
protected:
	int Rad0;
	int id;
public:
	int GetId();

	OConflict_abstract(int InitX, int InitY, int InitRad);
	~OConflict_abstract();

	virtual void edge_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue) = 0;
	virtual void inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue) = 0;
	
	
	virtual void Show();
	virtual void Hide();

	int GetRad();
	void SetRad(int InitRad);
};

// класс ЗЕЛЁНЫЙ КРУГ
class GreenCircle : public OConflict_abstract
{
public:
	GreenCircle(int InitX, int InitY, int InitRad);
	~GreenCircle();

	virtual void edge_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue);
	virtual void inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue) ;

	virtual void Show();
	virtual void Hide();
};

// класс ОБЛАКО
class Cloud : public OConflict_abstract
{
public:
	Cloud(int InitX, int InitY, int InitRad);
	~Cloud();

	virtual void edge_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue);
	virtual void inside_Circle(int InitRad, int InitRed, int InitGreen, int InitBlue);

	virtual void Show();
	virtual void Hide();

};

// класс МОЛНИЯ
class Thunderstorm : public Cloud
{
public:
	Thunderstorm(int InitX, int InitY, int InitRad);
	~Thunderstorm();

	virtual void Show();
	virtual void Hide();
};