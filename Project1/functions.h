#pragma once


/*
	��ȡϵͳ��λ��
*/
extern size_t getOSBit();
/*
	ʱ���ת��Ϊ�ַ���
*/
extern char *timestampToString(time_t timeb);
/*
	�����������ַ���
	@param const char *textA
	@param const char *textB
	@return char *
*/
extern char *strcat_t(const char *textA, const char *textB);
/*
	ȥ���ַ������ҿհ��ַ�
	@param char* text
	@return char * 
*/
extern char *trim(char *text);
/*
	���д���ļ��пո�����
*/
extern char *parseSpaceString(const char *text);
/*
	�����ȡ�ļ��޿ո�����
*/
extern char *parseStringSpace(const char *text);
/*
	���ִ洢
*/
extern void stringSave(char *TextA, const char *TextB);

extern void exitLMS();

extern char *delspace(const char *text);
/*
	��־��¼
*/
extern void consoleLog(const char *text = "Unknown Error");
/*
	��char��ָ��c 𤸽 00VAR_EMPTY99 �ַ���""
*/
extern const char *testCharNULLPTRToEmptyString(const char *text);
/*
	�ַ����ָ������
	����ȴ���һ��ָ���ַ������ָ��
	@param char delimiter �ָ��
	@param char *text �����ַ���
	@param const _EXPLODE_TYPE dest ָ���ָ��
	@return size_t Ԫ�ظ���
*/
extern size_t explode(char delimiter, char * string, char **& ptr);
/*
	ʱ���תʱ��
*/
extern char * timetstr(long time);
/*
	int ��תΪ�ַ���
*/
extern char *integerToString(int num);
/*
	�ַ���תlong
*/
extern long stringToLong(const char *text);
