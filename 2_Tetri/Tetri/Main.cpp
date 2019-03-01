#include "Console.h"
#include "Window.h"
#include "GameDefine.h"
#include "Tetris.h"
#include <WinUser.h>
#include <conio.h>

DWORD oldTime = 0;

// �õ���������
Cmd GetCmd(Tetris& tetris, Console& console)
{
	while (true)
	{
		// ��ʱ������CPUռ����
		Sleep(SLEEP_TIME);

		DWORD newTime = GetTickCount();

		// ��ʱ����
		if (newTime - oldTime > TIME_OUT)
		{
			oldTime = newTime;
			return CMD_DOWN;
		}

		// �а���
		if (_kbhit())
		{
			switch (_getch())
			{
			case KEY_ENTER:
				return CMD_BEGIN;
			case KEY_SPACE:
				return CMD_SINK;
			case KEY_ESC:
				return CMD_QUIT;

			case 0:
			case 0xE0:
				switch (_getch())
				{
				case KEY_F1:
					return CMD_PAUSE;
				case KEY_LBUTTON:
					return CMD_VOICE;
				case KEY_UP:
					return CMD_ROTATE;
				case KEY_LEFT:
					return CMD_LEFT;
				case KEY_RIGHT:
					return CMD_RIGHT;
				case KEY_DOWN:
					return CMD_DOWN;
				}

			}
		}

		if (tetris.IsRun() && tetris.GetLevel() <= 10)
		{
			return CMD_DOWN;
		}
	}
}

// �ַ����������
void DispatchCmd(Tetris& tetris, Console& console, Cmd cmd)
{
	switch (cmd)
	{
	case CMD_QUIT:
		exit(0);
		break;
	default:
		tetris.MessageProc(cmd);
		break;

	}
}

int main()
{
	// ����һ������̨
	Console console;

	// ����һ������
	COORD coordinate = { GameStartX, GameStartY };

	const char* strGameName = "����˹���� ---- By AceTan ";
	console.Init(strGameName, coordinate);

	int keys[KeyNum] = { KEY_ENTER, KEY_F1,KEY_LBUTTON, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_SPACE };
	char decs[KeyNum][5] = { "�س�", "F1", "F2", "��", "��", "��", "��", "�ո�" };

	COORD coord = { 0, 0 };
	Tetris tetris(console, coord);

	tetris.Init(keys, decs, DEFAULT_FREQUENCY, DEFAULT_DURATION);
	
	Cmd cmd;
	while (true)
	{
		//Beep(65,40);
		cmd = GetCmd(tetris, console);
		DispatchCmd(tetris, console, cmd);
	}

	return 0;
}

/*���ߣ�AceTan
���ӣ�https ://www.jianshu.com/p/7369e0a90580
��Դ������
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������*/