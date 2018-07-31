#include<stdio.h>
#include<graphics.h> //ͼ�ο�ͷ�ļ�
#include<conio.h>
#include<mmsystem.h> //����������Ҫ�õ���ͷ�ļ�
#pragma comment(lib,"winmm.lib") //����������Ҫ�õ��Ŀ��ļ�


/**
**  ����궨�������Դ���������͵�����
**/
#define STWO 1
#define STHREE 2
#define SFOUR 3
#define TWO 4
#define THREE 5
#define FOUR 6
#define FIVE 7

/**
**  ȫ�ֱ�������
**/
int iCount = 1; //�ڰ��ӽ�������
int board[15][15] = { 0 }; //��������
int chesstype[15][15][7] = { 0 };
unsigned int score_c[15][15] = { 0 };
unsigned int score_p[15][15] = { 0 };

/**
**  ���еĺ�������
**/
void PrePrint();
void Print();
void Judgement_x(int x, int y, int t);
void Judgement_y(int x, int y, int t);
void Judgement_xy(int x, int y, int t);
void Judgement_yx(int x, int y, int t);
void ScoreType(int t);
void ComputerPlay();
int Victory(int a, int b);
void PlayerVsComputer();
void PlayerVsPlayer();

int main() //������
{
	PrePrint();
	
	_getch();
	closegraph();
	return 0;
}
void PrePrint() //��������Ϸ��ʼ����
{
	initgraph(400, 520);
	cleardevice();
	//setbkcolor(HSLtoRGB(200, 0.5, 0.5));
	loadimage(NULL, L"Tesla.jpg");
	setbkmode(0);
	setfillcolor(HSLtoRGB(40, 0.8, 0.8));
	setlinecolor(BLACK); //�����ߵ���ɫ
	roundrect(80,50, 320,130, 20, 20);
	roundrect(80, 150, 320, 230, 20, 20);
	roundrect(80, 250, 320, 330, 20, 20);
	roundrect(80, 350, 320, 430, 20, 20);
	settextstyle(50, 0, _T("����"));
	settextcolor(BLACK);
	outtextxy(100, 60, _T("���˶�ս"));
	outtextxy(100, 160, _T("�˻���ս"));
	outtextxy(100, 260, _T("��Ϸ����"));
	outtextxy(100, 360, _T("�˳���Ϸ"));

	MOUSEMSG mm;
	while (true)
	{
		mm = GetMouseMsg(); //���һ�������Ϣ
							//�ж��������Ƿ��£����ж��������ֵ�Ƿ�����������
		if (mm.uMsg == WM_LBUTTONDOWN && (mm.x >= 80 && mm.x <= 320) && (mm.y >= 50 && mm.y <= 130))
		{
			Print();
			PlayerVsPlayer();
		}
		if (mm.uMsg == WM_LBUTTONDOWN && (mm.x >= 80 && mm.x <= 320) && (mm.y >= 150 && mm.y <= 230))
		{
			Print();
			PlayerVsComputer();
		}
		if (mm.uMsg == WM_LBUTTONDOWN && (mm.x >= 80 && mm.x <= 320) && (mm.y >= 250 && mm.y <= 330))
		{
			mciSendString(L"open �����.mp3",0, 0, 0);
			mciSendString(L"play �����.mp3",0, 0, 0);
		}
		if (mm.uMsg == WM_LBUTTONDOWN && (mm.x >= 80 && mm.x <= 320) && (mm.y >= 350 && mm.y <= 430))
		{
			exit(0);
		}
	}
}
void Print()  //����������������
{
	initgraph(1280, 720);
	cleardevice();
	loadimage(NULL, L"background.jpg");
	setbkmode(0);
	setlinecolor(BLACK);
	rectangle(1180, 0, 1280, 50);
	settextstyle(50, 0, _T("����"));
	settextcolor(HSLtoRGB(200, 0.5, 0.5));
	outtextxy(40, 100, _T("ī"));
	outtextxy(40, 250, _T("��"));
	outtextxy(40, 400, _T("��"));
	outtextxy(40, 550, _T("��"));
	settextcolor(BLACK);
	outtextxy(1180, 0, _T("����"));
	roundrect(106, 46, 715, 655, 20, 20);
	setlinestyle(PS_ENDCAP_FLAT, 3);
	rectangle(126, 66, 695, 635);
	setlinestyle(PS_ENDCAP_SQUARE, 0.5);
	rectangle(131, 71, 690, 630);
	for (int i = 171; i < 690; i += 40)
		line(i, 71, i, 630);
	for (int j = 111; j < 630; j += 40)
		line(131, j, 690, j);

	setfillcolor(HSLtoRGB(240, 0, 0.3));
	solidcircle(251, 191, 4);
	solidcircle(570, 510, 4);
	solidcircle(251, 510, 4);
	solidcircle(570, 191, 4);
	solidcircle(411, 351, 4);
}

