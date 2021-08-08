/*************************************************************************
	SVGAPLUS.C

	This contains some extra functions to suppllement the SVGA
		library SVGACC.

	Written By: Eric Jorgensen (1994)
**************************************************************************/
#include "svgaplus.h"
#include <DOS.h>
#include <alloc.h>
#include <stdarg.h>
																		// local function prototypes

int compare_ind(const void *a,const void *b);
int compare_active(const void *u,const void *v);
void cdelete(int i,int *nact, Edge active[]);
void cinsert(int i,int head,int y,int *nact,Edge active[]);

Font SVGAfont;
byte far *fontpointer = NULL;
D2Point *sortpt;
int assume_nocross = FALSE;

/**************************************************************************
	getinput(x,y,fc,bc,prompt,string,maxlength);

	DESCRIPTION: This gets string input from the user. This function
							 fills the variable 'string' with text information.
							 If string already has text information in it, getinput()
							 will use it.

	fc,bc = 		foregroundcolor, backgroundcolor
  *prompt = Text to prompt the user
  *string = Output buffer.  Should already containa default value
  maxlength = maxiumum length of input

**************************************************************************/
void getinput(int x,int y,int fc,int bc,
			char *prompt,char *string,int maxlength)
{
	int w,h,wx,wy,c,flag,dd=0,color;
	char buffer[255],r,minibuff[2];

	mousehide();                       		// Get rid of mouse cursor
	minibuff[1] = 0;                      // clear small string buffer

	w = textwidth("A");
	h = textheight("A");
	wx = x+textwidth(prompt);          		// get location if leftmost input char
	wy = y;

	sprintf(buffer,"%s%s",prompt,string);
	drwstring(SET,fc,bc,buffer,x,y);        // display prompt and default string

	strcpy(buffer,string);     							// copy string for editing */

	c = strlen(buffer);
	flag = 1;

	while(flag) {                          	// ANIMATED STRING EDITOR LOOP
		if(dd > 100) color = fc;       	 		 	// Blink cursor
		else color = bc;                      // draw cursor
		drwfillbox(SET,color,wx+c*w, wy, wx+c*w+w, wy+h);

		delay(10);                        		// control blink rate
		dd += 5;
		if(dd > 199) dd = 0;

		r = inkey();
		if(r) {                      					// look for a key stroke
			if( r >= ' ') {           					// If r is a regular alpha-numeric
																					// character, add it to the name
																					// string.
				buffer[c] = r;
																					// move the cursor
				drwfillbox(SET,bc,wx+c*w,wy,wx+c*w+w,wy+h);   // erase it
				drwfillbox(SET,bc,wx,wy,wx+maxlength*w+w,wy+h); 		 // erase string
				buffer[c+1] = 0;              		// extend string terminator
				drwstring(SET,fc,bc,buffer,wx,wy);  		// draw the new string
				c++;                      				// move cursor index
				if(c>maxlength) c = maxlength;// limit string length
			}
			else if(r == 13) flag = 0;    			// return = finished
			else if( r == 8) {             			// backspace
				drwfillbox(SET,bc,wx+c*w,wy,wx+c*w+w,	wy+h);  // erase cursor
				c--;                      				// move string index
				if(c < 0) c = 0;          				// don't go off te end!
				buffer[c] = 0;            				// move back string terminator
				drwfillbox(SET,bc,wx+w,wy,wx+maxlength*w+w,wy+h);  // erase string
				drwstring(SET,fc,bc,buffer,wx,wy); 		// draw the new string
			}
			else if(r == 27)	{									// escape key
				flag = 0;                         // end loop
				buffer[0] = 0;                    // clear input string
			}
		}
	}
	strcpy(string,buffer);                  // store new string
	*(string+maxlength) = 0;                // make sure string is of this length
	mouseshow();                         // bring mouse cursor back
}



