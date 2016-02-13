#include "project.h"


/*Library 数据的操作 */
int affected = 0;

/*
	高级图书ISBN验证
*/
inline int bookConflict(const pBOOK p)
{
	if (p == NULL)
	{
		return -2;//NULL error
	}
	pBOOK temp = head;

	while (temp != NULL)
	{
		if ((temp == p) || strcmp(temp->ISBN, p->ISBN) == 0)
		{
			return 1;//ISBN重复
		}
		temp = temp->next;
	}
	return 0;
}
/*
	高级图书添加
*/
int bookAdd(pBOOK p)
{
	if (p == NULL)
	{
		return -2;//NULL error
	}
	
	if (bookConflict(p))
	{
		return 1;
	}
	p->next = NULL;
	if (head == NULL)
	{
		head = p;
		return 0;
	}
	pBOOK temp = head;


	while (temp != NULL)
	{
		if (strcmp(p->ISBN, temp->ISBN) > 0)
		{
			p->next = temp->next;
			temp->next = p;
			return 0;
		}

		if (temp->next == NULL)
		{
			p->next = head;
			head = p;
			return 0;
		}
		temp = temp->next;
	}
	return -9;//未知
}
/*
	高级图书删除函数
*/
int bookDeleteAdv(pBOOK p)
{
	pBOOK temp = head;
	pBOOK _FATHER_T = NULL;
	if (p == NULL)
	{
		return -2;
	}
	pBOOK tmpGC = p;
	if (p == head)
	{
		head = head->next;
	}
	else {
		while (temp != NULL)
		{
			if (temp->next == p)
			{
				_FATHER_T = temp;
				break;
			}
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return -9;//未知错误
		}
		_FATHER_T->next = p->next;
	}
	free(tmpGC);
	return 0;
}
/*
	图书删除函数
	param char* text 需要查找的字符串
	param int	orderby = 0 查询种类（默认是isbn）
	return int 受影响的行数
*/
int bookDelete(const char *text, int orderby) 
{
	int count = 0;//影响个数
	pBOOK temp = head;//
	switch (orderby)
	{
		case 0://根据ISBN进行删除
			while (temp != NULL)
			{
				if (strcmp(temp->ISBN, text) == 0)
				{
					head = temp->next;
					free(temp);
					temp = head;
					count++;
					continue;
				}
				else if (temp->next == NULL)
				{
					break;
				}
				else if (strcmp(temp->next->ISBN, text) == 0)
				{
					pBOOK garbage = temp->next;
					temp->next = temp->next->next;
					free(garbage);
					count++;
				}
				temp = temp->next;
			}
			break;
		case 1:
		
			break;
		default:
			break;
	}
	return count;
}


