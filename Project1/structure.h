#pragma once



#ifndef STRUCT
#define STRUCT


typedef struct book_detail_linked {
	char name[__BUFFSIZE__];
	char author[__BUFFSIZE__];
	char publish[__BUFFSIZE__];
	char ISBN[__BUFFSIZE__];
	char store[__BUFFSIZE__];
	int   total;
	long  addtime;
	int   borrowed;
	struct  book_detail_linked *next = NULL; //new feature
} BOOK, *pBOOK;




typedef struct configuration {
	char version[512];
	char administrator[__BUFFSIZE__];
	char passwd[__BUFFSIZE__];
	char logPath[__BUFFSIZE__];
	char userPath[__BUFFSIZE__];
	char libPath[__BUFFSIZE__];
} *CONFIG;

typedef struct user_detail {
	long uid;
	char username[__BUFFSIZE__];
	char passwd[__BUFFSIZE__];
	short permission = 0;
	short status = 0;
	char  book[__BUFFBOOK__];
	struct user_detail *next; //new feature
} USER,*pUSER;



#endif // !STRUCT
