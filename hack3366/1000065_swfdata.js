    function tipFunction(obj) {
        trace(((("type:" + obj.type) + " msg:") + obj.msg) + newline);
    }
    function start0() {
        trace("start");
        comm.gameStart(_root.pid, _root, "score", tipFunction, startFunction);
    }
    function startFunction() {
        _root.canPlay = true;
        if (loading.done) {
            play();
        }
    }
    stop();
    System.security.allowDomain("img.3366.com");
    if (domain) {
        System.security.allowDomain(domain + ".3366.com");
    }
    _root.score = 0;
    this.createEmptyMovieClip("comm", this.getNextHighestDepth());
    var mclListener = new Object();
    mclListener.onLoadInit = start0;
    var mcl = new MovieClipLoader();
    mcl.addListener(mclListener);
    mcl.loadClip("http://img.3366.com/fileupload/flash/com/comm.swf", comm);
    stopAllSounds();
    _root.v = true;
    loading.onComplete = function () {
        if (_root.canPlay) {
            play();
        }
    };

----------------------------------------------------------------------
Frame 3
----------------------------------------------------------------------
    function empty() {
        _root.fdj = 0;
        _root.strong = false;
        _root.xzball = false;
        _root.luck = false;
        _root.kqk = false;
    }
    stop();
    select = 0;
    score = 0;
    pause = false;
    down = 75;
    up = 73;
    bomb = 0;
    fdj = 0;
    strong = false;
    xzball = false;
    luck = false;
    kqk = false;
    scoreup = new Sound();
    scoreup.attachSound("scoreup");
    fx = new Sound();
    fx.attachSound("fx");
    fk = new Sound();
    fk.attachSound("fk");
    an = new Sound();
    an.attachSound("an");
    shou = new Sound();
    shou.attachSound("shou");
    bell = new Sound();
    bell.attachSound("bell");
    bad = new Sound();
    bad.attachSound("bad");
    good = new Sound();
    good.attachSound("good");
    cool = new Sound();
    cool.attachSound("cool");
    bird = new Sound();
    bird.attachSound("bird");
    itemup = new Sound();
    itemup.attachSound("itemup");
    gold = new Sound();
    gold.attachSound("gold");
    _root.v = true;
    var mp3_sound = new Sound();
    mp3_sound.attachSound("bgmusic");

----------------------------------------------------------------------
Symbol 4 MovieClip Frame 1
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Symbol 4 MovieClip Frame 100
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Symbol 14 MovieClip Frame 1
----------------------------------------------------------------------
    var onProgress;
    var onComplete;
    var done = false;
    _root.stop();
    this.onEnterFrame = function () {
        var _local2 = Math.floor((_level0.getBytesLoaded() / _level0.getBytesTotal()) * 100);
        onProgress(_local2);
        if (_level0.getBytesLoaded() == _level0.getBytesTotal()) {
            onComplete();
            done = true;
            delete this.onEnterFrame;
        }
        bar.gotoAndStop(_local2);
    };
    this._x = Stage.width / 2;
    this._y = Stage.height / 2;

----------------------------------------------------------------------
Symbol 25 MovieClip Frame 1
----------------------------------------------------------------------
    _visible  = false;
    stop();

----------------------------------------------------------------------
Symbol 28 MovieClip Frame 1
----------------------------------------------------------------------
    _visible  = false;
    stop();

----------------------------------------------------------------------
Symbol 28 MovieClip Frame 6
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Symbol 55 Button
----------------------------------------------------------------------
on (release) {
    nextFrame();
}
----------------------------------------------------------------------
Symbol 65 Button
----------------------------------------------------------------------
on (press) {
    _root.gamePause = false;
    this._visible = false;
    _root.gotoAndPlay(2);
}
----------------------------------------------------------------------
Symbol 66 Button
----------------------------------------------------------------------
on (press) {
    _root.gamePause = false;
    this._visible = false;
}
----------------------------------------------------------------------
Symbol 72 Button
----------------------------------------------------------------------
on (release) {
    if (_root.gamePause) {
        _root.gamePause = false;
    } else {
        _root.gotoAndPlay(2);
    }
    this.gotoAndStop(1);
    this._visible = false;
}
----------------------------------------------------------------------
Symbol 75 MovieClip Frame 5
----------------------------------------------------------------------
    stop();
----------------------------------------------------------------------
Symbol 92 MovieClip Frame 9
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Symbol 95 Button
----------------------------------------------------------------------
on (release) {
    Round++;
    _root.Mscore = scor[Round][0] + random(100);
    gotoAndStop (3);
}
----------------------------------------------------------------------
Symbol 115 Button
----------------------------------------------------------------------
on (rollOver) {
    output = ("炸弹 $" + pp_0) + "\n在抓到异物后，按 i 键使用炸弹将其炸掉。";
}
on (release) {
    if ((_root.bomb < 8) && (_root.score >= pp_0)) {
        _root.cool.start();
        _root.gold.start();
        _root.bomb++;
        _root.score = _root.score - pp_0;
        shop0._visible = false;
        p_0 = "";
    } else {
        _root.bad.start();
    }
}
----------------------------------------------------------------------
Symbol 120 Button
----------------------------------------------------------------------
on (rollOver) {
    output = ("能量饮料 $" + pp_1) + "\n加快挖金子的速度。（限用本轮）";
}
on (release) {
    if (_root.score >= pp_1) {
        _root.cool.start();
        _root.gold.start();
        _root.strong = true;
        _root.score = _root.score - pp_1;
        shop1._visible = false;
        p_1 = "";
    } else {
        _root.bad.start();
    }
}
----------------------------------------------------------------------
Symbol 125 Button
----------------------------------------------------------------------
on (rollOver) {
    output = ("魔棒 $" + pp_2) + "\n使抓到蛇和蜗牛获得的金额是原来的4倍。（限用本轮）";
}
on (release) {
    if (_root.score >= pp_2) {
        _root.cool.start();
        _root.gold.start();
        _root.fdj = 3;
        _root.score = _root.score - pp_2;
        shop2._visible = false;
        p_2 = "";
    } else {
        _root.bad.start();
    }
}
----------------------------------------------------------------------
Symbol 130 Button
----------------------------------------------------------------------
on (rollOver) {
    output = ("旋转时钟 $" + pp_4) + "\n加速机械爪的摆动速率。（限用本轮）";
}
on (release) {
    if (_root.score >= pp_4) {
        _root.cool.start();
        _root.gold.start();
        _root.xzball = true;
        _root.score = _root.score - pp_4;
        shop4._visible = false;
        p_4 = "";
    } else {
        _root.bad.start();
    }
}
----------------------------------------------------------------------
Symbol 136 MovieClip Frame 1
----------------------------------------------------------------------
    stop();
    this.onEnterFrame = function () {
        gotoAndStop(_root.bomb + 1);
    };
----------------------------------------------------------------------
Symbol 141 Button
----------------------------------------------------------------------
on (rollOver) {
    output = ("幸运草 $" + pp_3) + "\n增大抓到福袋时获得宝物的机率。（限用本轮）";
}
on (release) {
    if (_root.score >= pp_3) {
        _root.cool.start();
        _root.gold.start();
        _root.luck = true;
        _root.score = _root.score - pp_3;
        shop3._visible = false;
        p_3 = "";
    } else {
        _root.bad.start();
    }
}
----------------------------------------------------------------------
Symbol 146 Button
----------------------------------------------------------------------
on (rollOver) {
    output = ("钻石卡 $" + pp_5) + "\n增大挖到钻石后兑换的金额。（限用本轮）";
}
on (release) {
    if (_root.score >= pp_5) {
        _root.cool.start();
        _root.gold.start();
        _root.kqk = true;
        _root.score = _root.score - pp_5;
        shop5._visible = false;
        p_5 = "";
    } else {
        _root.bad.start();
    }
}
----------------------------------------------------------------------
Symbol 149 Button
----------------------------------------------------------------------
on (release) {
    _root.start0();
    stopAllSounds();
    _root.gotoAndPlay(2);
}
----------------------------------------------------------------------
Symbol 153 MovieClip Frame 2
----------------------------------------------------------------------
    highScores_btn.onRelease = function () {
        _root.comm.showScoreList();
    };
    stop();
