#include "project.h"
#include "layout.h"


char *state = NULL;
inline void firstPageDrawText(char *text = "��ȴ�", int wait = 0, char *version = "loading...")
{
	consoleClear();
	//consoleColorSet("0f");
	consoleNewLine(2);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("Hafrans Flex Library Management System");
	consoledrawBorder(2, 3, ALIGN_CENTER);
	consoleDrawText(text, ALIGN_CENTER, ALIGN_CENTER);
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText("Copy Right (c) 2009-2016 Hafran Inc. All Rights Reserved.");
	consoleDrawText(version, ALIGN_CENTER, ALIGN_RIGHT);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	Sleep(wait);
}
int init()
{
	system("mode con cols=110 lines=30");
	firstPageDrawText("��ȴ�.", 500);
	firstPageDrawText("���ڼ���ϵͳ����ģ��", 200);
	if (iniReader())
	{
		firstPageDrawText("����ʧ�ܣ�����0x263e", 2000);
		consoleLog("can not load the ini file");
		return 1;
	}
	firstPageDrawText("���ڼ������ݿ�", 200, config->version);
	if (loadBOOK())
	{
		firstPageDrawText("ͼ�����ݿ����ʧ��", 200, config->version);
		return 1;
	}
	if (loadUSER())
	{
		firstPageDrawText("�û����ݿ����ʧ��", 200, config->version);
		return 1;
	}
	firstPageDrawText("�������", 200, config->version);
	consoleClear();
	return 0;

}

extern void loginPageViewer()
{
	page = 1;
	consoleClear();
	consoleColorSet("07");
	consoleNewLine(2);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("Hafrans Flex Library Management System");
	consoledrawBorder(2, 3, ALIGN_CENTER);
	consoleDrawText("�û���¼��ע��", ALIGN_CENTER, ALIGN_CENTER);
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText("*1):��¼");
	consoleDrawText("*2):ע��");
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("Copy Right (c) 2009-2016 Hafran Inc. All Rights Reserved.");
	consoleDrawText(config->version, ALIGN_CENTER, ALIGN_RIGHT);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	Sleep(100);
	//firstPage();

}


inline void loginStatusViewer(char *text, char *color = "")
{
	consoleClear();
	consoleColorSet(color);
	consoleNewLine(2);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("Hafrans Flex Library Management System");
	consoledrawBorder(2, 3, ALIGN_CENTER);
	consoleDrawText(text);
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText("������ת");
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText("Copy Right (c) 2009-2016 Hafran Inc. All Rights Reserved.");
	consoleDrawText(config->version, ALIGN_CENTER, ALIGN_RIGHT);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	Sleep(2500);
}
extern void loginStatus(enum LOGIN status)
{
	char *successColor = "20";
	char *failedColor = "40";

	switch (status)
	{
		case SUCCESS:
			loginStatusViewer("��¼�ɹ�", successColor);
			break;
		case FAILED:
			loginStatusViewer("�û��������벻��ȷ", failedColor);
			break;
		case LOCKED:
			loginStatusViewer("���û��ѱ�����", failedColor);
			break;
		default:
			loginStatusViewer("δ֪���� 0x664", failedColor);
			break;
	}
	consoleColorSet("07");//��ɫ
	consoleClear();
	if (status > SUCCESS)
	{
		loginPageViewer();
	}
}

