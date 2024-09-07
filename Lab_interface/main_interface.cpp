#include <windows.h>
#include <conio.h>
#include <iostream>

#include "header_interface.h"
#include "GetConlWin.h"		//указатель на консольное окно


using namespace std;

//макрос дл€ определени€ кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
HDC hdc;
//HWND GetConcolWindow(); //указатель на консольное окно

//void func_Conflict(OConflict_abstract* InitConflict, WindMill* InitBufWill, int InitTemp);
bool IsConflict(WindMill* InitCurrent_Mill, OConflict_abstract* InitoConflict)
{
	// условие дл€ осущестpвлени€ первого конфликта
	if (abs(InitCurrent_Mill->GetX() - InitoConflict->GetX()) < 300
		&& (abs(InitCurrent_Mill->GetY() - InitoConflict->GetY()) < 200))
		return 1;
	else
		return 0;
}






int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	system("color F0");

	//----------------------------------------------------
//  Ќј„јЋ№Ќџ≈ ƒјЌЌџ≈ ---------------------------------
//----------------------------------------------------
	int step0 = 20;  // шаг перемещени€

	// Ќƒ дл€ мельницы
	const int x0 = 300; // начальные координата X
	const int y0 = 250; // начальные координата Y

	// Ќƒ дл€ облака
	int x_cloud = x0 + 700;
	int y_cloud = y0;
	int Rad0 = 150;

	// Ќƒ дл€ зелЄного круга
	int x_Circle = x0 + 800;
	int y_Circle = y0 + 500;

	// присваиваю начальные значени€ дл€ переменных FigX и FigY
	int FigX = x0;
	int FigY = y0;

	// инициализирую переменные, которые помогут заканчивать контакт после
	// пересечени€ с конфликтом
	int Temp_first = 0;
	int Temp_second = 0;

	//------------------------------------------------------------------------------------------------------------------------
	// определение требуемых фигур и указателей на них
	WindMill AWindMill(x0, y0);                     // объ€вл€ем обычную мельницу
	WindMill* p_AWindMill = &AWindMill;               // ” ј«ј“≈Ћ№, в котором лежит адрес на AWindMill

	WindMill BWindMill(x0, y0);                     // объ€вл€ем обычную мельницу
	WindMill* p_BWindMill = &BWindMill;               // ” ј«ј“≈Ћ№, в котором лежит адрес на BWindMill

	WindMill_3axis_ AWindMill_3axis_(x0 + 1200, y0 + 200); // объ€вл€ем 3-х лопастную мельницу

	WindMill_small AWindMill_small(x0 + 600, y0 + 200);   // объ€вл€ем маленькую мельницу
	
	WindMill_broken AWindMill_broken(x0, y0 + 200);       // объ€вл€ем сгоревшую мельницу

	WindMill_wide AWindMill_wide(x0, y0);
	
	

	Cloud ACloud(x_cloud-400, y_cloud+600, Rad0);               // объ€вл€ем облако
	//std::cout<<ACloud.GetId() << " ";
	Cloud* p_ACloud = &ACloud;

	
	GreenCircle AGreenCircle(x_Circle+600, y_Circle+100, 3*Rad0);
	GreenCircle* p_AGreenCircle = &AGreenCircle;

	Thunderstorm AThunderstorm(x_cloud+700, y0-100, Rad0); // объ€вл€ем грозу
	Thunderstorm* p_AThunderstorm = &AThunderstorm; // ” ј«ј“≈Ћ№,в котором лежит адрес на AThunderstorm
	//-------------------------------------------------------------------------------------------------------------------------

	// создал массив указателей на производные класс
	WindMill* array_WindMills[4] = { &BWindMill, &AWindMill_wide, & AWindMill_small, &AWindMill_broken, };
	//WindMill* BufWindMill[4]     = { &AWindMill_3axis_, &AWindMill_small,&BWindMill, &AWindMill_broken,  };

	// создал массив указателей на конфликтные классы
	OConflict_abstract* array_conflicts[3] = {&AThunderstorm, &AGreenCircle, &ACloud};
	OConflict_abstract* CurConflict;

	WindMill* Current_Mill = array_WindMills[0]; // положил в указатель-буфер адрес моей нормальной мельницы;
	Current_Mill->SetX(x0);
	Current_Mill->SetY(y0);

	//---------------------------------------------------
	// ќ—Ќќ¬Ќјя „ј—“№ ѕ–ќ√–јћћџ -------------------------
	//---------------------------------------------------

	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();

	if (hwnd != 0)
	{
		//получим контекст устройства дл€ консольного окна
		hdc = GetWindowDC(hwnd);

		if (hdc != 0)
		{
			p_AWindMill->Show();             // показываем   обычную мельницы
			p_AWindMill->Drag(step0);        // двигаем      обычную мельницу
			//1
			while (true)
			{
				if (KEY_DOWN(49)) //1
					break;
			}
			p_AWindMill->Hide();
			
			Current_Mill->Show();              // показываем текущую мельницы
			
			
			while (true)
			{
				p_AThunderstorm->Show();          // показываем √–ќ«”
				p_AGreenCircle->Show();           // показывает «≈Ћ®Ќџ…  –”√
				p_ACloud->Show();
				if (KEY_DOWN(VK_ESCAPE)) break; // выход из while
				// стрелка влево
				if (KEY_DOWN(37))
				{
					FigX -= step0;
					Current_Mill->MoveTo(FigX, FigY);
				} // влево

				// стрелка вправо
				if (KEY_DOWN(39))
				{
					FigX += step0;
					Current_Mill->MoveTo(FigX, FigY);
				} // вправо

				 // стрелка вверх
				if (KEY_DOWN(38))
				{
					FigY -= step0;
					Current_Mill->MoveTo(FigX, FigY);
				}// вверх

				 // стрелка вниз
				if (KEY_DOWN(40))
				{
					FigY += step0;
					Current_Mill->MoveTo(FigX, FigY);
				} // вниз

				for (int i = 0; i < 3; i++)
				{
					CurConflict = array_conflicts[i];
					if (IsConflict(Current_Mill, CurConflict) == 1)
					{
						if ((CurConflict->GetId() == 0))  // пересечение с √–ќ«ќ…
						{
							Current_Mill->Hide(); // пр€чет нормальную мельницу

							// хороша€ в сломанную
							if ((Current_Mill->GetId() == 0))
								Current_Mill = array_WindMills[1];

							// маленька€ в гуманоидную
							if ((Current_Mill->GetId() == 2))
								Current_Mill = array_WindMills[3];
							
							FigX -= 200;
							Current_Mill->SetX(FigX);
							Current_Mill->SetY(FigY);
							Current_Mill->Show(); // показывает испорченную мельницу;
						}
						if  (CurConflict->GetId() == 1) // пересечение с ЅќЋќ“ќћ
						{
							Current_Mill->Hide(); // пр€чет нормальную мельницу

							// сломанна€ в маленькую
							if (Current_Mill->GetId() == 3)
								Current_Mill = array_WindMills[2];

							// нормальна€ в гуманоидную
							if (Current_Mill->GetId() == 1)
								Current_Mill = array_WindMills[3];


							FigX -= 200;
							Current_Mill->SetX(FigX);
							Current_Mill->SetY(FigY);
							Current_Mill->Show(); // показывает испорченную мельницу;
						}
						if  (CurConflict->GetId() == 2) // пересечение с ќЅЋј ќћ
						{
							Current_Mill->Hide(); // пр€чет нормальную мельницу

							// маленька€ в нормальную
							if (Current_Mill->GetId() == 2)
								Current_Mill = array_WindMills[0];

							// гуманоидна€ в сломанную
							if (Current_Mill->GetId() == 1)
								Current_Mill = array_WindMills[3];


							FigX -= 100;
							Current_Mill->SetX(FigX);
							Current_Mill->SetY(FigY);
							Current_Mill->Show(); // показывает испорченную мельницу;
						}
					}
				}

				Sleep(30);
			} // while (true) = drag конфликта
		system("PAUSE");
		} // (hdc != 0)
	} // (hwnd != 0)	
} // main()

