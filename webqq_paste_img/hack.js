chrome.webRequest.onHeadersReceived.addListener(function (details) {
    var yeniheaderlar1 = [ { name : "Content-Security-Policy", value : "sil" }
    , { name : "Content-Security-Policy-Report-Only", value : "sil" }
    , { name : "X-Content-Security-Policy", value : "sil" }
    , { name : "X-WebKit-CSP", value : "sil" }
    , { name : "X-Frame-Options", value : "sil" }
    , { name : "X-XSS-Protection", value : "sil" }
    , { name : "Access-Control-Allow-Origin", value : "*" }
    , { name : "Access-Control-Allow-Methods", value : "POST, GET, OPTIONS, DELETE, PUT" }
    , { name : "Access-Control-Allow-Headers", value : "*" }
    ];
    var yeniheaderlar = [
    { name : "Access-Control-Allow-Origin", value : "*" }
    , { name : "Access-Control-Allow-Headers", value : "accept, dnt, accept-language, origin, content-type"}
    ];
    for (z = 0; z < yeniheaderlar.length; z++) {
        var zamazingo = false;
        for (i = 0; i < details.responseHeaders.length; i++) {
            if (details.responseHeaders[i].name.toLowerCase() == yeniheaderlar[z].name.toLowerCase()) {
                if (yeniheaderlar[z].value == "sil") {
                    details.responseHeaders.splice(i, 1);
                } else {
                    details.responseHeaders[i].value = yeniheaderlar[z].value; ;
                }
                zamazingo = true;
            }
        }
        if (!zamazingo && (yeniheaderlar[z].value != 'sil')) {
            details.responseHeaders.push(yeniheaderlar[z]);
        }
    }
    return {
        responseHeaders : details.responseHeaders
    };
}, {
    urls : ["http://*.qq.com/*"],
    types : ["main_frame", "sub_frame", "stylesheet", "script", "image", "object", "xmlhttprequest", "other"]
},
    ["blocking", "responseHeaders"]
);
console.log("hack.js ok");
