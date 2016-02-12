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
		printf("������ִ��������˳�...");
		Sleep(1500);
		return -255;
	}

#ifdef DEBUG
	currentPer = 9;
	currentUsr = "root";
	puts("/********************���ǵ���ģʽ****************/");
#else
	while (currentUsr == NULL)
	{
		char buf[__BUFFSIZE__] = { '\0' };
		loginPageViewer();
		printf("������ѡ� ");
		gets_s(buf,__BUFFSIZE__);
		if (strcmp(buf, "1") == 0)
		{
			userLogin();
		}
		else if (strcmp(buf, "2") == 0)
		{
			userRegister();
			flushUSER(0);
		}
	}
	mainLayoutViewer();
	consoleWaitinCMD();
#endif
	/*bookDetails(head);
	Sleep(1520);
	userDetails(uhead);
	puts("�ѵ��ﺯ����");
	getchar();*/

#ifdef DEBUG
	/*
		���������ĵ���д�ڴ˴���
	*/
	pUSER *p = userSelect("2",1,1);
	currentBody = *p;
	//selectBooksViewer();
	//bookBorrow("9787123433242",BDAY);
	int pt = 0;
	pt = bookReturn("9784323242");
	printf("%d",pt);


	






	puts("�ѵ������ײ�");
	getchar();
#endif
	/*��ˢ����*/
	flushBOOK(0);
	flushUSER(0);
	//Sleep(1000);
	return 0;

}