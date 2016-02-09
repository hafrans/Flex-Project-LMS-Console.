
#include "project.h"



inline char *deleteEquals(char *text)
{
	while (text && *text == '=')
	{
		text++;
	}
	return text;
}

inline char *getValue(char *temp)
{
	char *substr = strchr(temp, '=');
	substr = deleteEquals(substr);
	substr = trim(substr);
	return substr;
}
inline void parseVersion(FILE *handle)
{

	int count = 1, i = 20;

	while (count--&&i--)
	{
		char temp[__BUFFSIZE__];
		fgets(temp, __BUFFSIZE__, handle);

		if (strstr(temp, "VERSION") != NULL)
		{
			strcpy_s(config->version, 512, getValue(temp));
		}
		else
		{
			count++;
			continue;
		}
	}
}
inline void parseAdmin(FILE *handle)
{

	int count = 2, i = 20;

	while (count--&&i--)
	{
		char temp[__BUFFSIZE__];
		fgets(temp, __BUFFSIZE__, handle);
		if (strstr(temp, "USERNAME") != NULL)
		{
			strcpy_s(config->administrator, __BUFFSIZE__, getValue(temp));
		}
		else if (strstr(temp, "PASSWD") != NULL)
		{
			strcpy_s(config->passwd, __BUFFSIZE__, getValue(temp));
		}
		else
		{
			count++;
			continue;
		}
	}
}
inline void parseDB(FILE *handle)
{

	int count = 2, i = 20;

	while (count--&&i--)
	{
		char temp[__BUFFSIZE__];
		fgets(temp, __BUFFSIZE__, handle);
		if (strstr(temp, "LIBPATH") != NULL)
		{
			strcpy_s(config->libPath, __BUFFSIZE__, getValue(temp));
		}
		else if (strstr(temp, "USERPATH") != NULL)
		{
			strcpy_s(config->userPath, __BUFFSIZE__, getValue(temp));
		}
		else
		{
			count++;
			continue;
		}
	}
}
inline void parseLOG(FILE *handle)
{


	int count = 1, i = 20;

	while (count--&&i--)
	{
		char temp[__BUFFSIZE__];
		fgets(temp, __BUFFSIZE__, handle);
		if (strstr(temp, "PATH") != NULL)
		{
			strcpy_s(config->logPath, __BUFFSIZE__, getValue(temp));
		}
		else
		{
			count++;
			continue;
		}
	}
}
extern int iniReader()
{

	FILE *handle = NULL;
	if (fopen_s(&handle, __INIFILE__, "r"))
	{
		return 1;
	}
	if (handle == NULL)
	{
		crashViewer("0x10000002", "接收数据时侦测到空指针错误");
		return -2;
	}
	while (!feof(handle))
	{

		char temp[__BUFFSIZE__];
		fgets(temp, __BUFFSIZE__, handle);

		if (strchr(temp, '#') != NULL)
		{
			continue;
		}
		if (strcmp(temp, "[VERSION]\n") == 0)
		{
			parseVersion(handle);
		}
		else if (strcmp(temp, "[ADMINISTRATOR]\n") == 0)
		{
			parseAdmin(handle);
		}
		else if (strcmp(temp, "[LOG]\n") == 0)
		{
			parseLOG(handle);
		}
		else if (strcmp(temp, "[DB]\n") == 0)
		{
			parseDB(handle);
		}
		else {
			continue;
		}

	}

	return 0;
}




