#ifndef __STH__
#define __STH__ 

//字符串转十六进制数方法集合
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//判断是否为16进制数
int isHexChar(char const *hex);
//讲十六进制字符串转换成十六进制
void *stringToHex(char const *hex_string, int **hex);

#endif
