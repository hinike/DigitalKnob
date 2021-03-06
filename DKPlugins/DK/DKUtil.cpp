#include "stdafx.h"
#include "DKUtil.h"
#include "DKLog.h"
#include "DKFile.h"
#include <iostream>

#ifdef WIN32
	#include "DKWindows.h"
#else
	#include "DKUnix.h"
#endif

#ifdef LINUX
	#include "DKLinux.h"
#endif 

#ifdef ANDROID
	#include "DKAndroid.h"
#endif 

#ifdef MAC
	#include "DKMac.h"
#endif
	
#include <boost/asio.hpp>

#include <iostream>
#ifndef MAC
#include <fstream>
#endif
#include <math.h>
#include <assert.h>



unsigned long int DKUtil::mainThreadId = 0;


///////////////////////////////
bool DKUtil::SetMainThreadNow()
{
	//ONLY SET THIS FROM THE MAIN THREAD ONCE
#ifdef WIN32
	return DKWindows::SetMainThreadNow(DKUtil::mainThreadId);
#endif
#ifdef UNIX
	return DKUnix::::SetMainThreadNow(DKUtil::mainThreadId);
#endif
/*/
#if defined(MAC)
	//DKUtil::mainThreadId = (unsigned long int)pthread_self();
	return DKMac::::SetMainThreadNow(DKUtil::mainThreadId);
#endif
#if defined(LINUX) || defined (IOS)
	DKUtil::mainThreadId = (unsigned long int)pthread_self();
#endif
*/
	DKLog("DKUtil::SetMainThreadNow() not implemented on this OS \n", DKERROR);
	return false;
}

///////////////////////////////////////////////
bool DKUtil::GetThreadId(unsigned long int& id)
{
#ifdef WIN32
	return DKWindows::GetThreadId(id);
#endif
#ifdef UNIX
	return DKUnix::GetThreadId(id);
#endif
/*
#if defined(MAC)
	//id = (unsigned long int)pthread_self();
	//return true;
	return DKMac::GetThreadId(id);
#endif
#if defined(LINUX) || defined (IOS)
	id = (unsigned long int)pthread_self();
	return true;
#endif
*/
	DKLog("DKUtil::GetThreadId() not implemented on this OS \n", DKERROR);
	return false;
}

///////////////////////////////////////////////
bool DKUtil::SetClipboard(DKString& text)
{
#ifdef WIN32
	return DKWindows::SetClipboard(text);
#endif
#ifdef LINUX
	return DKLinux::SetClipboard(text);
#endif
	DKLog("DKUtil::SetClipboard() not implemented on this OS \n", DKERROR);
	return false;
}

/////////////////////////////////////////
bool DKUtil::GetClipboard(DKString& text)
{
#ifdef WIN32
	return DKWindows::GetClipboard(text);
#endif
#ifdef LINUX
	return DKLinux::GetClipboard(text);
#endif
	DKLog("DKUtil::GetClipboard() not implemented on this OS \n", DKERROR);
	return false;
}

////////////////////////////////////////////////////////
bool DKUtil::SetClipboardFiles(const DKString& filelist)
{
#ifdef WIN32
	return DKWindows::SetClipboardFiles(filelist);
#endif
	DKLog("DKUtil::SetClipboardFiles() not implemented on this OS \n", DKERROR);
	return false;
}

/////////////////////////////////////////////////////////////////////
bool DKUtil::GetPixelFromScreen(int x, int y, int& r, int& g, int& b)
{
#ifdef WIN32
	return DKWindows::GetPixelFromScreen(x, y, r, g, b);
#endif
	DKLog("DKUtil::GetPixelFromScreen() not implemented on this OS \n", DKERROR);
	return false;
}

///////////////////////////////////////////////////////////////////
bool DKUtil::GetPixelFromImage(const DKString& image, int x, int y)
{
#ifdef WIN32
	return DKWindows::GetPixelFromImage(image, x, y);
#endif
	DKLog("DKUtil::GetPixelFromImage() not implemented on this OS \n", DKERROR);
	return false;
}

