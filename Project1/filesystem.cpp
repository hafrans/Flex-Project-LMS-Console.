#include "project.h"
#include "filesystem.h"

int loadBOOK()
{
	FILE *handle = NULL;
	if (fopen_s(&handle,config->libPath, "r"))
	{	
		printf("Read %s Failed ", config->libPath);
		return 1;
	}
	if (handle == NULL)
	{
		printf("Read %s Failed but the program can open the file", config->libPath);
		return 1;
	}
	rewind(handle);
	while(!feof(handle))
	{
		pBOOK newbook = (pBOOK)malloc(sizeof(BOOK));
		if (newbook == NULL)
		{
			printf("can not allocate any memory !");
			return -2;
		}
		fscanf_s(handle, "%s %s %s %s %s %ld %d %d\n",	&newbook->ISBN,    __BUFFSIZE__,
														&newbook->name,    __BUFFSIZE__,
														&newbook->publish, __BUFFSIZE__,
														&newbook->author,  __BUFFSIZE__,
														&newbook->store,   __BUFFSIZE__,
														&newbook->addtime,
														&newbook->total,   
														&newbook->borrowed
														);
		strcpy_s(newbook->name,__BUFFSIZE__,parseStringSpace(newbook->name));
		strcpy_s(newbook->publish,__BUFFSIZE__, parseStringSpace(newbook->publish));
		strcpy_s(newbook->ISBN,__BUFFSIZE__, parseStringSpace(newbook->ISBN));
		strcpy_s(newbook->author,__BUFFSIZE__, parseStringSpace(newbook->author));
		strcpy_s(newbook->store,__BUFFSIZE__, parseStringSpace(newbook->store));
		
		bookAdd(newbook);
		
		
		
	}
	fclose(handle);
	return 0;
}


int loadUSER()
{
	FILE *handle = NULL;
	if (fopen_s(&handle, config->userPath, "r"))
	{
		printf("Read %s Failed ", config->userPath);
		return 1;
	}
	if (handle == NULL)
	{
		printf("Read %s Failed but the program can open the file", config->userPath);
		return 1;
	}
	while (!feof(handle))
	{
		pUSER newuser = (pUSER)malloc(sizeof(USER));
		if (newuser == NULL)
		{
			printf("can not allocate any memory !");
			return -2;
		}
		fscanf_s(handle,"%ld %s %s %hd %hd %s\n", &newuser->uid,
											   &newuser->username,	__BUFFSIZE__,
											   &newuser->passwd,	__BUFFSIZE__,
											   &newuser->status,
											   &newuser->permission,
											   &newuser->book,      __BUFFBOOK__
											   );
		if (newuser->uid > maxUID)
		{
			maxUID = newuser->uid;
		}
		userAdd(newuser);
	}
	fclose(handle);
	return 0;
}
/*
	冲刷图书库
*/
int flushBOOK(int close = 0)
{
		pBOOK tmpHead = head;
		FILE *handle = NULL;
		fopen_s(&handle, config->libPath, "w+");
		if (handle == NULL)
		{
			return -2;// nullptr error
		}

		while (tmpHead != NULL)
		{
			const char *isbn = parseSpaceString(testCharNULLPTRToEmptyString(tmpHead->ISBN));
			const char *name = parseSpaceString(testCharNULLPTRToEmptyString(tmpHead->name));
			const char *publish = parseSpaceString(testCharNULLPTRToEmptyString(tmpHead->publish));
			const char *author = parseSpaceString(testCharNULLPTRToEmptyString(tmpHead->author));
			const char *store = parseSpaceString(testCharNULLPTRToEmptyString(tmpHead->store));
			const long addtime = tmpHead->addtime;
			const int  total = tmpHead->total;
			const int  borrowed = tmpHead->borrowed;

			fprintf_s(handle, "%s %s %s %s %s %ld %d %d\n",  isbn,
															name,
															publish,
															author,
															store,
															addtime,
															total,
															borrowed
															);

			pBOOK tmpGc = tmpHead;
			tmpHead = tmpHead->next;
			if (close)
			{
				free(tmpGc);
			}
		}
		fclose(handle);
		return 0;
	}

/*
	将内存中的用户数据刷出
*/
int flushUSER(int close = 0)
{
	pUSER tmpHead = uhead;
	FILE *handle = NULL;
	fopen_s(&handle, config->userPath, "w+");
	if (handle == NULL)
	{
		return -2;// nullptr error
	}
	while (tmpHead != NULL)
	{
		const long  uid = tmpHead->uid;
		const char *username = testCharNULLPTRToEmptyString(tmpHead->username);
		const char *password = testCharNULLPTRToEmptyString(tmpHead->passwd);
		const int   status = tmpHead->status;
		const int   permission = tmpHead->permission;
		const char *book = tmpHead->book;
		fprintf_s(handle, "%ld %s %s %hd %hd %s\n",    uid,
													username,
													password,
													status,
													permission,
													book);
		pUSER tmpGc = tmpHead;
		tmpHead = tmpHead->next;
		if (close)
		{
			free(tmpGc);
		}
	}
	fclose(handle);
	return 0;
}