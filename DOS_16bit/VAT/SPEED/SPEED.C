#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>

#define WORD unsigned int
#define BYTE unsigned char
#define CHAR signed char
#define DWORD unsigned long int

typedef struct {
	DWORD buffer;
	DWORD position;
	DWORD buffer2;
	DWORD *pos;
	DWORD pinc;
	DWORD end;


	CHAR *data;

} CHANNEL;

void InitTimerFunctions(void);
void TimerOn(void);
WORD TimerOff(void);
void timeit(void);



int blen = 64;
CHANNEL ch[4];
unsigned int *mixarray;
int vol = 32;
int vlook[256];



main(void)
{
	int i,j,k;
	WORD o;
	char r=' ';

	mixarray = (int *)farmalloc(10000);
	if(!mixarray) exit(1);

	for(i = 0; i < 4; i++) {
		ch[i].data = (CHAR *)farmalloc(1000);
		ch[i].position = 0;
		ch[i].pinc = 3;
		ch[i].end = 990;
		ch[i].pos = (DWORD *)(((BYTE *)&ch[i].position)+1);
	}

	InitTimerFunctions();

  i=1;
	while(r != 'q') {
/*		if(!(i%5)) {
			mixarray = (int *)((char *)mixarray + 1);
			printf("---------- New addr: %u\n",(WORD)mixarray);
		}
*/
		TimerOn();
		timeit();
		o = TimerOff();
		printf("Ticks: %u\n",o);
		r=getch();
//		i++;
	}

	return 0;
}




/**************************************************************************
	void timeit(void)

	DESCRIPTION:  basic function for timing;

**************************************************************************/
void timeit(void)
{
	int i,j,k;
	DWORD position,end,*pos;
	int pinc;
	CHAR *data;
	int *mae,*ma;
//	BYTE *data;

	mae = mixarray+blen;

	for(j = 0; j < 10; j++) {
		for(i = 0; i < 4; i++) {
			position = ch[i].position;
			end = ch[i].end*256;
			pinc = ch[i].pinc;
			pos = (DWORD *)(((BYTE *)&position)+1);
//			data = ch[i].data;
//			for(k = 0; k < blen; k++) {
			for(ma = mixarray; ma < mae; ma++) {
//				*(mixarray+k) += (*(ch[i].data + (WORD)*ch[i].pos) * vol)>>6;
				*(ma) += (*(data + (WORD)*pos) * vol)>>6;
//				*(mixarray+k) += vlook[*(data + (WORD)*pos) ];
				position += pinc;
//				position+=pinc;
				if(position > end) {
//				if(position > end) {
					*pos = 0;
				}
			}
			ch[i].position  = position;
		}
	}

}












/**************************************************************************
	void InitTimerFunctions()

	DESCRIPTION: Initializes speaker timer for timing operations.

**************************************************************************/
void InitTimerFunctions(void)
{
	BYTE b;

	b = inportb(0x61) & 0xfd;          // Read current port value.

																		 // Disable speaker output, but keep
																		 // timer 2 enabled.
	outportb(0x61,b | 0x01);
}


/**************************************************************************
	void TimerOn()

	DESCRIPTION: Turns on timer counter for a time measurement

**************************************************************************/
void TimerOn(void)
{
	outportb(0x43,0xb0);                 // Set up the timer for countdown
	outportb(0x42,0xff);                // Least significant byte
	outportb(0x42,0xff);                // Most significant byte
}


/**************************************************************************
	WORD TimerOff()

	DESCRIPTION: Turns off time and reports clicks elapsed.  Note that this
							 timer is so quick that it is wraps after only 56
							 milliseconds.  If you want to timer longer stuff, I suggest
							 using the global variable vclock.  It's tick frequency is
							 sample_rate / dma_bufferlen.

							 To convert to micro seconds, multiply the return value by
							 0.838.

	RETURNS:
		Current timer count

**************************************************************************/
WORD TimerOff(void)
{
	outportb(0x43,0xc0);                 // Read the timer countdown status
	return 0xffff - (inportb(0x42) + inportb(0x42) * 256);

}


