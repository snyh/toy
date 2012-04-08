function is_in_rect(x, y, r) 
{
	if (x > r[0] && x < r[0]+r[2] && y > r[1] && y < r[1] + r[3]) return true;
	else return false;
}

function LLK() 
{
	this.rect_score = [10, 0, 100, 28];
	this.rect_pause = [160, 0, 85, 28];
	this.rect_sound = [270, 0, 42, 42];
	this.rect_level = [340, 0, 100, 28];
	this.rect_title = [50, 530, 200, 40];
	this.rect_msg = [280, 550, 110, 40];
	this.init = function(w, h) {
		this.width = w || 10;
		this.height = h || 12;
		this.data = [];
		this.cur_pos = -1;
		this.cur_img = -1;
		this.score = 0;
		this.ctx = document.getElementById("view").getContext("2d");
		this.gobj = new GameObj(10, 12);
		this.dobj = new DrawObj(this.ctx);

		this.has_sound = true;

		this.img_square = new Image();
		this.img_square.src = "assets/img/is_32.png";

		this.img_soundon = new Image();
		this.img_soundon.src = "assets/img/soundon.svg";

		this.img_soundoff = new Image();
		this.img_soundoff.src = "assets/img/soundoff.svg";

		this.img_info = new Image();
		this.img_info.src = "assets/img/info.svg";

		this.sound_ok = new Audio();
		this.sound_ok.src = "assets/sound/effect.ogg";
		this.sound_error = new Audio();
		this.sound_error.src = "assets/sound/error.ogg";

		var that = this;
		this.img_square.onload = function () {
			that.new_game(1);
		}
		this.img_soundon.onload = function () {
			that.draw_image(that.img_soundon, that.rect_sound);
		};

		this.bindclick();

	};
	this.new_game = function(level) {
		this.data = this.gobj.gen_data();
		this.level = level;
		this.timeinit();
		this.removenum = 0;
		this.timer_start();
		this.game_running = true;
		this.in_message = false;
		this.drawPage();
	};
	this.timeinit = function() {
		this.time = 300 - this.level * 50;
		if (this.time < 0 ) this.time = 5;
	};
	this.timer_start = function() {
		var that = this;
		this.timer = setInterval(function() { 
			that.time -= 1;
			that.drawTimeBar();
			if (that.time < 1) 
				that.gameover();
		}, 1000);
	};
	this.timer_stop = function() {
		clearInterval(this.timer);
	};
	this.msg_callback = function() {
		this.in_message = false;
		this.toggle_msg();
	};

	this.unbindclick = function() {
		$("#view").unbind('click');
	};
	this.bindclick = function() {
		var that = this;
		$("#view").click(function(e) {
				var x = e.pageX-$("#view").offset().left;
				var y = e.pageY-$("#view").offset().top;

				if (that.in_message && is_in_rect(x,y, that.rect_msg)) that.msg_callback();

				if (is_in_rect(x, y, that.rect_pause)) that.toggle_game();
				if (!that.game_running) return;


				//是否是音量键
				if (is_in_rect(x, y, that.rect_sound)) that.toggle_sound();



				var col = Math.floor(x / 50);
				var row = Math.floor(y / 50);
				var i = that.data[x+y*that.width];
				if (i == 0 || col == 0 || col == that.width -1 || row == 0 || row == that.height - 1) return;
				that.drawSelect(col, row);
		});
	};
	this.toggle_sound = function() {
		this.has_sound = !this.has_sound;
		if (this.has_sound) {
			this.draw_image(this.img_soundon, this.rect_sound);
			this.sound_ok.play();
		} else {
			this.draw_image(this.img_soundoff, this.rect_sound);
		}
	};
	this.toggle_game = function() {
		this.game_running = !this.game_running;
		if (this.game_running) {
			this.timer_start();
			this.drawPage();
		} else {
			this.timer_stop();
			this.message("游戏暂停中", "继续", this.toggle_game);
		}
	};
	this.gameover = function() {
		this.timer_stop();
		this.game_running = false;
		this.message("游戏结束!", "重来?", function() {
				this.score -= this.removenum * 10;
				this.new_game(this.level);
				});
	};
	this.message = function(text1, text2, f) {
		this.in_message = true;
		this.ctx.save();
		this.ctx.fillStyle = "rgba(0, 0, 0, 0.7)";
		this.ctx.fillRect(0, 00, 480, 600);
		this.ctx.fillStyle = "rgba(0, 0, 0, 0.0)";
		this.ctx.shadowOffsetX = 4;
		this.ctx.shadowOffsetY = 4;
		this.ctx.shadowBlur = 5;
		this.ctx.shadowColor = "rgba(1, 1, 1, 0.4)";

		var rt = this.rect_title;
		var rf = this.rect_msg;

		this.ctx.fillStyle = "rgba(255, 255, 255, 0.1)";
		this.ctx.fillRect(rf[0], rf[1], rf[2], rf[3]);

		this.ctx.fillStyle = "rgba(0, 0, 0, 1)";
		this.ctx.font = "normal 30px Arial";
		this.ctx.fillText(text1, rt[0], rt[1]+50);

		this.ctx.fillStyle = "rgba(255, 255, 0, 1)";
		this.ctx.fillText(text2, rf[0]+20, rf[1]+30);

		this.ctx.restore();

		this.toggle_msg = f;
	};
	this.gamewin = function() {
		this.game_running = false;
		this.timer_stop();
		this.message("挺不错嘛!", "继续", function(){this.new_game(this.level+1);});
		//this.drawPage();
	};

	this.draw_out = function(pos) {
		var x = pos % this.width;
		var y = Math.floor(pos / this.width);
		var i = this.data[pos];
		this.drawOne(i, x, y, 40, 40, 0.6);
	};
	this.draw_norm = function(pos) {
		var x = pos % this.width;
		var y = Math.floor(pos / this.width);
		var i = this.data[pos];
		this.drawOne(i, x, y, 40, 40, 0.2);
	};

	this.drawOne =  function(i, x, y, w, h, weight) {
		w = w || 36;
		h = h || 40;
		weight = weight || 0.2;
		this.ctx.save();
		this.ctx.shadowOffsetX = 3;
		this.ctx.shadowOffsetY = 4;
		this.ctx.shadowBlur = 5;
		this.ctx.shadowColor = "rgba(0, 0, 0, " + weight + ")";
		this.ctx.fillStyle = "rgba(0, 0, 0, " + weight + ")";
		this.ctx.clearRect(x*50, y*50, 50, 50);
		this.ctx.fillRect(x*50, y*50, 50, 50);
		this.ctx.drawImage(this.img_square, 0, i*40,  36, 40,
					x*50, y*50, w, h);
		this.ctx.restore();

	};
	this.drawToolbar = function () {
		this.draw_text("Score: " + this.score, this.rect_score);
		this.draw_text("Level: " + this.level, this.rect_level);
		this.draw_text("Pause", this.rect_pause);
		this.drawTimeBar();
	};
	this.drawTimeBar = function() {
		this.dobj.progressBar(10, 50, 30, 500, this.time, this.time/(600-(this.level*50)));
	};
	this.draw_text = function(text, r) {
		var size = r[3]; 
		this.ctx.save();
		this.ctx.shadowOffsetX = 4;
		this.ctx.shadowOffsetY = 4;
		this.ctx.shadowBlur = 5;
		this.ctx.shadowColor = "rgba(0, 0, 0, 1)";
		this.ctx.font = "normal " + size + " Arial";
		this.ctx.fillText(text, r[0], r[1]+r[3]);
		this.ctx.restore();
	};

	this.drawPage = function() {

		this.ctx.save();
		this.ctx.shadowOffsetX = 3;
		this.ctx.shadowOffsetY = 4;
		this.ctx.shadowBlur = 10;
		this.ctx.shadowColor = "rgba(0, 0, 0, 0.3)";
		this.ctx.clearRect(0,0,480,650);
		this.ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
		this.ctx.fillRect(0,0,480,650);
		this.ctx.restore();


		for (var i=0; i < this.data.length; i++) {
			var x = i % this.width;
			var y = Math.floor(i / this.width);
			var img = this.data[i];
			if (img != 0)
				this.drawOne(img, x, y);
		}

		this.drawToolbar();
		this.draw_image(this.img_soundon, this.rect_sound);
	};
	this.draw_bg = function(r) {
		this.ctx.clearRect(r[0], r[1], r[2], r[3]);
		this.ctx.save();
		this.ctx.shadowOffsetX = 3;
		this.ctx.shadowOffsetY = 4;
		this.ctx.shadowBlur = 10;
		this.ctx.shadowColor = "rgba(0, 0, 0, 0.3)";
		this.ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
		this.ctx.fillRect(r[0], r[1], r[2], r[3]);
		this.ctx.restore();
	};

	this.draw_image = function(img, r) {
		//this.draw_bg(r);
		this.draw_bg(r);
		this.ctx.drawImage(img, r[0], r[1], r[2], r[3]);
	};


	this.check_connect = function(x, y) {
		var b = new Date().getTime();
		var path = this.gobj.get_path(this.cur_pos, x+y*this.width);
		var e = new Date().getTime() - b;
		console.log("RUn: " + e + "ms");
		return path;
	};

	this.draw_path = function(path) {
		//console.log(path);
		this.ctx.beginPath();
		var p1 = path[0];
		var x = p1%this.width;
		var y = Math.floor(p1/this.width);
		this.ctx.moveTo(x*50+25, y*50+25);
		var delay = 500 / path.length;

		this.data[path[0]] = 0;
		this.data[path[path.length-1]] = 0;

		//console.log("MoveTO: (" +x+", " + y +")" );
		var i = 1;
		var that = this;
		function draw() {
			var p2 = path[i];
			var x = p2%that.width;
			var y = Math.floor(p2/that.width);
			that.ctx.lineTo(x*50+25, y*50+25);
			that.ctx.stroke();
			//console.log("LineTO: (" +x+", " + y +")" );
			if (i<path.length) {
				i++;
				setTimeout(draw, delay);
			} else {
				that.ctx.closePath();
				setTimeout(function() {
					that.drawPage();
					if (that.removenum == 40)
						that.gamewin();
				}, delay);
			}
		}
		draw();
		if (this.has_sound) this.sound_ok.play();
	};

	this.drawSelect = function(x, y) {
		var pos = x + y*this.width;
		if (this.data[pos] == 0) return;

		if (this.cur_pos == pos) {
			this.draw_norm(this.cur_pos);
			this.cur_pos = -1;
			this.cur_img = -1;
		} else if (this.cur_pos === -1 ) {
			//如果当前没有选择节点则记录此节点
			this.cur_pos = pos;
			this.cur_img = this.data[this.cur_pos]; 
			//并放大此节点
			this.draw_out(this.cur_pos); 
		} else {
			//否则检查当前选择的节点是否能和之前选择的节点进行连通 
			var path = this.check_connect(x,y);
			if (this.cur_img == this.data[pos] && path.length > 0) {
				this.removenum += 1;
				this.score += 10;
				this.time += 5;
				this.draw_path(path);
			} else {
				this.draw_norm(this.cur_pos);
				if (this.has_sound) this.sound_error.play();
			}
			this.cur_pos = -1;
			this.cur_img = -1;
		}
	};
};

$(function() {
	llk = new LLK();
	llk.init();
	$("#btn").click(function() {
		var path = llk.gobj.find_one_path();
		console.log("FUCK:" + path);
		llk.draw_out(llk.data[path[0]], path[0]%llk.width, Math.floor(path[0]/llk.width), 40,44);
		llk.draw_out(llk.data[path[1]], path[1]%llk.width, Math.floor(path[1]/llk.width), 40,44);
	});
});
