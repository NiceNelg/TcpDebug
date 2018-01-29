#include "tcpoperate.h"
#include "sth.h"
#include "display.h"

int main() {
	
	char c;
	display_win *win;
	display_init(&win);
	while(1) {
		c=wgetch(win->win_send);
		switch(c) {
			case 'q':{
				display_end(&win);
				return 0;
			}
			break;
		}
	}
	return 0;

}
