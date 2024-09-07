#include <windows.h>
#include <conio.h>
#include <iostream>

#include "header_interface.h"
#include "GetConlWin.h"		//��������� �� ���������� ����


using namespace std;

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
HDC hdc;
//HWND GetConcolWindow(); //��������� �� ���������� ����

//void func_Conflict(OConflict_abstract* InitConflict, WindMill* InitBufWill, int InitTemp);
bool IsConflict(WindMill* InitCurrent_Mill, OConflict_abstract* InitoConflict)
{
	// ������� ��� �������p������ ������� ���������
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
//  ��������� ������ ---------------------------------
//----------------------------------------------------
	int step0 = 20;  // ��� �����������

	// �� ��� ��������
	const int x0 = 300; // ��������� ���������� X
	const int y0 = 250; // ��������� ���������� Y

	// �� ��� ������
	int x_cloud = x0 + 700;
	int y_cloud = y0;
	int Rad0 = 150;

	// �� ��� ������� �����
	int x_Circle = x0 + 800;
	int y_Circle = y0 + 500;

	// ���������� ��������� �������� ��� ���������� FigX � FigY
	int FigX = x0;
	int FigY = y0;

	// ������������� ����������, ������� ������� ����������� ������� �����
	// ����������� � ����������
	int Temp_first = 0;
	int Temp_second = 0;

	//------------------------------------------------------------------------------------------------------------------------
	// ����������� ��������� ����� � ���������� �� ���
	WindMill AWindMill(x0, y0);                     // ��������� ������� ��������
	WindMill* p_AWindMill = &AWindMill;               // ���������, � ������� ����� ����� �� AWindMill

	WindMill BWindMill(x0, y0);                     // ��������� ������� ��������
	WindMill* p_BWindMill = &BWindMill;               // ���������, � ������� ����� ����� �� BWindMill

	WindMill_3axis_ AWindMill_3axis_(x0 + 1200, y0 + 200); // ��������� 3-� ��������� ��������

	WindMill_small AWindMill_small(x0 + 600, y0 + 200);   // ��������� ��������� ��������
	
	WindMill_broken AWindMill_broken(x0, y0 + 200);       // ��������� ��������� ��������

	WindMill_wide AWindMill_wide(x0, y0);
	
	

	Cloud ACloud(x_cloud-400, y_cloud+600, Rad0);               // ��������� ������
	//std::cout<<ACloud.GetId() << " ";
	Cloud* p_ACloud = &ACloud;

	
	GreenCircle AGreenCircle(x_Circle+600, y_Circle+100, 3*Rad0);
	GreenCircle* p_AGreenCircle = &AGreenCircle;

	Thunderstorm AThunderstorm(x_cloud+700, y0-100, Rad0); // ��������� �����
	Thunderstorm* p_AThunderstorm = &AThunderstorm; // ���������,� ������� ����� ����� �� AThunderstorm
	//-------------------------------------------------------------------------------------------------------------------------

	// ������ ������ ���������� �� ����������� �����
	WindMill* array_WindMills[4] = { &BWindMill, &AWindMill_wide, & AWindMill_small, &AWindMill_broken, };
	//WindMill* BufWindMill[4]     = { &AWindMill_3axis_, &AWindMill_small,&BWindMill, &AWindMill_broken,  };

	// ������ ������ ���������� �� ����������� ������
	OConflict_abstract* array_conflicts[3] = {&AThunderstorm, &AGreenCircle, &ACloud};
	OConflict_abstract* CurConflict;

	WindMill* Current_Mill = array_WindMills[0]; // ������� � ���������-����� ����� ���� ���������� ��������;
	Current_Mill->SetX(x0);
	Current_Mill->SetY(y0);

	//---------------------------------------------------
	// �������� ����� ��������� -------------------------
	//---------------------------------------------------

	//������� ���������� ����������� ����
	HWND hwnd = GetConcolWindow();

	if (hwnd != 0)
	{
		//������� �������� ���������� ��� ����������� ����
		hdc = GetWindowDC(hwnd);

		if (hdc != 0)
		{
			p_AWindMill->Show();             // ����������   ������� ��������
			p_AWindMill->Drag(step0);        // �������      ������� ��������
			//1
			while (true)
			{
				if (KEY_DOWN(49)) //1
					break;
			}
			p_AWindMill->Hide();
			
			Current_Mill->Show();              // ���������� ������� ��������
			
			
			while (true)
			{
				p_AThunderstorm->Show();          // ���������� �����
				p_AGreenCircle->Show();           // ���������� ��˨��� ����
				p_ACloud->Show();
				if (KEY_DOWN(VK_ESCAPE)) break; // ����� �� while
				// ������� �����
				if (KEY_DOWN(37))
				{
					FigX -= step0;
					Current_Mill->MoveTo(FigX, FigY);
				} // �����

				// ������� ������
				if (KEY_DOWN(39))
				{
					FigX += step0;
					Current_Mill->MoveTo(FigX, FigY);
				} // ������

				 // ������� �����
				if (KEY_DOWN(38))
				{
					FigY -= step0;
					Current_Mill->MoveTo(FigX, FigY);
				}// �����

				 // ������� ����
				if (KEY_DOWN(40))
				{
					FigY += step0;
					Current_Mill->MoveTo(FigX, FigY);
				} // ����

				for (int i = 0; i < 3; i++)
				{
					CurConflict = array_conflicts[i];
					if (IsConflict(Current_Mill, CurConflict) == 1)
					{
						if ((CurConflict->GetId() == 0))  // ����������� � ������
						{
							Current_Mill->Hide(); // ������ ���������� ��������

							// ������� � ���������
							if ((Current_Mill->GetId() == 0))
								Current_Mill = array_WindMills[1];

							// ��������� � �����������
							if ((Current_Mill->GetId() == 2))
								Current_Mill = array_WindMills[3];
							
							FigX -= 200;
							Current_Mill->SetX(FigX);
							Current_Mill->SetY(FigY);
							Current_Mill->Show(); // ���������� ����������� ��������;
						}
						if  (CurConflict->GetId() == 1) // ����������� � �������
						{
							Current_Mill->Hide(); // ������ ���������� ��������

							// ��������� � ���������
							if (Current_Mill->GetId() == 3)
								Current_Mill = array_WindMills[2];

							// ���������� � �����������
							if (Current_Mill->GetId() == 1)
								Current_Mill = array_WindMills[3];


							FigX -= 200;
							Current_Mill->SetX(FigX);
							Current_Mill->SetY(FigY);
							Current_Mill->Show(); // ���������� ����������� ��������;
						}
						if  (CurConflict->GetId() == 2) // ����������� � �������
						{
							Current_Mill->Hide(); // ������ ���������� ��������

							// ��������� � ����������
							if (Current_Mill->GetId() == 2)
								Current_Mill = array_WindMills[0];

							// ����������� � ���������
							if (Current_Mill->GetId() == 1)
								Current_Mill = array_WindMills[3];


							FigX -= 100;
							Current_Mill->SetX(FigX);
							Current_Mill->SetY(FigY);
							Current_Mill->Show(); // ���������� ����������� ��������;
						}
					}
				}

				Sleep(30);
			} // while (true) = drag ���������
		system("PAUSE");
		} // (hdc != 0)
	} // (hwnd != 0)	
} // main()