----------------------------------------------------------------------
Symbol 155 MovieClip Frame 1
----------------------------------------------------------------------
    trace("_parent:" + _parent.Round);

----------------------------------------------------------------------
Symbol 155 MovieClip Frame 8
----------------------------------------------------------------------
    out = _parent.Round;
    stop();
    my_data = new Date();
    year = my_data.getFullYear();
    month = my_data.getMonth() + 1;
    if (month < 10) {
        m_month = "0" + month;
    } else {
        m_month = month;
    }
    var dt = my_data.getDate();
    if (date < 10) {
        m_date = "0" + dt;
    } else {
        m_date = dt;
    }
    hour = my_data.getHours();
    if (hour < 10) {
        m_hour = "0" + hour;
    } else {
        m_hour = hour;
    }
    minutes = my_data.getMinutes();
    if (minutes < 10) {
        m_minutes = "0" + minutes;
    } else {
        m_minutes = minutes;
    }
    seconds = my_data.getSeconds();
    if (seconds < 10) {
        m_seconds = "0" + seconds;
    } else {
        m_seconds = seconds;
    }
    i = 0;
    while (i < 6) {
        this["num" + i] = random(10);
        i++;
    }
    my_str = new String();
    _root.orderId = my_str.concat(year, m_month, m_date, m_hour, m_minutes, m_seconds, num0, num1, num2, num3, num4, num5);
    _root.comm.gameOver();
    trace(_root.comm);

----------------------------------------------------------------------
Symbol 159 MovieClip Frame 1
----------------------------------------------------------------------
    stopAllSounds();

----------------------------------------------------------------------
Symbol 159 MovieClip Frame 8
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Instance of Symbol 166 MovieClip in Symbol 179 MovieClip Frame 1
----------------------------------------------------------------------
onClipEvent (load) {
    _visible  = false;
}
onClipEvent (enterFrame) {
    if (_root.strong == true) {
        _visible  = true;
    } else {
        _visible  = false;
    }
}
----------------------------------------------------------------------
Instance of Symbol 169 MovieClip in Symbol 179 MovieClip Frame 1
----------------------------------------------------------------------
onClipEvent (load) {
    _visible  = false;
}
onClipEvent (enterFrame) {
    if (_root.luck == true) {
        _visible  = true;
    } else {
        _visible  = false;
    }
}
----------------------------------------------------------------------
Instance of Symbol 172 MovieClip in Symbol 179 MovieClip Frame 1
----------------------------------------------------------------------
onClipEvent (load) {
    _visible  = false;
}
onClipEvent (enterFrame) {
    q = _parent._parent.qianzi;
    if (_root.xzball == true) {
        q.rotspeed = 5;
        _visible  = true;
    } else {
        q.rotspeed = q.m_rotspeed;
        _visible  = false;
    }
}
----------------------------------------------------------------------
Instance of Symbol 175 MovieClip in Symbol 179 MovieClip Frame 1
----------------------------------------------------------------------
onClipEvent (load) {
    _visible  = false;
}
onClipEvent (enterFrame) {
    if (_root.kqk == true) {
        _visible  = true;
    } else {
        _visible  = false;
    }
}
----------------------------------------------------------------------
Instance of Symbol 178 MovieClip in Symbol 179 MovieClip Frame 1
----------------------------------------------------------------------
onClipEvent (load) {
    _visible  = false;
}
onClipEvent (enterFrame) {
    if (_root.fdj > 0) {
        _parent.fdjout = _root.fdj;
        _visible  = true;
    } else {
        _parent.fdjout = "";
        _visible  = false;
    }
}
----------------------------------------------------------------------
Symbol 183 Button
----------------------------------------------------------------------
on (press) {
    _root.game.pausepanel._visible = true;
    _root.game.helppanel._visible = false;
    _root.game.exitpanel._visible = false;
    _root.gamePause = true;
    stopAllSounds();
}
----------------------------------------------------------------------
Symbol 189 Button
----------------------------------------------------------------------
on (press) {
    _root.game.helppanel._visible = true;
    _root.game.helppanel.gotoAndPlay(2);
    _root.game.pausepanel._visible = false;
    _root.game.exitpanel._visible = false;
    _root.gamePause = true;
    stopAllSounds();
}
----------------------------------------------------------------------
Symbol 192 Button
----------------------------------------------------------------------
on (press) {
    _root.game.pausepanel._visible = false;
    _root.game.exitpanel._visible = true;
    _root.game.helppanel._visible = false;
    _root.gamePause = true;
    stopAllSounds();
}
----------------------------------------------------------------------
Symbol 204 MovieClip Frame 1
----------------------------------------------------------------------
    stop();
    t.onRelease = function () {
        _parent.v = !_parent.v;
        _parent.onoff();
    };

----------------------------------------------------------------------
Symbol 204 MovieClip Frame 2
----------------------------------------------------------------------
    stop();
    t.onRelease = function () {
        _parent.v = !_parent.v;
        _parent.onoff();
    };

----------------------------------------------------------------------
Symbol 205 MovieClip Frame 4
----------------------------------------------------------------------
    function onoff() {
        if (v) {
            onoff_mc.gotoAndStop(1);
            _root.v = true;
            var m = 0;
            onEnterFrame = function () {
                m = m + 10;
                if (m > 80) {
                    m = 80;
                    delete onEnterFrame;
                }
                _root.mp3_sound.setVolume(m);
            };
        } else {
            _root.v = false;
            stopAllSounds();
            onoff_mc.gotoAndStop(2);
            var n = 80;
            onEnterFrame = function () {
                n = n - 10;
                if (n < 0) {
                    n = 0;
                    delete onEnterFrame;
                }
                _root.mp3_sound.setVolume(n);
            };
        }
    }
    stop();
    _root.mp3_sound.start(0, 99999);
    if (_root.v) {
        onoff_mc.gotoAndStop(1);
        _root.mp3_sound.setVolume(80);
        var v = true;
    } else {
        _root.mp3_sound.setVolume(0);
        onoff_mc.gotoAndStop(2);
        var v = false;
    }
----------------------------------------------------------------------
Symbol 209 MovieClip Frame 1
----------------------------------------------------------------------
    _visible  = false;

----------------------------------------------------------------------
Symbol 215 MovieClip Frame 1
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Instance of Symbol 209 MovieClip in Symbol 215 MovieClip Frame 1
----------------------------------------------------------------------
onClipEvent (enterFrame) {
    q = _parent._parent.qianzi;
    if (q.go == 1) {
        _parent.gotoAndStop("放线");
    }
}
----------------------------------------------------------------------
Symbol 215 MovieClip Frame 3
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Instance of Symbol 209 MovieClip in Symbol 215 MovieClip Frame 3
----------------------------------------------------------------------
onClipEvent (enterFrame) {
    q = _parent._parent.qianzi;
    if (q.out == 1) {
        _parent.gotoAndStop("收线");
    }
}
----------------------------------------------------------------------
Symbol 215 MovieClip Frame 6
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Instance of Symbol 209 MovieClip in Symbol 215 MovieClip Frame 6
----------------------------------------------------------------------
onClipEvent (enterFrame) {
    q = _parent._parent.qianzi;
    if (q._y <= q.csy) {
        _parent.gotoAndStop("站");
    }
}
----------------------------------------------------------------------
Symbol 215 MovieClip Frame 17
----------------------------------------------------------------------
    gotoAndStop (1);
----------------------------------------------------------------------
Symbol 228 MovieClip Frame 1
----------------------------------------------------------------------
    gotoAndPlay(Math.floor(Math.random(30)));

----------------------------------------------------------------------
Symbol 228 MovieClip Frame 92
----------------------------------------------------------------------
    gotoAndPlay (2);
