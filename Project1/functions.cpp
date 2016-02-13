#include "project.h"
#include "functions.h"

/**
*��ȡϵͳ��λ��
*@return size_t ϵͳλ��
*@author Hafrans Newton
*/
extern size_t getOSBit()
{
	return sizeof(char *) * 8;
}

/**
*��ʱ���ת��Ϊ�ַ�����ʽ
*@param time_t timeʱ��
*@return char* ʱ����ַ���
*@author Hafrans Newton
*/
extern char *timestampToString(time_t timeb)
{
	char str[4096] = { '\0' };
	int i = 0;
	do {
		str[i++] = timeb % 10 + 48;
	} while ((timeb /= 10));
	str[i + 1] = '\0';
	return _strrev(str);
}
/*
	int����ת��Ϊ�ַ���
*/
extern char *integerToString(int num)
{
	char *str = (char *)calloc(12, sizeof(char));
	if (str == NULL)
	{
		consoleLog("��ת��Ϊ�ַ���ʱ�������޷������ڴ������");
		return NULL;
	}
	int flag = 0;
	int count = 0;
	if (num < 0)
	{
		num *= -1;
		flag = 1;
	}
	do {
		str[count++] = num % 10 + 48;
		num /= 10;
	} while (num != 0);
	if (flag)
	{
		str[count++] = '-';
	}
	str[count] = '\0';
	return _strrev(str);
}
/*
	�ַ���ת��long
*/
extern long stringToLong(const char *text)
{
	//assert(text);
	long num = 0;
	int len = (int)strlen(text);
	int i;
	for (i = len-1; i >= 0; i--)
	{
		if (text[i] == '-')
		{
			num *= -1;
			break;
		}
		if (text[i] >= '0'&&text[i] <= '9')
		{
			num += (int)(text[i] - 48)*(int)pow(10, len - 1 - i);
		}
	}
	
	return num;
}
/**
*�������ַ�������
*@param const char* TextA �ַ���A
*@param const char* TextB �ַ���B
*@return char* ������ɵ��ַ���
*@author Hafrans Newton
*/
extern char *strcat_t(const char *textA, const char *textB)
{
	size_t len = strlen(textA);
	len += strlen(textB);
	char *str = (char *)calloc(len + 2, sizeof(char));
	if (str != NULL)
	{
		strcat_s(str, len + 2, textA);
		strcat_s(str, len + 2, textB);
	}
	
	return str;
}
/**
*ȥ���ַ������˿հ�
*@param char* Text �ַ���
*@return char* ������ɵ��ַ���
*@author Hafrans Newton
*/
extern char *trim(char *text)
{
	size_t len = strlen(text);
	char *p = text + len - 1;
	while (text && isspace(*text))
	{
		text++;//ָ������ƶ�
	}
	while (p > text && isspace(*p))
	{
		*(p--) = '\0';//��Ϊ��
	}
	return text;
}

/**
* �ַ�������
*@param char* TextA Ŀ��Դ
*@param char* TextB ����Դ
*@author Hafrans Newton
*/
extern void stringSave(char *TextA, const char *TextB)
{
	char *str = parseSpaceString(TextB);
	#ifdef DEBUG
	#endif 
	strcpy_s(TextA,__BUFFSIZE__,str);
	return;
}

