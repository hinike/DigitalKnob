#ifdef USE_DKRocket
#ifdef USE_DKDuktape 
#include "DKWidgetJS.h"
#include "DKWindow.h"
#include "DKFile.h"
#include "Controls/WidgetTextInput.h"
#include "Controls/ElementTextSelection.h"

DKString DKWidgetJS::htmlfile;

///////////////////////
void DKWidgetJS::Init()
{
	//DKDuktape::AttachFunction("DKWidget_NewWidget", DKWidgetJS::NewWidget, 2);
	DKDuktape::AttachFunction("DKWidget_AddDragHandle", DKWidgetJS::AddDragHandle, 2);
	DKDuktape::AttachFunction("DKWidget_AddResizeHandle", DKWidgetJS::AddResizeHandle, 2);
	DKDuktape::AttachFunction("DKWidget_AppendChild", DKWidgetJS::AppendChild, 2);
	DKDuktape::AttachFunction("DKWidget_Copy", DKWidgetJS::Copy, 1);
	DKDuktape::AttachFunction("DKWidget_CreateElement", DKWidgetJS::CreateElement, 3);
	DKDuktape::AttachFunction("DKWidget_CreateElementBefore", DKWidgetJS::CreateElementBefore, 3);
	DKDuktape::AttachFunction("DKWidget_Cut", DKWidgetJS::Cut, 1);
	DKDuktape::AttachFunction("DKWidget_ElementExists", DKWidgetJS::ElementExists, 1);
	DKDuktape::AttachFunction("DKWidget_GetAttribute", DKWidgetJS::GetAttribute, 2);
	DKDuktape::AttachFunction("DKWidget_GetAvailableId", DKWidgetJS::GetAvailableId, 1);
	DKDuktape::AttachFunction("DKWidget_GetClientHeight", DKWidgetJS::GetClientHeight, 1);
	DKDuktape::AttachFunction("DKWidget_GetClientWidth", DKWidgetJS::GetClientWidth, 1);
	DKDuktape::AttachFunction("DKWidget_GetElements", DKWidgetJS::GetElements, 1);
	DKDuktape::AttachFunction("DKWidget_GetFile", DKWidgetJS::GetFile, 1);
	DKDuktape::AttachFunction("DKWidget_GetFirstChild", DKWidgetJS::GetFirstChild, 1); 
	DKDuktape::AttachFunction("DKWidget_GetFocusElement", DKWidgetJS::GetFocusElement, 0);
	DKDuktape::AttachFunction("DKWidget_GetHoverElement", DKWidgetJS::GetHoverElement, 0);
	DKDuktape::AttachFunction("DKWidget_GetInnerHtml", DKWidgetJS::GetInnerHtml, 1);
	DKDuktape::AttachFunction("DKWidget_GetInnerHtmlString", DKWidgetJS::GetInnerHtmlString, 1);
	DKDuktape::AttachFunction("DKWidget_GetMouseElementX", DKWidgetJS::GetMouseElementX, 1); 
	DKDuktape::AttachFunction("DKWidget_GetMouseElementY", DKWidgetJS::GetMouseElementY, 1);
	DKDuktape::AttachFunction("DKWidget_GetMouseWindowX", DKWidgetJS::GetMouseWindowX, 0); 
	DKDuktape::AttachFunction("DKWidget_GetMouseWindowY", DKWidgetJS::GetMouseWindowY, 0);
	DKDuktape::AttachFunction("DKWidget_GetOffsetHeight", DKWidgetJS::GetOffsetHeight, 1);
	DKDuktape::AttachFunction("DKWidget_GetOffsetWidth", DKWidgetJS::GetOffsetWidth, 1);
	DKDuktape::AttachFunction("DKWidget_GetOption", DKWidgetJS::GetOption, 1);
	DKDuktape::AttachFunction("DKWidget_GetOuterHtml", DKWidgetJS::GetOuterHtml, 1);
	DKDuktape::AttachFunction("DKWidget_GetParent", DKWidgetJS::GetParent, 1);
	DKDuktape::AttachFunction("DKWidget_GetProperty", DKWidgetJS::GetProperty, 2);
	DKDuktape::AttachFunction("DKWidget_GetScale", DKWidgetJS::GetScale, 0);
	DKDuktape::AttachFunction("DKWidget_GetTagName", DKWidgetJS::GetTagName, 1);
	DKDuktape::AttachFunction("DKWidget_GetValue", DKWidgetJS::GetValue, 1);
	DKDuktape::AttachFunction("DKWidget_HasAttribute", DKWidgetJS::HasAttribute, 2);
	DKDuktape::AttachFunction("DKWidget_HasProperty", DKWidgetJS::HasProperty, 2);
	DKDuktape::AttachFunction("DKWidget_Hide", DKWidgetJS::Hide, 1);
	DKDuktape::AttachFunction("DKWidget_InsertBefore", DKWidgetJS::InsertBefore, 2);
	DKDuktape::AttachFunction("DKWidget_IsChildOf", DKWidgetJS::IsChildOf, 2);
	DKDuktape::AttachFunction("DKWidget_OpenLink", DKWidgetJS::OpenLink, 1);
	DKDuktape::AttachFunction("DKWidget_Paste", DKWidgetJS::Paste, 1);
	DKDuktape::AttachFunction("DKWidget_PrependChild", DKWidgetJS::PrependChild, 2);
	DKDuktape::AttachFunction("DKWidget_RemoveAttribute", DKWidgetJS::RemoveAttribute, 2);
	DKDuktape::AttachFunction("DKWidget_RemoveDragHandle", DKWidgetJS::RemoveDragHandle, 1);
	DKDuktape::AttachFunction("DKWidget_RemoveElement", DKWidgetJS::RemoveElement, 1);
	DKDuktape::AttachFunction("DKWidget_RemoveProperty", DKWidgetJS::RemoveProperty, 2);
	DKDuktape::AttachFunction("DKWidget_RemoveResizeHandle", DKWidgetJS::RemoveResizeHandle, 1);
	DKDuktape::AttachFunction("DKWidget_ScrollToBottom", DKWidgetJS::ScrollToBottom, 1);
	DKDuktape::AttachFunction("DKWidget_ScrollToTop", DKWidgetJS::ScrollToTop, 1);
	DKDuktape::AttachFunction("DKWidget_SetAttribute", DKWidgetJS::SetAttribute, 3);
	DKDuktape::AttachFunction("DKWidget_SetFile", DKWidgetJS::SetFile, 2);
	DKDuktape::AttachFunction("DKWidget_SetInnerHtml", DKWidgetJS::SetInnerHtml, 2);
	DKDuktape::AttachFunction("DKWidget_SetInnerHtmlString", DKWidgetJS::SetInnerHtmlString, 2);
	DKDuktape::AttachFunction("DKWidget_SetOption", DKWidgetJS::SetOption, 2);
	DKDuktape::AttachFunction("DKWidget_SetProperty", DKWidgetJS::SetProperty, 3);
	DKDuktape::AttachFunction("DKWidget_SetScale", DKWidgetJS::SetScale, 1);
	DKDuktape::AttachFunction("DKWidget_SetValue", DKWidgetJS::SetValue, 2);
	DKDuktape::AttachFunction("DKWidget_Show", DKWidgetJS::Show, 1);
	DKDuktape::AttachFunction("DKWidget_Toggle", DKWidgetJS::Toggle, 1);
	DKDuktape::AttachFunction("DKWidget_ValidateColor", DKWidgetJS::ValidateColor, 1); 
	DKDuktape::AttachFunction("DKWidget_Visible", DKWidgetJS::Visible, 1);
	DKDuktape::AttachFunction("DKWidget_WindowHeight", DKWidgetJS::WindowHeight, 0);
	DKDuktape::AttachFunction("DKWidget_WindowWidth", DKWidgetJS::WindowWidth, 0);

	DKString jsfile = DKFile::local_assets + "DKRocket/DKRocket.js";
	DKDuktape::LoadFile(jsfile);
}