----------------------------------------------------------------------
Symbol 229 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.good.start(0.1);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 4;
            } else {
                q.speeds = 8;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    _parent.showScore.out = 300;
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot * 2) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 232 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.good.start(0.1);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 5;
            } else {
                q.speeds = 8;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    _parent.showScore.out = 200;
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 245 MovieClip Frame 1
----------------------------------------------------------------------
    gotoAndPlay(Math.floor(Math.random(30)));

----------------------------------------------------------------------
Symbol 245 MovieClip Frame 75
----------------------------------------------------------------------
    gotoAndPlay (2);
----------------------------------------------------------------------
Symbol 246 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.cool.start();
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 2;
            } else {
                q.speeds = 4;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    _parent.showScore.out = 500;
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot * 2) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 254 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.good.start();
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 5;
            } else {
                q.speeds = 8;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    if (_root.luck == true) {
                        lucknum = 2;
                    } else {
                        lucknum = 4;
                    }
                    aaa = random(lucknum);
                    if (aaa == 0) {
                        _parent.showScore.out = random(451) + 400;
                        _root.scoreup.start();
                        _parent.showScore.gotoAndPlay(2);
                    }
                    if (aaa == 1) {
                        _parent.takeitem.gotoAndPlay("炸弹增加");
                    }
                    if ((aaa != 0) && (aaa != 1)) {
                        _parent.showScore.out = random(351) + 350;
                        _root.scoreup.start();
                        _parent.showScore.gotoAndPlay(2);
                    }
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot * 2) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 262 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.bad.start(0.1);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 2;
            } else {
                q.speeds = 4;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    if (_root.fdj > 0) {
                        _parent.showScore.out = 200;
                        _root.fdj--;
                    } else {
                        _parent.showScore.out = 50;
                    }
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 265 MovieClip Frame 2
----------------------------------------------------------------------
    stop();
    m_speedf = (speedf = 10);
    m_speeds = (speeds = 23);
    m_rotspeed = (rotspeed = 3);
    rot = 70;
    lock = 0;
    lock1 = 0;
    go = 0;
    out = 0;
    csx = _x;
    csy = _y;
    cs = 0;
    this.onEnterFrame = function () {
        if ((_root.pause == false) && (!_root.gamePause)) {
            _parent.line._visible = true;
            this._visible = true;
            posX = Math.sin(angle);
            posY = Math.cos(angle);
            angle = _rotation * 0.017453;
            if (((_x >= 550) || (_x <= 0)) || (_y >= 400)) {
                out = 1;
            }
            if (((_rotation <= rot) && (lock == 0)) && (lock1 == 0)) {
                _rotation  = (_rotation + rotspeed);
                if (_rotation >= rot) {
                    lock = 1;
                }
            }
            if (((_rotation >= (-rot)) && (lock == 1)) && (lock1 == 0)) {
                _rotation  = (_rotation - rotspeed);
                if (_rotation <= (-rot)) {
                    lock = 0;
                }
            }
            if (Key.isDown(_root.down) && (go == 0)) {
                lock1 = 1;
                go = 1;
                _root.an.start(0.2);
                _root.fx.start(0.4);
            }
            if ((go == 1) && (out == 0)) {
                _x  = (_x - (posX * speedf));
                _y  = (_y + (posY * speedf));
            }
            if ((out == 1) && (_y > csy)) {
                _x  = (_x + (posX * speeds));
                _y  = (_y - (posY * speeds));
            }
            if (((out == 1) && (_y > csy)) && (_rotation == 0)) {
                _x  = (_x + 0);
                _y  = (_y - speeds);
            }
            if ((_y <= csy) && (out == 1)) {
                _x  = csx;
                _y  = csy;
                lock1 = 0;
                out = 0;
                go = 0;
            }
            with (_parent) {
                qidian_x = qianzi.csx;
                qidian_y = qianzi.csy;
                with (line) {
                    _x = qidian_x;
                    _y = qidian_y;
                    _xscale = 0;
                    _yscale = 0;
                    _visible = 1;
                }
                endX = Math.abs(qianzi._x);
                endY = Math.abs(qianzi._y);
                line._xscale = endX - qidian_x;
                line._yscale = endY - qidian_y;
            }
        } else {
            _parent.line._visible = false;
            this._visible = false;
        }
    };

----------------------------------------------------------------------
Symbol 269 MovieClip Frame 1
----------------------------------------------------------------------
    tim = 40;
    a = getTimer();
    this.onEnterFrame = function () {
        if (!_root.gamePause) {
            b = getTimer() - a;
            if (b >= 1000) {
                if (tim < 11) {
                    _root.bell.start();
                }
                tim--;
                a = getTimer();
                if (tim <= 10) {
                    my_fmt = new TextFormat();
                    my_fmt["color"] = 16711680 /* 0xFF0000 */;
                    tt.setTextFormat(my_fmt);
                } else {
                    delete my_fmt;
                }
                if (tim <= -1) {
                    _root.empty();
                    if (_root.score >= _root.Mscore) {
                        _parent.gotoAndPlay("pass");
                    } else {
                        _parent.gotoAndStop("over");
                    }
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 270 MovieClip Frame 1
----------------------------------------------------------------------
    _visible  = false;
    stop();
    this.onEnterFrame = function () {
        if (_parent.qianzi.out == 1) {
            play();
        } else {
            stop();
        }
    };

----------------------------------------------------------------------
Symbol 286 MovieClip Frame 1
----------------------------------------------------------------------
    stop();

----------------------------------------------------------------------
Symbol 286 MovieClip Frame 5
----------------------------------------------------------------------
    _root.score = _root.score + out;

----------------------------------------------------------------------
Symbol 286 MovieClip Frame 23
----------------------------------------------------------------------
    out = "";

----------------------------------------------------------------------
Symbol 296 MovieClip Frame 1
----------------------------------------------------------------------
    stop();
----------------------------------------------------------------------
Symbol 296 MovieClip Frame 2
----------------------------------------------------------------------
    _parent[man].gotoAndPlay("扔");

----------------------------------------------------------------------
Symbol 296 MovieClip Frame 19
----------------------------------------------------------------------
    _parent[na]._visible = false;
    _parent.qianzi.speeds = _parent.qianzi.m_speeds;
    _root.pause = false;
----------------------------------------------------------------------
Symbol 305 MovieClip Frame 1
----------------------------------------------------------------------
    _x  = 750;
    stop();

----------------------------------------------------------------------
Symbol 313 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.bad.start(0.1);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 1;
            } else {
                q.speeds = 3;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    if (_root.fdj > 0) {
                        _parent.showScore.out = 400;
                        _root.fdj--;
                    } else {
                        _parent.showScore.out = 100;
                    }
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot * 2) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 320 MovieClip Frame 1
----------------------------------------------------------------------
    weight = 4;
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.cool.start(0.1);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 2;
            } else {
                q.speeds = 4;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    if (_root.luck == true) {
                        lucknum = 4;
                    } else {
                        lucknum = 8;
                    }
                    aaa = random(lucknum);
                    if (aaa == 0) {
                        _parent.takeitem.gotoAndPlay("力量增加");
                    }
                    if (aaa == 1) {
                        _parent.takeitem.gotoAndPlay("炸弹增加");
                    }
                    if (aaa == 2) {
                        _parent.showScore.out = random(301) + 1000;
                        _root.scoreup.start();
                        _parent.showScore.gotoAndPlay(2);
                    }
                    if (((aaa != 0) && (aaa != 1)) && (aaa != 2)) {
                        _parent.showScore.out = random(401) + 800;
                        _root.scoreup.start();
                        _parent.showScore.gotoAndPlay(2);
                    }
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot * 2) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 338 MovieClip Frame 1
----------------------------------------------------------------------
    fx = random(2);
    cc = _xscale;
    bspeed = random(5) + 3;
    weight = 4;
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.bird.start();
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 4;
            } else {
                q.speeds = 8;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    _parent.showScore.out = 10;
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
        if (fx == 0) {
            _xscale  = cc;
            _x  = (_x - bspeed);
            if (_x <= 10) {
                fx = 1;
                bspeed = random(3) + 3;
            }
        }
        if (fx == 1) {
            _xscale  = (-cc);
            _x  = (_x + bspeed);
            if (_x >= 540) {
                fx = 0;
                bspeed = random(3) + 3;
            }
        }
    };

----------------------------------------------------------------------
Symbol 353 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.cool.start(0.1);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 5;
            } else {
                q.speeds = 8;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    if (_root.kqk == true) {
                        _parent.showScore.out = 1500;
                    } else {
                        _parent.showScore.out = 1000;
                    }
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 361 MovieClip Frame 1
----------------------------------------------------------------------
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.bad.start(0.1);
                _parent.bz._x = _x;
                _parent.bz._y = _y;
                _parent.bz.gotoAndPlay(2);
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 4;
            } else {
                q.speeds = 7;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(2);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    _parent.showScore.out = 10;
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot * 2) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
    };

