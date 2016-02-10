#include "project.h"
#include "layout.h"


char *state = NULL;
inline void firstPageDrawText(char *text = "请等待", int wait = 0, char *version = "loading...")
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
	firstPageDrawText("请等待.", 500);
	firstPageDrawText("正在加载系统核心模块", 200);
	if (iniReader())
	{
		firstPageDrawText("加载失败！错误0x263e", 2000);
		consoleLog("can not load the ini file");
		return 1;
	}
	firstPageDrawText("正在加载数据库", 200, config->version);
	if (loadBOOK())
	{
		firstPageDrawText("图书数据库加载失败", 200, config->version);
		return 1;
	}
	if (loadUSER())
	{
		firstPageDrawText("用户数据库加载失败", 200, config->version);
		return 1;
	}
	firstPageDrawText("加载完毕", 200, config->version);
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
	consoleDrawText("用户登录与注册", ALIGN_CENTER, ALIGN_CENTER);
	consoledrawBorder(2, 2, ALIGN_CENTER);
	consoleDrawText("*1):登录");
	consoleDrawText("*2):注册");
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
	consoleDrawText("正在跳转");
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
			loginStatusViewer("登录成功", successColor);
			break;
		case FAILED:
			loginStatusViewer("用户名或密码不正确", failedColor);
			break;
		case LOCKED:
			loginStatusViewer("该用户已被锁定", failedColor);
			break;
		default:
			loginStatusViewer("未知错误 0x664", failedColor);
			break;
	}
	consoleColorSet("07");//换色
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
		puts("系统管理员禁止了用户注册");
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
				printf("用户名规则：长度大于3小于10的英文或数字\n");
				printf("请输入您的用户名 ");
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
						printf("系统不允许注册该用户\n");
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
				printf("密码规则：长度大于3小于16的英文或数字\n");
				printf("请输入您的密码 ");
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
				printf("请再次输入您的密码 ");
				while (gets_s(buf2, __BUFFSIZE__) == NULL || buf2[0] == '\0');
				if (strcmp(buf, buf2) != 0)
				{
					stringSave(buf, "");
					puts("两次输入的密码不相符！");
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
				printf("请输入该用户的权限 ");
				scanf_s("%c",&*buf,1);
			}
			p->permission = (int)(*buf - 48);
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			stringSave(buf, "");
			while (!isdigit(*buf) && *buf < '9')
			{
				printf("请输入该用户的状态 ");
				scanf_s("%c", &*buf,1);
			}
			p->status = (int)(*buf - 48);
			stringSave(buf, "");
			while ((c = getchar()) != '\n' && c != EOF);
		}
		consoleClear();
		sprintf_s(buf, __BUFFSIZE__, "用户名： %s     密　码： %s", p->username, p->passwd);
		consoledrawBorder(1, 1, ALIGN_CENTER);
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText("您输入的信息如下");
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText(buf);
		if (currentPer > 5)
		{
			sprintf_s(buf,__BUFFSIZE__,"用户权限： %d    用户状态： %d", p->permission, p->status);
			consoleDrawText(buf);
		}
		consoledrawBorder(2, 2, ALIGN_CENTER);
		consoledrawBorder(1, 1, ALIGN_CENTER);
		printf("您确认？(y/N)");
		while (!gets_s(buf, __BUFFSIZE__));
		if (strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0)
		{
			if (userAdd(p) == 1)
			{
				printf("用户名重复！请重新注册！\n");
				Sleep(1500);
				return 1;
			}
			puts("注册成功啦！");
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
			printf("你好像没事找事哈\n");
			return -1;
		}
		int c = 0;
		char buf[__BUFFSIZE__] = { '\0' };
		printf("请输入用户名 ");
		while (gets_s(buf, __BUFFSIZE__) == NULL || buf[0] == '\0' || strcmp("",buf) == 0);
		if (strcmp(buf, config->administrator) == 0 )
		{
			printf("请输入密码 ");
			while (strcmp(gets_s(buf, __BUFFSIZE__), config->passwd) != 0 && c < 3)
			{
				printf("密码错误，请重新输入密码： ");
				c++;
			}
			if (c == 3)
			{
				puts("输入错误次数过多，登录失败，请重试！");
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
			puts("该用户不存在！");
			continue;
		}
		printf("请输入密码 ");
		while (strcmp(gets_s(buf, __BUFFSIZE__), (*p)->passwd) != 0 && c < 3)
		{
			printf("密码错误，请重新输入密码： ");
			c++;
		}
		if (c == 3)
		{
			puts("输入错误次数过多，登录失败，请重试！");
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
	time_t nowtime = p->addtime;//time(NULL); //取得当前时间戳
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
	consoleDrawText("图书信息");
	consoleDrawText(strcat_t(" 图书名称 | ", p->name), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" ISBN     | ", p->ISBN), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 作    者 | ", p->author), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 出 版 社 | ", p->publish), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 存储地址 | ", p->store), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 加入日期 | ", timefstr), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 馆藏数量 | ", integerToString(p->total)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 借出数量 | ", integerToString(p->borrowed)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 剩余数量 | ", integerToString(p->total - p->borrowed)), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
}

