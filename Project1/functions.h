#pragma once


/*
	获取系统的位数
*/
extern size_t getOSBit();
/*
	时间戳转换为字符串
*/
extern char *timestampToString(time_t timeb);
/*
	无限制连接字符串
	@param const char *textA
	@param const char *textB
	@return char *
*/
extern char *strcat_t(const char *textA, const char *textB);
/*
	去除字符串左右空白字符
	@param char* text
	@return char * 
*/
extern char *trim(char *text);
/*
	解决写入文件有空格问题
*/
extern char *parseSpaceString(const char *text);
/*
	解决读取文件无空格问题
*/
extern char *parseStringSpace(const char *text);
/*
	文字存储
*/
extern void stringSave(char *TextA, const char *TextB);

extern void exitLMS();

extern char *delspace(const char *text);
/*
	日志记录
*/
extern void consoleLog(const char *text = "Unknown Error");
/*
	将char空指针c 黏附 00VAR_EMPTY99 字符串""
*/
extern const char *testCharNULLPTRToEmptyString(const char *text);
/*
	字符串分割成数组
	务必先创建一个指向字符串组的指针
	@param char delimiter 分割符
	@param char *text 处理字符串
	@param const _EXPLODE_TYPE dest 指向的指针
	@return size_t 元素个数
*/
extern size_t explode(char delimiter, char * string, char **& ptr);
/*
	时间戳转时间
*/
extern char * timetstr(long time);
/*
	int 型转为字符串
*/
extern char *integerToString(int num);
/*
	字符串转long
*/
extern long stringToLong(const char *text);
