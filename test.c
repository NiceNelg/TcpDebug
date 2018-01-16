#include <stdio.h>
#include "display.h"

int main() {

	setlocale(LC_ALL, "");
	display_win *win;
	display_init(&win);
	getch();

	display_end(&win);

	return 0;
}
