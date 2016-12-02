var USE_CEF = true;
//DKLog("DK_GetBrowser() = "+DK_GetBrowser()+"\n");

DKCreate("DKWindow");
DKCreate("DKRocket");
DKCreate("DKWidget");
DKCreate("DKDebug/DKDebug.js", function(){});


if(DK_GetBrowser() == "Rocket" && USE_CEF){
	var assets = DKAssets_LocalAssets();
	var url = "file:///"+assets+"/index.html";
	var iframe = DKWidget_CreateElement("body", "iframe", "DKCef_frame");
	DKWidget_SetAttribute(iframe, "src", url);
	DKWidget_SetProperty(iframe, "position", "absolute");
	DKWidget_SetProperty(iframe, "top", "0rem");
	DKWidget_SetProperty(iframe, "left", "0rem");
	DKWidget_SetProperty(iframe, "width", "100%");
	DKWidget_SetProperty(iframe, "bottom", "0rem");
	var currentBrowser = DKCef_GetCurrentBrowser(iframe);
	DKCef_SetUrl(iframe, url, currentBrowser);
	DKCef_SetFocus(iframe);
	
	/*
	DKCreate("DKGoogleAd/DKGoogleAd.js", function(){
		var id = DKGoogleAd_CreateAd("body", "100%", "100rem");
	});
	*/
}
else{
	DKWidget_SetProperty("body","background-color","grey");
	DKCreate("DKScale/DKScale.js", function(){});
	DKCreate("DKBuild/DKBuild.js", function(){});
	/*
	DKCreate("DKDev/DKDev.js", function(){});
	DKCreate("DKDev/DKMenuRight.js", function(){
		DKWidget_RemoveProperty("DKMenuRight.html","left");
		DKWidget_SetProperty("DKMenuRight.html","right","0rem");
	});
	DKCreate("DKDebug/Input.js", function(){});
	*/
	
	/*
	if(DK_GetBrowser() != "CEF"){ 
		DKCreate("DKGoogleAd/DKGoogleAd.js", function(){
			var id = DKGoogleAd_CreateAd("body", "100%", "100rem");
		});
	}
	*/
}
//DKCreate("DKUpdate");