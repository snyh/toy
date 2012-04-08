/** Dijkstra算法请参考wiki
    var d = new GameObj(宽，高);
    d.get_path(begin, end); 若返回空数组表示没有连通路径,否则按目标点掉起始点顺序返回路径
*/
GameObj = function (w, h) {
	this.width = w;
	this.height = h;
	this.data = [];
	this.INF = 1000; //表示无限大
};
GameObj.prototype = {
	shuffle: function(data) {
		var j, x;
		for (var i=data.length; i; ) {
			j = Math.round(Math.random()*i);
			x = data[--i];
			data[i] = data[j];
			data[j] = x;
		}
		return data;
	},
	gen_data: function() {
		var tmp = [];
		var len = this.width * this.height - 2*this.width - 2*this.height+ 4;
		for (var i = 0; i<len/2; i++)
			tmp.push(1+Math.round(Math.random()*15));
		tmp = this.shuffle(tmp.concat(tmp));

		for (var y=0; y < this.height; y++) {
			for(var x=0; x < this.width; x++) {
				if (y == 0 || y == this.height-1 || x == 0 || x == this.width-1) {
					this.data[x + y*this.width] = 0;
					//console.log("draw " +(x+y*this.width) + " "  + x + ":" + y);
				} else {
					this.data[x + y*this.width] = tmp.pop();
				}
			}
		}
		return this.data;
	},
	get_path: function(begin, end) {
		this.dist = [];
		this.prev = [];
		this.visted = [];
		for (var i=0; i<this.width*this.height; i++) this.dist[i] = this.INF;
		this.dist[begin] = 0;

		//console.log("Dijkstra.init: "  + begin + " " + end);
		//计算最短路径
		this.dijkstra(begin, end); 
		//整理路径
		var path = [];
		var i = this.prev[end];
		if (i === undefined) return [];
		path.push(end);
		while (i != begin) {
			path.push(i);
			i = this.prev[i];
			if (i == undefined) throw "get_path error!!!!"; //如果出现这种情况则是算法错误
		}
		path.push(begin);
		path = this.check_path(path);
		return path;
	},
	check_path : function(path) {
		var corner = 0;
		for (var i=2; i<path.length; i++) {
			var p1 = path[i-2];
			var p2 = path[i];
			var x1 = p1 % this.width;
			var y1 = Math.floor(p1 / this.width);
			var x2 = p2 % this.width;
			var y2 = Math.floor(p2 / this.width);
			p1 = p2;
			if ( Math.abs(x1-x2) == 1 && Math.abs(y1-y2) == 1) {
				//两个拐角以上
				corner += 1;
				if (corner > 2) return [];
				console.log(path);
			}
		}
		return path;
	},
	erase_point: function(ps) {
		ps.forEach(function(x) {
			this.data[x] = 0;
			this.data[x] = 0;
		});
	},
	dijkstra: function (begin, d) {
		var v = this.min_elem();
		while (v != -1) { 
			if (v == d) { this.prev[d] = v; break; }

			if (d == v-1) { this.prev[d] = v; break; }
			this.relax(v, v-1); //左

			if (d == v+1) { this.prev[d] = v; break; }
			this.relax(v, v+1); //右

			if (d == v-this.width) { this.prev[d] = v; break; }
			this.relax(v, v-this.width); //上

			if (d == v+this.width) { this.prev[d] = v; break; }
			this.relax(v, v+this.width); //下

			this.visted[v] = 1;
			v = this.min_elem();
		}
	},
	relax: function(u, v) {
		if (v > this.data.length || v < 0) return;

		var x1 = u % this.width;
		var y1 = Math.floor(u / this.width);

		var x2 = v % this.width;
		var y2 = Math.floor(v / this.width);
		if (Math.abs(x1 - x2) + Math.abs(y1-y2) > 2) { 
			return;
		}
		var pu = this.prev[u];
		var x3 = pu % this.width;
		var y3 = Math.floor(pu / this.width);

		var len = 0;
		if (Math.abs(x3-x2) == 1 && Math.abs(y3-y2) == 1)
			len = 5;

		var newdist = this.dist[u] + (this.data[v] === 0 ? 1 : this.INF) + len;
		if (newdist < this.dist[v]) {
			this.dist[v] = newdist;
			this.prev[v] = u;
		}
	},
	min_elem: function ()
	{
		//因为数据量不大，没有使用效率较高的堆算法
		var min = this.INF;
		var pos = -1;
		for (var i=0; i<this.data.length; i++)
			if (this.visted[i] != 1 && this.dist[i] < min) {
				min = this.dist[i];
				pos = i;
			}
		return pos;
	},
	print : function() {
		var index = [];
		for (var i=0; i<this.data.length;) {
			for (var j=0; j<this.width; j++) {
				var pos = i + j;
				index[this.data[pos]] = index[this.data[pos]] || 0;
				index[this.data[pos]] += 1;
			}
			var n = i + this.width;
			console.log(this.data.slice(i,n));
			i = n;
		}
		console.log("IMGS:" + index);
	},
	find_one_path:  function() {
		var path = [];
		var visted = [];
		for (var i=0; i<this.data.length; i++) {
			if (this.data[i] != 0 && visted[i] != 1) {
				visted[i] = 1;
				for (var j=i+1; j<this.data.length; j++) {
					if (this.data[j] != 0 && this.data[i] == this.data[j]) {
						path = this.get_path(i, j, true);
						if (path.length > 0) return [path[path.length-1], path[0]];
					}
				}
			}
		}
		console.log("ERROR:");
		return [];
	}
};

DrawObj = function (ctx) {
	this.ctx = ctx;
};
DrawObj.prototype = {
	roundRect: function(x, y, width, height, radius) {
		   this.ctx.beginPath();
		   radius = 3;
		   this.ctx.moveTo(x, y);
		   this.ctx.lineTo(x + width, y);
		   //this.ctx.arc(x+width-radius, y+radius, radius, -Math.PI/2, Math.PI/2, false);
		   this.ctx.lineTo(x + width, y + height);
		   //this.ctx.arc(x+radius, y+radius, radius, Math.PI/2, 3*Math.PI/2, false);
		   this.ctx.lineTo(x, y+height);
		   this.ctx.closePath();
		   //this.ctx.stroke();
		   this.ctx.fill();
	},
	progressBar: function(x, y, width, height, text, ratio) {
		this.ctx.save();
		this.ctx.fillStyle = "rgba(0, 0, 0, 0.2)";
		this.ctx.clearRect(x-10, y, width+20, height);
		this.ctx.fillRect(x-10, y, width+20, height);
		// Set shadows to make some depth
		this.ctx.shadowOffsetX = 2;
		this.ctx.shadowOffsetY = 2;
		this.ctx.shadowBlur = 5;
		this.ctx.shadowColor = '#666';

		var lingrad = this.ctx.createLinearGradient(0,y+height,0,0);
		lingrad.addColorStop(0, 'rgba(255,255,200, 0.1)');
		lingrad.addColorStop(0.4, 'rgba(255,255,200, 0.7)');
		lingrad.addColorStop(1, 'rgba(255,255,200,0.4)');
		this.ctx.fillStyle = lingrad;
		this.roundRect(x, y, width, height);


		this.ctx.shadowColor = 'rgba(0,0,0,0)'


		this.ctx.fillStyle = 'green';
		this.ctx.fillText(text, 13, height*(1-ratio)+28);

		this.ctx.lineJoin = "round";
		this.ctx.lineWidth = 5;
		this.ctx.strokeRect(x-5, height*(1-ratio)+10, width+10, 25);

		this.ctx.restore();

	},
};
