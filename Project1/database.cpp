#include "project.h"


/*Library ���ݵĲ��� */
int affected = 0;

/*
	������

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
			case 0: // ISBN ����
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
	return -9; //δ֪
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