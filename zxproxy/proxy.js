var siteURL = "https://www.zxproxy.com/browse.php?b=2&flag=norefer&u="

function zxproxyIt(info, tab) {
    window.open(siteURL+encodeURIComponent(info.linkUrl))
}
var zx = chrome.contextMenus.create({"title": "ProxyIt", "onclick": zxproxyIt,
contexts:["link", "image", "video", "audio"]
})

var no_proxy = -1;
var proxy_me = chrome.contextMenus.create({"title": "ProxyMe", "onclick": zxproxyMe})
function zxproxyMe(info, tab) {
    //console.log("link:" +info.pageUrl);
    //if (no_proxy != -1) {
        //chrome.contextMenus.remove(no_proxy)
        //no_proxy = -1;
    //}
    //if (proxy_me != -1) {
    //chrome.contextMenus.remove(proxy_me);
    //proxy_me = -1;
    //}
    //no_proxy = chrome.contextMenus.create({"title": "NoProxy", "onclick": noZxproxy
    //})
    //alert(siteURL+info.pageUrl)
    window.open(siteURL+encodeURIComponent(info.pageUrl));
}

function noZxproxy(info, tab) {
    if (no_proxy != -1) {
        chrome.contextMenus.remove(no_proxy);
        no_proxy = -1;
    }
    proxy_me = chrome.contextMenus.create({"title": "ProxyMe", "onclick": zxproxyMe});
}


var rule_normal = {
};


chrome.extension.onRequest.addListener(function(request, sender, callback){
    var tabId = request.tabId;
    chrome.tabs.executeScript(tabId, { file: "content.js" }, function() {
        chrome.tabs.sendRequest(tabId, {}, function(results) {
            validateLinks(results, callback);
        });
    });
});
