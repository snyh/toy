console.log("start paste_img.js")
var s = document.createElement("script");
s.src = chrome.extension.getURL("new.js");
//s.onload = function() {
    //this.parentNode.removeChild(this);
//}
(document.head || document.documentElement).appendChild(s);

//chrome.WebRequest.onHeadersReceived.addListener(function(o) {
    ////o.url == 
//});