////////////////////////////////////////////////////////////
bool DKUtil::WaitForImage(const DKString& file, int timeout)
{
#ifdef WIN32
	return DKWindows::WaitForImage(file, timeout);
#endif
	DKLog("DKUtil::WaitForImage() not implemented on this OS \n", DKERROR);
	return false;
}

/////////////////////////////////////////////////////////////////////
bool DKUtil::FindImageOnScreen(const DKString& file, int& x, int& y)
{
#ifdef WIN32
	return DKWindows::FindImageOnScreen(file, x, y);
#endif
	DKLog("DKUtil::FindImageOnScreen() not implemented on this OS \n", DKERROR);
	return false;
}

////////////////////////////////////////////////////
bool DKUtil::SetMousePos(const int& x, const int& y)
{
#ifdef WIN32
	return DKWindows::SetMousePos(x, y);
#endif
	DKLog("DKUtil::SetMousePos() not implemented on this OS \n", DKERROR);
	return false;
}


////////////////////////////////////////
bool DKUtil::GetMousePos(int& x, int& y)
{
#ifdef WIN32
	return DKWindows::GetMousePos(x, y);
#endif
#ifdef LINUX
	return DKLinux::GetMousePos(x, y);
#endif
#ifdef ANDROID
	return DKAndroid::GetMousePos(x, y);
#endif
#ifdef MAC
	//return DKMac::GetMousePos(x, y);
#endif
	DKLog("DKUtil::GetMousePos() not implemented on this OS \n", DKERROR);
	x = 0;
	y = 0;
	return false;
}


////////////////////////
bool DKUtil::LeftClick()
{
#ifdef WIN32
	return DKWindows::LeftClick();
#endif
	DKLog("DKUtil::LeftClick() not implemented on this OS \n", DKERROR);
	return false;
}

//////////////////////////
bool DKUtil::DoubleClick()
{
#ifdef WIN32
	DKWindows::LeftClick();
	return DKWindows::LeftClick();
#endif
	DKLog("DKUtil::DoubleClick() not implemented on this OS \n", DKERROR);
	return false;
}

/////////////////////////
bool DKUtil::RightClick()
{
#ifdef WIN32
	return DKWindows::RightClick();
#endif
	DKLog("DKUtil::RightClick() not implemented on this OS \n", DKERROR);
	return false;
}

////////////////////////////////////
bool DKUtil::Sleep(int milliseconds)
{
#ifdef WIN32
	return DKWindows::Sleep(milliseconds);
#else
	return DKUnix::Sleep(milliseconds);
#endif
	return false;
}

