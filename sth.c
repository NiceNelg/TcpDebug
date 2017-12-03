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
void stringToHex(char const *hex_string, int **hex) {
	
	//筛选后的字符串存放位置
	char *hex_temp;
	//记录筛选后字符串的起始位置
	int hex_frist = 0;
	//转换后的十六进制数组
	int *string_to_hex;
	char hex_next;
	int i;

	hex_temp = (char *)malloc(strlen(hex_string));

	//筛选字符串
	while(*hex_string != '\0') {
		if(isHexChar(hex_string)) {
			*hex_temp = *hex_string;
			hex_temp++;
		}
		hex_string++;
	}
	*hex_temp = '\0';
	//复位指针下标
	hex_temp = hex_temp - hex_frist;
	hex_frist = 0;
	//初始化十六进制数组
	string_to_hex = (int *)malloc(strlen(hex_temp) * 4);
	//转换字符串
	while(*hex_temp) {
		switch(*hex_temp) {
			case '0': { *string_to_hex = 0x00;} break;
			case '1': { *string_to_hex = 0x01;} break;
			case '2': { *string_to_hex = 0x02;} break;
			case '3': { *string_to_hex = 0x03;} break;
			case '4': { *string_to_hex = 0x04;} break;
			case '5': { *string_to_hex = 0x05;} break;
			case '6': { *string_to_hex = 0x06;} break;
			case '7': { *string_to_hex = 0x07;} break;
			case '8': { *string_to_hex = 0x08;} break;
			case '9': { *string_to_hex = 0x09;} break;
			case 'a': { *string_to_hex = 0x0a;} break;
			case 'b': { *string_to_hex = 0x0b;} break;
			case 'c': { *string_to_hex = 0x0c;} break;
			case 'd': { *string_to_hex = 0x0d;} break;
			case 'e': { *string_to_hex = 0x0e;} break;
			case 'f': { *string_to_hex = 0x0f;} break;
			case 'A': { *string_to_hex = 0x0a;} break;
			case 'B': { *string_to_hex = 0x0b;} break;
			case 'C': { *string_to_hex = 0x0c;} break;
			case 'D': { *string_to_hex = 0x0d;} break;
			case 'E': { *string_to_hex = 0x0e;} break;
			case 'F': { *string_to_hex = 0x0f;} break;
		}
		hex_temp++;
		string_to_hex++;
		hex_frist++;
	}
	//复位指针下标
	string_to_hex = string_to_hex - hex_frist;
	//初始化指针
	if( (hex_frist%2 != 0) ) {
		*hex = (int *)malloc((hex_frist/2+1) * 4);
	} else {
		*hex = (int *)malloc(hex_frist/2*4);
	}
	//重组数据
	for(i=0; i<hex_frist;) {
		if( (i+1 == hex_frist) && (hex_frist%2 != 0) ) {
			hex_next = 0x00;
		} else {
			hex_next = *(string_to_hex + i + 1);
		}
		**hex = (*(string_to_hex + i) << 4) + *(string_to_hex + i + 1);
		i += 2;
	}

}

