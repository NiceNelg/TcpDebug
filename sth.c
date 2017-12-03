#include "sth.h"

//判断是否为16进制数
int isHexChar(char const *hex) {
	if( (*hex >= '0' && *hex <='9') || (*hex >= 'a' && *hex <='f') || (*hex >= 'A' && *hex <='F') ) {
		return 1;
	} else {
		return 0;
	}
}

//讲十六进制字符串转换成十六进制
void *stringToHex(char const *hex_string, int **hex) {
	//筛选后的字符串存放位置
	char *hex_temp;
	hex_temp = (char *)malloc(strlen(hex_string));

	while(*hex_string != '\0') {
		if(isHexChar(hex_string)) {
			*hex_temp = *hex_string;
		}
		hex_string++;
		hex_temp++;
	}
	*hex_temp = '\0';
	*hex = (int *)malloc(strlen(hex_temp));

}

