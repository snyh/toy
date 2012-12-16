(function() {
    var tryRemoveLinks = function() {
        var els = document.getElementsByTagName('a');
        for(var i=0; i<els.length; i++) {
            var redict = els[i].getAttribute("onmousedown");
            if (/return\s+rwt/i.exec(redict)) {
                els[i].setAttribute("onmousedown", null);
            } 
        }
    };
    tryRemoveLinks();
    setInterval(tryRemoveLinks, 1000);
})();
