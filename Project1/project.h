/*
	ȫ������ͷ�ļ�
	Date:2016/01/13
*/
//#define DEBUG 
//�Ƿ��� ����ģʽ
#pragma once
//ȫ�ֺ궨��
#ifndef __HEAD__
#define __HEAD__ 
#define __DIR__ "./"
#define __INIFILE__ "bms.ini"
typedef char***   __EXPLODE_PTR;
typedef char**    __EXPLODE_TYPE;
#endif // Head

#ifndef PROJECT
	#define PROJECT 
	#define __BUFFSIZE__ 4096
	#define BDAY 60 //�������ʱ��
	#define __BUFFBOOK__ 10240
	//ϵͳ������
	#include <stdio.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <time.h>
	#include <windows.h>
	//#include <assert.h>
	
#endif // !PROJECT

/**  ���뷽ʽ����   **/
#ifndef ALIGN_LEFT 
	#define ALIGN_LEFT 0
#endif
#ifndef ALIGN_RIGHT 
	#define ALIGN_RIGHT 40
#endif
#ifndef ALIGN_CENTER 
	#define ALIGN_CENTER 20
#endif

#ifndef  MODULES
#define  MODULES
	#include "functions.h"
	#include "structure.h"
	#include "inireader.h"
	#include "database.h"
	#include "filesystem.h"
	#include "consolegraph.h"
	#include "layout.h"

/*
Linked List
*/
	extern pBOOK head;
	extern pUSER uhead;
/*
 global usr name
*/
	extern pUSER currentBody;
	extern char *currentUsr;
	extern int   currentPer;
	extern long  maxUID;
/*
	 page
*/
	extern int page;
#endif // ! MODULES
/*
	�ļ��еĿ���Ϣ����
*/
#ifndef __EMPTY_OR_NULL_ALTERNATIVE_STRING__
	#define __EMPTY_OR_NULL_ALTERNATIVE_STRING__ "008899EMPTY998800"
#endif // !__EMPTY_OR_NULL_ALTERNATIVE_STRING

#ifndef  __SPACE__FILE_READ__
#define __SPACE__FILE_READ__ "#@SAE@#"
#endif // ! __SPACE__FILEREAD__




