#pragma once


/*
ͼ�����

*/

extern int bookAdd(pBOOK p);
/*
	�߼�ͼ��ɾ��
*/
extern int bookDeleteAdv(pBOOK p);

extern int bookDelete(const char *text, int orderby = 0);

extern pBOOK *bookSelect(const char *text, int orderby = 0, int maxnum = 3);

extern pUSER *userSelect(const char *text, int orderby = 0, int maxmum = 3);

extern int getAffected();

extern int userDeleteAdv(pUSER p);

extern int userAdd(pUSER p);

extern int userDelete(const char *text, int orderby = 0);

#ifdef DEBUG
extern void linkdump();
extern void linkdumpusr();
#endif // DEBUG

/*
�û�����

*/

extern int userAdd(const pUSER p);

extern int userBorrowedBook(const char *str);

extern int bookBorrow(char *isbn, int Days);

extern int bookReturn(char * isbn);


