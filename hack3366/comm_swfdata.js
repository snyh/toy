    function _startInterval() {
        _stopInterval();
        cookiesRefreshTimer = setInterval(function () {
            isSubmit = false;
            _submitScore();
        }, 300000);
    }
    function _stopInterval() {
        clearInterval(cookiesRefreshTimer);
    }
    function _callJSEvtHandler(flashArg, isServerReturn) {
        flash.external.ExternalInterface.call("detail_alert", flashArg);
        if (gameObject.jsEvtHandler) {
            gameObject.jsEvtHandler(flashArg);
        }
        if (!isServerReturn) {
            flashArg.flash = true;
        }
        flash.external.ExternalInterface.call("flashEvent", flashArg);
    }
    function _checkTime() {
        _times++;
        _lastTime = _currentTime;
        _currentTime = new Date();
        var _local1 = (_currentTime.getTime() - _startTime.getTime()) / _times;
        var _local2 = _currentTime.getTime() - _lastTime.getTime();
        if ((Math.abs(_local2 - _local1) / _local1) <= 0.15) {
            return(true);
        }
        _callJSEvtHandler(JSEVENT.c701);
        return(false);
    }
    function _checkURL() {
        if (System.capabilities.isDebugger && (System.capabilities.playerType == "External")) {
            _callJSEvtHandler(JSEVENT.c901);
            return(true);
        }
        var _local3 = gameObject.flashUrl;
        if ((!_local3) || (_local3 == "")) {
            return(false);
        }
        var _local2 = ["http://imgcache.qq.com/", "http://cnc.imgcache.qq.com/", "http://ctc.imgcache.qq.com/", "http://edu.imgcache.qq.com/", "http://isdimg0.qq.com/", "http://qzs.qq.com/", "http://ctc.qzs.qq.com/", "http://cnc.qzs.qq.com/", "http://edu.qzs.qq.com/", "http://os.qzs.qq.com/", "http://cm.qzs.qq.com/", "http://img.3366.com/", "http://cgi.3366.com/", "http://fcg.3366.com/", "http://www.3366.com/"];
        var _local1 = _local2.length - 1;
        while (_local1 >= 0) {
            if (String(_local3).indexOf(_local2[_local1]) == 0) {
                return(true);
            }
            _local1--;
        }
        return(false);
    }
    function bootStrap(keyLoadedHandler, scoreDataField) {
        if (!scoreDataField) {
            scoreDataField = "score";
        }
        gameStart(_root.pid, _root, scoreDataField, null, keyLoadedHandler);
    }
    function gameStart(gameId, scoreContainer, scoreDataField, jsEvtHandler, keyLoadedHandler) {
        var _local2 = new LoadVars();
        _local2.pid = gameId;
        _local2.act = "get";
        _local2.uin = scoreContainer.uin;
        gameObject.bookid = ((scoreContainer.bookid != undefined) ? (parseInt(scoreContainer.bookid, 10)) : -1);
        gameObject.pktype = ((scoreContainer.pktype != undefined) ? (parseInt(scoreContainer.pktype, 10)) : 0);
        gameObject.platForm = ((scoreContainer.platform != undefined) ? (parseInt(scoreContainer.platform, 10)) : 0);
        gameObject.flashUrl = scoreContainer._url;
        gameObject.pageUrl = pageLocation;
        gameObject.jsEvtHandler = jsEvtHandler;
        gameObject.keyLoadedHandler = keyLoadedHandler;
        gameObject.root = scoreContainer;
        gameObject.sField = scoreDataField;
        gameObject.gameId = gameId;
        if (gameObject.pktype == 1) {
            GET_MODE = 1;
            SUBMIT_MODE = 1;
        } else if ((gameObject.pktype >= 2) && (gameObject.pktype <= 4)) {
            GET_MODE = 1;
            SUBMIT_MODE = 2;
        } else if (gameObject.pktype == 5) {
            GET_MODE = 1;
            SUBMIT_MODE = 7;
        } else if (gameObject.pktype == 6) {
            GET_MODE = 1;
            SUBMIT_MODE = 8;
        } else if (gameObject.pktype == 7) {
            GET_MODE = 1;
            SUBMIT_MODE = 9;
        }
        if (gameObject.platForm == 3) {
            if (gameObject.pktype == 1) {
                GET_MODE = 2;
                SUBMIT_MODE = 3;
            } else if ((gameObject.pktype >= 2) && (gameObject.pktype <= 4)) {
                GET_MODE = 2;
                SUBMIT_MODE = 4;
            }
        }
        if (gameObject.platForm == 4) {
            if (gameObject.pktype == 1) {
                GET_MODE = 3;
                SUBMIT_MODE = 5;
            } else if ((gameObject.pktype >= 2) && (gameObject.pktype <= 4)) {
                GET_MODE = 3;
                SUBMIT_MODE = 6;
            }
        }
        if (!_checkURL()) {
            return(false);
        }
        _local2.sendAndLoad(GET_URL[GET_MODE], _local2, "POST");
        _local2.onData = function (src) {
            try {
                var _local1 = json.decode(src);
                if (_local1["key"]) {
                    hasKey = true;
                    key = _local1["key"];
                    _callJSEvtHandler(JSEVENT.c1002);
                    if (gameObject.keyLoadedHandler) {
                        gameObject.keyLoadedHandler(_local1);
                        gameObject.keyLoadedHandler = null;
                    }
                    _startInterval();
                } else {
                    _callJSEvtHandler(_local1, true);
                }
            } catch(e) {
                var _local2 = {msg:(((("数据格式出错: " + e.message) + "\nat: ") + e.at) + "\ntext: ") + e.text, type:2, flash:true};
                _callJSEvtHandler(_local2);
                _stopInterval();
            }
        };
        return(true);
    }
    function showRank(referr, score) {
        if (!referr) {
            referr = 0;
        }
        if (!score) {
            score = 0;
        }
        JSEVENT.c1020.refer = referr;
        JSEVENT.c1020.score = score;
        _callJSEvtHandler(JSEVENT.c1020);
    }
    function showScoreList(referr, score) {
        showRank(referr, score);
    }
    function gameOver(callback) {
        isSubmit = true;
        _stopInterval();
        _submitScore(callback);
    }
    function _submitScore(callback) {
        if (!_checkURL()) {
            return(false);
        }
        if (isSubmit) {
            _stopInterval();
        }
        var _local1 = new LoadVars();
        _local1.pid = gameObject.gameId;
        _local1.act = (isSubmit ? "set" : "get");
        _local1.score = gameObject.root[gameObject.sField];
        _local1.uin = gameObject.root.uin;
        _local1.submit = isSubmit;
        if (gameObject.root.ouin) {
            _local1.ouin = gameObject.root.ouin;
        }
        var _s = parseInt(_local1.score, 10);
        if (_s < 0) {
            _s = 0;
        }
        if (gameObject.pktype) {
            _local1.pkMode = gameObject.pktype;
            _local1.bookId = gameObject.bookid;
        }
        _local1.score = _s;
        _local1["key"] = _getFinalKey(key, _s);
        _local1.sendAndLoad(SUBMIT_URL[SUBMIT_MODE], _local1, "POST");
        if (isSubmit) {
            _local1.onData = function (src) {
                isSubmit = false;
                try {
                    var _local1 = json.decode(src);
                    if (_local1["key"]) {
                        key = _local1["key"];
                    }
                    if (_local1.score == _s) {
                        _callJSEvtHandler(JSEVENT.c1000);
                        showRank(1, _s);
                        if (callback) {
                            callback();
                        }
                        _startInterval();
                    } else {
                        _callJSEvtHandler(JSEVENT.c1001);
                    }
                    _callJSEvtHandler(_local1, true);
                } catch(e) {
                    var _local2 = {msg:(((("数据格式出错: " + e.message) + "\nat: ") + e.at) + "\ntext: ") + e.text, type:2};
                    _callJSEvtHandler(_local2);
                    _stopInterval();
                }
            };
        }
        return(true);
    }
    function _getFinalKey(key, gScore) {
        if ((!key) || (gScore == undefined)) {
            return(null);
        }
        if (key.length != 48) {
            return(null);
        }
        gScore = Number(gScore);
        if (gScore > 999999999) {
            return(null);
        }
        var _local10 = key;
        key = key.substr(42, 6);
        var _local8 = parseInt(key, 36);
        var _local4 = _local8.toString(35);
        var _local13 = _local4.length;
        var _local3 = parseInt(key.substr(key.length - 1), 36) % _local13;
        var _local6 = gScore.toString(36);
        var _local12 = _local4.substr(0, _local3);
        var _local7 = _local4.substr(_local3);
        var _local5 = _local3 + 10;
        var _local11 = _local5 + _local6.length;
        var _local9 = [_local5.toString(36), _local12, _local6, _local7, _local11.toString(36), _local10].join("");
        return(_local9);
    }
    System.security.allowDomain("imgcache.qq.com");
    System.security.allowDomain("isdimg0.qq.com");
    System.security.allowDomain("edu.imgcache.qq.com");
    System.security.allowDomain("cnc.imgcache.qq.com");
    System.security.allowDomain("qzonestyle.qtimg.cn");
    System.security.allowDomain("ctc.imgcache.qq.com");
    System.security.allowDomain("qzs.qq.com");
    System.security.allowDomain("ctc.qzs.qq.com");
    System.security.allowDomain("cnc.qzs.qq.com");
    System.security.allowDomain("edu.qzs.qq.com");
    System.security.allowDomain("os.qzs.qq.com");
    System.security.allowDomain("cm.qzs.qq.com");
    System.security.allowDomain("cn.qzs.qq.com");
    System.security.allowDomain("img.3366.com");
    System.security.allowDomain("a1.img.3366.com");
    System.security.allowDomain("a2.img.3366.com");
    System.security.allowDomain("a3.img.3366.com");
    System.security.allowDomain("a4.img.3366.com");
    System.security.allowDomain("cgi.3366.com");
    System.security.allowDomain("fcg.3366.com");
    System.security.allowDomain("www.3366.com");
    var pageLocation = ExternalInterface.call("eval", "location.href");
    var cookiesRefreshTimer = 0;
    var clockCheckTimer = 0;
    var key = "";
    var gameObject = {};
    var isSubmit = false;
    var owner = this;
    var hasKey = false;
    var _timePass = true;
    var _times = 0;
    var _startTime = new Date();
    var _lastTime = new Date();
    var _currentTime = new Date();
    var SUBMIT_URL = ["http://fcg.3366.com/fcg-bin/scoregame/mgp_score_qz_play", "http://fcg.3366.com/fcg-bin/qz/play", "http://fcg.3366.com/fcg-bin/qz/cgi_pk_post_score", "http://fcg.3366.com/fcg-bin/xiaoyou/xy_play", "http://fcg.3366.com/fcg-bin/xiaoyou/xy_cgi_pk_post_score", "http://fcg.3366.com/fcg-bin/webqq/webqq_cgi_play", "http://fcg.3366.com/fcg-bin/webqq/webqq_cgi_pk_post_score", "http://fcg.3366.com/fcg-bin/qz/qz_challenge_post_score", "http://fcg.3366.com/fcg-bin/qz/qz_post_attact_score", "http://fcg.3366.com/fcg-bin/qz/qz_post_sysarena_score"];
    var GET_URL = ["http://fcg.3366.com/fcg-bin/scoregame/mgp_score_qz_play", "http://fcg.3366.com/fcg-bin/qz/play", "http://fcg.3366.com/fcg-bin/xiaoyou/xy_play", "http://fcg.3366.com/fcg-bin/webqq/webqq_cgi_play"];
    var GET_MODE = 0;
    var SUBMIT_MODE = 0;
    var json = new JSON();
    var JSEVENT = {c701:{type:701, msg:"检测到系统速率异常，将不能提交分数！"}, c901:{type:901, msg:"检测到当前环境为本地环境,以模拟方式运行."}, c1000:{type:1000, msg:"最终游戏分数提交成功!"}, c1000:{type:1001, msg:"最终游戏分数提交失败!"}, c1002:{type:1002, msg:"游戏授权成功,可以开始游戏!"}, c1003:{type:1003, msg:"自动分数提交!"}, c1004:{type:1004, msg:"获取游戏分数出错!"}, c1005:{type:1005, msg:"提交当前阶段游戏分数,注意当前以模拟方式运行!未发送至服务器!"}, c1006:{type:1006, msg:"获取制定游戏分数错误!"}, c1007:{type:1007, msg:"提交当前游戏分数!"}, c1020:{type:1020, msg:"显示排行榜"}};
    flash.external.ExternalInterface.addCallback("reSubmit", this, gameOver);
