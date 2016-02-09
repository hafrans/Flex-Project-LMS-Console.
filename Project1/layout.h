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
��ʼ��
*/
extern int init();
/*
��¼����
*/
extern void loginPageViewer();
/*
��¼�������
*/
extern void loginStatus(LOGIN status);
/*
Bule screen�������
*/
extern void crashViewer(const char *text = "0x0000000", const char *text2 = "�������δ����˴����ԭ��");

extern int userRegister();

extern int userLogin();  

extern void bookDetails(pBOOK p);

extern void userDetails(pUSER p);
/*
		������
*/
extern void mainLayoutViewer();

extern void bookAppend();

extern void userPwdChange();

extern void systemInfoViewer();

extern void showBookLists(pBOOK * p);

extern void selectBooksViewer();

#endif