/**/
pBOOK *bookSelect(const char *text,int orderby,int maxnum)
{
	pBOOK *arr = (BOOK **)calloc(maxnum,sizeof(pBOOK));
	if (arr == NULL)
	{
		consoleLog("在SELECT过程中出现了无法申请内存的现象");
		affected = -1;
		return NULL;
	}
	affected = 0;
	pBOOK temp = head;
	while (temp != NULL && affected <= maxnum)
	{
		switch (orderby)
		{
			case 0: // ISBN 查找(模糊)
				if (strstr(temp->ISBN, text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 1:  //图书名称查找
				if (strstr(temp->name, text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 2:  //图书书库查找
				if (strstr(temp->store, text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case -1: // ISBN 查找(精确)
				if (strcmp(temp->ISBN, text) == 0 )
				{
					*(arr + affected++) = temp;
				}
				break;
			default:
				break;
			}

		temp = temp->next;
	}

	return arr;
}

int getAffected()
{
	return affected;
}




void linkdump()
{
	puts("/**********************************/");
	pBOOK temp = head;
	while (temp != NULL )
	{
		printf("%s   %s\n",temp->ISBN,temp->name);
		temp = temp->next;
	}
	puts("/**********************************/");
}


inline int usrConflict(const pUSER p)
{

	if (p == NULL)
	{
		return -2;//NULL error
	}
	pUSER temp = uhead;

	while (temp != NULL)
	{
		if (strcmp(temp->username, p->username) == 0)
		{
			return 1;//用户重复
		}
		temp = temp->next;
	}
	return 0;
}
int userDeleteAdv(pUSER p)
{

	pUSER temp = uhead;
	pUSER _FATHER_T = NULL;
	if (p == NULL)
	{
		return -2;
	}
	pUSER tmpGC = p;
	if (p == uhead)
	{
		uhead = uhead->next;
	}
	else {
		while (temp != NULL)
		{
			if (temp->next == p)
			{
				_FATHER_T = temp;
				break;
			}
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return -9;//未知错误
		}
		_FATHER_T->next = p->next;
	}
	free(tmpGC);
	return 0;
}

int userAdd(pUSER p)
{
	if (p == NULL)
	{
		return -2;//NULL error
	}
	p->next = NULL;
	p->uid = maxUID++;

	if (usrConflict(p))
	{
		return 1;
	}
	if (uhead == NULL)
	{
		uhead = p;
		return 0;
	}
	pUSER temp = uhead;

	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			temp->next = p;
			return 0;
		}
		temp = temp->next;
	}
	return -9; //未知
}
/*查询用户借书内容*/
int userBorrowedBook(const char * str)
{
	//size_t count();
	return 0;
}
/*
	用户删除
*/
int userDelete(const char *text, int orderby)
{
	int count = 0;//影响个数
	pUSER temp = uhead;//
	switch (orderby)
	{
		case 0://根据username进行删除
			while (temp != NULL)
			{
				if (strcmp(temp->username,text) == 0)
				{
					uhead = temp->next;
					temp = uhead;
					count++;
					continue;
				}
				else if (temp->next == NULL)
				{
					break;
				}
				else if (strcmp(temp->next->username, text) == 0)
				{
					pUSER garbage = temp->next;
					temp->next = temp->next->next;
					//free(garbage);
					count++;
				}
				temp = temp->next;
			}
			break;
		case 1:
			while (temp != NULL)
			{
				if (temp->uid == stringToLong(text))
				{
					uhead = temp->next;
					temp = uhead;
					count++;
					continue;
				}
				else if (temp->next == NULL)
				{
					break;
				}
				else if (temp->uid == stringToLong(text))
				{
					pUSER garbage = temp->next;
					temp->next = temp->next->next;
					//free(garbage);
					count++;
				}
				temp = temp->next;
			}
			break;
		case 2:
			while (temp != NULL)
			{
				if (temp->status == (short)stringToLong(text))
				{
					uhead = temp->next;
					temp = uhead;
					count++;
					continue;
				}
				else if (temp->next == NULL)
				{
					break;
				}
				else if (temp->status == (short)stringToLong(text))
				{
					pUSER garbage = temp->next;
					temp->next = temp->next->next;
					//free(garbage);
					count++;
				}
				temp = temp->next;
			}
			break;
		default:
			break;
		}
	return count;
}
void linkdumpusr()
{
	puts("/**********************************/");
	pUSER temp = uhead;
	while (temp != NULL)
	{
		printf("%ld   %s\n", temp->uid, temp->username);
		temp = temp->next;
	}
	puts("/**********************************/");
}


/*
	多用户取出
	@param const char *text 需要搜索的内容
	@param int	 orderby =0 搜索方式
	@param unsigned int maximum 最大返回数量
*/
pUSER *userSelect(const char *text, int orderby,int maxmum)
{
	pUSER *arr = (pUSER *)calloc(maxmum + 1 , sizeof(pUSER));
	if (arr == NULL)
	{
		consoleLog("在SELECT过程中出现了无法申请内存的现象");
		affected = -1;
		return NULL;
	}
	affected = 0;
	pUSER temp = uhead;
	while (temp != NULL && affected <= maxmum)
	{
		switch (orderby)
		{
			case 0:
				if (strstr(temp->username,text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 1:
				if (strcmp(integerToString((long)temp->uid), text) == 0)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 2:
				if (strstr(integerToString((int)temp->status), text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 3:
				if (strstr(integerToString((int)temp->permission), text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			default:
				break;
		}
		temp = temp->next;
	}
	*(arr + affected) = NULL;
	return arr;
}

int bookBorrowedList()
{
	char **t = NULL;
	char *tmp = currentBody->book;
	size_t i = explode('|',tmp, t);
	return 0;
}
int bookBorrow(char *isbn, int Days)
{
	char strDueTime[__BUFFSIZE__] = { '\0' };
	pBOOK p = getSingleBook(isbn);
	if (getAffected() == 0)
	{
		return -2;//所查找数目不存在
	}
	
	if (p->total - p->borrowed <= 0)
	{
		return -1;//图书数量不足
	}
	p->borrowed++;
	time_t nowtime = time(NULL);
	time_t borrowTime = (time_t)(Days * 3600 * 24);
	time_t dueTime = nowtime + borrowTime;
		_ltoa_s(dueTime, strDueTime,__BUFFSIZE__, 10);
	char *newborrow = strcat_t("|",isbn);
		  newborrow = strcat_t(newborrow, ",");
		  newborrow = strcat_t(newborrow, strDueTime);
    char *newstr = strcat_t(currentBody->book,newborrow);
	strcpy_s(currentBody->book,__BUFFBOOK__,newstr);
	return 0;//借书完成
}

int bookReturn(char *isbn)
{
	char **t = NULL;
	char *str = (char *)calloc(__BUFFBOOK__,sizeof(char));
	if (str == NULL)
	{
		crashViewer("0x00000012 (0x00000010 0x0000002)", "内存申请异常于EXPLODESTR");
	}
	strcpy_s(str,__BUFFBOOK__,currentBody->book);
	size_t count;
	size_t i = explode('|',str,t);
	if (i <= 1)
	{
		return -3; // 无书可还
	}
	for (count = 1; count < i; count++)
	{
		if (strstr(t[count], isbn) != NULL)
		{
			break;
		}
	}
	if (count == i)
	{
		return -2;//查询不到书目
	}
	pBOOK *ep = bookSelect(isbn,0,1);
	if (!getAffected())
	{
		return 1; // 书库中无法查询到
	}
	ep[0]->borrowed -= 1;
	size_t tr = 0;
	char *newstr = (char *)calloc(__BUFFBOOK__, sizeof(char));
	newstr = strcat_t(newstr, "0");
	for (tr = 1;tr < i; tr++)
	{

		if (tr == count)
		{
			continue;
		}
		newstr = strcat_t(newstr,"|");
		newstr = strcat_t(newstr,t[tr]);
	}
	strcpy_s(currentBody->book, __BUFFBOOK__, newstr);
#ifdef DEBUG
	puts(t[count]);
#endif
	
	return 0;
}
