/*
*
*Name : Hafrans Flex Project Library Management System Main
*
*/

#include "project.h"
extern pBOOK head = NULL;
extern pUSER uhead = NULL;
extern pUSER currentBody = NULL;
extern char *currentUsr = NULL;
extern int   currentPer = -1;
extern long maxUID = 1;
extern CONFIG config = (CONFIG)malloc(sizeof(struct configuration));
extern int page = 0;

int main()
{
	consoleTitleSet("Hafrans Flex LMS Alpha");
	if (init())
	{
		printf("程序出现错误，正在退出...");
		Sleep(1500);
		return -255;
	}

#ifdef DEBUG
	currentPer = 9;
	currentUsr = "root";
	puts("/********************这是调试模式****************/");
#else
	while (currentUsr == NULL)
	{
		while (currentUsr == NULL)
		{
			char buf[__BUFFSIZE__] = { '\0' };
			loginPageViewer();
			printf("请输入选项： ");
			gets_s(buf, __BUFFSIZE__);
			if (strcmp(buf, "1") == 0)
			{
				userLogin();
			}
			else if (strcmp(buf, "2") == 0)
			{
				userRegister();
				flushUSER(0);
			}
			else if (strcmp(buf, "3") == 0)
			{
				printf("将要退出程序。。\n");
				Sleep(1500);
				puts("正在退出...");
				Sleep(1500);
				flushBOOK(0);
				flushUSER(0);
				return 0;

			}
		}
		mainLayoutViewer();
		consoleWaitinCMD();
	}
#endif
	/*bookDetails(head);
	Sleep(1520);
	userDetails(uhead);
	puts("已到达函数底");
	getchar();*/

#ifdef DEBUG
	/*
		程序设置文档请写在此处。
	*/
	pUSER *p = userSelect("2",1,1);
	currentBody = *p;
	puts("已到达程序底部");
	getchar();
#endif
	/*冲刷数据*/
	flushBOOK(0);
	flushUSER(0);
	//Sleep(1000);
	return 0;

}