----------------------------------------------------------------------
Symbol 373 MovieClip Frame 1
----------------------------------------------------------------------
    fx = random(2);
    cc = _xscale;
    bspeed = random(5) + 3;
    weight = 4;
    hited = 0;
    i = 0;
    time = 20;
    this.onEnterFrame = function () {
        if (box.hitTest(_parent.bz.hit)) {
            _visible  = false;
            delete this.onEnterFrame;
        }
        q = _parent.qianzi;
        if (box.hitTest(q.fk) && (q.out != 1)) {
            if (hited != 1) {
                _root.bird.start();
                _root.cool.start();
            }
            hited = 1;
            _rotation  = q._rotation;
            if (_root.strong == false) {
                q.speeds = 4;
            } else {
                q.speeds = 8;
            }
            q.out = 1;
        }
        if (hited == 1) {
            if (Key.isDown(_root.up)) {
                if (_root.bomb > 0) {
                    _root.pause = true;
                    _root.bomb--;
                    _parent.tbomb._x = _x;
                    _parent.tbomb._y = _y;
                    _parent.tbomb.na = _name;
                    _parent.tbomb.gotoAndPlay(2);
                    delete this.onEnterFrame;
                }
            }
            _x  = q._x;
            _y  = q._y;
            jb.gotoAndStop(1);
            if (q._y <= q.csy) {
                if (_root.pause == false) {
                    if (_root.kqk == true) {
                        _parent.showScore.out = 1500;
                    } else {
                        _parent.showScore.out = 1000;
                    }
                    _root.scoreup.start();
                    _parent.showScore.gotoAndPlay(2);
                }
                _root.pause = true;
                if (i < time) {
                    i++;
                } else {
                    _root.pause = false;
                    q.speeds = q.m_speeds;
                    _visible  = false;
                    q._rotation = 0;
                    _root.fk.start();
                    q._rotation = random(q.rot) - q.rot;
                    delete this.onEnterFrame;
                }
            }
        }
        if (fx == 0) {
            _xscale  = cc;
            _x  = (_x - bspeed);
            if (_x <= 10) {
                fx = 1;
                bspeed = random(3) + 3;
            }
        }
        if (fx == 1) {
            _xscale  = (-cc);
            _x  = (_x + bspeed);
            if (_x >= 540) {
                fx = 0;
                bspeed = random(3) + 3;
            }
        }
    };

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 1
----------------------------------------------------------------------
    function drawLine() {
        stopAllSounds();
        _root.pause = false;
        _root.mp3.gotoAndPlay("音乐1");
        createEmptyMovieClip("line", n);
        with (line) {
            lineStyle(0, 0, 100);
            moveTo(0, 0);
            lineTo(100, 100);
            line._visible = 0;
        }
    }
    Stage.showMenu = false;
    Stage.scaleMode = "noscale";
    stop();
    Round = 1;
    scor = [["no", "no"], [1500, "2100"], [3200, "2800"], [4500, "3100"], [6000, "3500"], [8500, "3900"], [12000, "3100"], [15000, "3700"], [18000, "3300"], [20000, "4300"], [23500, "4000"], [30000, "7300"], [33500, "5600"], [37000, "5200"], [43000, "6500"], [46000, "7300"], [50000, "5700"], [54000, "5700"], [58000, "5000"], [63000, "4400"], [66000, "4200"], [69000, "4300"], [73000, "4000"], [77000, "6000"], [80000, "3000"], [83000, "3400"], [87000, "5000"], [90000, "4600"], [94000, "4200"], [100000, "7300"], [107500, "7600"], [111000, "7100"], [128000, "7000"], [134000, "6300"], [149000, "7300"], [155000, "3200"]];
    _root.Mscore = scor[1][0];
    highScores_btn.onRelease = function () {
        _root.comm.showScoreList();
    };
    helppanel._visible = false;
    helpa.onRelease = function () {
        helppanel._visible = true;
        helppanel.gotoAndPlay(2);
    };
    exitpanel._visible = false;
    helppanel._visible = false;
    pausepanel._visible = false;

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 2
----------------------------------------------------------------------
    _root.select = 3;
    play();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 3
----------------------------------------------------------------------
    stop();
    _root.gamePause = false;
    pausepanel.visible = false;

----------------------------------------------------------------------
Instance of Symbol 85 MovieClip in Symbol 374 MovieClip Frame 3
----------------------------------------------------------------------
onClipEvent (load) {
    i = 0;
    _visible  = false;
}
onClipEvent (enterFrame) {
    i++;
    if (i > 50) {
        _parent.gotoAndStop(_parent.Round + "st");
    }
}
----------------------------------------------------------------------
Symbol 374 MovieClip Frame 5
----------------------------------------------------------------------
    stop();
    var n = 0;
    ii = 0;
    while (ii < 6) {
        sho = random(3);
        if (sho == 0) {
            this["shop" + ii]._visible = true;
            n++;
        } else {
            this["p_" + ii] = "";
            this["shop" + ii]._visible = false;
        }
        ii++;
    }
    if (n == 0) {
        shop0._visible = true;
    }
    if (shop0._visible != false) {
        pp_0 = random(400) + 100;
        p_0 = "$" + pp_0;
    }
    if (shop1._visible != false) {
        pp_1 = random(400) + 300;
        p_1 = "$" + pp_1;
    }
    if (shop2._visible != false) {
        pp_2 = random(200) + 100;
        p_2 = "$" + pp_2;
    }
    if (shop3._visible != false) {
        pp_3 = random(150) + 50;
        p_3 = "$" + pp_3;
    }
    if (shop4._visible != false) {
        pp_4 = random(400) + 200;
        p_4 = "$" + pp_4;
    }
    if (shop5._visible != false) {
        pp_5 = random(700) + 300;
        p_5 = "$" + pp_5;
    }

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 7
----------------------------------------------------------------------
    stop();
    this.line.removeMovieClip();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 9
----------------------------------------------------------------------
    stop();
    this.line.removeMovieClip();

----------------------------------------------------------------------
Instance of Symbol 85 MovieClip in Symbol 374 MovieClip Frame 9
----------------------------------------------------------------------
onClipEvent (load) {
    i = 0;
    _visible  = false;
}
onClipEvent (enterFrame) {
    i++;
    if (i > 100) {
        if (_parent.Round >= 35) {
            _parent.gotoAndStop("over");
        } else {
            _parent.gotoAndStop("商店");
        }
    }
}
----------------------------------------------------------------------
Symbol 374 MovieClip Frame 13
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Instance of Symbol 215 MovieClip in Symbol 374 MovieClip Frame 13
----------------------------------------------------------------------
onClipEvent (load) {
    if (_root.select == 3) {
        _parent.tbomb.man = _name;
        _x  = 280;
        _y  = 100;
    } else {
        _x  = 136.6;
        _y  = -124.3;
    }
}
----------------------------------------------------------------------
Symbol 374 MovieClip Frame 15
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 17
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 19
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 21
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 23
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 25
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 27
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 29
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 31
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 33
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 35
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 37
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 39
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 41
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 43
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 45
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 47
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 49
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 51
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 53
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 55
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 57
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 59
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 61
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 63
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 65
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 67
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 69
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 71
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 73
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 75
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 77
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 79
----------------------------------------------------------------------
    stop();
    drawLine();

----------------------------------------------------------------------
Symbol 374 MovieClip Frame 81
----------------------------------------------------------------------
    stop();
    drawLine();