void PlayerVsPlayer() //���˶�ս
{
	iCount = 1;   //ÿ�ν���ý��涼���г�ʼ��
	board[15][15] = { 0 };
	chesstype[15][15][7] = { 0 };
	score_c[15][15] = { 0 };
	score_p[15][15] = { 0 };

	int a = 0, b = 0;
	int x, y;
	MOUSEMSG m;

	HWND hw; //���ھ��
	hw = GetHWnd(); //������ǰ

	while (true)
	{
		m = GetMouseMsg(); //���һ�������Ϣ
						   //�ж��������Ƿ��£����ж��������ֵ�Ƿ�����������
		if (m.uMsg == WM_LBUTTONDOWN && (m.x >= 111 && m.x <= 710) && (m.y >= 51 && m.y <= 650))
		{
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (abs(m.x - 130 - i * 40) <= 20 && abs(m.y - 71 - j * 40) <= 20)
					{
						a = i;   b = j; //�������к�
										//�������ӵ�����
						x = i * 40 + 130;
						y = j * 40 + 70;
					}
				}
			}
			if (board[a][b]) //�жϴ�λ���Ƿ��������ӣ����У����˳��ô�ѭ��
			{
				MessageBox(hw, L"��λ���������ӣ����������壡", L"����", MB_OK);
				continue;
			}
			if (iCount % 2 == 0)
			{
				setfillcolor(BLACK);
				board[a][b] = 1;
				solidcircle(x, y, 17);
			}
			else
			{
				setfillcolor(WHITE);
				board[a][b] = 2;
				solidcircle(x, y, 17);
			}
			if (Victory(a, b)) //���ú������ж�ʤ��
			{
				if (iCount % 2 == 0)
				{
					MessageBox(hw, L"����ʤ����", L"��Ϸ����", MB_OK);  PrePrint();
				}
				else
				{
					MessageBox(hw, L"����ʤ����", L"��Ϸ����", MB_OK);  PrePrint();
				}
			}
			iCount++;
		}
		if (m.uMsg == WM_LBUTTONDOWN && (m.x >= 1180 && m.x <= 1280) && (m.y >= 0 && m.y <= 50))
			PrePrint();
	}
}
void PlayerVsComputer() //�˻���ս
{
	iCount = 1;   //ÿ�ν���ý��涼���г�ʼ��
	board[15][15] = { 0 };
	chesstype[15][15][7] = { 0 };
	score_c[15][15] = { 0 };
	score_p[15][15] = { 0 };

	int a = 0, b = 0;
	int x, y;
	MOUSEMSG m;

	HWND hw; //���ھ��
	hw = GetHWnd(); //������ǰ

	while (true)
	{
		m = GetMouseMsg(); //���һ�������Ϣ
						   //�ж��������Ƿ��£����ж��������ֵ�Ƿ�����������
		if (m.uMsg == WM_LBUTTONDOWN && (m.x >= 111 && m.x <= 710) && (m.y >= 51 && m.y <= 650))
		{
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (abs(m.x - 130 - i * 40) <= 20 && abs(m.y - 71 - j * 40) <= 20)
					{
						a = i;   b = j; //�������к�
						x = i * 40 + 130; //�������ӵ�����
						y = j * 40 + 70;
					}
				}
			}
			if (board[a][b]) //�жϴ�λ���Ƿ��������ӣ����У����˳��ô�ѭ��
			{
				MessageBox(hw, L"��λ���������ӣ����������壡", L"����", MB_OK);
				continue;
			}

			setfillcolor(WHITE);
			board[a][b] = 2;
			solidcircle(x, y, 17);
			if (Victory(a, b))
			{
				if (iCount % 2 == 1)
				{
					MessageBox(hw, L"����ʤ������Ϸ������", L"Game Over", MB_OK);  PrePrint();
				}
				else
				{
					MessageBox(hw, L"����ʤ������Ϸ������", L"Game Over", MB_OK);  PrePrint();
				}
			}
			iCount++;
			ComputerPlay();
		}
		if (m.uMsg == WM_LBUTTONDOWN && (m.x >= 1180 && m.x <= 1280) && (m.y >= 0 && m.y <= 50))
			PrePrint();
	}
}
void ComputerPlay() //��������
{
	HWND hw; //���ھ��
	hw = GetHWnd(); //������ǰ

	unsigned int TempMax_c, TempMax_p;
	unsigned int aMax_p = 0, bMax_p = 0;
	unsigned int aMax_c = 0, bMax_c = 0;
	unsigned int x = 0, y = 0;
	ScoreType(1);
	ScoreType(2);
	TempMax_c = score_c[0][0];
	TempMax_p = score_p[0][0];

	for (int i = 0;i < 15;i++)
	{
		for (int j = 0;j < 15;j++)
		{
			if (board[i][j])
				continue;
			if (score_c[i][j] > TempMax_c)
			{
				TempMax_c = score_c[i][j];
				aMax_c = i;
				bMax_c = j;
			}
			if (score_p[i][j] > TempMax_p)
			{
				TempMax_p = score_p[i][j];
				aMax_p = i;
				bMax_p = j;
			}
		}
	}
	if (TempMax_c > TempMax_p)
	{
		x = aMax_c;   y = bMax_c;
	}
	else
	{
		x = aMax_p;   y = bMax_p;
	}
	setfillcolor(BLACK);
	board[x][y] = 1;
	solidcircle(x * 40 + 130, y * 40 + 70, 17);
	if (Victory(x, y))
	{
		if (iCount % 2 == 1)
		{
			MessageBox(hw, L"����ʤ������Ϸ������", L"Game Over", MB_OK); PrePrint();
		}
		else
		{
			MessageBox(hw, L"����ʤ������Ϸ������", L"Game Over", MB_OK); PrePrint();
		}
	}
	iCount++;
}
void Judgement_x(int x, int y, int t) //�жϺ�����������
{
	int k = 1, i = 1;
	int k1, k2;
	for (;board[x + i][y] == t && x + i < 15;i++)   k++;
	k1 = k;
	for (i = 1;board[x - i][y] == t && x - i >= 0;i++)   k++;
	k2 = k + 1 - k1;
	if (((board[x + k1][y] == 2 / t || x + k1 >= 15) && (board[x - k2][y] == 0 && x - k2 >= 0)) || ((board[x + k1][y] == 0 && x + k1 < 15) && (board[x - k2][y] == 2 / t || x - k2 < 0)))
	{
		switch (k) {
		case 2:chesstype[x][y][STWO]++;break;
		case 3:chesstype[x][y][STHREE]++;break;
		case 4:chesstype[x][y][SFOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
	if ((board[x + k1][y] == 0 && x + k1<15) && (board[x - k2][y] == 0 && x - k2 >= 0))
	{
		switch (k) {
		case 2:chesstype[x][y][TWO]++;break;
		case 3:chesstype[x][y][THREE]++;break;
		case 4:chesstype[x][y][FOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
}
void Judgement_y(int x, int y, int t) //�ж�������������
{
	int k = 1, i = 1;
	int k1, k2;
	for (;board[x][y + i] == t && y + i < 15;i++)   k++;
	k1 = k;
	for (i = 1;board[x][y - i] == t && y - i >= 0;i++)   k++;
	k2 = k + 1 - k1;
	if (((board[x][y + k1] == 2 / t || y + k1 >= 15) && (board[x][y - k2] == 0 && y - k2 >= 0)) || ((board[x][y + k1] == 0 && y + k1 < 15) && (board[x][y - k2] == 2 / t || y - k2 < 0)))
	{
		switch (k) {
		case 2:chesstype[x][y][STWO]++;break;
		case 3:chesstype[x][y][STHREE]++;break;
		case 4:chesstype[x][y][SFOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
	if ((board[x][y + k1] == 0 && y + k1<15) && (board[x][y - k2] == 0 && y - k2 >= 0))
	{
		switch (k) {
		case 2:chesstype[x][y][TWO]++;break;
		case 3:chesstype[x][y][THREE]++;break;
		case 4:chesstype[x][y][FOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
}
void Judgement_xy(int x, int y, int t) //�ж���б������������
{
	int k = 1, i = 1;
	int k1, k2;
	for (;board[x + i][y - i] == t && x + i < 15 && y - i >= 0;i++)   k++;
	k1 = k;
	for (i = 1;board[x - i][y + i] == t && x - i >= 0 && y + i<15;i++)   k++;
	k2 = k + 1 - k1;
	if (((board[x + k1][y - k1] == 2 / t || x + k1 >= 15 || y - k1<0) && (board[x - k2][y + k2] == 0 && x - k2 >= 0 && y + k2<15)) || ((board[x + k1][y - k1] == 0 && x + k1 < 15 && y - k1 >= 0) && (board[x - k2][y + k2] == 2 / t || x - k2 < 0 || y + k2 >= 15)))
	{
		switch (k) {
		case 2:chesstype[x][y][STWO]++;break;
		case 3:chesstype[x][y][STHREE]++;break;
		case 4:chesstype[x][y][SFOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
	if ((board[x + k1][y - k1] == 0 && x + k1<15 && y - k1 >= 0) && (board[x - k2][y + k2] == 0 && x - k2 >= 0 && y + k2<15))
	{
		switch (k) {
		case 2:chesstype[x][y][TWO]++;break;
		case 3:chesstype[x][y][THREE]++;break;
		case 4:chesstype[x][y][FOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
}
void Judgement_yx(int x, int y, int t) //�ж���б������������
{
	int k = 1, i = 1;
	int k1, k2;
	for (;board[x + i][y + i] == t && x + i < 15 && y + i;i++)   k++;
	k1 = k;
	for (i = 1;board[x - i][y - i] == t && x - i >= 0 && y - i >= 0;i++)   k++;
	k2 = k + 1 - k1;
	if (((board[x + k1][y + k1] == 2 / t || x + k1 >= 15 || y + k1 >= 15) && (board[x - k2][y - k2] == 0 && x - k2 >= 0 && y - k2 >= 0)) || ((board[x + k1][y + k1] == 0 && x + k1 < 15 && y + k1<15) && (board[x - k2][y - k2] == 2 / t || x - k2 < 0 || y - k2<0)))
	{
		switch (k) {
		case 2:chesstype[x][y][STWO]++;break;
		case 3:chesstype[x][y][STHREE]++;break;
		case 4:chesstype[x][y][SFOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
	if ((board[x + k1][y + k1] == 0 && x + k1<15 && y + k1<15) && (board[x - k2][y - k2] == 0 && x - k2 > 0 && y - k2>0))
	{
		switch (k) {
		case 2:chesstype[x][y][TWO]++;break;
		case 3:chesstype[x][y][THREE]++;break;
		case 4:chesstype[x][y][FOUR]++;break;
		case 5:chesstype[x][y][FIVE]++;break;
		default:break;
		}
	}
}
void ScoreType(int t) //����λ�ü�ֵ����
{
	int i, j;
	unsigned int TempScore = 0;
	for (i = 0;i < 15;i++)//�����������꣬ͳ�Ƴ�ÿ��λ�õ����͸��ж���
	{
		for (j = 0;j < 15;j++)
		{
			if (board[i][j] == 0)
			{
				Judgement_x(i, j, t);
				Judgement_y(i, j, t);
				Judgement_xy(i, j, t);
				Judgement_yx(i, j, t);
				if (chesstype[i][j][FIVE])
					TempScore += chesstype[i][j][FIVE] * 9999;
				if (chesstype[i][j][FOUR])
					TempScore += chesstype[i][j][FOUR] * 9990;
				if (chesstype[i][j][SFOUR])
					TempScore += chesstype[i][j][SFOUR] * 9980;
				if (chesstype[i][j][THREE] > 1)
					TempScore += ((chesstype[i][j][THREE] - 2) * 2000 + 2 * 9970);
				if (chesstype[i][j][THREE] == 1)
					TempScore += chesstype[i][j][THREE] * 200;
				if (chesstype[i][j][STHREE])
					TempScore += chesstype[i][j][STHREE] * 10;
				if (chesstype[i][j][TWO])
					TempScore += chesstype[i][j][TWO] * 4;
				if (chesstype[i][j][STWO])
					TempScore += chesstype[i][j][STWO] * 1;
				if (t == 1)
					score_c[i][j] = TempScore;
				else
					score_p[i][j] = TempScore;
			}
		}
	}
}

int Victory(int a, int b) //�ж�ʤ���ı�־
{
	int i, j;
	int t;
	t = 1 + iCount % 2;
	for (i = a - 4, j = b;i <= a;i++)    /*�жϺ�������*/
	{
		if ((i >= 0 && i < 11) && (j >= 0 && j < 15) && (board[i][j] == t && board[i + 1][j] == t && board[i + 2][j] == t && board[i + 3][j] == t && board[i + 4][j] == t))
			return 1;
	}
	for (i = a, j = b - 4;j <= b;j++)    /*�ж���������*/
	{
		if ((i >= 0 && i < 15) && (j >= 0 && j <11) && (board[i][j] == t && board[i][j + 1] == t && board[i][j + 2] == t && board[i][j + 3] == t && board[i][j + 4] == t))
			return 1;
	}
	for (i = a - 4, j = b - 4;i <= a;i++)    /*�ж���б��������*/
	{
		if ((i >= 0 && i < 11) && (j >= 0 && j <11) && (board[i][j] == t && board[i + 1][j + 1] == t && board[i + 2][j + 2] == t && board[i + 3][j + 3] == t && board[i + 4][j + 4] == t))
			return 1;
	}
	for (i = a + 4, j = b - 4;j <= b;j++)    /*�ж���б��������*/
	{
		if ((i >= 4 && i < 15) && (j >= 0 && j <11) && (board[i][j] == t && board[i - 1][j + 1] == t && board[i - 2][j + 2] == t && board[i - 3][j + 3] == t && board[i - 4][j + 4] == t))
			return 1;
	}
	return 0;
}

