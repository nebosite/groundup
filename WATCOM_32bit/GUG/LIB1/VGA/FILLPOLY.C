#include "stdio.h"

#define FALSE 0
#define TRUE  1 

typedef struct  {
  int x;
  int y;
}GUGVertex;

typedef struct  {
	int i;
	long int x,dx;
} Edge;
    
int  GUGFillPoly(int color, int points, GUGVertex poly[]);

// Internal Functions
int  GUG_poly_cmp_ind(const void *a,const void *b);
int  GUG_poly_cmp_act(const void *u,const void *v);
void GUG_poly_c_del(int i,int *nact, Edge active[]);
void GUG_poly_c_ins(int i,int head,int y,int *nact,Edge active[]);

GUGVertex *sortpt;
int GUG_Poly_No_Cross = TRUE;

/**************************************************************************
  void GUGFillPoly(int color, int points, GUGVertex poly[])

  DESCTRIPTION: Scan converts a polygon of any shape.


  RETURNS:

    -1 Number of points inncorrectly specified
    -2 Not enough memory

**************************************************************************/
int GUGFillPoly(int color, int points, GUGVertex poly[])
{
  int i,j,k,nact,y,rx,dx,sortflag = 0;
  int attitude;
  static int *s= NULL,mostpoints = 0;   // sort array and point counter
  static Edge *active;                  // active edge array
  char *string;

  if(points < 1) return(-1);            // sanity check

                                        // Allocate memory for sorted
                                        // indeces and Edges. The allocated
                                        // memory is static so that we
                                        // don't have to keep reallocating
                                        //  it every time.

  if(!s) {                              // First time here?
    s = (int *)calloc(points+1,sizeof(int));
    active = (Edge *)calloc(points+1,sizeof(Edge));
    if(!s || !active) return (-2);
    mostpoints = points;
	}
  else if(mostpoints < points) {        // enough memory for this polygon?
    free(s);
    free(active);
    s = (int *)calloc(points+1,sizeof(int));
    active = (Edge *)calloc(points+1,sizeof(Edge));
    if(!s || !active) return (-2);
    mostpoints = points;
  }

  sortpt = poly;                        // initialize sorting pointer

                                        // initialize index array.
  for(i = 0 ; i < points; i++) {
    *(s+i) = i;
  }
  qsort(s,points,sizeof(int),GUG_poly_cmp_ind);  // sort the indices

  nact = 0;                              // start with empty active list
  k = 0;                                // *(s+k) is next (sorted) vertex to
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

      if (attitude > 0 ) GUG_poly_c_del(*(s+k),&nact,active);  // delete edge
      else   {                           // add edge to active list
        if(*(s+k)==points-1) GUG_poly_c_ins(*(s+k),0,y,&nact,active);
        else GUG_poly_c_ins(*(s+k),*(s+k)+1,y,&nact,active);
      }

                                        //  check the prev point
      if (*(s+k) == 0) attitude = y - sortpt[points-1].y;
      else attitude = y - sortpt[*(s+k)-1].y;

      if (attitude > 0 ) {             // delete edge
        if (*(s+k) == 0) GUG_poly_c_del(points-1,&nact,active);
        else GUG_poly_c_del(*(s+k)-1,&nact,active);
      }
      else {                            // add edge to active list
        if (*(s+k) == 0) GUG_poly_c_ins(points-1,0,y,&nact,active);
        else GUG_poly_c_ins(*(s+k)-1,*(s+k),y,&nact,active);
      }

      k++;                              // advance to next vertex
      if(k == points) return(0);           // end condition

      sortflag = 1;                     // Change in vertices means that
                                        // We sould sort them again.
    }
                                        // Sort the edge list.  If none of
                                        // edges cross, the it is only
                                        // necessary to sort when the edge
                                        // list changes.
    if((GUG_Poly_No_Cross && sortflag) || (!GUG_Poly_No_Cross))
      qsort(active, nact, sizeof(Edge), GUG_poly_cmp_act);
    sortflag = 0;

		for(j= 0; j<nact; j+= 2) {          // draw the scanline segments
      rx = ((active[j+1].x)>>10);               // right x value for segment

        GUGHLine((active[j].x)>>10,rx,y,color);

      active[j].x += active[j].dx;      // update x values for segement
      active[j+1].x += active[j+1].dx;
    }
  }
  return(0);
}

/**************************************************************************
  GUG_poly_cmp_ind,GUG_poly_cmp_act

  DESCTRIPTION: Used by scanconvetpoly().  These functions are used for
                sorting indeces/edges with qsort.

**************************************************************************/
int GUG_poly_cmp_ind(const void *a,const void *b)
{
  if(sortpt[*((int *)a)].y < sortpt[*((int *)b)].y) return -1;
  else if(sortpt[*((int *)a)].y > sortpt[*((int *)b)].y) return 1;
  return(0);
}

int GUG_poly_cmp_act(const void *u,const void *v)
{
  if(((Edge *)u)->x <= ((Edge *)v)->x) return(1);
  else return  -1;
}


/**************************************************************************
  void GUG_poly_c_del(int i)

	DESCTRIPTION:  Used by scanconvertpoly() to remove edge i from active list

**************************************************************************/
void GUG_poly_c_del(int i,int *nact, Edge active[])
{
    int j;
    for (j=0; j<*nact && active[j].i!=i; j++);
    if (j>=*nact) return;  // edge not in active list
    (*nact)--;
		memcpy(&active[j],&active[j+1],(*nact-j)*sizeof(Edge));
}

/**************************************************************************
	void GUG_poly_c_del(int i)

	DESCTRIPTION:  Used by scanconvertpoly() toappend edge i to end
								 of active list.

**************************************************************************/
void GUG_poly_c_ins(int i,int head,int y,int *nact,Edge active[])
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
}