----------------------------------------------------------------------
Frame Labels
----------------------------------------------------------------------
"闂婂厖绠?"	Symbol 28 MovieClip Frame 5
"站"	Symbol 215 MovieClip Frame 1
"放线"	Symbol 215 MovieClip Frame 3
"收线"	Symbol 215 MovieClip Frame 6
"閹"	Symbol 215 MovieClip Frame 8
"目标"	Symbol 374 MovieClip Frame 3
"商店"	Symbol 374 MovieClip Frame 5
"over"	Symbol 374 MovieClip Frame 7
"pass"	Symbol 374 MovieClip Frame 9
"1st"	Symbol 374 MovieClip Frame 13
"2st"	Symbol 374 MovieClip Frame 15
"3st"	Symbol 374 MovieClip Frame 17
"4st"	Symbol 374 MovieClip Frame 19
"5st"	Symbol 374 MovieClip Frame 21
"6st"	Symbol 374 MovieClip Frame 23
"7st"	Symbol 374 MovieClip Frame 25
"8st"	Symbol 374 MovieClip Frame 27
"9st"	Symbol 374 MovieClip Frame 29
"10st"	Symbol 374 MovieClip Frame 31
"11st"	Symbol 374 MovieClip Frame 33
"12st"	Symbol 374 MovieClip Frame 35
"13st"	Symbol 374 MovieClip Frame 37
"14st"	Symbol 374 MovieClip Frame 39
"15st"	Symbol 374 MovieClip Frame 41
"16st"	Symbol 374 MovieClip Frame 43
"17st"	Symbol 374 MovieClip Frame 45
"18st"	Symbol 374 MovieClip Frame 47
"19st"	Symbol 374 MovieClip Frame 49
"20st"	Symbol 374 MovieClip Frame 51
"21st"	Symbol 374 MovieClip Frame 53
"22st"	Symbol 374 MovieClip Frame 55
"23st"	Symbol 374 MovieClip Frame 57
"24st"	Symbol 374 MovieClip Frame 59
"25st"	Symbol 374 MovieClip Frame 61
"26st"	Symbol 374 MovieClip Frame 63
"27st"	Symbol 374 MovieClip Frame 65
"28st"	Symbol 374 MovieClip Frame 67
"29st"	Symbol 374 MovieClip Frame 69
"30st"	Symbol 374 MovieClip Frame 71
"31st"	Symbol 374 MovieClip Frame 73
"32st"	Symbol 374 MovieClip Frame 75
"33st"	Symbol 374 MovieClip Frame 77
"34st"	Symbol 374 MovieClip Frame 79
"35st"	Symbol 374 MovieClip Frame 81

----------------------------------------------------------------------
Instance Names
----------------------------------------------------------------------
"loading"	Frame 1	Symbol 14 MovieClip
"mp3"	Frame 2	Symbol 28 MovieClip
"game"	Frame 3	Symbol 374 MovieClip
"bar"	Symbol 14 MovieClip Frame 1	Symbol 4 MovieClip
"highScores_btn"	Symbol 153 MovieClip Frame 1	Symbol 56 Button
"t"	Symbol 204 MovieClip Frame 1	Symbol 199 Button
"t"	Symbol 204 MovieClip Frame 2	Symbol 203 Button
"onoff_mc"	Symbol 205 MovieClip Frame 1	Symbol 204 MovieClip
"box"	Symbol 229 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 232 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 246 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 254 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 262 MovieClip Frame 1	Symbol 209 MovieClip
"fk"	Symbol 265 MovieClip Frame 2	Symbol 209 MovieClip
"hit"	Symbol 305 MovieClip Frame 10	Symbol 209 MovieClip
"box"	Symbol 313 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 320 MovieClip Frame 1	Symbol 209 MovieClip
"jb"	Symbol 320 MovieClip Frame 1	Symbol 319 MovieClip
"box"	Symbol 338 MovieClip Frame 1	Symbol 209 MovieClip
"jb"	Symbol 338 MovieClip Frame 1	Symbol 337 MovieClip
"box"	Symbol 353 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 361 MovieClip Frame 1	Symbol 209 MovieClip
"box"	Symbol 373 MovieClip Frame 1	Symbol 209 MovieClip
"jb"	Symbol 373 MovieClip Frame 1	Symbol 372 MovieClip
"helpa"	Symbol 374 MovieClip Frame 1	Symbol 56 Button
"highScores_btn"	Symbol 374 MovieClip Frame 1	Symbol 57 Button
"exitpanel"	Symbol 374 MovieClip Frame 1	Symbol 69 MovieClip
"helppanel"	Symbol 374 MovieClip Frame 1	Symbol 75 MovieClip
"pausepanel"	Symbol 374 MovieClip Frame 1	Symbol 80 MovieClip
"shop0"	Symbol 374 MovieClip Frame 5	Symbol 115 Button
"shop1"	Symbol 374 MovieClip Frame 5	Symbol 120 Button
"shop2"	Symbol 374 MovieClip Frame 5	Symbol 125 Button
"shop4"	Symbol 374 MovieClip Frame 5	Symbol 130 Button
"bom"	Symbol 374 MovieClip Frame 5	Symbol 136 MovieClip
"shop3"	Symbol 374 MovieClip Frame 5	Symbol 141 Button
"shop5"	Symbol 374 MovieClip Frame 5	Symbol 146 Button
"qianzi"	Symbol 374 MovieClip Frame 13	Symbol 265 MovieClip
"showScore"	Symbol 374 MovieClip Frame 13	Symbol 286 MovieClip
"bom"	Symbol 374 MovieClip Frame 13	Symbol 136 MovieClip
"tbomb"	Symbol 374 MovieClip Frame 13	Symbol 296 MovieClip
"bz"	Symbol 374 MovieClip Frame 13	Symbol 305 MovieClip

----------------------------------------------------------------------
Dynamic Text Variables
----------------------------------------------------------------------
_root.Mscore	Symbol 89 EditableText	"000"
_root.Mscore	Symbol 90 EditableText	"000"
_root.Mscore	Symbol 91 EditableText	"000"
p_0	Symbol 105 EditableText	""
p_1	Symbol 106 EditableText	""
p_2	Symbol 107 EditableText	""
p_3	Symbol 108 EditableText	""
p_4	Symbol 109 EditableText	"3000"
p_5	Symbol 110 EditableText	""
output	Symbol 132 EditableText	""
_root.score	Symbol 133 EditableText	"125849"
_root.score	Symbol 152 EditableText	"123"
_root.score	Symbol 266 EditableText	"125849"
_root.Mscore	Symbol 267 EditableText	"1111111"
tim	Symbol 268 EditableText	"600"
Round	Symbol 271 EditableText	"12"
out	Symbol 272 EditableText	""
out	Symbol 273 EditableText	""
out	Symbol 274 EditableText	""
out	Symbol 275 EditableText	""
out	Symbol 276 EditableText	"9000"
out	Symbol 277 EditableText	"9000"
out	Symbol 278 EditableText	"9000"
out	Symbol 279 EditableText	"9000"
out	Symbol 280 EditableText	"9000"
out	Symbol 281 EditableText	"9000"
out	Symbol 282 EditableText	"9000"
out	Symbol 283 EditableText	"9000"
out	Symbol 284 EditableText	"9000"
out	Symbol 285 EditableText	"9000"

