#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"
#include "comm.h"
#include <string.h>

#define n_block 80	//Number of small block
#define N_BLOCK 10	//Number of big block which would be sent to the server

void print4ch(char* c){
	printf("%c%c%c%c\n",c[0],c[1],c[2],c[3]);
}

void fill4ch(char* c2, char* c1) {
	c2[0] = c1[0];
	c2[1] = c1[1];
	c2[2] = c1[2];
	c2[3] = c1[3];
}

void testTone(int f, double d){
	WAVHDR h;
	FILE* fh;
	int i;
	short int sample;
	fill4ch(h.ChunkID, "RIFF");
	fill4ch(h.Format, "WAVE");
	fill4ch(h.Subchunk1ID, "fmt ");
	fill4ch(h.Subchunk2ID, "data");
	h.Subchunk1Size = 16;
	h.AudioFormat = 1;
	h.NumChannels = 1;
	h.SampleRate = SAMPLE_RATE;
	h.BitsPerSample = 16;
	h.ByteRate = SAMPLE_RATE*h.BitsPerSample*h.NumChannels/8;
	h.BlockAlign = h.NumChannels*h.BitsPerSample/8;
	h.Subchunk2Size = h.ByteRate * d;
	h.ChunkSize = h.Subchunk2Size + 36;
	fh = fopen("testtone.wav","w");
	fwrite(&h, sizeof(h), 1, fh);
	for (i=0; i<SAMPLE_RATE*d; i++){
		sample = 32767 * sin(2*PI*f*i/SAMPLE_RATE);
		fwrite(&sample, sizeof(sample), 1 , fh);
	}
	fclose(fh);
	printf("Test tone ready!\n");
}

void dispWAVHDR(WAVHDR h){
	double duration;
#ifdef DEBUG
	printf("Chunk ID:        "); print4ch(h.ChunkID);
	printf("Chunk size:      %d\n",h.ChunkSize);
	printf("Format:          "); print4ch(h.Format);
	printf("Subchunk 1 ID:   "); print4ch(h.Subchunk1ID);
	printf("Subchunk 1 Size: %d\n",h.Subchunk1Size);
	printf("Audio Format:    %d\n",h.AudioFormat);
	printf("Num Channels:    %d\n",h.NumChannels);
	printf("Sample Rate:     %d\n",h.SampleRate);
	printf("Byte Rate:       %d\n",h.ByteRate);
	printf("Block Align:     %d\n",h.BlockAlign);
	printf("Bits Per Sample: %d\n",h.BitsPerSample);
	printf("Subchunk 2 ID:   "); print4ch(h.Subchunk2ID);
	printf("Subchunk 2 size: %d\n",h.Subchunk2Size);
#else
	duration = (double) h.Subchunk2Size/h.ByteRate;
	gotoXY(2,1); setFGcolor(CYAN);
	printf("%.3f sec",duration);
	gotoXY(22,1); setFGcolor(RED);
	printf("%d bits",h.BitsPerSample);
	gotoXY(42,1); setFGcolor(YELLOW);
	printf("%d Hz",h.SampleRate);
	resetcolor();
#endif
}

void dispWAVdata(short int* s){
	int i,j;
	
	int size;				//size of a small block
	int SIZE;				//Each big block contains (SIZE) small blocks

	double sum, rms;		//sum, rms, of a small block
	double RMS[N_BLOCK];	//RMS values of big blocks
	
	char tmp[20];
	char data[200] = "";	//Data sent to the server

	SIZE = n_block/N_BLOCK;
	size = SAMPLE_RATE/n_block;
	
	for (i=0; i<n_block; i++){
		sum = 0.0;				//Sum of a block
		for (j=0; j<size; j++){
			sum += (int)(*s)*(*s);
			s++;
		}
		rms = sqrt(sum/size);	//RMS of a block
		displayBar(i+3,rms,60,20);

		RMS[i/SIZE] += sum;
	}
	for (i=0; i<N_BLOCK; i++) {
		sprintf(tmp,"%.2lf\n",sqrt(RMS[i]/(SAMPLE_RATE/N_BLOCK)));
		strcat(data,tmp);
	}
	gotoXY(2,2);
	send_post(SERVER_URL,data);
}
