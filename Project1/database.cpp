#include "project.h"


/*Library 数据的操作 */
int affected = 0;

/*
	书增加

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

int bookDeleteAdv(pBOOK p)
{
	if (p == NULL)
	{
		return -2;
	}
	pBOOK tmpGC = p;
	p = p->next;
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
			case 0: // ISBN 查找
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
	if (p == NULL)
	{
		return -2;
	}
	pUSER tmpGC = p;
	p = p->next;
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
				if (strstr(integerToString((long)temp->username), text) != NULL)
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