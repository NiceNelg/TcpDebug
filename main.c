#include "tcpoperate.h"
#include "sth.h"
#include "display.h"

int main() {
	
	display_win *win;
	display_init(&win);
	getch();
	display_end(&win);
	return 0;

}