//// ����������� �������-��������, ������� ���������� � ��� �������� � ���������� ���� ��������
//void func_Conflict(OConflict_abstract* InitConflict, WindMill*InitBufWill, int InitTemp)
//{
//	if(InitTemp = Temp_first)
//	{
//		InitBufWill->Hide(); // ������ ���������� ��������
//		InitConflict->Hide(); // ��������� ��������
//
//		if (InitBufWill == &BWindMill)
//		{
//			// ����� � ��������� ����� ������� �������� �� ����� ��������� ��������
//			InitBufWill = &AWindMill_broken;
//		}
//
//		if (InitBufWill == &AWindMill_small)
//		{
//			// ����� � ��������� ����� ������� �������� �� ����� ���� ��������
//			InitBufWill = &BWindMill;
//		}
//
//		Temp_first += 1; // ������ �� if
//	}
//
//	if (InitTemp = Temp_second)
//	{
//		InitBufWill->Hide(); // ������ ���������� ��������
//		InitConflict->Hide(); // ��������� �������� 
//
//		if (InitBufWill == &BWindMill)
//		{
//			// ����� � ��������� ����� ������� �������� �� ����� ��������� ��������
//			InitBufWill = &AWindMill_small;
//		}
//
//		if (InitBufWill == &AWindMill_broken)
//		{
//			// ����� � ��������� ����� ������� �������� �� ����� ���� ��������
//			InitBufWill = &BWindMill;
//		}
//
//		Temp_second += 1;
//	}
//}