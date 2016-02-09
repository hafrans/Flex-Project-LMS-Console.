#pragma once

enum LOGIN
{
	SUCCESS,
	FAILED,
	LOCKED
};

#ifndef LAYOUT
#define LAYOUT

/*
初始化
*/
extern int init();
/*
登录窗口
*/
extern void loginPageViewer();
/*
登录结果弹窗
*/
extern void loginStatus(LOGIN status);
/*
Bule screen　ちゃん
*/
extern void crashViewer(const char *text = "0x0000000", const char *text2 = "软件厂商未定义此错误的原因");

extern int userRegister();

extern int userLogin();  

extern void bookDetails(pBOOK p);

extern void userDetails(pUSER p);
/*
		主窗口
*/
extern void mainLayoutViewer();

extern void bookAppend();

extern void userPwdChange();

extern void systemInfoViewer();

extern void showBookLists(pBOOK * p);

extern void selectBooksViewer();

#endif