////////////////////////////////////
bool DKUtil::GetTicks(double& ticks)
{
	//boost::posix_time::ptime tick = boost::posix_time::second_clock::local_time();
	//boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	//boost::posix_time::time_duration diff = tick - now;
	//return (double)diff.total_milliseconds();

#ifdef WIN32
    ticks = GetTickCount();
	return true;
#else
    struct timeval tv;
    gettimeofday(&tv, 0);
    ticks = unsigned((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return true;
#endif
}

/////////////////////////////////////
bool DKUtil::GetTime(DKString& _time)
{
	time_t t = time(0);   // get time now
    struct tm * now = localtime(&t);

	
	int standard = now->tm_hour % 12;
	if(standard == 0){ standard = 12; }
	_time = toString(standard);
	_time += ":";
	DKString minute = toString(now->tm_min);
	Pad(2, '0', minute);
	_time += minute;
	//DKLog("DKUtil::GetTime(): now->tm_hour="+toString(now->tm_hour)+"\n", DKDEBUG);
	if(now->tm_hour > 12 || (now->tm_hour % 12) == 0){
		_time += " PM";
	}
	else{
		_time += " AM";
	}

	return true;
}

////////////////////////////////////
bool DKUtil::GetDate(DKString& date)
{
	time_t t = time(0);   // get time now
    struct tm * now = localtime(&t);

	int standard = now->tm_hour % 12;
	date = toString(now->tm_mon+1);
	date += "/";
	DKString day = toString(now->tm_mday);
	//Pad(2, '0', day);
	date += day;
	date += "/";
	date += toString(now->tm_year + 1900);

	return true;
}

/////////////////////////////
bool DKUtil::GetKey(int& key)
{
#if defined(WIN32)
	return DKWindows::GetKey(key);
#endif
#if defined(MAC)
	return DKUnix::GetKey(key);
#endif
#if defined(IOS)
	return DKUnix::GetKey(key);
#endif
#if defined(LINUX)
	return DKUnix::GetKey(key);
#endif
#if defined(ANDROID)
	DKLog("DKUtil::GetKey(): not implemented on Android \n", DKERROR);
#endif
	return false;
}

//////////////////////////////
bool DKUtil::PressKey(int key)
{
#ifdef WIN32
	return DKWindows::PressKey(key);
#endif
	DKLog("DKUtil::PressKey(): not implemented on this OS \n", DKERROR);
	return false;
}

////////////////////////////////
bool DKUtil::ReleaseKey(int key)
{
#ifdef WIN32
	return DKWindows::ReleaseKey(key);
#endif
	DKLog("DKUtil::ReleaseKey(): not implemented on this OS \n", DKERROR);
	return false;
}

///////////////////////////////
bool DKUtil::StrokeKey(int key)
{
#ifdef WIN32
	DKWindows::PressKey(key);
	return DKWindows::ReleaseKey(key);
#endif
	DKLog("DKUtil::StrokeKey(): not implemented on this OS \n", DKERROR);
	return false;
}

/////////////////////////////////////
bool DKUtil::GetLocalIP(DKString& ip)
{
	boost::asio::io_service io_service; 
	boost::asio::ip::tcp::resolver resolver(io_service); 
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), boost::asio::ip::host_name(), ""); 
	boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
	boost::asio::ip::tcp::endpoint endpoint = *it; 

    ip = endpoint.address().to_string();
	return true;
}

/////////////////////////////////////////
bool DKUtil::ChangeVolume(double& volume)
{
#ifdef WIN32
	return DKWindows::ChangeVolume(volume);
#endif
#ifdef LINUX
	return DKLinux::ChangeVolume(volume);
#endif
	DKLog("DKUtil::ChangeVolume() not implemented on this OS OS \n", DKERROR);
	return false;
}

/////////////////////////////////////
bool DKUtil::GetVolume(float& volume)
{
#ifdef WIN32
	return DKWindows::GetVolume(volume);
#endif
#ifdef LINUX
	return DKLinux::GetVolume(volume);
#endif
	DKLog("DKUtil::GetVolume() not implemented on this OS \n", DKERROR);
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
bool DKUtil::C2Bin(const unsigned char* header, const long int size, const DKString& output)
{
#ifndef MAC
	std::basic_ofstream<unsigned char> file(output.c_str(), std::ios::binary);
	file.write(header, size);
	file.close();
	return true;
#endif //!MAC
return false;
}

/////////////////////////////////////////////////////////////////
bool DKUtil::Bin2C(const DKString& input, const DKString& output)
{
#ifndef MAC
	char *buf;
    const char* ident  = "assets";
    unsigned int i, file_size, need_comma;
    FILE *f_input, *f_output;

	f_input = fopen(input.c_str(), "rb");
    if (f_input == NULL) {
        printf("can't open file for reading\n");
        return false;
    }

	// Get the file length
    fseek(f_input, 0, SEEK_END);
    file_size = ftell(f_input);
    fseek(f_input, 0, SEEK_SET);
    file_size++;

    buf = (char *)malloc(file_size);
    assert(buf);   

    fread(buf, file_size, 1, f_input);
    fclose(f_input);
	f_output = fopen(output.c_str(), "w");
    if (f_output == NULL){
        printf("can't open file for writing\n");
        return false;
    }

    //ident = "assets";
    need_comma = 0;
    fprintf (f_output, "const unsigned char %s[%i] = {", ident, file_size);

    for (i = 0; i < file_size; ++i){
        if (need_comma) fprintf(f_output, ", ");
        else need_comma = 1;
        if (( i % 11 ) == 0) fprintf(f_output, "\n\t");
        fprintf(f_output, "0x%.2x", buf[i] & 0xff);
    }
	fprintf(f_output, "\n};\n\n");
    fprintf(f_output, "const int %s_size = %i;\n", ident, file_size);

	fclose(f_output);
	return true;
#endif //!MAC
return false;
}

/////////////////////////////////////////
bool DKUtil::Run(const DKString& command)
{
	DKLog("DKUtil::Run("+command+")\n", DKDEBUG);
#ifdef WIN32
	ShellExecute(NULL,NULL,command.c_str(),NULL,NULL,SW_SHOWNORMAL); //TODO: error control
	return true;
#endif
#ifdef LINUX
	return DKLinux::Run(command);
#endif
	DKLog("DKUtil::Run() not implemented on this OS. \n", DKERROR);
	return false;
}

///////////////////////////////////////////
bool DKUtil::System(const DKString& command)
{
	DKLog("DKUtil::System("+command+")\n", DKDEBUG);
	int rval = system(command.c_str());
	//DKLog("DKUtil::System(): returned "+toString(rval)+"\n", DKDEBUG);
	return true;
}

////////////////////////////////////////////////////////////
bool DKUtil::Execute(const DKString& command, DKString& rtn)
{
	DKLog("DKUtil::Execute("+command+")\n", DKDEBUG);

#ifdef WIN32
	FILE* pipe = _popen(command.c_str(), "r");
    if(!pipe){
		DKLog("DKUtil::Execute(): Error, pipe invalid.", DKERROR);
		return "ERROR";
	}
    char buffer[128];
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		rtn += buffer;
			DKLog(buffer, DKINFO);
    }
    _pclose(pipe);
    return true;
#else
	FILE* pipe = popen(command.c_str(), "r");
    if(!pipe){
		DKLog("DKUtil::Execute(): Error, pipe invalid.", DKERROR);
		return "ERROR";
	}
    char buffer[128];
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		rtn += buffer;
			DKLog(buffer, DKINFO);
    }
    pclose(pipe);
    return true;
