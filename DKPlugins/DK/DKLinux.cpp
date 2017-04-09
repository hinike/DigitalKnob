#include "stdafx.h"
#ifdef LINUX
#include "DKLinux.h"
#include "DKLog.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>


/////////////////////////////////////////
bool DKLinux::GetMousePos(int& x, int& y)
{
	//Compile with:
    //cc -Wall -I/usr/X11R6/include -L/usr/X11R6/lib -lXm -o xquerypointer xquerypointer.c
	//or on solaris:
    //cc -I/usr/openwin/include xquerypointer.c -L/usr/openwin/lib -lX11
	
	Display *dpy;
	Window root;
	Window ret_root;
	Window ret_child;
	int root_x;
	int root_y;
	int win_x;
	int win_y;
	unsigned int mask;
 
	dpy = XOpenDisplay(NULL);
	root = XDefaultRootWindow(dpy);
 
	if(XQueryPointer(dpy, root, &ret_root, &ret_child, &root_x, &root_y, &win_x, &win_y, &mask)){
		// original version
		//    printf("root loc: %4d,%4d win loc: %3d,%3d mask: 0x%08X\n", root_x, root_y, win_x, win_y, mask);
		// This returns in -geometry format
		// I added \n so it actually shows something so people who test it know it works.
		x = root_x;
		y = root_y;
		return true;
	}
	
	x = 0;
	y = 0;
	return false;
}

//////////////////////////////////////////
bool DKLinux::Run(const DKString& command)
{
	DKString cmd = command;
	cmd = "xdg-open "+cmd+" &";
	system(cmd.c_str());
	//execl(cmd.c_str(), (char*)0);
	return true;
}

//////////////////////////////
bool DKLinux::KeyIsDown(int& key)
{
	//TODO - character keys
	DKLog("DKLinux::KeyIsDown("+toString(key)+")\n", DKDEBUG);
	
	XkbStateRec r;
    Display* d = XOpenDisplay(NULL);
    XkbGetState(d, XkbUseCoreKbd, &r);
    //printf("mod: 0x%x\n", r.mods);
	if((r.mods & 0x01) && key == 16){ //Shift
		return true;
	}
	if((r.mods & 0x04) && key == 17){ //Ctrl
		return true;
	}
	if((r.mods & 0x08) && key == 18){ //Alt
		return true;
	}
    XCloseDisplay(d);
	return false;
}

////////////////////////
bool DKLinux::GetClipboard(DKString& text)
{
	//TODO
	DKLog("DKLinux::GetClipboard()\n", DKINFO);
	DKClass::CallFunc("DKSDLWindow::GetClipboard", NULL, &text);
	return true;
}

///////////////////////
bool DKLinux::SetClipboard(DKString& text)
{
	//TODO
	DKLog("DKLinux::SetClipboard("+text+")\n", DKINFO);
	DKClass::CallFunc("DKSDLWindow::SetClipboard", &text, NULL);
	return false;
}

bool DKLinux::ChangeVolume(double nVolume)
{
	//TODO
	DKLog("DKLinux::ChangeVolume(): not implemented\n", DKERROR);
	return false;
}

bool DKLinux::GetVolume(float& volume)
{
	//TODO
	DKLog("DKLinux::GetVolume(): not implemented\n", DKERROR);
	return false;
}


#endif //LINUX