#include "project.h"


/**
*设置控制台颜色
*@param const char* color 颜色
*详情请在‘命令提示符’下键入 “color ?”查看使用说明
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
	设定窗口标题
	@param const char title 标题名称
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
*在控制台输出边框
*@param int type 边框种类
*@param int count = 1 重复输出次数
*@param int align = ALIGN_LEFT 对齐方式
*详情请在‘命令提示符’下键入 “color ?”查看使用说明
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
*刷新控制台
*
*@author Hafrans Newton
*/
extern void consoleClear()
{
	system("cls");
	return;
}
/**
*在控制台输出与边框相符的文字，长度不要大于68
*@param int type 边框种类
*@param int count = 1 重复输出次数
*@param int align = ALIGN_LEFT 对齐方式
*@param int talign = ALIGN_LEFT 文字对齐方式
*
*@author Hafrans Newton
*/ 
extern void consoleDrawText(char *text, int align,int talign, int type)
{
	size_t len = strlen(text);
	if (len > 68)
	{
		return;//如果过长就自动退出函数
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
*去除字符串两端空白
*@param int count 换行行数
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
				puts("最高权限账户不适合本功能哦");
			}
			else {
				userDetails(currentBody);
			}
		}
		else if (strcmp(cmd, "cpwd") == 0 || *cmd == '2')
		{
			if (currentPer == 9)
			{
				puts("最高权限账户不适合本功能哦，请在配置文件下进行更改");
			}
			else {
				userPwdChange();
			}
		}
		else if (strcmp(cmd, "help") == 0 || *cmd == '?' || strcmp(cmd, "？") == 0)
		{
			mainLayoutViewer();
		}
		else if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "E") == 0 || strcmp(cmd, "e") == 0)
		{
			printf("将要退出程序，请回车继续。。");
			Sleep(1500);
			puts("正在退出...");
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