----------------------------------------------------------------------
Library
----------------------------------------------------------------------
Symbol 1 Graphic		Used by:14 	
Symbol 2 Graphic		Used by:4 	
Symbol 3 Graphic		Used by:4 	
Symbol 4 MovieClip	Uses:2 3 	Used by:14 	
Symbol 5 Graphic		Used by:7 	
Symbol 6 Graphic		Used by:7 	
Symbol 7 MovieClip	Uses:5 6 	Used by:14 	
Symbol 8 Graphic		Used by:10 	
Symbol 9 Graphic		Used by:10 	
Symbol 10 MovieClip	Uses:8 9 	Used by:14 	
Symbol 11 Bitmap		Used by:12 	
Symbol 12 Graphic	Uses:11 	Used by:13 	
Symbol 13 MovieClip	Uses:12 	Used by:14 	
Symbol 14 MovieClip	Uses:1 4 7 10 13 	Used by:Timeline	
Symbol 15 Graphic		Used by:25 270 	
Symbol 16 Sound [scoreup]		Used by:25 	
Symbol 17 Sound [fx]		Used by:25 	
Symbol 18 Sound [an]		Used by:25 	
Symbol 19 Sound [bell]		Used by:25 	
Symbol 20 Sound [bad]		Used by:25 	
Symbol 21 Sound [cool]		Used by:25 	
Symbol 22 Sound [good]		Used by:25 	
Symbol 23 Sound [itemup]		Used by:25 	
Symbol 24 Sound [gold]		Used by:25 	
Symbol 25 MovieClip	Uses:15 16 17 18 19 20 21 22 23 24 	Used by:Timeline	
Symbol 26 Graphic		Used by:28 	
Symbol 27 Sound		Used by:28 	
Symbol 28 MovieClip	Uses:26 27 	Used by:Timeline	
Symbol 29 Bitmap		Used by:30 	
Symbol 30 Graphic	Uses:29 	Used by:374 	
Symbol 31 Bitmap		Used by:32 	
Symbol 32 Graphic	Uses:31 	Used by:374 	
Symbol 33 Bitmap		Used by:34 	
Symbol 34 Graphic	Uses:33 	Used by:35 	
Symbol 35 MovieClip	Uses:34 	Used by:37 	
Symbol 36 Graphic		Used by:37 	
Symbol 37 MovieClip	Uses:35 36 	Used by:374 	
Symbol 38 Graphic		Used by:43 	
Symbol 39 Bitmap		Used by:40 	
Symbol 40 Graphic	Uses:39 	Used by:41 	
Symbol 41 MovieClip	Uses:40 	Used by:42 	
Symbol 42 MovieClip	Uses:41 	Used by:43 	
Symbol 43 MovieClip	Uses:38 42 	Used by:374 	
Symbol 44 Bitmap		Used by:46 52 	
Symbol 45 Bitmap		Used by:46 	
Symbol 46 Graphic	Uses:44 45 	Used by:374 	
Symbol 47 Graphic		Used by:48 	
Symbol 48 MovieClip	Uses:47 	Used by:51 	
Symbol 49 Graphic		Used by:50 	
Symbol 50 MovieClip	Uses:49 	Used by:51 	
Symbol 51 MovieClip	Uses:48 50 	Used by:374 	
Symbol 52 Graphic	Uses:44 	Used by:374 	
Symbol 53 Graphic		Used by:55 56 57 65 66 72 95 149 	
Symbol 54 Graphic		Used by:55 56 57 65 66 72 95 115 149 	
Symbol 55 Button	Uses:53 54 	Used by:374 	
Symbol 56 Button	Uses:53 54 	Used by:153 374 	
Symbol 57 Button	Uses:53 54 	Used by:374 	
Symbol 58 Bitmap		Used by:61 	
Symbol 59 Bitmap		Used by:61 	
Symbol 60 Bitmap		Used by:61 	
Symbol 61 Graphic	Uses:58 59 60 	Used by:374 	
Symbol 62 Graphic		Used by:374 	
Symbol 63 Bitmap		Used by:64 	
Symbol 64 Graphic	Uses:63 	Used by:69 	
Symbol 65 Button	Uses:53 54 	Used by:69 	
Symbol 66 Button	Uses:53 54 	Used by:69 80 	
Symbol 67 Bitmap		Used by:68 	
Symbol 68 Graphic	Uses:67 	Used by:69 	
Symbol 69 MovieClip	Uses:64 65 66 68 	Used by:374 	
Symbol 70 Bitmap		Used by:71 	
Symbol 71 Graphic	Uses:70 	Used by:75 	
Symbol 72 Button	Uses:53 54 	Used by:75 	
Symbol 73 Bitmap		Used by:74 	
Symbol 74 Graphic	Uses:73 	Used by:75 	
Symbol 75 MovieClip	Uses:71 72 74 	Used by:374 	
Symbol 76 Bitmap		Used by:77 	
Symbol 77 Graphic	Uses:76 	Used by:80 	
Symbol 78 Bitmap		Used by:79 	
Symbol 79 Graphic	Uses:78 	Used by:80 	
Symbol 80 MovieClip	Uses:77 66 79 	Used by:374 	
Symbol 81 Bitmap		Used by:82 161 	
Symbol 82 Graphic	Uses:81 	Used by:374 	
Symbol 83 Font		Used by:84 	
Symbol 84 Text	Uses:83 	Used by:374 	
Symbol 85 MovieClip		Used by:374 	
Symbol 86 Bitmap		Used by:87 	
Symbol 87 Graphic	Uses:86 	Used by:92 	
Symbol 88 Font		Used by:89 90 91 105 106 107 108 109 110 133 152 266 267 268 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 	
Symbol 89 EditableText	Uses:88 	Used by:92 	
Symbol 90 EditableText	Uses:88 	Used by:92 	
Symbol 91 EditableText	Uses:88 	Used by:92 	
Symbol 92 MovieClip	Uses:87 89 90 91 	Used by:374 	
Symbol 93 Bitmap		Used by:94 	
Symbol 94 Graphic	Uses:93 	Used by:374 	
Symbol 95 Button	Uses:53 54 	Used by:374 	
Symbol 96 Bitmap		Used by:97 	
Symbol 97 Graphic	Uses:96 	Used by:374 	
Symbol 98 Bitmap		Used by:99 	
Symbol 99 Graphic	Uses:98 	Used by:104 	
Symbol 100 Bitmap		Used by:101 	
Symbol 101 Graphic	Uses:100 	Used by:104 	
Symbol 102 Bitmap		Used by:103 	
Symbol 103 Graphic	Uses:102 	Used by:104 	
Symbol 104 MovieClip	Uses:99 101 103 	Used by:374 	
Symbol 105 EditableText	Uses:88 	Used by:374 	
Symbol 106 EditableText	Uses:88 	Used by:374 	
Symbol 107 EditableText	Uses:88 	Used by:374 	
Symbol 108 EditableText	Uses:88 	Used by:374 	
Symbol 109 EditableText	Uses:88 	Used by:374 	
Symbol 110 EditableText	Uses:88 	Used by:374 	
Symbol 111 Bitmap		Used by:112 	
Symbol 112 Graphic	Uses:111 	Used by:115 	
Symbol 113 Bitmap		Used by:114 134 	
Symbol 114 Graphic	Uses:113 	Used by:115 	
Symbol 115 Button	Uses:112 114 54 	Used by:374 	
Symbol 116 Bitmap		Used by:117 	
Symbol 117 Graphic	Uses:116 	Used by:120 	
Symbol 118 Bitmap		Used by:119 	
Symbol 119 Graphic	Uses:118 	Used by:120 	
Symbol 120 Button	Uses:117 119 	Used by:374 	
Symbol 121 Bitmap		Used by:122 	
Symbol 122 Graphic	Uses:121 	Used by:125 	
Symbol 123 Bitmap		Used by:124 	
Symbol 124 Graphic	Uses:123 	Used by:125 	
Symbol 125 Button	Uses:122 124 	Used by:374 	
Symbol 126 Bitmap		Used by:127 	
Symbol 127 Graphic	Uses:126 	Used by:130 	
Symbol 128 Bitmap		Used by:129 	
Symbol 129 Graphic	Uses:128 	Used by:130 	
Symbol 130 Button	Uses:127 129 	Used by:374 	
Symbol 131 Font		Used by:132 	
Symbol 132 EditableText	Uses:131 	Used by:374 	
Symbol 133 EditableText	Uses:88 	Used by:374 	
Symbol 134 Graphic	Uses:113 	Used by:135 	
Symbol 135 MovieClip	Uses:134 	Used by:136 296 	
Symbol 136 MovieClip	Uses:135 	Used by:374 	
Symbol 137 Bitmap		Used by:138 	
Symbol 138 Graphic	Uses:137 	Used by:141 	
Symbol 139 Bitmap		Used by:140 	
Symbol 140 Graphic	Uses:139 	Used by:141 	
Symbol 141 Button	Uses:138 140 	Used by:374 	
Symbol 142 Bitmap		Used by:143 	
Symbol 143 Graphic	Uses:142 	Used by:146 	
Symbol 144 Bitmap		Used by:145 	
Symbol 145 Graphic	Uses:144 	Used by:146 	
Symbol 146 Button	Uses:143 145 	Used by:374 	
Symbol 147 Bitmap		Used by:148 	
Symbol 148 Graphic	Uses:147 	Used by:153 	
Symbol 149 Button	Uses:53 54 	Used by:153 	
Symbol 150 Bitmap		Used by:151 	
Symbol 151 Graphic	Uses:150 	Used by:153 	
Symbol 152 EditableText	Uses:88 	Used by:153 	
Symbol 153 MovieClip	Uses:148 149 56 151 152 	Used by:155 	
Symbol 154 Sound		Used by:155 	
Symbol 155 MovieClip	Uses:153 154 	Used by:374 	
Symbol 156 Bitmap		Used by:157 	
Symbol 157 Graphic	Uses:156 	Used by:159 	
Symbol 158 Sound		Used by:159 	
Symbol 159 MovieClip	Uses:157 158 	Used by:374 	
Symbol 160 Bitmap		Used by:161 	
Symbol 161 Graphic	Uses:81 160 	Used by:374 	
Symbol 162 Bitmap		Used by:163 	
Symbol 163 Graphic	Uses:162 	Used by:179 	
Symbol 164 Bitmap		Used by:165 	
Symbol 165 Graphic	Uses:164 	Used by:166 	
Symbol 166 MovieClip	Uses:165 	Used by:179 	
Symbol 167 Bitmap		Used by:168 	
Symbol 168 Graphic	Uses:167 	Used by:169 	
Symbol 169 MovieClip	Uses:168 	Used by:179 	
Symbol 170 Bitmap		Used by:171 	
Symbol 171 Graphic	Uses:170 	Used by:172 	
Symbol 172 MovieClip	Uses:171 	Used by:179 	
Symbol 173 Bitmap		Used by:174 	
Symbol 174 Graphic	Uses:173 	Used by:175 	
Symbol 175 MovieClip	Uses:174 	Used by:179 	
Symbol 176 Bitmap		Used by:177 	
Symbol 177 Graphic	Uses:176 	Used by:178 	
Symbol 178 MovieClip	Uses:177 	Used by:179 	
Symbol 179 MovieClip	Uses:163 166 169 172 175 178 	Used by:374 	
Symbol 180 Bitmap		Used by:181 	
Symbol 181 Graphic	Uses:180 	Used by:183 	
Symbol 182 Graphic		Used by:183 186 189 192 	
Symbol 183 Button	Uses:181 182 	Used by:205 	
Symbol 184 Bitmap		Used by:185 198 202 	
Symbol 185 Graphic	Uses:184 	Used by:186 	
Symbol 186 Button	Uses:185 182 	Used by:205 	
Symbol 187 Bitmap		Used by:188 	
Symbol 188 Graphic	Uses:187 	Used by:189 	
Symbol 189 Button	Uses:188 182 	Used by:205 	
Symbol 190 Bitmap		Used by:191 	
Symbol 191 Graphic	Uses:190 	Used by:192 	
Symbol 192 Button	Uses:191 182 	Used by:205 	
Symbol 193 Bitmap		Used by:194 	
Symbol 194 Graphic	Uses:193 	Used by:205 	
Symbol 195 Bitmap		Used by:196 	
Symbol 196 Graphic	Uses:195 	Used by:199 	
Symbol 197 Bitmap		Used by:198 202 	
Symbol 198 Graphic	Uses:184 197 	Used by:199 	
Symbol 199 Button	Uses:196 198 	Used by:204 	
Symbol 200 Bitmap		Used by:201 	
Symbol 201 Graphic	Uses:200 	Used by:203 	
Symbol 202 Graphic	Uses:184 197 	Used by:203 	
Symbol 203 Button	Uses:201 202 	Used by:204 	
Symbol 204 MovieClip	Uses:199 203 	Used by:205 	
Symbol 205 MovieClip	Uses:183 186 189 192 194 204 	Used by:374 	
Symbol 206 Bitmap		Used by:207 	
Symbol 207 Graphic	Uses:206 	Used by:214 215 	
Symbol 208 Graphic		Used by:209 	
Symbol 209 MovieClip	Uses:208 	Used by:215 229 232 246 254 262 265 305 313 320 338 353 361 373 	
Symbol 210 Bitmap		Used by:211 	
Symbol 211 Graphic	Uses:210 	Used by:214 	
Symbol 212 Bitmap		Used by:213 	
Symbol 213 Graphic	Uses:212 	Used by:214 	
Symbol 214 MovieClip	Uses:207 211 213 	Used by:215 	
Symbol 215 MovieClip	Uses:207 209 214 	Used by:374 	
Symbol 216 Bitmap		Used by:217 	
Symbol 217 Graphic	Uses:216 	Used by:228 	
Symbol 218 Bitmap		Used by:219 	
Symbol 219 Graphic	Uses:218 	Used by:228 	
Symbol 220 Bitmap		Used by:221 	
Symbol 221 Graphic	Uses:220 	Used by:228 	
Symbol 222 Bitmap		Used by:223 	
Symbol 223 Graphic	Uses:222 	Used by:228 	
Symbol 224 Bitmap		Used by:225 	
Symbol 225 Graphic	Uses:224 	Used by:228 	
Symbol 226 Bitmap		Used by:227 	
Symbol 227 Graphic	Uses:226 	Used by:228 	
Symbol 228 MovieClip	Uses:217 219 221 223 225 227 	Used by:229 	
Symbol 229 MovieClip	Uses:209 228 	Used by:374 	
Symbol 230 Bitmap		Used by:231 	
Symbol 231 Graphic	Uses:230 	Used by:232 	
Symbol 232 MovieClip	Uses:209 231 	Used by:374 	
Symbol 233 Bitmap		Used by:234 	
Symbol 234 Graphic	Uses:233 	Used by:245 	
Symbol 235 Bitmap		Used by:236 	
Symbol 236 Graphic	Uses:235 	Used by:245 	
Symbol 237 Bitmap		Used by:238 	
Symbol 238 Graphic	Uses:237 	Used by:245 	
Symbol 239 Bitmap		Used by:240 	
Symbol 240 Graphic	Uses:239 	Used by:245 	
Symbol 241 Bitmap		Used by:242 	
Symbol 242 Graphic	Uses:241 	Used by:245 	
Symbol 243 Bitmap		Used by:244 	
Symbol 244 Graphic	Uses:243 	Used by:245 	
Symbol 245 MovieClip	Uses:234 236 238 240 242 244 	Used by:246 	
Symbol 246 MovieClip	Uses:209 245 	Used by:374 	
Symbol 247 Bitmap		Used by:248 	
Symbol 248 Graphic	Uses:247 	Used by:253 	
Symbol 249 Bitmap		Used by:250 	
Symbol 250 Graphic	Uses:249 	Used by:253 	
Symbol 251 Bitmap		Used by:252 	
Symbol 252 Graphic	Uses:251 	Used by:253 	
Symbol 253 MovieClip	Uses:248 250 252 	Used by:254 	
Symbol 254 MovieClip	Uses:209 253 	Used by:374 	
Symbol 255 Bitmap		Used by:256 	
Symbol 256 Graphic	Uses:255 	Used by:261 	
Symbol 257 Bitmap		Used by:258 	
Symbol 258 Graphic	Uses:257 	Used by:261 	
Symbol 259 Bitmap		Used by:260 	
Symbol 260 Graphic	Uses:259 	Used by:261 	
Symbol 261 MovieClip	Uses:256 258 260 	Used by:262 	
Symbol 262 MovieClip	Uses:209 261 	Used by:374 	
Symbol 263 Bitmap		Used by:264 	
Symbol 264 Graphic	Uses:263 	Used by:265 	
Symbol 265 MovieClip	Uses:209 264 	Used by:374 	
Symbol 266 EditableText	Uses:88 	Used by:374 	
Symbol 267 EditableText	Uses:88 	Used by:374 	
Symbol 268 EditableText	Uses:88 	Used by:269 	
Symbol 269 MovieClip	Uses:268 	Used by:374 	
Symbol 270 MovieClip	Uses:15 	Used by:374 	
Symbol 271 EditableText	Uses:88 	Used by:374 	
Symbol 272 EditableText	Uses:88 	Used by:286 	
Symbol 273 EditableText	Uses:88 	Used by:286 	
Symbol 274 EditableText	Uses:88 	Used by:286 	
Symbol 275 EditableText	Uses:88 	Used by:286 	
Symbol 276 EditableText	Uses:88 	Used by:286 	
Symbol 277 EditableText	Uses:88 	Used by:286 	
Symbol 278 EditableText	Uses:88 	Used by:286 	
Symbol 279 EditableText	Uses:88 	Used by:286 	
Symbol 280 EditableText	Uses:88 	Used by:286 	
Symbol 281 EditableText	Uses:88 	Used by:286 	
Symbol 282 EditableText	Uses:88 	Used by:286 	
Symbol 283 EditableText	Uses:88 	Used by:286 	
Symbol 284 EditableText	Uses:88 	Used by:286 	
Symbol 285 EditableText	Uses:88 	Used by:286 	
Symbol 286 MovieClip	Uses:272 273 274 275 276 277 278 279 280 281 282 283 284 285 	Used by:374 	
Symbol 287 Graphic		Used by:296 	
Symbol 288 Graphic		Used by:296 	
Symbol 289 Sound		Used by:296 305 	
Symbol 290 Graphic		Used by:296 	
Symbol 291 Graphic		Used by:296 	
Symbol 292 Graphic		Used by:296 	
Symbol 293 Graphic		Used by:296 	
Symbol 294 Graphic		Used by:296 	
Symbol 295 Graphic		Used by:296 	
Symbol 296 MovieClip	Uses:135 287 288 289 290 291 292 293 294 295 	Used by:374 	
Symbol 297 Graphic		Used by:305 	
Symbol 298 Graphic		Used by:305 	
Symbol 299 Graphic		Used by:305 	
Symbol 300 Graphic		Used by:305 	
Symbol 301 Graphic		Used by:305 	
Symbol 302 Graphic		Used by:305 	
Symbol 303 Graphic		Used by:305 	
Symbol 304 Graphic		Used by:305 	
Symbol 305 MovieClip	Uses:297 298 289 299 300 301 209 302 303 304 	Used by:374 	
Symbol 306 Bitmap		Used by:307 	
Symbol 307 Graphic	Uses:306 	Used by:312 	
Symbol 308 Bitmap		Used by:309 	
Symbol 309 Graphic	Uses:308 	Used by:312 	
Symbol 310 Bitmap		Used by:311 	
Symbol 311 Graphic	Uses:310 	Used by:312 	
Symbol 312 MovieClip	Uses:307 309 311 	Used by:313 	
Symbol 313 MovieClip	Uses:209 312 	Used by:374 	
Symbol 314 Bitmap		Used by:315 	
Symbol 315 Graphic	Uses:314 	Used by:319 	
Symbol 316 Bitmap		Used by:317 318 	
Symbol 317 Graphic	Uses:316 	Used by:319 	
Symbol 318 Graphic	Uses:316 	Used by:319 	
Symbol 319 MovieClip	Uses:315 317 318 	Used by:320 	
Symbol 320 MovieClip	Uses:209 319 	Used by:374 	
Symbol 321 Bitmap		Used by:322 	
Symbol 322 Graphic	Uses:321 	Used by:337 	
Symbol 323 Bitmap		Used by:324 	
Symbol 324 Graphic	Uses:323 	Used by:337 	
Symbol 325 Bitmap		Used by:326 	
Symbol 326 Graphic	Uses:325 	Used by:337 	
Symbol 327 Bitmap		Used by:328 	
Symbol 328 Graphic	Uses:327 	Used by:337 	
Symbol 329 Bitmap		Used by:330 	
Symbol 330 Graphic	Uses:329 	Used by:337 	
Symbol 331 Bitmap		Used by:332 	
Symbol 332 Graphic	Uses:331 	Used by:337 	
Symbol 333 Bitmap		Used by:334 	
Symbol 334 Graphic	Uses:333 	Used by:337 	
Symbol 335 Bitmap		Used by:336 	
Symbol 336 Graphic	Uses:335 	Used by:337 	
Symbol 337 MovieClip	Uses:322 324 326 328 330 332 334 336 	Used by:338 	
Symbol 338 MovieClip	Uses:209 337 	Used by:374 	
Symbol 339 MovieClip		Used by:374 	
Symbol 340 Bitmap		Used by:341 	
Symbol 341 Graphic	Uses:340 	Used by:352 	
Symbol 342 Bitmap		Used by:343 	
Symbol 343 Graphic	Uses:342 	Used by:352 	
Symbol 344 Bitmap		Used by:345 	
Symbol 345 Graphic	Uses:344 	Used by:352 	
Symbol 346 Bitmap		Used by:347 	
Symbol 347 Graphic	Uses:346 	Used by:352 	
Symbol 348 Bitmap		Used by:349 	
Symbol 349 Graphic	Uses:348 	Used by:352 	
Symbol 350 Bitmap		Used by:351 	
Symbol 351 Graphic	Uses:350 	Used by:352 	
Symbol 352 MovieClip	Uses:341 343 345 347 349 351 	Used by:353 	
Symbol 353 MovieClip	Uses:209 352 	Used by:374 	
Symbol 354 Bitmap		Used by:355 	
Symbol 355 Graphic	Uses:354 	Used by:360 	
Symbol 356 Bitmap		Used by:357 	
Symbol 357 Graphic	Uses:356 	Used by:360 	
Symbol 358 Bitmap		Used by:359 	
Symbol 359 Graphic	Uses:358 	Used by:360 	
Symbol 360 MovieClip	Uses:355 357 359 	Used by:361 	
Symbol 361 MovieClip	Uses:209 360 	Used by:374 	
Symbol 362 Bitmap		Used by:363 	
Symbol 363 Graphic	Uses:362 	Used by:372 	
Symbol 364 Bitmap		Used by:365 	
Symbol 365 Graphic	Uses:364 	Used by:372 	
Symbol 366 Bitmap		Used by:367 	
Symbol 367 Graphic	Uses:366 	Used by:372 	
Symbol 368 Bitmap		Used by:369 	
Symbol 369 Graphic	Uses:368 	Used by:372 	
Symbol 370 Bitmap		Used by:371 	
Symbol 371 Graphic	Uses:370 	Used by:372 	
Symbol 372 MovieClip	Uses:363 365 367 369 371 	Used by:373 	
Symbol 373 MovieClip	Uses:209 372 	Used by:374 	
Symbol 374 MovieClip	Uses:30 32 37 43 46 51 52 55 56 57 61 62 69 75 80 82 84 85 92 94 95 97 104 105 106 107 108 109 110 115 120 125 130 132 133 136 141 146 155 159 161 179 205 215 229 232 246 254 262 265 266 267 269 270 271 286 296 305 313 320 338 339 353 361 373 	Used by:Timeline	

----------------------------------------------------------------------
Special Tags
----------------------------------------------------------------------
FileAttributes (69)	Timeline Frame 1	Access local files only, Metadata not present, AS1/AS2.
ExportAssets (56)	Timeline Frame 2	Symbol 16 as "scoreup"
ExportAssets (56)	Timeline Frame 2	Symbol 17 as "fx"
ExportAssets (56)	Timeline Frame 2	Symbol 18 as "an"
ExportAssets (56)	Timeline Frame 2	Symbol 19 as "bell"
ExportAssets (56)	Timeline Frame 2	Symbol 20 as "bad"
ExportAssets (56)	Timeline Frame 2	Symbol 21 as "cool"
ExportAssets (56)	Timeline Frame 2	Symbol 22 as "good"
ExportAssets (56)	Timeline Frame 2	Symbol 23 as "itemup"
ExportAssets (56)	Timeline Frame 2	Symbol 24 as "gold"