/**************************************************************************
	void scanconvertpoly(int color, int points, D2Point poly[])

	DESCTRIPTION: Scan converts a polygon of any shape.


	RETURNS:

		-1 Number of points inncorrectly specified
		-2 Not enough memory

**************************************************************************/
/*int scanconvertpoly(int color, int points, D2Point poly[])
{
	int i,j,k,nact,y,rx,sortflag = 0;
	int attitude;
	static int far *s= NULL,mostpoints = 0;   // sort array and point counter
	static far Edge *active;                  // active edge array
	char *string;

	if(points < 1) return(-1);						// sanity check

																				// Allocate memory for sorted
																				// indeces and Edges. The allocated
																				// memory is static so that we
																				// don't have to keep reallocating
																				//  it every time.

	if(!s) {                              // First time here?
		s = (int *)farcalloc(points+1,sizeof(int));
		active = (Edge *)farcalloc(points+1,sizeof(Edge));
		if(!s || !active) return (-2);
		mostpoints = points;
	}
	else if(mostpoints < points) {        // enough memory for this polygon?
		farfree(s);
		farfree(active);
		s = (int *)farcalloc(points+1,sizeof(int));
		active = (Edge *)farcalloc(points+1,sizeof(Edge));
		if(!s || !active) return (-2);
		mostpoints = points;
	}

	sortpt = poly;												// initialize sorting pointer

																				// initialize index array.
	for(i = 0 ; i < points; i++) {
		*(s+i) = i;
	}
	qsort(s,points,sizeof(int),compare_ind);  // sort the indices

	nact = 0;															// start with empty active list
	k = 0;																// *(s+k) is next (sorted) vertex to
																				// process.

																				// Loop from the top of the polygon
																				// to the bottom.  Each time a
																				// vertex is reached, add or subtract
																				// active edges as necessary.
	for (y=sortpt[*s].y; y< sortpt[*(s+points-1)].y; y++) {
		while(sortpt[*(s+k)].y < y) {       // Any vertices on this scanline?

																				// Check slope of line from this
																				// vertex to next point.  Positive
																				// slope means the edge is beind us,
																				// so we can delete it.
			if (*(s+k) == points-1) attitude = y - sortpt[0].y;
			else attitude = y - sortpt[*(s+k)+1].y;

			if (attitude > 0 ) cdelete(*(s+k),&nact,active);	// delete edge
			else   {                   				// add edge to active list
				if(*(s+k)==points-1) cinsert(*(s+k),0,y,&nact,active);
				else cinsert(*(s+k),*(s+k)+1,y,&nact,active);
			}

																				//  check the prev point
			if (*(s+k) == 0) attitude = y - sortpt[points-1].y;
			else attitude = y - sortpt[*(s+k)-1].y;

			if (attitude > 0 ) {             // delete edge
				if (*(s+k) == 0) cdelete(points-1,&nact,active);
				else cdelete(*(s+k)-1,&nact,active);
			}
			else {                            // add edge to active list
				if (*(s+k) == 0) cinsert(points-1,0,y,&nact,active);
				else cinsert(*(s+k)-1,*(s+k),y,&nact,active);
			}

			k++;                              // advance to next vertex
			if(k == points) return;           // end condition

			sortflag = 1;                     // Change in vertices means that
																				// We sould sort them again.
		}
																				// Sort the edge list.  If none of
																				// edges cross, the it is only
																				// necessary to sort when the edge
																				// list changes.
		if((assume_nocross && sortflag) || (!assume_nocross))
			qsort(active, nact, sizeof(Edge), compare_active);
		sortflag = 0;


		for(j= 0; j<nact; j+= 2) {          // draw the scanline segments
			rx = ((active[j+1].x)>>10);               // right x value for segment
			drwline(SET,color,(active[j].x)>>10,y,rx,y);   // draw it
			active[j].x += active[j].dx;      // update x values for segement
			active[j+1].x += active[j+1].dx;
		}
	}
}
*/
/**************************************************************************
	compare_ind,compare_active

	DESCTRIPTION: Used by scanconvetpoly().  These functions are used for
								sorting indeces/edges with qsort.

**************************************************************************/
/*int compare_ind(const void *a,const void *b)
{
	if(sortpt[*((int *)a)].y < sortpt[*((int *)b)].y) return -1;
	else if(sortpt[*((int *)a)].y > sortpt[*((int *)b)].y) return 1;
	return(0);
}

int compare_active(const void *u,const void *v)
{
	if(((Edge *)u)->x <= ((Edge *)v)->x) return(1);
	else return  -1;
} */


/**************************************************************************
	void cdelete(int i)

	DESCTRIPTION:  Used by scanconvertpoly() to remove edge i from active list

**************************************************************************/
/*void cdelete(int i,int *nact, Edge active[])
{
		int j;
		for (j=0; j<*nact && active[j].i!=i; j++);
		if (j>=*nact) return;	// edge not in active list
		(*nact)--;
		memcpy(&active[j],&active[j+1],(*nact-j)*sizeof(Edge));
} */

