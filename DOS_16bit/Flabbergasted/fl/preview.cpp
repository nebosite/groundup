
#include "stdafx.h"
#include <windows.h>
#include "resource.h"

/*** FUNCTION HEADER *********************************************************
*	LRESULT CALLBACK PreviewWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
* 
*   DESCRIPTION:	Handles messages for the preview window.  

* [REVISIONS]
*		6/24/98		Eric Jorgensen		InitialVersion
*
\******************************************************************************/
LRESULT CALLBACK PreviewWindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{ 
	HDC hdc,hdcImage = NULL;
	HBITMAP hbm = NULL;
	static int f = 0;

	switch (msg) { 
								// When we get a timer message, we just draw
					 			// a bitmap in the preview window 
	case WM_TIMER:
		{
								// Get dimensions of the window
			RECT rc;
			GetWindowRect(hwnd,&rc);
			int cx=rc.right-rc.left; 
			int	cy=rc.bottom-rc.top;

								// Make sure bitmap is loaded
			if(!hbm) hbm = (HBITMAP)LoadImage(
										GetModuleHandle(NULL), 
										MAKEINTRESOURCE(IDB_PREVIEW), 
										IMAGE_BITMAP, 
										0, 
										0, 
										LR_CREATEDIBSECTION
										);
 			if(!hbm) break;

								// Make sure bitmap is selected into a memory context
			if(!hdcImage) {
				hdcImage = CreateCompatibleDC(NULL);
				SelectObject(hdcImage, hbm);
			}
			if(!hdcImage) break;
								// Set bitmap dimensions (You need to set these
								// by hand, I have yet to find a convenient way
								// to get the dimensions of a bitmap resource!)
								// Note:  152x112 is the size of the preview window
			int bw = 152, bh = 112;
			int x,y;
								// Figure out which part of the bitmap to show
			switch(f%4) {
			case 0: x = 0;		y = 0;		break;
			case 1: x = bw;	y = 0;		break;
			case 2: x = 0;		y = bh;	break;
			case 3: x = bw;	y = bh;	break;
			}
			f++;
								// Blit the bitmap to the screen


			hdc = GetDC(hwnd);
			if(hdc) StretchBlt(hdc, 0, 0, cx, cy, hdcImage, x, y, bw, bh, SRCCOPY);
			ReleaseDC(hwnd,hdc);				 
		}
		break;
								// The destroy message comes when the preview
								// window is getting shut down.
	case WM_DESTROY:
		PostQuitMessage(0);
		if(hdcImage) {
			DeleteDC(hdcImage);
			DeleteObject(hbm);
		}
		break;
  }
								// Handle all other messages...
  return DefWindowProc(hwnd,msg,wParam,lParam);	   
}

/*** FUNCTION HEADER *********************************************************
	void runminidemo(HINSTANCE hInstance,HWND hparent)
* 
*   DESCRIPTION:	Operates the screen saver inside a teeny tiny window
					provided by the main screen saver dialog.  Since a DirectX app
					has to worry about conflicting video modes, we are just going
					to show a bitmap here.
*
* [REVISIONS]
*		6/12/98		Eric Jorgensen		InitialVersion
*
\******************************************************************************/
void runminidemo(HINSTANCE hInstance,HWND hparent)
{
	RECT rc; 
	HWND hpreviewwnd;
	int cx,cy;
	WNDCLASS wc;   
								// Set up a windows class for the preview window
	wc.style=CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc=PreviewWindowProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=NULL;
	wc.hCursor=NULL;
	wc.hbrBackground=NULL;//(HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName="PreviewScrClass";
	RegisterClass(&wc);

								// Create a child window
	GetWindowRect(hparent,&rc);
    cx=rc.right-rc.left; 
	cy=rc.bottom-rc.top;
	
    hpreviewwnd=CreateWindowEx(
		0,
		"PreviewScrClass",
		"SaverPreview",
		WS_CHILD|WS_VISIBLE,
		0,
		0,
		cx,
		cy,
		hparent,
		NULL,
		hInstance,
		NULL
	);
												 
	if(!hpreviewwnd) return;

	SetTimer(hpreviewwnd,1,250,NULL);
								// Pump the message loop
	MSG         msg;
	while (GetMessage(&msg,NULL,0,0)){ 
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hpreviewwnd,1);

}