//// определение функции-конфликт, котора€ определ€ет с кем конфликт и производит необ действи€
//void func_Conflict(OConflict_abstract* InitConflict, WindMill*InitBufWill, int InitTemp)
//{
//	if(InitTemp = Temp_first)
//	{
//		InitBufWill->Hide(); // пр€чет нормальную мельницу
//		InitConflict->Hide(); // пропадает конфликт
//
//		if (InitBufWill == &BWindMill)
//		{
//			// мен€ю в указателе адрес текущей мельницы на адрес сломанной мельницы
//			InitBufWill = &AWindMill_broken;
//		}
//
//		if (InitBufWill == &AWindMill_small)
//		{
//			// мен€ю в указателе адрес текущей мельницы на адрес норм мельницы
//			InitBufWill = &BWindMill;
//		}
//
//		Temp_first += 1; // выхожу из if
//	}
//
//	if (InitTemp = Temp_second)
//	{
//		InitBufWill->Hide(); // пр€чет нормальную мельницу
//		InitConflict->Hide(); // пропадает конфликт 
//
//		if (InitBufWill == &BWindMill)
//		{
//			// мен€ю в указателе адрес текущей мельницы на адрес сломанной мельницы
//			InitBufWill = &AWindMill_small;
//		}
//
//		if (InitBufWill == &AWindMill_broken)
//		{
//			// мен€ю в указателе адрес текущей мельницы на адрес норм мельницы
//			InitBufWill = &BWindMill;
//		}
//
//		Temp_second += 1;
//	}
//}