#include "screen.h"
#include <stdio.h>
#include <math.h>

// function definition
int get_color(int i, int lim, int lev){
	return i/(lim/lev);
}

void setFGcolor(int color){
	printf("\033[%d;1m", color);
	fflush(stdout);
}

void resetcolor(void){
	printf("\033[0m");
	fflush(stdout);
}

void gotoXY(int x, int y){
	printf("\033[%d;%dH",y,x);
	fflush(stdout);
}

void displayBar(int col, double rms, int lim, int reso){
	int i,j,fl = 0,color;

	int rainbow[6] = {RED,YELLOW,GREEN,CYAN,BLUE,MAGENTA};

	j = trunc(rms/reso+1);

	if (j>lim) j=lim;
	for (i=0; i<j; i++){
		color = get_color(i,lim,5);
		setFGcolor(rainbow[color]);
		gotoXY(col,lim-i+2);
#ifdef UNICODE
		printf("%s", UBAR);
#else
		printf("*");
#endif
	}
	resetcolor();
	fflush(stdout);
}

void clrscr(){
	printf("\033[2J");
	fflush(stdout);
}