#endif

	return "";
}

///////////////////////////
bool DKUtil::InMainThread()
{
	//DKString pid = "mainThreadId: "+toString(mainThreadId)+"\n";
	//DKLog(pid, DKINFO); DO NOT DO THIS!

#ifdef WIN32
	DKString tid = "GetCurrentThreadId()(): "+toString((int)GetCurrentThreadId())+"\n";
	//DKLog(tid, DKINFO); DO NOT DO THIS!
	return mainThreadId == GetCurrentThreadId();
#endif
#if defined(MAC)
	return mainThreadId == (unsigned long int)pthread_self();
#endif
#if defined (IOS) || defined (ANDROID) //|| defined(LINUX)
	DKString tid = "GetCurrentThreadId()(): "+toString((unsigned int)pthread_self())+"\n";
	//DKLog(tid, DKINFO); DO NOT DO THIS!
	return mainThreadId == (unsigned long int)pthread_self();
#endif
	return false;
}

///////////////////////////////
bool DKUtil::round(double& num)
{
	num = floor(num + 0.5);
	return true;
}

///////////////////////////////
bool DKUtil::Round(double& num)
{
    num = (num < 0.0 ? ceil(num - 0.5) : floor(num + 0.5));
	return true;
}

///////////////////
bool DKUtil::Beep()
{
    std::cout << '\a' << std::flush;
	return true;
}

///////////////////////////////////////////
bool DKUtil::GetProcessList(DKString& list)
{
	DKLog("DKUtil::GetProcessList("+list+")\n", DKDEBUG);
#ifdef WIN32
	return DKWindows::GetProcessList(list);
#endif
	DKLog("DKUtil::GetProcessList() not implemented on this OS. \n", DKERROR);
	return false;
}

////////////////////////////////
bool DKUtil::KeyIsDown(int& key)
{
	DKLog("DKUtil::KeyIsDown("+toString(key)+")\n", DKDEBUG);
#ifdef WIN32
	return DKWindows::KeyIsDown(key);
#endif
#ifdef LINUX
	return DKLinux::KeyIsDown(key);
#endif	
	DKLog("DKUtil::KeyIsDown() not implemented on this OS. \n", DKERROR);
	return false;
}