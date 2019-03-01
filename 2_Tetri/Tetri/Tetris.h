//--------------------------------------------------------------------
// �ļ���:        Tetris.h
// ��  ��:        ����˹������
// ˵  ��:        
// ��������:        2016��9��6��
//--------------------------------------------------------------------

#pragma once
#include "Console.h"
#include "Window.h"
#include "GameDefine.h"

class Tetris
{
public:

	/// \brief ���캯��
	/// \param console ����̨
	/// \param coordinate ����̨�ĸߺͿ�
	Tetris(Console& console, COORD coordinate);

	/// \brief ��ʼ����Ϸ
	/// \param keys ����
	/// \param keyDesc ��������
	/// \param frequency ��ЧƵ��
	/// \param duration ����ʱ��
	void Init(int keys[KeyNum], char keyDesc[KeyNum][5], DWORD frequency, DWORD duration);

	/// \brief �Ƿ�����������Ϸ
	bool IsRun();

	/// \brief ��ȡ��ǰ�ȼ�
	int GetLevel() const;

	/// \brief ��������
	bool Fall();

	/// \brief ��Ϣ����
	/// \param key ����
	/// \return ��Ϸ��������false
	bool MessageProc(const Cmd cmd);

private:
	/// \brief ��Ч
	void VoiceBeep();

	/// \brief ���Ƶ÷�
	void DrawScoreLevel();

	/// \brief ������һ����Ҫ���ֵ�ͼ��
	void DrawNext();

	/// \brief ������Ϸ��������
	void DrawGameOver();

	/// \brief ������ɫ
	void Draw(WORD color);

	/// \brief �������Ƿ����
	bool IsFit(int x, int y, int c, int z);

	/// \brief ������
	void RemoveRow();

	/// \brief ��ת(��ʱ��)
	void MoveTrans();

	/// \brief �����ƶ�
	void MoveLeft();

	/// \brief �����ƶ�
	void MoveRight();

	/// \brief �����ƶ�
	/// \return 0: ��Ϸ������ -1:���ף� 1:û�д���
	int MoveDown();

	/// \brief ���䵽��
	bool FallToBottom();

private:
	char bg[GAME_HIGHT * GAME_WIDTH + 1];
	char bk[DIAMONDS_TYPES][DIAMONDS_TRANS][DIAMONDS_IFNO_ROW][DIAMONDS_IFNO_COL];

private:
	// ��ЧƵ��
	DWORD m_voiceFrequency;

	// ����ʱ��
	DWORD m_voiceDuration;    

	// ���ư���
	int m_keys[KeyNum];

	// ���ư���������
	char m_keyDesc[KeyNum][5];

	// ��Ϸ�Ƿ����
	bool m_gameover;

	// ��Ϸ��ͣ
	bool m_pause;

	// ��Ϸ��Ч����
	bool m_voice;

	// ��Ϸ�÷�
	int m_score;

	// ��Ϸ�ٶ�
	int m_speed;

	// ��Ϸ����(ʵ�ʷ���Ĵ������)
	char m_data[ROWS][COLS];

	// ��һ������
	int m_next;

	// λ��(x, y)
	int m_x, m_y;

	// ��ǰ����
	int m_currentDiamonds;

	// ��ǰ����
	int m_currentDir;

	// ����
	Window win;

};