----------------------------------------------------------------------
Symbol 1 MovieClip [__Packages.JSON] Frame 0
----------------------------------------------------------------------
    class JSON
    {
        var text;
        function JSON () {
        }
        function encode(arg) {
            return(stringify(arg));
        }
        function decode(arg) {
            return(parse(arg));
        }
        function stringify(arg) {
            var _local4;
            var _local3;
            var _local7;
            var _local2 = "";
            var _local5;
            switch (typeof(arg)) {
                case "object" : 
                    if (arg) {
                        if (arg instanceof Array) {
                            _local3 = 0;
                            while (_local3 < arg.length) {
                                _local5 = stringify(arg[_local3]);
                                if (_local2) {
                                    _local2 = _local2 + ",";
                                }
                                _local2 = _local2 + _local5;
                                _local3++;
                            }
                            return(("[" + _local2) + "]");
                        } else if (typeof(arg.toString) != "undefined") {
                            for (_local3 in arg) {
                                _local5 = arg[_local3];
                                if ((typeof(_local5) != "undefined") && (typeof(_local5) != "function")) {
                                    _local5 = stringify(_local5);
                                    if (_local2) {
                                        _local2 = _local2 + ",";
                                    }
                                    _local2 = _local2 + ((stringify(_local3) + ":") + _local5);
                                }
                            }
                            return(("{" + _local2) + "}");
                        }
                    }
                    return("null");
                case "number" : 
                    return((isFinite(arg) ? (String(arg)) : "null"));
                case "string" : 
                    _local7 = arg.length;
                    _local2 = "\"";
                    _local3 = 0;
                    while (_local3 < _local7) {
                        _local4 = arg.charAt(_local3);
                        if (_local4 >= " ") {
                            if ((_local4 == "\\") || (_local4 == "\"")) {
                                _local2 = _local2 + "\\";
                            }
                            _local2 = _local2 + _local4;
                        } else {
                            switch (_local4) {
                                case "\b" : 
                                    _local2 = _local2 + "\\b";
                                    break;
                                case "\f" : 
                                    _local2 = _local2 + "\\f";
                                    break;
                                case newline : 
                                    _local2 = _local2 + "\\n";
                                    break;
                                case "\r" : 
                                    _local2 = _local2 + "\\r";
                                    break;
                                case "\t" : 
                                    _local2 = _local2 + "\\t";
                                    break;
                                default : 
                                    _local4 = _local4.charCodeAt();
                                    _local2 = _local2 + (("\\u00" + Math.floor(_local4 / 16).toString(16)) + (_local4 % 16).toString(16));
                            }
                        }
                        _local3 = _local3 + 1;
                    }
                    return(_local2 + "\"");
                case "boolean" : 
                    return(String(arg));
            }
            return("null");
        }
        function white() {
            while (ch) {
                if (ch <= " ") {
                    next();
                } else if (ch == "/") {
                    switch (next()) {
                        case "/" : 
                            while ((next() && (ch != newline)) && (ch != "\r")) {
                            }
                            break;
                        case "*" : 
                            next();
                            for(;;){
                                if (ch) {
                                    if (ch == "*") {
                                        if (next() == "/") {
                                            next();
                                            // unexpected jump
                                        }
                                    } else {
                                        next();
                                    }
                                } else {
                                    error("Unterminated comment");
                                }
                            };
                            break;
                        default : 
                            error("Syntax error");
                    }
                } else {
                    break;
                }
            }
        }
        function error(m) {
            throw {name:"JSONError", message:m, at:at - 1, text:text};
        }
        function next() {
            ch = text.charAt(at);
            at = at + 1;
            return(ch);
        }
        function str() {
            var _local5;
            var _local2 = "";
            var _local4;
            var _local3;
            var _local6 = false;
            if (ch == "\"") {
                while (next()) {
                    if (ch == "\"") {
                        next();
                        return(_local2);
                    } else if (ch == "\\") {
                        switch (next()) {
                            case "b" : 
                                _local2 = _local2 + "\b";
                                break;
                            case "f" : 
                                _local2 = _local2 + "\f";
                                break;
                            case "n" : 
                                _local2 = _local2 + newline;
                                break;
                            case "r" : 
                                _local2 = _local2 + "\r";
                                break;
                            case "t" : 
                                _local2 = _local2 + "\t";
                                break;
                            case "u" : 
                                _local3 = 0;
                                _local5 = 0;
                                while (_local5 < 4) {
                                    _local4 = parseInt(next(), 16);
                                    if (!isFinite(_local4)) {
                                        _local6 = true;
                                        break;
                                    }
                                    _local3 = (_local3 * 16) + _local4;
                                    _local5 = _local5 + 1;
                                }
                                if (_local6) {
                                    _local6 = false;
                                    break;
                                }
                                _local2 = _local2 + String.fromCharCode(_local3);
                                break;
                            default : 
                                _local2 = _local2 + ch;
                        }
                    } else {
                        _local2 = _local2 + ch;
                    }
                }
            }
            error("Bad string");
        }
        function arr() {
            var _local2 = [];
            if (ch == "[") {
                next();
                white();
                if (ch == "]") {
                    next();
                    return(_local2);
                }
                while (ch) {
                    _local2.push(value());
                    white();
                    if (ch == "]") {
                        next();
                        return(_local2);
                    } else if (ch != ",") {
                        break;
                    }
                    next();
                    white();
                }
            }
            error("Bad array");
        }
        function obj() {
            var _local3;
            var _local2 = {};
            if (ch == "{") {
                next();
                white();
                if (ch == "}") {
                    next();
                    return(_local2);
                }
                while (ch) {
                    _local3 = str();
                    white();
                    if (ch != ":") {
                        break;
                    }
                    next();
                    _local2[_local3] = value();
                    white();
                    if (ch == "}") {
                        next();
                        return(_local2);
                    } else if (ch != ",") {
                        break;
                    }
                    next();
                    white();
                }
            }
            error("Bad object");
        }
        function num() {
            var _local2 = "";
            var _local3;
            if (ch == "-") {
                _local2 = "-";
                next();
            }
            while ((ch >= "0") && (ch <= "9")) {
                _local2 = _local2 + ch;
                next();
            }
            if (ch == ".") {
                _local2 = _local2 + ".";
                next();
                while ((ch >= "0") && (ch <= "9")) {
                    _local2 = _local2 + ch;
                    next();
                }
            }
            if ((ch == "e") || (ch == "E")) {
                _local2 = _local2 + ch;
                next();
                if ((ch == "-") || (ch == "+")) {
                    _local2 = _local2 + ch;
                    next();
                }
                while ((ch >= "0") && (ch <= "9")) {
                    _local2 = _local2 + ch;
                    next();
                }
            }
            _local3 = Number(_local2);
            if (!isFinite(_local3)) {
                error("Bad number");
            }
            return(_local3);
        }
        function word() {
            switch (ch) {
                case "t" : 
                    if (((next() == "r") && (next() == "u")) && (next() == "e")) {
                        next();
                        return(true);
                    }
                    break;
                case "f" : 
                    if ((((next() == "a") && (next() == "l")) && (next() == "s")) && (next() == "e")) {
                        next();
                        return(false);
                    }
                    break;
                case "n" : 
                    if (((next() == "u") && (next() == "l")) && (next() == "l")) {
                        next();
                        return(null);
                    }
                    break;
            }
            error("Syntax error");
        }
        function value() {
            white();
            switch (ch) {
                case "{" : 
                    return(obj());
                case "[" : 
                    return(arr());
                case "\"" : 
                    return(str());
                case "-" : 
                    return(num());
            }
            return((((ch >= "0") && (ch <= "9")) ? (num()) : (word())));
        }
        function parse(_text) {
            text = _text;
            at = 0;
            ch = " ";
            return(value());
        }
        var ch = "";
        var at = 0;
    }

