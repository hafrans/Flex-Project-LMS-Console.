#include "project.h"


/**
*���ÿ���̨��ɫ
*@param const char* color ��ɫ
*�������ڡ�������ʾ�����¼��� ��color ?���鿴ʹ��˵��
*@author Hafrans Newton
*/
extern void consoleColorSet(const char *color)
{
	char *str = "color ";
	char *cmd = strcat_t(str, color);
	system(cmd);
	return;
}
/*
	�趨���ڱ���
	@param const char title ��������
	@return void
*/
void consoleTitleSet(const char * title)
{
	char *cmd = "title ";
	char *mycmd = strcat_t(cmd, title);
	system(mycmd);
	return;
}

/**
*�ڿ���̨����߿�
*@param int type �߿�����
*@param int count = 1 �ظ��������
*@param int align = ALIGN_LEFT ���뷽ʽ
*�������ڡ�������ʾ�����¼��� ��color ?���鿴ʹ��˵��
*@author Hafrans Newton
*/
extern void consoledrawBorder(int type, int count = 1, int align = ALIGN_CENTER)
{
	while (count--)
	{
		int ali = align;
		while (ali--)
		{
			printf(" ");
		}
		switch (type)
		{
		case 1:
			printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			break;
		case 2:
			printf("+                                                                    +\n");
			break;
		case 3:
			printf("/********************************************************************/\n");
			break;
		case 4:
			printf("*                                                                    *\n");
			break;
		default:
			break;
		}
	}
	return;
}
/**
*ˢ�¿���̨
*
*@author Hafrans Newton
*/
extern void consoleClear()
{
	system("cls");
	return;
}
/**
*�ڿ���̨�����߿���������֣����Ȳ�Ҫ����68
*@param int type �߿�����
*@param int count = 1 �ظ��������
*@param int align = ALIGN_LEFT ���뷽ʽ
*@param int talign = ALIGN_LEFT ���ֶ��뷽ʽ
*
*@author Hafrans Newton
*/ 
extern void consoleDrawText(char *text, int align,int talign, int type)
{
	size_t len = strlen(text);
	if (len > 68)
	{
		return;//����������Զ��˳�����
	}
	int ali = align;
	char *str = NULL;
	if (len % 2)
	{
		str = strcat_t(text, " ");
		len++;
	}
	else
	{
		str = text;
	}
	char *head = NULL;
	if (type == 1)
	{
		head = "+";
	}
	else {
		head = "*";
	}
	while (ali--)
	{
		printf(" ");
	}
	printf("%s", head);
	size_t count, pcount;
	switch (talign)
	{
		case ALIGN_LEFT:
			count = 70 - 2 - len;
			printf("%s", str);
			while (count--)
			{
				printf(" ");
			}
			break;
		case ALIGN_RIGHT:
			count = 70 - 2 - len;
			while (count--)
			{
				printf(" ");
			}
			printf("%s", str);
			break;
		case ALIGN_CENTER:
			count = (70 - 2 - len) / 2;
			pcount = count;
			while (pcount--)
			{
				printf(" ");
			}
			printf("%s", str);
			while (count--)
			{
				printf(" ");
			}
			break;
		default:
			break;
	}
	printf("%s\n", head);
	return;
}

/**
*ȥ���ַ������˿հ�
*@param int count ��������
*@author Hafrans Newton
*/
extern void consoleNewLine(int count = 1)
{
	while (count--)
	{
		printf("\n");
	}
}

void consoleWaitinCMD()
{
	char cmd[__BUFFSIZE__] = {'\0'};
	char cmdc = '$';
	if (currentPer == 9)
	{
		cmdc = '#';
	}
	while (1)
	{
		printf("[%s@LMS]%c", currentUsr, cmdc);
		if (!gets_s(cmd, __BUFFSIZE__) || *cmd == '\0')
		{
			continue;
		}
		if (strcmp(cmd,"adbk") == 0 || strcmp(cmd, "a") == 0 || strcmp(cmd, "A") == 0)
		{
			bookAppend();
		}
		else if (strcmp(cmd, "info") == 0 || *cmd == '1')
		{
			if (currentPer == 9)
			{
				puts("���Ȩ���˻����ʺϱ�����Ŷ");
			}
			else {
				userDetails(currentBody);
			}
		}
		else if (strcmp(cmd, "cpwd") == 0 || *cmd == '2')
		{
			if (currentPer == 9)
			{
				puts("���Ȩ���˻����ʺϱ�����Ŷ�����������ļ��½��и���");
			}
			else {
				userPwdChange();
			}
		}
		else if (strcmp(cmd, "help") == 0 || *cmd == '?' || strcmp(cmd, "��") == 0)
		{
			mainLayoutViewer();
		}
		else if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "E") == 0 || strcmp(cmd, "e") == 0)
		{
			printf("��Ҫ�˳�������س���������");
			Sleep(1500);
			puts("�����˳�...");
			Sleep(1500);
			return;
		}
		else if (strcmp(cmd, "adur") == 0 || *cmd == '0' && currentPer > 5)
		{
			userRegister();
		}
		else if (strcmp(cmd, "fdbk") == 0 || *cmd == '3')
		{
			selectBooksViewer();
		}
		else if (strcmp(cmd, "dhbd") == 0 || *cmd == '7' && currentPer > 5)
		{
			systemInfoViewer();
		}
		else if (strcmp(cmd, "fdur") == 0 || *cmd == '9' && currentPer > 5)
		{
			userSelectViewer();
		}
		else {
			printf("-fshell: %s : command not found.\n",cmd);
		}
	}
}


/*********************************************/
//For User
/*********************************************/