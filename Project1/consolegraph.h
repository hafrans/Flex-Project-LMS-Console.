#pragma once
/**/
extern void consoleClear();

extern void consoleColorSet(const char *color);
/*
设定窗口标题
@param const char title 标题名称
@return void
*/
extern void consoleTitleSet(const char *title = "Hafrans Flex Project");

extern void consoledrawBorder(int type, int count, int align);
/**
*在控制台输出与边框相符的文字，长度不要大于68
*@param int type 边框种类
*@param int count = 1 重复输出次数
*@param int align = ALIGN_LEFT 对齐方式
*@param int talign = ALIGN_LEFT 文字对齐方式
*
*@author Hafrans Newton
*/
extern void consoleDrawText(char *text, int align = ALIGN_CENTER, int talign = ALIGN_CENTER, int type = 1);

extern void consoleNewLine(int count);

extern void consoleWaitinCMD();

