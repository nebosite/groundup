// ROUTINE.H
//
// Routine (virtual base) Class for handling a linked list
// of drawing routines
//

#define NULL 0

#ifndef Flabbergasted_Routine
#define Flabbergasted_Routine

//-------------------------------------- VARPACKET class -----
typedef struct{
	int 		color,colorbase;
	double 	x1,y1,x2,y2,x3,y3;
	double 	dx,dy;
	int   	d1,d2,d3;
	int   	w,h,r;

}VARPACKET;

//-------------------------------------- CRoutine Class -----

class CRoutine {

	CRoutine *next,*prev;

public:
	VARPACKET vp;
	int 	counter;
	int   colorcounter;
	int 	started;
	int 	frames_per_draw;
	int   framecount;

	CRoutine(VARPACKET &packet) {
		vp = packet;
		next = prev = NULL;
		started = counter = 0;
		colorcounter = 10000;
		frames_per_draw = 1;
	}
	virtual ~CRoutine() {}

	virtual int draw() = 0;
																// Adds this to end of specified link chain
	void addtochain(CRoutine *link) {
		CRoutine *temp = link;
		while(temp->next) temp = temp->next;
		next = temp->next;
		prev = temp;
		temp->next = this;
	}
	void unlinkme() {
		if(prev) prev->next = next;
		if(next) next->prev = prev;
		prev = next = NULL;
	}
	CRoutine *Next() {return next;}
	CRoutine *Prev() {return prev;}
};

//-------------------------------------- CBoxesDraw Class -----

class CBoxesDraw : public CRoutine
{
	public:
	CBoxesDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

//-------------------------------------- CCoinDraw Class -----

class CCoinDraw : public CRoutine
{
	public:
	CCoinDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

//-------------------------------------- CTargetDraw Class -----

class CTargetDraw : public CRoutine
{
	public:
	CTargetDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

//-------------------------------------- CConeDraw Class -----

class CConeDraw : public CRoutine
{
	public:
	CConeDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};
//-------------------------------------- CCheckerBall Class -----

class CCheckerBall : public CRoutine
{
	int k,color1,color2;

	public:
	CCheckerBall(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};
//-------------------------------------- CStarBurstDraw Class -----

class CStarBurstDraw : public CRoutine
{

	public:
	CStarBurstDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};
//-------------------------------------- CSpiralBarDraw Class -----

class CSpiralBarDraw : public CRoutine
{
	int angle;
	public:
	CSpiralBarDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

//-------------------------------------- CTreeDraw Class -----

class CTreeDraw : public CRoutine
{
	int width,angle;
	public:
	CTreeDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};
//-------------------------------------- CBallDraw Class -----

class CBallDraw : public CRoutine
{
	int t;
	public:
	CBallDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

//-------------------------------------- CSpiralDraw Class -----

class CSpiralDraw : public CRoutine
{
	double dr,dt,radius,theta;
	public:
	CSpiralDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

//-------------------------------------- CFireWorkDraw Class -----

#define MAX_SPARKS 100

class CFireWorkDraw : public CRoutine
{
private:
	int type,numactive,stage,nextcolor[10];
	float xm[MAX_SPARKS],
				ym[MAX_SPARKS],
				x[MAX_SPARKS],
				y[MAX_SPARKS];
	int   scount[MAX_SPARKS];
	int   sswitch[MAX_SPARKS];
	BYTE  scolor[MAX_SPARKS];

public:

	static int iNumFireworks;

	CFireWorkDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();
	void stage1(void);
	void stage2(void);
	void stage3(void);

};

//-------------------------------------- CBounceDraw Class -----

class CBounceDraw : public CRoutine
{
private:
	float gravity,bounciness;
public:

	static int iNumBalls;

	CBounceDraw(VARPACKET &packet) : CRoutine(packet) {}
	int draw();

};

#endif
