#pragma once
/**/
extern void consoleClear();

extern void consoleColorSet(const char *color);
/*
�趨���ڱ���
@param const char title ��������
@return void
*/
extern void consoleTitleSet(const char *title = "Hafrans Flex Project");

extern void consoledrawBorder(int type, int count, int align);
/**
*�ڿ���̨�����߿���������֣����Ȳ�Ҫ����68
*@param int type �߿�����
*@param int count = 1 �ظ��������
*@param int align = ALIGN_LEFT ���뷽ʽ
*@param int talign = ALIGN_LEFT ���ֶ��뷽ʽ
*
*@author Hafrans Newton
*/
extern void consoleDrawText(char *text, int align = ALIGN_CENTER, int talign = ALIGN_CENTER, int type = 1);

extern void consoleNewLine(int count);

extern void consoleWaitinCMD();

