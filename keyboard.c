#include "keyboard.h"

//初始化键盘
void keyboard_init() {
	//获取输入串口（键盘的串口文件符为0）的配置
	tcgetattr(0, &keyboard_setting);
	//创建新的串口配置
	keyboard_new_setting = keyboard_setting;
	keyboard_new_setting.c_lflag |= ICANON;
	keyboard_new_setting.c_lflag |= ECHO;
	keyboard_new_setting.c_lflag |= ISIG;
	keyboard_new_setting.c_cc[VMIN] = 1;
	keyboard_new_setting.c_cc[VTIME] = 0;
	//将新的键盘配置设置到输入串口
	tcsetattr(0, TCSANOW, &keyboard_new_setting);
}

//键盘键入触发的事件
int keyboard_hit() {
	unsigned char ch;
	int nread;

	if(keyboard_character != -1) {
		return 1;
	}
	keyboard_new_setting.c_cc[VMIN] = 0;
	tcsetattr(0, TCSANOW, &keyboard_new_setting);
	nread = read(0, &ch, 1);
	keyboard_new_setting.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &keyboard_new_setting);
	if(nread == 1) {
		keyboard_character = ch;
		return 1;
	}
	return 0;
}

int keyboard_readch() {
	char ch;

	if(keyboard_character != -1) {
		ch = keyboard_character;
		keyboard_character = -1;
		return ch;
	}

	read(0, &ch, 1);
	return ch;
}

//结束键盘监听
void keyboard_close() {
	tcsetattr(0, TCSANOW, &keyboard_setting);
}
