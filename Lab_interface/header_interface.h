#pragma once
// ����� �������
class Location
{
protected:
	int X; // ���������� X
	int Y; // ���������� Y
public:
	Location(int InitX, int InitY); // ����������
	~Location(); // ����������

	int GetX(); // ��������� ���������� �
	int GetY(); // ��������� ���������� Y
	void SetX(int InitX); // ������ ���������� X
	void SetY(int InitY); // ������ ���������� Y

	// �������� ������� ��� ��������� �������� ���� �����
	void Show_Rect(int InitX, int InitY, int InitLength, int InitWidth,
		int InitRed, int InitGreen, int InitBlue);
	void Show_Triangle(int InitX, int InitY, int InitBase, int InitHeight,
		int InitRed, int InitGreen, int InitBlue);
};

// ����� �����
class Point : public Location
{
public:
	Point(int InitX, int InitY); // ����������
	~Point();  // ����������

	virtual void Show(); // �������, ������� ���������� �����
	virtual void Hide(); // �������, ������� �������� �����
	void MoveTo(int NewX, int NewY); // �������, ������� ������� �����
	void Drag(int InitStep); // �������, ������� ������� ����� 4-�� ���������
};

// ����� ���������
class WindMill_interface
{
public:
	virtual void Main_Building() = 0;
	virtual void Roof() = 0;
	virtual void Axis() = 0;
	virtual void Blades() = 0;
};

// ����� ��������
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

// ����� �������� � ����� ���������
class WindMill_3axis_ : public WindMill
{
public:
	WindMill_3axis_(int InitX, int InitY);  // ����������
	~WindMill_3axis_();                     // ����������

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

// ����� �������� � ����������� ��������
class WindMill_small : public WindMill
{
public:
	WindMill_small(int InitX, int InitY);  // ����������
	~WindMill_small();                     // ����������

	virtual void Main_Building();
	virtual void Roof();
	virtual void Axis();
	virtual void Blades();

	virtual void Hide();
};

// ����� ��������, ����� ����������� � �������
class WindMill_broken : public WindMill
{
public:
	WindMill_broken(int InitX, int InitY);  // ����������
	~WindMill_broken();                     // ����������

	virtual void Main_Building();
	virtual void Roof();
	virtual void Axis();
	virtual void Blades();

	virtual void Hide();
};


//-------------������-����������-------------------

// �����
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

// ����� ��˨��� ����
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

// ����� ������
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

// ����� ������
class Thunderstorm : public Cloud
{
public:
	Thunderstorm(int InitX, int InitY, int InitRad);
	~Thunderstorm();

	virtual void Show();
	virtual void Hide();
};