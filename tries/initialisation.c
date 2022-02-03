#include <stdio.h>
#include <stdlib.h>
#include "initialisation.h"
#include <errno.h>
#include <string.h>
/*
char key_pressed()
{
struct termios oldterm, newterm;
int oldfd; char c, result = 0;
tcgetattr (STDIN_FILENO, &oldterm);
newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
c = getchar();
tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
fcntl (STDIN_FILENO, F_SETFL, oldfd);
if (c != EOF) {
ungetc(c, stdin); result = getchar();
}
return result;
}
*/

void corresp_char(char c){
	if(c=='a') printf ("▓");
	else if(c=='b') printf ("◙");
	else if(c=='c') printf ("¤");
	else if(c=='d') printf ("╬");
	else if(c=='e') printf ("░");
	else printf ("%c",c);
}


