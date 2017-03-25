#include <stdio.h>
#include "sound.h"
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h>

int main(int argc, char *argv[]){
	WAVHDR hdr;
	FILE* f;
	char c;
	short int sa[SAMPLE_RATE];
	int ret,i;

	while (1) {
		gotoXY(1,1);
		ret = system("arecord -q -r16000 -c1 -d1 -f S16_LE data.wav");
		if (WIFSIGNALED(ret) && WTERMSIG(ret)==SIGINT) {
			clrscr();
			break;
		}
	    clrscr();
		f = fopen("data.wav", "r");
		fread(&hdr,sizeof(hdr),1,f);
		dispWAVHDR(hdr);
		fread(&sa, sizeof(short int), SAMPLE_RATE, f);
		dispWAVdata(sa);
		fclose(f);
	}

	return 0;
}
