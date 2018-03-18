#include "keyboard.h"

void keyboard_init() {
	//获取输入串口（键盘的串口文件符为0）的配置
	tcgetattr(0, &keyboard_setting);
	//创建新的串口配置
	
}