/*
	顯示用戶信息
*/
void userDetails(pUSER p)
{
	consoleClear();
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("用户信息");
	consoleDrawText(strcat_t(" 用户ID  | ", integerToString((int)p->uid)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 用户名  | ", p->username), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 密  码  | ", p->passwd), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 权  限  | ", integerToString(p->permission)), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 状  态  | ", integerToString(p->status)), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	return;
}

void mainLayoutViewer()
{
	consoleClear();
	consoledrawBorder(1, 1, ALIGN_CENTER);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("【帮助】");
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("(1/info)用户信息     (2/cpwd)修改密码");
	consoleDrawText("(3/fdbk)查询图书     (4/nrbk)已借图书");
	consoleDrawText("(5/bobk)借阅图书     (6/rtbk)归还图书");
	if (currentPer > 5)
	{
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText("【管理员功能】");
		consoledrawBorder(2, 1, ALIGN_CENTER);
		consoleDrawText("(7/dhbd)系统信息     (8/cusr)修改用户");
		consoleDrawText("(9/fdur)查询用户     (0/adur)增加用户");
		consoleDrawText("(a/adbk)添加图书     (b/cgbk)修改图书");
	}
	consoleDrawText("(?/help)命令查询     (e/exit)退出系统");
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText("请输入代码或者快捷命令进行操作");
	//consoleDrawText("(c/dhbd)系统情况     (d/cusr)修改用户");
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
		puts("/******************添加图书*******************/");
		printf("请输入图书ISBN： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf,"") == 0 )
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->ISBN, delspace(buf));
		printf("请输入图书书名： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->name, buf);
		printf("请输入图书作者： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->author, buf);
		printf("请输入图书出版社： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->publish,buf);
		printf("请输入图书书库： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		stringSave(p->store,buf);
		printf("请输入图书总量： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL || strcmp(buf, "") == 0)
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    adbk"); return;
			}
		}
		p->total = (short)stringToLong(buf);
		printf("请输入图书已借数量： ");
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
		printf("您确认添加该图书？(y/N) ");
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
				puts("添加失败！");
				if (result == 1)
				{
					puts("失败原因;图书添加后惊现ISBN重名");
				}
				else {
					puts("失败原因：未知错误！");

				}
			}
			else {
				flushBOOK(0);
				puts("添加成功！");
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
	printf("请输入当前密码： ");
	while (gets_s(buf, __BUFFSIZE__) == NULL || buf[0] == '\0');
	if (strcmp(buf, currentBody->passwd) != 0)
	{
		puts("密码有误，请重试！");
		return; 
	}

	stringSave(buf, "");
	while (1)
	{
		

		while (strlen(buf) < 4 || strlen(buf) >= 16)
		{
			printf("密码规则：长度大于3小于16的英文或数字\n");
			printf("请输入您的新密码 ");
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
			printf("请再次输入您的新密码 ");
			while (gets_s(buf2, __BUFFSIZE__) == NULL || buf2[0] == '\0');
			if (strcmp(buf, buf2) != 0)
			{
				stringSave(buf, "");
				puts("两次输入的密码不相符！");
			}
			else
			{
				stringSave(currentBody->passwd, buf);
				puts("密码修改成功，本次成功关闭后，下次登录时请使用新密码");
			}
		}
		break;

	}
	return;
}

void systemInfoViewer()
{
	time_t nowtime = time(NULL); //取得当前时间戳
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
	consoleDrawText("系统信息");
	consoleDrawText(strcat_t(" 系统信息 | ", "Flex Project LMS ConsoleVer."), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 系统版本 | ", config->version), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 作    者 | ", "Hafrans Newton"), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 创始账户 | ", config->administrator), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoleDrawText(strcat_t(" 系统时间 | ", timefstr), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 图书数据 | ", config->libPath), ALIGN_CENTER, ALIGN_LEFT);
	consoleDrawText(strcat_t(" 用户数据 | ", config->userPath), ALIGN_CENTER, ALIGN_LEFT);
	consoledrawBorder(2, 1, ALIGN_CENTER);
	consoledrawBorder(1, 1, ALIGN_CENTER);
	return;
}

void showBookLists(pBOOK *p)
{
	int i;
	char buf[__BUFFSIZE__] = { '\0' };
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	puts("+     ISBN      +            图书名称            +  入库时间  +       存储书库       + 剩余  +");
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	if (p == NULL)
	{
		pBOOK temp = head;
		while (temp != NULL)
		{
			time_t nowtime = temp->addtime; //取得当前时间戳
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
			time_t nowtime = temp->addtime; //取得当前时间戳
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
	puts("+    1 - 图书名称  +");
	puts("+    2 - 存储书库  +");
	puts("++++++++++++++++++++");
	printf("请按照上面的提示输入以下的查找方法，否则默认为ISBN： ");
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
	printf("请输入您要查找的字段，否则默认为全部显示： ");
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
	puts("+     UID       +            用户名称            +  用户权限  + 用户状态 +");
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
	puts("+    0|按照用户名     +");
	puts("+    1|按照UID        +");
	puts("+    2|按照状态       +");
	puts("+    3|按照权限       +");
	puts("+++++++++++++++++++++++");
	printf("请输入查找方式，默认为用户名： ");
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
	printf("请输入您要查找的内容，默认是全部： ");
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
	puts("请输入特殊指令进行快捷操作..");
	return;
}

void changeUserViewer() 
{
	char buf[__BUFFSIZE__] = {'\0'};
	pUSER *p = NULL;
	puts("*******注意：请牢记用户的uid再进行操作，以免造成不必要的麻烦*******");
	puts("");
	while (1)
	{
		printf("请输入用户的uid： ");
		while ((state = gets_s(buf, __BUFFSIZE__)) == NULL  || *buf == '\0')
		{
			if (state == NULL)
			{
				puts("\n\n[ +1 ]      Stopped    cusr"); return;
			}
		}
		p = userSelect(buf, 1, 1);
		userDetails(*p);
		printf("确定是这个用户么？ (y/N) ");
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
	printf("请输入用户密码，回车默认不修改： ");
	while (gets_s(buf, __BUFFSIZE__) == NULL );
	if (strcmp(buf, "") != 0)
	{
		stringSave((*p)->passwd,buf);
	}
	printf("请输入用户权限，回车默认不修改： ");
	while (gets_s(buf, __BUFFSIZE__) == NULL);
	if (strcmp(buf, "") != 0)
	{
		(*p)->permission = (short)stringToLong(buf);
	}
	printf("请输入用户状态，回车默认不修改： ");
	while (gets_s(buf, __BUFFSIZE__) == NULL);
	if (strcmp(buf, "") != 0)
	{
		(*p)->status = (short)stringToLong(buf);
	}
	puts("修改成功！");
	return;
}