///////////////////////////////////////////
int DKWidgetJS::NewWidget(duk_context* ctx)
{
    DKString file = duk_require_string(ctx, 0);
	DKString parent;
	if(duk_get_string(ctx, 1)){
		parent = duk_get_string(ctx, 1);
	}

	DKString file2;
	DKFile::GetFileName(file, file2);

	//DKWidget::NewWidget(file, parent);
	DKCreate(file2+","+parent+","+file);

	return 1;
}

//////////////////////////////////////
int DKWidgetJS::Show(duk_context* ctx)
{
	DKString string = duk_require_string(ctx, 0);
	if(!DKWidget::Show(string)){ return 0; }
	return 1;
}

//////////////////////////////////////
int DKWidgetJS::Hide(duk_context* ctx)
{
	DKString string = duk_require_string(ctx, 0);
	if(!DKWidget::Hide(string)){ return 0; }
	return 1;
}

////////////////////////////////////////
int DKWidgetJS::Toggle(duk_context* ctx)
{
	DKString string = duk_require_string(ctx, 0);
	if(!DKWidget::Toggle(string)){ return 0; }
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::GetAttribute(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString param = duk_require_string(ctx, 1);
	DKString value;
	if(!DKWidget::GetAttribute(id, param, value)){ value = ""; }
	duk_push_string(ctx, value.c_str());
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::SetAttribute(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString param = duk_require_string(ctx, 1);
	DKString value = duk_require_string(ctx, 2);
	if(!DKWidget::SetAttribute(id, param, value)){ return 0; }
	return 1;
}

//////////////////////////////////////////
int DKWidgetJS::GetValue(duk_context* ctx)
{
	DKString evt = duk_require_string(ctx, 0);
	DKLog("DKWidgetJS::GetValue("+evt+")\n", DKINFO);
	DKStringArray arry;
	toStringArray(arry, evt, ",");
	if(arry.size() > 2){
		DKString params = arry[2];
		for(unsigned int i=3; i<arry.size(); ++i){
			params += ","+arry[i];
		}
		duk_push_string(ctx, params.c_str());
		return 1;
	}
	if(arry.size() > 1){
		if(DKWidget::GetElementById(arry[0])){
			duk_push_string(ctx, DKWidget::GetValue(arry[0]).c_str());
		}
		else{
			duk_push_string(ctx, arry[0].c_str());
		}
		return 1;
	}
	duk_push_string(ctx, DKWidget::GetValue(arry[0]).c_str());
	return 1;
}

//////////////////////////////////////////
int DKWidgetJS::SetValue(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value = duk_require_string(ctx, 1);
	if(!DKWidget::SetValue(id, value)){ return 0; }
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::SetInnerHtml(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value = duk_require_string(ctx, 1);
	if(!DKWidget::SetInnerHtml(id, value)){ return 0; }
	return 1;
}

////////////////////////////////////////////////////
int DKWidgetJS::SetInnerHtmlString(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value = duk_require_string(ctx, 1);
	if(!DKWidget::SetInnerHtmlString(id, value)){ return 0; }
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::GetInnerHtml(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value;
	if(!DKWidget::GetInnerHtml(id, value)){ value = ""; }
	duk_push_string(ctx, value.c_str());
	return 1;
}

////////////////////////////////////////////////////
int DKWidgetJS::GetInnerHtmlString(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value;
	if(!DKWidget::GetInnerHtmlString(id, value)){ value = ""; }
	duk_push_string(ctx, value.c_str());
	return 1;
}

////////////////////////////////////////////////
int DKWidgetJS::GetAvailableId(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString out;
	DKWidget::GetAvailableId(id, out);
	duk_push_string(ctx, out.c_str());
	return 1;
}

///////////////////////////////////////////////
int DKWidgetJS::CreateElement(duk_context* ctx)
{
	DKString parent = duk_require_string(ctx, 0);
	DKString tag = duk_require_string(ctx, 1);
	DKString id = duk_require_string(ctx, 2);	
	DKString ele_id = DKWidget::CreateElement(parent, tag, id);
	if(ele_id.empty()){ return 0; }
	duk_push_string(ctx, ele_id.c_str());
	return 1;
}

/////////////////////////////////////////////////////
int DKWidgetJS::CreateElementBefore(duk_context* ctx)
{
	DKString parent = duk_require_string(ctx, 0);
	DKString tag = duk_require_string(ctx, 1);
	DKString id = duk_require_string(ctx, 2);	
	DKString ele_id = DKWidget::CreateElementBefore(parent, tag, id);
	if(ele_id.empty()){ return 0; }
	duk_push_string(ctx, ele_id.c_str());
	return 1;
}

/////////////////////////////////////////////
int DKWidgetJS::GetProperty(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString param = duk_require_string(ctx, 1);
	DKString value;
	if(!DKWidget::GetProperty(id, param, value)){ value = ""; }
	if(same(value,"0")){ value = ""; }
	duk_push_string(ctx, value.c_str());
	return 1;
}

/////////////////////////////////////////////
int DKWidgetJS::SetProperty(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString param = duk_require_string(ctx, 1);
	DKString value = duk_require_string(ctx, 2);
	if(!DKWidget::SetProperty(id, param, value)){ return 0; }
	return 1;
}

///////////////////////////////////////////
int DKWidgetJS::GetParent(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString parent;
	if(!DKWidget::GetParent(id, parent)){
		return 0;
	}
	duk_push_string(ctx, parent.c_str());
	return 1;
}

///////////////////////////////////////////////
int DKWidgetJS::GetFirstChild(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString child = DKWidget::GetFirstChild(id);
	duk_push_string(ctx, child.c_str());
	return 1;
}

///////////////////////////////////////////////
int DKWidgetJS::ValidateColor(duk_context* ctx)
{
	DKString string = duk_require_string(ctx, 0);
	if(!DKWidget::ValidateColor(string)){ string = ""; }
	duk_push_string(ctx, string.c_str());
	return 1;
}

/////////////////////////////////////////////
int DKWidgetJS::GetElements(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKStringArray elements;
	if(!DKWidget::GetElements(id, elements)){ return 0; }
	DKString list = toString(elements, ",");
	duk_push_string(ctx, list.c_str());
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::GetMouseWindowX(duk_context* ctx)
{
	int mouseX = 0;
	DKWidget::GetMouseWindowX(mouseX);
	duk_push_int(ctx, mouseX);
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::GetMouseWindowY(duk_context* ctx)
{
	int mouseY = 0;
	DKWidget::GetMouseWindowY(mouseY);
	duk_push_int(ctx, mouseY);
	return 1;
}

//////////////////////////////////////////////////
int DKWidgetJS::GetMouseElementX(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	int winX = 0;
	int winY = 0;
	DKWidget::GetMouseElementPosition(element,winX,winY);
	duk_push_int(ctx, winX);
	return 1;
}

//////////////////////////////////////////////////
int DKWidgetJS::GetMouseElementY(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	int winX = 0;
	int winY = 0;
	DKWidget::GetMouseElementPosition(element,winX,winY);
	duk_push_int(ctx, winY);
	return 1;
}

///////////////////////////////////////////
int DKWidgetJS::IsChildOf(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	DKString parent = duk_require_string(ctx, 1);
	if(!DKWidget::IsChildOf(element, parent)){ return 0; }
	return 1;
}

///////////////////////////////////////////////
int DKWidgetJS::ElementExists(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	if(!DKWidget::GetElementById(id)){ return 0; }
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::HasAttribute(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString attrib = duk_require_string(ctx, 1);
	DKElement* element = DKWidget::GetElementById(id);
	if(!element){ return 0; }
	if(!element->HasAttribute(attrib.c_str())){ return 0; }
	return 1;
}

/////////////////////////////////////////////
int DKWidgetJS::HasProperty(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString property = duk_require_string(ctx, 1);
	DKElement* element = DKWidget::GetElementById(id);
	if(!element){ return 0; }
	if(!element->GetProperty(property.c_str())){ return 0; }
	return 1;
}

////////////////////////////////////////////
int DKWidgetJS::GetTagName(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKElement* element = DKWidget::GetElementById(id);
	if(!element){ return 0; }
	duk_push_string(ctx, element->GetTagName().CString());
	return 1;
}

/////////////////////////////////////////////
int DKWidgetJS::AppendChild(duk_context* ctx)
{
	DKString parent = duk_require_string(ctx, 0);
	DKString child = duk_require_string(ctx, 1);
	if(!DKWidget::AppendChild(parent, child)){ return 0; }
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::PrependChild(duk_context* ctx)
{
	DKString parent = duk_require_string(ctx, 0);
	DKString child = duk_require_string(ctx, 1);
	if(!DKWidget::PrependChild(parent, child)){ return 0; }
	return 1;
}

///////////////////////////////////////////////
int DKWidgetJS::RemoveElement(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	if(!DKWidget::RemoveElement(id)){ return 0; }
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::InsertBefore(duk_context* ctx)
{
	DKString parent = duk_require_string(ctx, 0);
	DKString child = duk_require_string(ctx, 1);
	if(!DKWidget::InsertBefore(parent, child)){ return 0; }
	return 1;
}

///////////////////////////////////////////////
int DKWidgetJS::AddDragHandle(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	DKString drag = duk_require_string(ctx, 1);
	if(!DKWidget::AddDragHandle(element, drag)){ return 0; }
	return 1;
}

//////////////////////////////////////////////////
int DKWidgetJS::RemoveDragHandle(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	if(!DKWidget::RemoveDragHandle(element)){ return 0; }
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::AddResizeHandle(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	DKString resize = duk_require_string(ctx, 1);
	if(!DKWidget::AddResizeHandle(element, resize)){ return 0; }
	return 1;
}

////////////////////////////////////////////////////
int DKWidgetJS::RemoveResizeHandle(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	if(!DKWidget::RemoveResizeHandle(id)){ return 0; }
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::GetOffsetHeight(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKElement* element = DKWidget::GetElementById(id);
	if(!element){ return 0; }
	int offsetHeight = element->GetOffsetHeight();
	duk_push_int(ctx, offsetHeight);
	return 1;
}

////////////////////////////////////////////////
int DKWidgetJS::GetOffsetWidth(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKElement* element = DKWidget::GetElementById(id);
	if(!element){ return 0; }
	int offsetWidth = element->GetOffsetWidth();
	duk_push_int(ctx, offsetWidth);
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::GetOuterHtml(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString string;
	if(!DKWidget::GetOuterHtml(id, string)){ string = ""; }
	duk_push_string(ctx, string.c_str());
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::RemoveAttribute(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	DKString attrib = duk_require_string(ctx, 1);
	DKElement* ele = DKWidget::GetElementById(element);
	if(!ele){ return 0; }
	ele->RemoveAttribute(attrib.c_str());
	return 0;
}

////////////////////////////////////////////////
int DKWidgetJS::RemoveProperty(duk_context* ctx)
{
	DKString element = duk_require_string(ctx, 0);
	DKString attrib = duk_require_string(ctx, 1);
	DKElement* ele = DKWidget::GetElementById(element);
	if(!ele){ return 0; }
	ele->RemoveProperty(attrib.c_str());
	return 0;
}

/////////////////////////////////////////////////
int DKWidgetJS::GetFocusElement(duk_context* ctx)
{
	DKString id;
	if(!DKWidget::GetFocusElement(id)){ return 0; }
	duk_push_string(ctx, id.c_str());
	return 1;
}

/////////////////////////////////////////
int DKWidgetJS::Visible(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	if(!DKWidget::Visible(id)){ return 0; }
	return 1;
}

/////////////////////////////////////////////
int DKWidgetJS::WindowWidth(duk_context* ctx)
{
	duk_push_int(ctx, DKWindow::GetWidth());
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::WindowHeight(duk_context* ctx)
{
	duk_push_int(ctx, DKWindow::GetHeight());
	return 1;
}

/////////////////////////////////////////
int DKWidgetJS::GetFile(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString file;
	DKWidget::GetFile(id,file);
	duk_push_string(ctx, file.c_str());
	return 1;
}

/////////////////////////////////////////
int DKWidgetJS::SetFile(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString file = duk_require_string(ctx, 1);
	if(!DKWidget::SetFile(id,file)){ return 0; }
	return 1;
}

///////////////////////////////////////////
int DKWidgetJS::GetOption(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	//DKLog("DKWidgetJS::GetOption("+id+")\n");
	int n = 0;
	if(!DKWidget::GetOption(id,n)){
		return 0;
	}
	duk_push_int(ctx, n);
	return 1;
}

///////////////////////////////////////////
int DKWidgetJS::SetOption(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	int n = duk_require_int(ctx, 1);
	//DKLog("DKWidgetJS::SelectOption("+id+")\n");
	if(!DKWidget::SetOption(id,n)){
		return 0;
	}
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::GetHoverElement(duk_context* ctx)
{
	DKString id;
	if(!DKWidget::GetHoverElement(id)){
		return 0;
	}
	duk_push_string(ctx, id.c_str());
	return 1;
}

//////////////////////////////////////////
int DKWidgetJS::GetScale(duk_context* ctx)
{
	DKString scale;
	DKWidget::GetProperty("html","font-size",scale);
	replace(scale, "px", "");
	//DKLog("DKWidgetJS::GetScale() = "+scale+" \n", DKDEBUG);
	duk_push_number(ctx, toFloat(scale));
	return 1;
}

//////////////////////////////////////////
int DKWidgetJS::SetScale(duk_context* ctx)
{
	double scale = duk_require_number(ctx, 0);
	//DKLog("DKWidgetJS::SetScale("+toString(scale)+")\n", DKDEBUG);
	DKWidget::SetProperty("html","font-size",toString(scale)+"px");
	DKWidget::SetProperty("body","font-size",toString(scale)+"px");
	return 1;
}

/////////////////////////////////////
int DKWidgetJS::Cut(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKElement* element = DKWidget::GetElementById(id);
	Rocket::Controls::ElementTextSelection* ele = static_cast<Rocket::Controls::ElementTextSelection*>(element);
	Rocket::Controls::WidgetTextInput* widget = NULL;
	if(element->GetTagName() == "input"){
		Rocket::Core::ElementText* ti = static_cast<Rocket::Core::ElementText*>(ele->widget->selected_text_element);
		widget = reinterpret_cast<Rocket::Controls::WidgetTextInput*>(ti);
	}
	else{
		Rocket::Controls::ElementTextSelection* ele = static_cast<Rocket::Controls::ElementTextSelection*>(element);
		widget = ele->widget;
	}

	/*
	Rocket::Core::WString pre, selection, post, line;
	widget->GetLineSelection(pre, selection, post, line, 1);
	DKCString text;
	text = selection.ToUTF8(text,0);
	DKLog("DKWidgetJS::Cut("+toString(text.CString())+")\n", DKINFO);
	*/
		
	widget->CopySelection();  //TODO - use DKUtil::SetClipboard()
	widget->DeleteSelection();
	widget->UpdateRelativeCursor();
	widget->ShowCursor(true,true);
	element->Focus();
	return 1;
}

//////////////////////////////////////
int DKWidgetJS::Copy(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKElement* element = DKWidget::GetElementById(id);
	Rocket::Controls::ElementTextSelection* ele = static_cast<Rocket::Controls::ElementTextSelection*>(element);
	Rocket::Controls::WidgetTextInput* widget = NULL;
	if(element->GetTagName() == "input"){
		Rocket::Core::ElementText* ti = static_cast<Rocket::Core::ElementText*>(ele->widget->selected_text_element);
		widget = reinterpret_cast<Rocket::Controls::WidgetTextInput*>(ti);
	}
	else{
		Rocket::Controls::ElementTextSelection* ele = static_cast<Rocket::Controls::ElementTextSelection*>(element);
		widget = ele->widget;
	}

	widget->CopySelection(); //TODO - use DKUtil::SetClipboard()
	return 1;
}

///////////////////////////////////////
int DKWidgetJS::Paste(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKElement* element = DKWidget::GetElementById(id);
	Rocket::Controls::ElementTextSelection* ele = static_cast<Rocket::Controls::ElementTextSelection*>(element);
	Rocket::Controls::WidgetTextInput* widget = NULL;
	if(element->GetTagName() == "input"){
		Rocket::Core::ElementText* ti = static_cast<Rocket::Core::ElementText*>(ele->widget->selected_text_element);
		widget = reinterpret_cast<Rocket::Controls::WidgetTextInput*>(ti);
	}
	else{
		Rocket::Controls::ElementTextSelection* ele = static_cast<Rocket::Controls::ElementTextSelection*>(element);
		widget = ele->widget;
	}

	if(widget->selection_length > 0){
		widget->DeleteSelection();
	}
	Rocket::Core::WString value = element->GetAttribute<DKCString>("value", "");
	DKString clipboard;
	DKUtil::GetClipboard(clipboard);
	int cursor = widget->GetCursorIndex();
	value.Insert(cursor, Rocket::Core::WString(clipboard.c_str()));
	widget->edit_index += 1;
	Rocket::Core::String utf8_value;
	value.ToUTF8(utf8_value);
	element->SetAttribute("value", utf8_value);
	widget->absolute_cursor_index = cursor + clipboard.length();
	widget->UpdateRelativeCursor();
	widget->ShowCursor(true,true);
	element->Focus();
	return 1;
}

//////////////////////////////////////////////
int DKWidgetJS::ScrollToTop(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	if(!DKWidget::ScrollToTop(id)){
		return 0;
	}
	return 1;
}

////////////////////////////////////////////////
int DKWidgetJS::ScrollToBottom(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	if(!DKWidget::ScrollToBottom(id)){
		return 0;
	}
	return 1;
}

//////////////////////////////////////////
int DKWidgetJS::OpenLink(duk_context* ctx)
{
	DKString url = duk_require_string(ctx, 0);
	DKUtil::Run(url); 
	return 1;
}

////////////////////////////////////////////////
int DKWidgetJS::GetClientWidth(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value;
	if (!DKWidget::GetClientWidth(id, value)) {
		return 0;
	}
	duk_push_string(ctx, value.c_str());
	return 1;
}

/////////////////////////////////////////////////
int DKWidgetJS::GetClientHeight(duk_context* ctx)
{
	DKString id = duk_require_string(ctx, 0);
	DKString value;
	if (!DKWidget::GetClientHeight(id, value)) {
		return 0;
	}
	duk_push_string(ctx, value.c_str());
	return 1;
}

#endif //USE_DKDuktape
#endif //USE_DKRocket