void crashViewer(const char * text,const char *text2)
{
	char *str = strcat_t(" **STOP : ",text);
	char *log = strcat_t(str, text2);
	consoleLog(log);
	consoleClear();
	consoleTitleSet("Fatal Error !");
	consoleColorSet("17");
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoleDrawText("  A problem has been detected and LMS has been shut down to prevent");
	consoleDrawText(" damage to your computer.",ALIGN_CENTER,ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("  If this is the first time you've seen this stop error screen ,re-", ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(" restart your LMS.", ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("  If this screen appears again,follow these steps:", ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("  1)check to be sure you have adequate memory and disk space.", ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText("  2)check to be sure LMS sotware's file integrity .", ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText("  2)anti-virus software can cause this crash ,shut it down and ", ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText("  restart LMS.", ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText("  *Techical Information:", ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText(str,ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText(config->version, ALIGN_CENTER, ALIGN_RIGHT);
	consoledrawBorder(1, 1, ALIGN_CENTER);
}

int userRegister()
{
	consoleClear();
	
	char buf[__BUFFSIZE__] = { '\0' };
	if (strstr(config->administrator, "noreg") != NULL)
	{
		puts("ϵͳ����Ա��ֹ���û�ע��");
		return -1;
	}
	pUSER p = (pUSER)malloc(sizeof(USER));
	stringSave(p->passwd, "");
	stringSave(p->username, "test");
	p->permission = (short) 0;
	p->status = (short) 0;
	strcpy_s(p->book,__BUFFBOOK__,"0|");
	while (1)
	{
		consoleClear();
		stringSave(buf,"");
		while (1)
		{
			while (strlen(buf) < 4 || strlen(buf) > 10)
			{
				printf("�û������򣺳��ȴ���3С��10��Ӣ�Ļ�����\n");
				printf("�����������û��� ");
				while (gets_s(buf, __BUFFSIZE__) == NULL || buf[0] == '\0' || strcmp("",buf) == 0);
				int len = strlen(buf);
				while (--len)
				{
					if (isalnum(buf[len]) == 0)
					{
						break;
					}
				}
				if (len > 0)
				{
					stringSave(buf, "");
				}
				else
				{
					if (strcmp(buf, trim(config->administrator)) == 0)
					{
						printf("ϵͳ������ע����û�\n");
						stringSave(buf, "");
						continue;
					}
					stringSave(p->username, buf);
				}
			}
			break;
		}
		stringSave(buf, "");
		while (1)
		{
			char buf2[__BUFFSIZE__] = { '\0' };

			while (strlen(buf) < 4 || strlen(buf) >= 16)
			{
				printf("������򣺳��ȴ���3С��16��Ӣ�Ļ�����\n");
				printf("�������������� ");
				gets_s(buf, __BUFFSIZE__);
				int len = strlen(buf);
				while (--len)
				{
					if (isalnum(buf[len]) == 0)
					{
						break;
					}
				}
				if (len > 0)
				{
					stringSave(buf, "");
				}
				printf("���ٴ������������� ");
				while (gets_s(buf2, __BUFFSIZE__) == NULL || buf2[0] == '\0');
				if (strcmp(buf, buf2) != 0)
				{
					stringSave(buf, "");
					puts("������������벻�����");
				}
				else
				{
					stringSave(p->passwd, buf);
				}
			}
			break;
		}
		stringSave(buf,"");
		if (currentPer > 5)
		{
			while (!isdigit(*buf) || *buf > '8')
			{
				printf("��������û���Ȩ�� ");
				scanf_s("%c",&*buf,1);
			}
			p->permission = (int)(*buf - 48);
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			stringSave(buf, "");
			while (!isdigit(*buf) && *buf < '9')
			{
				printf("��������û���״̬ ");
				scanf_s("%c", &*buf,1);
			}
			p->status = (int)(*buf - 48);
			stringSave(buf, "");
			while ((c = getchar()) != '\n' && c != EOF);
		}
		consoleClear();
		sprintf_s(buf, __BUFFSIZE__, "�û����� %s     �ܡ��룺 %s", p->username, p->passwd);
		consoledrawBorder(1, 1, ALIGN_CENTER);
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText("���������Ϣ����");
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText(buf);
		if (currentPer > 5)
		{
			sprintf_s(buf,__BUFFSIZE__,"�û�Ȩ�ޣ� %d    �û�״̬�� %d", p->permission, p->status);
			consoleDrawText(buf);
		}
		consoledrawBorder(2, 2, ALIGN_CENTER);
		consoledrawBorder(1, 1, ALIGN_CENTER);
		printf("��ȷ�ϣ�(y/N)");
		while (!gets_s(buf, __BUFFSIZE__));
		if (strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0)
		{
			if (userAdd(p) == 1)
			{
				printf("�û����ظ���������ע�ᣡ\n");
				Sleep(1500);
				return 1;
			}
			puts("ע��ɹ�����");
			Sleep(1500);
			break;
		}
		else {
			continue;
		}
	}
	return 0;
}

int userLogin()
{

	consoleClear();
	while (1)
	{
		if (currentUsr != NULL)
		{
			printf("�����û�����¹�\n");
			return -1;
		}
		int c = 0;
		char buf[__BUFFSIZE__] = { '\0' };
		printf("�������û��� ");
		while (gets_s(buf, __BUFFSIZE__) == NULL || buf[0] == '\0' || strcmp("",buf) == 0);
		if (strcmp(buf, config->administrator) == 0 )
		{
			printf("���������� ");
			while (strcmp(gets_s(buf, __BUFFSIZE__), config->passwd) != 0 && c < 3)
			{
				printf("��������������������룺 ");
				c++;
			}
			if (c == 3)
			{
				puts("�������������࣬��¼ʧ�ܣ������ԣ�");
				Sleep(1500);
				loginStatus(FAILED);
				return 1;
			}
			else {
				currentUsr = config->administrator;
				currentPer = 9;
				loginStatus(SUCCESS);
				return 0;
			}
		}
		pUSER *p = userSelect(buf, 0, 1);
		if (!getAffected() || buf[0] == '\0' || strcmp("",buf) == 0 || strcmp(buf,(*p)->username) != 0)
		{
			puts("���û������ڣ�");
			continue;
		}
		printf("���������� ");
		while (strcmp(gets_s(buf, __BUFFSIZE__), (*p)->passwd) != 0 && c < 3)
		{
			printf("��������������������룺 ");
			c++;
		}
		if (c == 3)
		{
			puts("�������������࣬��¼ʧ�ܣ������ԣ�");
			Sleep(1500);
			loginStatus(FAILED);
			return 1;
		}
		else {
			if ((*p)->status == (short)1)
			{
				loginStatus(LOCKED);
				return -2;
			}
			currentUsr = (*p)->username;
			currentPer = (*p)->permission;
			currentBody = *p;
			loginStatus(SUCCESS);
			return 0;
		}
	}
	return 0;
}

void bookDetails(pBOOK p)
{
	time_t nowtime = p->addtime;//time(NULL); //ȡ�õ�ǰʱ���
	struct tm ptr;
	char timefstr[__BUFFSIZE__] = { '\0' };
	localtime_s(&ptr, &nowtime);
	if (&ptr == NULL)
	{
		return;
	}
	strftime(timefstr, sizeof(timefstr), "%F %T", &ptr);
	consoleClear();
	consoledrawBorder(1,1,ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("ͼ����Ϣ");
	consoleDrawText(strcat_t(" ͼ������ | ", p->name), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ISBN     | ", p->ISBN), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ��    �� | ", p->author), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" �� �� �� | ", p->publish), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" �洢��ַ | ", p->store), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" �������� | ", timefstr), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" �ݲ����� | ", integerToString(p->total)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ������� | ", integerToString(p->borrowed)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ʣ������ | ", integerToString(p->total - p->borrowed)), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
}

/*
	�@ʾ�Ñ���Ϣ
*/
void userDetails(pUSER p)
{
	consoleClear();
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("�û���Ϣ");
	consoleDrawText(strcat_t(" �û�ID  | ", integerToString((int)p->uid)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" �û���  | ", p->username), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ��  ��  | ", p->passwd), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" Ȩ  ��  | ", integerToString(p->permission)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ״  ̬  | ", integerToString(p->status)), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	return;
}

void mainLayoutViewer()
{
	consoleClear();
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("��������");
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("(1/info)�û���Ϣ     (2/cpwd)�޸�����");
	consoleDrawText("(3/fdbk)��ѯͼ��     (4/nrbk)�ѽ�ͼ��");
	consoleDrawText("(5/bobk)����ͼ��     (6/rtbk)�黹ͼ��");
	if (currentPer > 5)
	{
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText("������Ա���ܡ�");
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText("(7/dhbd)ϵͳ��Ϣ     (8/cusr)�޸��û�");
		consoleDrawText("(9/fdur)��ѯ�û�     (0/adur)�����û�");
		consoleDrawText("(a/adbk)���ͼ��     (b/cgbk)�޸�ͼ��");
	}
	consoleDrawText("(?/help)�����ѯ     (e/exit)�˳�ϵͳ");
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("�����������߿��������в���");
	//consoleDrawText("(c/dhbd)ϵͳ���     (d/cusr)�޸��û�");
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	
	return;
}

void bookAppend()
{
	consoleClear();
	char buf[__BUFFSIZE__] = {'\0'};
	while (1)
	{
		pBOOK p = (pBOOK)malloc(sizeof(BOOK));
		puts("/******************���ͼ��*******************/");
		printf("������ͼ��ISBN�� ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf,"") == 0 )
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->ISBN, delspace(buf));
		printf("������ͼ�������� ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->name, buf);
		printf("������ͼ�����ߣ� ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->author, buf);
		printf("������ͼ������磺 ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->publish,buf);
		printf("������ͼ����⣺ ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->store,buf);
		printf("������ͼ�������� ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		p->total = (short)stringToLong(buf);
		printf("������ͼ���ѽ������� ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		p->borrowed = (short)stringToLong(buf);
		p->addtime = (long)time(NULL);
		bookDetails(p);
		printf("��ȷ����Ӹ�ͼ�飿(y/N) ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		if (*buf == 'y' || *buf == 'Y')
		{
			int result = 0;
			if (result = bookAdd(p))
			{
				puts("���ʧ�ܣ�");
				if (result == 1)
				{
					puts("ʧ��ԭ��;ͼ����Ӻ���ISBN����");
				}
				else {
					puts("ʧ��ԭ��δ֪����");

				}
			}
			else {
				flushBOOK(0);
				puts("��ӳɹ���");
			}
			break;
		}
		else {
			continue;
		}
	}
	return;
}

void userPwdChange()
{
	char buf[__BUFFSIZE__] = { '\0' };
	char buf2[__BUFFSIZE__] = { '\0' };
	printf("�����뵱ǰ���룺 ");
	while (gets_s(buf, __BUFFSIZE__) == NULL || buf[0] == '\0');
	if (strcmp(buf, currentBody->passwd) != 0)
	{
		puts("�������������ԣ�");
		return; 
	}

	stringSave(buf, "");
	while (1)
	{
		

		while (strlen(buf) < 4 || strlen(buf) >= 16)
		{
			printf("������򣺳��ȴ���3С��16��Ӣ�Ļ�����\n");
			printf("���������������� ");
			gets_s(buf, __BUFFSIZE__);
			int len = strlen(buf);
			while (--len)
			{
				if (isalnum(buf[len]) == 0)
				{
					break;
				}
			}
			if (len > 0)
			{
				stringSave(buf, "");
			}
			printf("���ٴ��������������� ");
			while (gets_s(buf2, __BUFFSIZE__) == NULL || buf2[0] == '\0');
			if (strcmp(buf, buf2) != 0)
			{
				stringSave(buf, "");
				puts("������������벻�����");
			}
			else
			{
				stringSave(currentBody->passwd, buf);
				puts("�����޸ĳɹ������γɹ��رպ��´ε�¼ʱ��ʹ��������");
			}
		}
		break;

	}
	return;
}

void systemInfoViewer()
{
	time_t nowtime = time(NULL); //ȡ�õ�ǰʱ���
	struct tm ptr;
	char timefstr[__BUFFSIZE__] = { '\0' };
	localtime_s(&ptr, &nowtime);
	if (&ptr == NULL)
	{
		return;
	}
	strftime(timefstr, sizeof(timefstr), "%F %T", &ptr);
	consoleClear();
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("ϵͳ��Ϣ");
	consoleDrawText(strcat_t(" ϵͳ��Ϣ | ", "Flex Project LMS ConsoleVer."), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ϵͳ�汾 | ", config->version), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ��    �� | ", "Hafrans Newton"), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ��ʼ�˻� | ", config->administrator), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText(strcat_t(" ϵͳʱ�� | ", timefstr), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ͼ������ | ", config->libPath), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" �û����� | ", config->userPath), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	return;
}

void showBookLists(pBOOK *p)
{
	int i;
	char buf[__BUFFSIZE__] = { '\0' };
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	puts("+     ISBN      +            ͼ������            +  ���ʱ��  +       �洢���       + ʣ��  +");
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	if (p == NULL)
	{
		pBOOK temp = head;
		while (temp != NULL)
		{
			time_t nowtime = temp->addtime; //ȡ�õ�ǰʱ���
			struct tm ptr;
			char timefstr[__BUFFSIZE__] = { '\0' };
			localtime_s(&ptr, &nowtime);
			if (&ptr == NULL)
			{
				return;
			}
			strftime(timefstr, sizeof(timefstr), "%F", &ptr);
			sprintf_s(buf,__BUFFSIZE__,"+ %13s + %30s + %10s + %20s + %5hd +",temp->ISBN,temp->name,timefstr,temp->store,(temp->total-temp->borrowed));
			puts(buf);
			temp = temp->next;
		}
	}
	else {
		for (i = 0; i < getAffected(); i++)
		{
			pBOOK temp = p[i];
			time_t nowtime = temp->addtime; //ȡ�õ�ǰʱ���
			struct tm ptr;
			char timefstr[__BUFFSIZE__] = { '\0' };
			localtime_s(&ptr, &nowtime);
			if (&ptr == NULL)
			{
				return;
			}
			strftime(timefstr, sizeof(timefstr), "%F", &ptr);
			sprintf_s(buf, __BUFFSIZE__, "+ %13s + %30s + %10s + %20s + %5hd +", temp->ISBN, temp->name, timefstr, temp->store, (temp->total - temp->borrowed));
			puts(buf);
		}
	}
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	return;
}
void selectBooksViewer()
{
	char buf[__BUFFSIZE__] = { '\0' };
	pBOOK *p = NULL;
	int orderby = 0;
	puts("++++++++++++++++++++");
	puts("+    0 - ISBN      +");
	puts("+    1 - ͼ������  +");
	puts("+    2 - �洢���  +");
	puts("++++++++++++++++++++");
	printf("�밴���������ʾ�������µĲ��ҷ���������Ĭ��ΪISBN�� ");
	while ((state = gets_s(buf, __BUFFSIZE__)) == NULL)
	{
		if (state == NULL)
		{
			puts("\n\n[ +1 ]      Stopped    fdbk"); return;
		}
	}
	if (strcmp(buf, "") != 0)
	{
		if (*buf >= '0' && *buf <= '2')
		{
			orderby = (*buf) - 48;
		}
	}
	printf("��������Ҫ���ҵ��ֶΣ�����Ĭ��Ϊȫ����ʾ�� ");
	while ((state = gets_s(buf, __BUFFSIZE__)) == NULL)
	{
		if (state == NULL)
		{
			return;
		}
	}
	if (strcmp(buf, "") != 0)
	{
		p = bookSelect(buf,orderby,1024);
		showBookLists(p);
	}
	else {
		showBookLists(NULL);
	}
	return;
}

void showUserLists(pUSER *p)
{
	int i;
	char buf[__BUFFSIZE__] = { '\0' };
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	puts("+     UID       +            �û�����            +  �û�Ȩ��  + �û�״̬ +");
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	if (p == NULL)
	{
		pUSER temp = uhead;
		while (temp != NULL)
		{
			sprintf_s(buf, __BUFFSIZE__, "+ %13ld + %30s + %10hd + %8hd +", temp->uid, temp->username, temp->permission, temp->status);
			puts(buf);
			temp = temp->next;
		}
	}
	else {
		for (i = 0; i < getAffected(); i++)
		{
			pUSER temp = p[i];
			sprintf_s(buf, __BUFFSIZE__, "+ %13ld + %30s + %10hd + %8hd +", temp->uid, temp->username, temp->permission, temp->status);
			puts(buf);
		}
	}
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	return;
}

void userSelectViewer()
{
	char buf[__BUFFSIZE__] = { '\0' };
	int orderby = 0;
	puts("+++++++++++++++++++++++");
	puts("+    0|�����û���     +");
	puts("+    1|����UID        +");
	puts("+    2|����״̬       +");
	puts("+    3|����Ȩ��       +");
	puts("+++++++++++++++++++++++");
	printf("��������ҷ�ʽ��Ĭ��Ϊ�û����� ");
	while ((state = gets_s(buf, __BUFFSIZE__)) == NULL)
	{
		if (state == NULL)
		{
			puts("\n\n[ +1 ]      Stopped    fdur"); return;
		}
	}
	if (strcmp(buf, "") != 0)
	{
		if (*buf >= '0' && *buf <= '3')
		{
			orderby = (*buf) - 48;
		}
	}
	printf("��������Ҫ���ҵ����ݣ�Ĭ����ȫ���� ");
	while ((state = gets_s(buf, __BUFFSIZE__)) == NULL)
	{
		if (state == NULL)
		{
			puts("\n\n[ +1 ]      Stopped    fdur"); return;
		}
	}
	if (strcmp(buf, "") != 0)
	{
		pUSER *p = userSelect(buf,orderby,1024);
		showUserLists(p);
	}
	else {
		showUserLists(NULL);
	}
	puts("����������ָ����п�ݲ���..");
	return;
}

void changeUserViewer() 
{
	char buf[__BUFFSIZE__] = {'\0'};
	pUSER *p = NULL;
	puts("*******ע�⣺���μ��û���uid�ٽ��в�����������ɲ���Ҫ���鷳*******");
	puts("");
	while (1)
	{
		printf("�������û���uid�� ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL  || *buf == '\0')
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    cusr"); return;
			}
		}
		p = userSelect(buf, 1, 1);
		userDetails(*p);
		printf("ȷ��������û�ô�� (y/N) ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || *buf == '\0')
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    cusr"); return;
			}
		}
		if (*buf == 'y' || *buf == 'Y')
		{
			break;
		}
		else {
			continue;
		}
	}
	printf("�������û����룬�س�Ĭ�ϲ��޸ģ� ");
	while (gets_s(buf, __BUFFSIZE__) == NULL );
	if (strcmp(buf, "") != 0)
	{
		stringSave((*p)->passwd,buf);
	}
	printf("�������û�Ȩ�ޣ��س�Ĭ�ϲ��޸ģ� ");
	while (gets_s(buf, __BUFFSIZE__) == NULL);
	if (strcmp(buf, "") != 0)
	{
		(*p)->permission = (short)stringToLong(buf);
	}
	printf("�������û�״̬���س�Ĭ�ϲ��޸ģ� ");
	while (gets_s(buf, __BUFFSIZE__) == NULL);
	if (strcmp(buf, "") != 0)
	{
		(*p)->status = (short)stringToLong(buf);
	}
	puts("�޸ĳɹ���");
	return;
}

