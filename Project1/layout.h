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
/*
	�û�ע�����
*/
extern int userRegister();
/*
	�û���½����
*/
extern int userLogin();  
/*
	���ݽṹ��ָ���ȡͼ�����ϸ��Ϣ
*/
extern void bookDetails(pBOOK p);
/*
	���ݽṹ��ָ���ȡ�û�����ϸ��Ϣ
*/
extern void userDetails(pUSER p);
/*
		������
*/
extern void mainLayoutViewer();
/*
	����ͼ��
*/
extern void bookAppend();
/*
	�û������޸�
*/
extern void userPwdChange();
/*
	ϵͳ��Ϣ
*/
extern void systemInfoViewer();
/*
	���ͼ��ļ�Ҫ��Ϣ
*/
extern void showBookLists(pBOOK * p);
/*
	��ѯͼ���������
*/
extern void selectBooksViewer();
/*
	����û��ļ�Ҫ��Ϣ
*/
extern void showUserLists(pUSER * p);
/*
	��ѯ�û�������Ϣ
*/
extern void userSelectViewer();
/*
	�ı��û�����������Ϣ
*/
extern void changeUserViewer();
/*
	����ISBN��ȡͼ��ṹ��ָ��
*/
extern pBOOK getSingleBook(char *isbn);
/*
	��������
*/
extern void bookBorrowViewer();

extern void bookReturnViewer();

extern void bookBorrowListsViewer();

extern void bookChangeViewer();




#endif



