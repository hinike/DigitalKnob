#pragma once
#ifndef DKCefHandler_H
#define DKCefHandler_H

#ifdef LINUX
#include <gdk/gdk.h>
#endif

#include "DKCef.h"
class DKCef;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DKCefHandler : public CefClient, public CefRenderHandler, public CefLoadHandler, public CefLifeSpanHandler, 
					 public CefContextMenuHandler, public CefDownloadHandler, public CefDisplayHandler, 
	                 public CefKeyboardHandler, public CefGeolocationHandler
{
public:
	DKCefHandler(){}
	DKCef* dkCef;
#ifdef WIN32
	WINDOWPLACEMENT g_wpPrev = { sizeof(g_wpPrev) };
#endif

	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler(){ return this; }
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler(){ return this; }
	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler(){ return this; }
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler(){ return this; }
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler(){ return this; }
	//virtual CefRefPtr<CefRenderHandler> GetRenderHandler(){ return this; }
	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler() { return this; }
	virtual CefRefPtr<CefGeolocationHandler> GetGeolocationHandler() { return this; }
	
	//////////////
	void DoFrame()
	{ 
		//FIXME: this breaks SDL keyboard events for Mac OSX
		CefDoMessageLoopWork(); 
	}

	///////////////////////////////////////////
	bool DoClose(CefRefPtr<CefBrowser> browser);


	//////////////////////////////////////////////////////////////
	bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
	{
		DKLog("DKSDLCefHandler::GetViewRect(CefBrowser, CefRect&)\n", DKDEBUG);
		
		//rect = CefRect(0, 0, dkCef->width, dkCef->height);
		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
	{
		DKLog("DKCefHandler::OnPaint()\n", DKDEBUG);
	}

	//////////////////////////////////////////////////////////
	void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
	{
		DKLog("DKCefHandler::OnPopupShow()\n", DKDEBUG);
	}

	////////////////////////////////////////////////////////////////////
	void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
	{
		DKLog("DKSDLCefHandler::OnPopupSize()\n", DKDEBUG);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
	{
		DKLog("DKSDLCefHandler::OnLoadingStateChange("+toString(isLoading)+","+toString(canGoBack)+","+toString(canGoForward)+")\n", DKDEBUG);
		
		//for (unsigned int i = 0; i<dkCef->browsers.size(); ++i) {
			//if (browser->GetIdentifier() == dkCef->browsers[i]->GetIdentifier()) {
				DKEvent::SendEvent("GLOBAL", "DKCef_OnLoadingStateChange", toString(0));
				return;
			///}
		//}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
	{ 
		CEF_REQUIRE_UI_THREAD();
		DKLog("DKSDLCefHandler::OnLoadError("+toString(errorCode)+","+errorText.ToString()+","+failedUrl.ToString()+")\n", DKDEBUG);
	}

	///////////////////////////////////////////////////////////////////////////
	void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen)
	{
		DKLog("DKSDLCefHandler::OnFullscreenModeChange()\n", DKINFO);

#ifdef WIN32
		HWND hwnd = GetActiveWindow();

		DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
		if(dwStyle & WS_OVERLAPPEDWINDOW){
			MONITORINFO mi = { sizeof(mi) };
			if(GetWindowPlacement(hwnd, &g_wpPrev) && GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi)){
				SetWindowLong(hwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
					SetWindowPos(hwnd, HWND_TOP,
						 mi.rcMonitor.left, mi.rcMonitor.top,
						 mi.rcMonitor.right - mi.rcMonitor.left,
						 mi.rcMonitor.bottom - mi.rcMonitor.top,
						SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
		} 
		else{
			SetWindowLong(hwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
			SetWindowPlacement(hwnd, &g_wpPrev);
			SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                 SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
#endif

#ifdef LINUX
		//gdk_init(NULL, NULL);
		GdkWindow* gdk_window = gdk_window_foreign_new(browser->GetHost()->GetWindowHandle());
		if(!gdk_window){
		      DKLog("DKSDLCefHandler::OnFullscreenModeChange(): gdk_window invalid\n", DKINFO);
		      return;
		}
		if(fullscreen){
		  gdk_window_fullscreen(gdk_window);
		}
		else{
		  gdk_window_unfullscreen(gdk_window);
		}
		
#endif //LINUX
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, CefLifeSpanHandler::WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, bool* no_javascript_access)
	{
		DKLog("DKSDLCefHandler::OnBeforePopup("+target_url.ToString()+","+target_frame_name.ToString()+","+toString(target_disposition)+")\n", DKDEBUG);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnBeforeDownload(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name, CefRefPtr<CefBeforeDownloadCallback> callback)
	{
		DKLog("DKSDLCefHandler::OnBeforeDownload("+suggested_name.ToString()+")\n", DKINFO);

#ifdef WIN32
		UNREFERENCED_PARAMETER(browser);
		UNREFERENCED_PARAMETER(download_item);
#endif
		callback->Continue(suggested_name, true);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model)
	{
		//DKLog("DKSDLCefHandler::OnBeforeContextMenu()\n", DKINFO);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, int command_id, CefContextMenuHandler::EventFlags event_flags)
	{
		//DKLog("DKSDLCefHandler::OnContextMenuCommand()\n", DKINFO);
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, const CefString& message, const CefString& source, int line )
	{
		DKString msg = message.ToString();
		replace(msg, "%c", "");
		//DKLog("DKSDLCefHandler::OnConsoleMessage("+msg+","+source.ToString()+","+toString(line)+")\n", DKDEBUG);
		DKString string = message.ToString();
		replace(string,"%c","");
		DKLog("[CEF] "+string+"\n", DKINFO);
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor, CursorType type, const CefCursorInfo& custom_cursor_info)
	{
		DKLog("OnCursorChange()\n", DKINFO);
	}

	//////////////////////////////////////////////////
	void OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
		CEF_REQUIRE_UI_THREAD();
		//dkCef->browsers.push_back(browser);
	}
	
	//////////////////////////////////////////////////////
	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) 
	{
		//DKLog("DKSDLCefHandler::OnProcessMessageReceived()\n", DKINFO);
		
		if(message->GetName() == "GetFunctions"){
			//DKLog("DKSDLCefHandler::OnProcessMessageReceived(GetFunctions)\n", DKINFO);
			DKV8::GetFunctions(browser);
		}
		
		if(has(message->GetName(),"CallFunc(")){
			//DKLog("DKSDLCefHandler::OnProcessMessageReceived(CallFunc)\n", DKINFO);
		
			//get function name
			DKString func = message->GetName();
			replace(func,"CallFunc(", "");
			replace(func,")", "");

			//get arguments
			CefRefPtr<CefListValue> arguments = message->GetArgumentList();
			DKV8::Execute(browser, func, arguments);
		}

		return false;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool OnPreKeyEvent(CefRefPtr<CefBrowser> browser, const CefKeyEvent& event, CefEventHandle os_event, bool* is_keyboard_shortcut)
	{
		//DKLog("OnPreKeyEvent(): char="+toString(event.character)+", native="+toString(event.native_key_code)+", mods="+toString(event.modifiers)+"\n", DKINFO);

		if(event.type == KEYEVENT_RAWKEYDOWN){
			//DKLog("OnPreKeyEvent(): RawKeyDown: "+toString(event.character)+"\n", DKINFO);
			DKEvent::SendEvent("GLOBAL", "keydown", toString(event.character));
		}
		if(event.type == KEYEVENT_KEYDOWN){
			DKLog("OnPreKeyEvent(): KeyDown: "+toString(event.character)+"\n", DKINFO);
		}
		if(event.type == KEYEVENT_KEYUP){
			//DKLog("OnPreKeyEvent(): KeyUp: "+toString(event.character)+"\n", DKINFO);
		}
		if(event.type == KEYEVENT_CHAR){
			//DKLog("OnPreKeyEvent(): KeyChar: "+toString(event.character)+"\n", DKINFO);
			DKEvent::SendEvent("GLOBAL", "keypress", toString(event.character));
		}
		
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool OnRequestGeolocationPermission(CefRefPtr< CefBrowser > browser, const CefString& requesting_url, int request_id, CefRefPtr< CefGeolocationCallback > callback)
	{
		DKLog("DKSDLCefHandler::OnRequestGeolocationPermission()\n", DKINFO);
		callback->Continue(true);
		return true;
	}

	IMPLEMENT_REFCOUNTING(DKCefHandler);
};

#endif //DKCefHandler_H