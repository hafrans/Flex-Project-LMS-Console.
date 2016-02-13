#include "project.h"


/*Library ���ݵĲ��� */
int affected = 0;

/*
	�߼�ͼ��ISBN��֤
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
			return 1;//ISBN�ظ�
		}
		temp = temp->next;
	}
	return 0;
}
/*
	�߼�ͼ�����
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
	return -9;//δ֪
}
/*
	�߼�ͼ��ɾ������
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
			return -9;//δ֪����
		}
		_FATHER_T->next = p->next;
	}
	free(tmpGC);
	return 0;
}
/*
	ͼ��ɾ������
	param char* text ��Ҫ���ҵ��ַ���
	param int	orderby = 0 ��ѯ���ࣨĬ����isbn��
	return int ��Ӱ�������
*/
int bookDelete(const char *text, int orderby) 
{
	int count = 0;//Ӱ�����
	pBOOK temp = head;//
	switch (orderby)
	{
		case 0://����ISBN����ɾ��
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
		consoleLog("��SELECT�����г������޷������ڴ������");
		affected = -1;
		return NULL;
	}
	affected = 0;
	pBOOK temp = head;
	while (temp != NULL && affected <= maxnum)
	{
		switch (orderby)
		{
			case 0: // ISBN ����(ģ��)
				if (strstr(temp->ISBN, text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 1:  //ͼ�����Ʋ���
				if (strstr(temp->name, text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case 2:  //ͼ��������
				if (strstr(temp->store, text) != NULL)
				{
					*(arr + affected++) = temp;
				}
				break;
			case -1: // ISBN ����(��ȷ)
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
			return 1;//�û��ظ�
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
			return -9;//δ֪����
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
	return -9; //δ֪
}
/*��ѯ�û���������*/
int userBorrowedBook(const char * str)
{
	//size_t count();
	return 0;
}
/*
	�û�ɾ��
*/
int userDelete(const char *text, int orderby)
{
	int count = 0;//Ӱ�����
	pUSER temp = uhead;//
	switch (orderby)
	{
		case 0://����username����ɾ��
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
	���û�ȡ��
	@param const char *text ��Ҫ����������
	@param int	 orderby =0 ������ʽ
	@param unsigned int maximum ��󷵻�����
*/
pUSER *userSelect(const char *text, int orderby,int maxmum)
{
	pUSER *arr = (pUSER *)calloc(maxmum + 1 , sizeof(pUSER));
	if (arr == NULL)
	{
		consoleLog("��SELECT�����г������޷������ڴ������");
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
		return -2;//��������Ŀ������
	}
	
	if (p->total - p->borrowed <= 0)
	{
		return -1;//ͼ����������
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
	return 0;//�������
}

int bookReturn(char *isbn)
{
	char **t = NULL;
	char *str = (char *)calloc(__BUFFBOOK__,sizeof(char));
	if (str == NULL)
	{
		crashViewer("0x00000012 (0x00000010 0x0000002)", "�ڴ������쳣��EXPLODESTR");
	}
	strcpy_s(str,__BUFFBOOK__,currentBody->book);
	size_t count;
	size_t i = explode('|',str,t);
	if (i <= 1)
	{
		return -3; // ����ɻ�
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
		return -2;//��ѯ������Ŀ
	}
	pBOOK *ep = bookSelect(isbn,0,1);
	if (!getAffected())
	{
		return 1; // ������޷���ѯ��
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