/**************************************************************************
	void cdelete(int i)

	DESCTRIPTION:  Used by scanconvertpoly() toappend edge i to end
								 of active list.

**************************************************************************/
/*void cinsert(int i,int head,int y,int *nact,Edge active[])
{
	double islope;
	long int x1,x2,y1,y2;
					// find the slope
	y1 = sortpt[i].y;
	y2 = sortpt[head].y;
	x1 = sortpt[i].x;
	x2 = sortpt[head].x;
	islope = ((double)x2-x1)/(y2-y1);
	active[*nact].x = (long int)(islope * (y-y1) + x1)<<10;
	active[*nact].i = i;
	active[*nact].dx = islope*1024;

	(*nact)++;
}  */
/***************************************************************************
	textheight(string);

	DESCRIPTION: returns the height of a string in pixels.  Right now it
								returns a constant because SVGACC has limited font
								capabilities.

****************************************************************************/
int textheight(char *string)
{
	int width,height,i,t;

	fontgetinfo(&width,&height);
	t = 1;
	for(i = 0 ; i < strlen(string); i++) {     // count number of linefeeds
		if(*(string+i) == '\n') {
			t++;
		}
	}
	return(height*t);                          // return total eight
}
/***************************************************************************
	textwidth(string);

	DESCRIPTION: returns the width of a string in pixels.  Right now it
								returns a quasi-constant because SVGACC has limited font
								capabilities.

****************************************************************************/
int textwidth(char *string)
{
	int width,height;

	fontgetinfo(&width,&height);
	return(width*strlen(string));
}
/*************************************************************************
	setcol(p,r,g,b);

	DESCRIPTION: macro for setting rgb values

****************************************************************************/
void setcol(RGB *p,int r, int g, int b)
{
	p->r = r;
	p->b = b;
	p->g = g;
}

/***************************************************************************
	print(pmode,color,x,y,*s,...)

	DESCRIPTION: This draws a string without changing the background color.

  INPUTS:
  	pmode			Drawing mode
    color			Drawing color
    x,y				Upper left of text
    *s				Format string
    ...				Optional arguments (Just like printf)

								NOTE:  normally, I make sure that any function that I
								write that changes graphics includes a mousehide()
								and mouseshow(), but I am making a special exception
								for this since I want print() to go faster.  Plus
								printf() is much more like a primitive anyway.

****************************************************************************/
void print(PixelMode pmode, int color, int x, int y, char *s, ...)
{
	int i,w,h,xx = x, yy = y;
	va_list ap;
  static char string[1024];

  va_start(ap, s);                  		// sort out variable argument list
	vsprintf(string,s,ap);      					// dump output to a string

																				// make sure font is avail by pointing
																				// to default font
	if(!fontpointer) fontpointer = (byte *)MK_FP(fontseg,fontoff);

																				// check for NULL string pointer
	if(!string) {
		va_end(ap);                         // clean up
		return;
  }

	fontgetinfo(&w,&h);          					// get font size

	for(i=0; i < strlen(string); i++) {   // loop through the string
		if(string[i] == '\t') xx += w*TAB;  // tab? 5 spaces
		else if (string[i] == '\n') {       // return?  newline
			xx = x;
			yy += h;
		}
		else drwchar(pmode,color,xx,yy,string[i]);  // default- draw the char
		xx += w;
	}
  va_end(ap);                            // clean up

}

/***************************************************************************
	drwchar(pmode,color,x,y,c)

	DESCRIPTION: Draws a character without altering background.

								NOTE:  normally, I make sure that any function that I
								write that changes graphics includes a mousehide()
								and mouseshow(), but I am making a special exception
								for this since I want print() to go faster.

****************************************************************************/
void drwchar(PixelMode pmode, int color, int x, int y, char c)
{
	int w,h,xx;
	byte *b,bb;

	fontgetinfo(&w,&h);          					// get font size
	h += y;                               // create pseudo values (for speed)
	w += x;

	b = (byte *)(fontpointer + c*16);     // get character data location

	for(; y <= h+1; y++) {                   // loop through scan lines
		bb = *b;                            // grab the byte for this line
		for(xx = x; xx < w; xx++) {         // loop through pixels
			if(bb & 0x80) drwpoint(pmode,color,xx,y); // draw if set
			bb = bb << 1;                     // move to next pixel
		}
		b++;                                // move to next line
	}
}

/*************************************************************************
	inkey();

	DESCRIPTION: Works like the BASIC function inkey$. It returns the top
							 character in the keyboard buffer, and NULL if the buffer
							 is empty.

**************************************************************************/
char inkey(void)
{
	if(kbhit()) {
		return(getch());
	}
	else return 0;
}
