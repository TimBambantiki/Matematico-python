

var Matematico = {
	/*
	 * Object for game Matematico.
	 *
	 * @author: Juda Kaleta <juda.kaleta@gmail.com>
	 * @version: 0.1 alpha
	 * @license: GNU GPL3
	 */

	init : function () {
		this.model = this.Model.init();
		this.controller = this.Controller.init();
		this.viewer = this.Viewer.init();

		this.controller.setEvents();
		this.controller.setNumber();
	},

	Model : {
		object : undefined,
		finished : false,
		number : undefined,
		round : 0,

		numbers : new Array(
			1,1,1,1,
			2,2,2,2,
			3,3,3,3,
			4,4,4,4,
			5,5,5,5,
			6,6,6,6,
			7,7,7,7,
			8,8,8,8,
			9,9,9,9,
			10,10,10,10,
			11,11,11,11,
			12,12,12,12,
			13,13,13,13
		),

		table : new Array(
			new Array( undefined, undefined, undefined, undefined, undefined, undefined ),
			new Array( undefined, undefined, undefined, undefined, undefined, undefined ),
			new Array( undefined, undefined, undefined, undefined, undefined, undefined ),
			new Array( undefined, undefined, undefined, undefined, undefined, undefined ),
			new Array( undefined, undefined, undefined, undefined, undefined, undefined )
		),

		init : function () {
			this.shuffleNumbers();
			return this;
		},

		shuffle : function(o){
			/*
			* Randomize items in array.
			*
			* @authors: Jonas Raoni Soares Silva
			* @url: http://jsfromhell.com/array/shuffle
			* @version: 1.0
			*/
			for(var j, x, i = o.length; i; j = parseInt(Math.random() * i), x = o[--i], o[i] = o[j], o[j] = x);
			return o;
		},

		shuffleNumbers : function() {
			this.numbers = this.shuffle(this.numbers);
		},

		pullNumber : function() {
			if (this.round==25) {
				this.finished = true;
				return this.calcScore();
			}


			this.round++;
			this.shuffleNumbers();
			this.number = this.numbers.pop();
			return this.number;
		},

		saveNumber : function(x, y) {
			this.table[x][y] = this.number;
		},

		sortNumbers : function(a, b) {
			return a - b;
		},

		calcScore : function() {
			if(this.check()) {
				var sum = 0;
				var t = this.table;

				for(var x=0; x<5; x++) {
					sum = sum + this.calcRow(new Array(t[x][0],t[x][1],t[x][2],t[x][3],t[x][4]));
				}

				for(var y=0; y<5; y++) {
					sum = sum + this.calcRow(new Array(t[0][y], t[1][y], t[2][y], t[3][y], t[4][y]));
				}

				var u = this.calcRow(new Array(t[0][0], t[1][1], t[2][2], t[3][3], t[4][4]));
				if (u!=0) { sum = sum+10+u; }

				var u = this.calcRow(new Array(t[4][0], t[3][1], t[2][2], t[1][3], t[0][4]));
				if (u!=0) { sum = sum+10+u; }

				return sum;
			} else {
				return ":-(";
			}
		},

		calcRow : function(row) {
			row.sort(this.sortNumbers);

			if ((row[0]==row[1]&&row[0]==row[2]&&row[0]==row[3])||(row[1]==row[2]&&row[1]==row[3]&&row[1]==row[4])) {
				return 160;
			} else if (row[0]==1&&row[1]==1&&row[2]==13&&row[3]==13&&row[4]==13) {
				return 100;
			} else if ((row[0]==row[1]&&row[0]==row[2]&&row[3]==row[4])||(row[0]==row[1]&&row[2]==row[3]&&row[2]==row[4])) {
				return 80;
			} else if (row[0]==row[1]-1&&row[0]==row[2]-2&&row[0]==row[3]-3&&row[0]==row[4]-4) {
				return 50;
			} else if ((row[0]==row[1]&&row[0]==row[2])||(row[1]==row[2]&&row[1]==row[3])||(row[2]==row[3]&&row[2]==row[4])) {
				return 40;
			} else if ((row[0]==row[1]&&row[2]==row[3])||(row[0]==row[1]&&row[3]==row[4])||(row[1]==row[2]&&row[3]==row[4])) {
				return 30;
			} else if (row[0]==row[1]||row[1]==row[2]||row[2]==row[3]||row[3]==row[4]) {
				return 10;
			}

			return 0;
		},

		check : function() {
			var sum = 0;

			for(var x=0; x<5; x++) {
				for(var y=0; y<5; y++) {
					sum = sum + this.table[x][y];
				}
			}

			if ((sum < 91)||(sum > 259)) {
				return false;
			} else {
				return true;
			}
		}
	},

	Controller : {
		init : function () {
			return this;
		},

		setEvents : function () {
			for(var x=1; x<=5; x++) {
				for(var y=1; y<=5; y++) {
					document.getElementById(x+'-'+y).onclick = Matematico.controller.saveNumber;
				}
			}
		},

		saveNumber : function () {
			if (this.innerHTML=='') {
				position = this.id.split('-');
				Matematico.model.saveNumber(position[0]-1, position[1]-1);
				this.innerHTML = Matematico.model.number;

				Matematico.controller.setNumber();
			}
		},

		setNumber : function () {
			document.getElementById('number').innerHTML = Matematico.model.pullNumber();

			if (Matematico.model.finished==true) {
				document.getElementById('number').innerHTML = "<span class='little'>Tvoje skóre:</span><br>"+document.getElementById('number').innerHTML;
				document.getElementById('number').style.height = "250px";
				document.getElementById('newgame').style.display = "block";
				document.getElementById('info').style.display = "none";
			}
		}
	},

	Viewer : {
		init : function () {
			return this;
		},
	},
};