void exitLMS()
{
	/*
		1.�������е�������Ϣд���ļ�
		2.ini����
	*/
}
/*
	ȥ���ַ����еĿո�
*/
char * delspace(const char * text)
{
	size_t offset=0,i=0,len = strlen(text);
	char *newstr = (char *)calloc(len + 1, sizeof(char));
	if (newstr == NULL)
	{
		consoleLog("������ո�ʱ�������޷������ڴ������");
		return NULL;
	}
	for (i = 0; i < len; i++)
	{
		if (text[i]>=0 && text[i]<=32)
		{
			continue;
		}
		newstr[offset++] = text[i];
	}
	newstr[offset] = '\0';
	
	return newstr;
}
/*
	��־��¼
*/
void consoleLog(const char * text)
{
	if (text == NULL)
	{
		return;
	}
	time_t nowtime = time(NULL); //ȡ�õ�ǰʱ���
	struct tm ptr;
	char timefstr[__BUFFSIZE__] = { '\0' };
	localtime_s(&ptr,&nowtime);
	if (&ptr == NULL)
	{
		return;
	}
	strftime(timefstr, sizeof(timefstr)," echo [ %F %T ]",&ptr);
	char *textStepA = strcat_t(timefstr,text);
	char *cmdMixed = strcat_t(textStepA,"�� >> log.log");
	system(cmdMixed);
	return;
}

const char * testCharNULLPTRToEmptyString(const char * text)
{
	if (text == NULL)
	{
		return __EMPTY_OR_NULL_ALTERNATIVE_STRING__;
	}
	return text;
}



char * parseSpaceString(const char * text)
{
	if (text == NULL)
	{
		crashViewer("0x10000002", "��������ʱ��⵽��ָ�����");
		return "";
	}
	char *space = __SPACE__FILE_READ__;
	size_t i = 0, len = strlen(text),offset = 0;
	char *str = (char *) calloc(__BUFFSIZE__*strlen(__SPACE__FILE_READ__)+1,sizeof(char));
	if (str == NULL)
	{
		consoleLog("��ת���ո�ʱ�������޷������ڴ������");
		return NULL;
	}
	for (i = 0; i < len; i++)
	{
		if (text[i] <= 32 && text[i] >= 0 )
		{
			size_t ts = strlen(__SPACE__FILE_READ__),p=0;
			while (p<ts)
			{
				str[offset++] = space[p++];
			}
		}
		else
		{
			str[offset++] = text[i];
		}
	}
	return str;
}

char * parseStringSpace(const char * text)
{
	if (text == NULL)
	{
		crashViewer("0x10000002", "��������ʱ��⵽��ָ�����");
		return NULL;
	}
	char *space = __SPACE__FILE_READ__;
	char *str = (char *)calloc(__BUFFSIZE__, sizeof(char));
	if (str == NULL)
	{
		consoleLog("�ڿո�ת��ʱ�������޷������ڴ������");
		return NULL;
	}
	size_t i = 0;//textѭ��
	size_t j = 0;//strѭ��
	size_t lens = strlen(space), len = strlen(text);
	for (i = 0; i < len; i++)
	{
		size_t offset = 0, ioffset = i, joffset = j;
		while (text[ioffset++] == space[offset++] && offset<lens)
		{
			if (offset == lens - 1)
			{
				str[j++] = ' ';
				i += lens-1;
			}
		}
		if (offset != lens)
		{
			str[j++] = text[i];
		}
	}
	str[i] = '\0';
	return str;
}
/*
	�ַ����ָ������
	����ȴ���һ��ָ���ַ������ָ��
	Sample : 
	char *str = (char *)calloc(200, sizeof(char));
	strcpy_s(str,200,"sdf,d,df,dsf4565355555,11111111,1");
	char ** t = NULL;
	size_t p = explode(',',str, t);
	for (int i = 0; i < 5; i++)
	{
		char *strp = t[i];
		puts(strp);
	}
*/
size_t explode(char delimiter, char *string, char ** &ptr)
{
	size_t i = 0,t=0,len = strlen(string);
	ptr = (char **)malloc(1024*sizeof(char *));
	if (ptr == NULL)
	{
		crashViewer("0x00000012 (0x00000010 0x0000002)","�ڴ������쳣��EXPLODESTR");
	}
	ptr[i++] = string;
	while (t < len)
	{
		if (string[t] == delimiter)
		{
			string[t] = '\0';
			//ptr = (char **)realloc(ptr,sizeof(char *) + sizeof(ptr));
			ptr[i++] = string + ++t;
		}
		else {
			t++;
		}
	}
	///ptr = &arr;
	return i;
}