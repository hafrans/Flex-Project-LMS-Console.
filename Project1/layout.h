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
/*
	用户注册界面
*/
extern int userRegister();
/*
	用户登陆界面
*/
extern int userLogin();  
/*
	根据结构体指针获取图书的详细信息
*/
extern void bookDetails(pBOOK p);
/*
	根据结构体指针获取用户的详细信息
*/
extern void userDetails(pUSER p);
/*
		主窗口
*/
extern void mainLayoutViewer();
/*
	增加图书
*/
extern void bookAppend();
/*
	用户密码修改
*/
extern void userPwdChange();
/*
	系统信息
*/
extern void systemInfoViewer();
/*
	输出图书的简要信息
*/
extern void showBookLists(pBOOK * p);
/*
	查询图书命令界面
*/
extern void selectBooksViewer();
/*
	输出用户的简要信息
*/
extern void showUserLists(pUSER * p);
/*
	查询用户命令信息
*/
extern void userSelectViewer();
/*
	改变用户密码命令信息
*/
extern void changeUserViewer();
/*
	根据ISBN获取图书结构体指针
*/
extern pBOOK getSingleBook(char *isbn);
/*
	借书命令
*/
extern void bookBorrowViewer();

extern void bookReturnViewer();

extern void bookBorrowListsViewer();

extern void bookChangeViewer();




#endif



