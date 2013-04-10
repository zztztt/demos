
var snakegame = new snake("#FF000",5,50,25);
function start(){
	snakegame.init();
}
function move(x){

}
function Map(x,y){
	var map = Array();
	this.x = x;
	this.y = y;
	for(i = 0 ; i < x ; i++){
		map[i] = Array();
		for(j = 0 ; j < y ; j++){
			map[i][j] = 0;
		}
	}
	this.get = function(x,y){
		return map[x][y];
	}
	/**
	 *	x, y is position
	 *	type : 0 is null, 1 is snake, 2 is 
	 */
	this.set = function(x,y,type){
		//console.debug("map[%s][%s] is %s",x,y,type);
		map[x][y] = type;
	}
}
function snake(color,snakelength){
	/**
	 *获得节点对象，获取其宽和高
	 *设置最小的单位块大小
	 */
	var c=document.getElementById("snakegame");
	var ctx=c.getContext("2d");
	var c_width = c.offsetWidth;
	var c_height = c.offsetHeight;
	console.debug("width : %s px height is %s px",c_width,c_height);
	/**
	 *设置画布的格局分布大小
	 */
	var minblock = 8;
	var x = c_width / minblock;
	var y = c_height / minblock;
	init_x = 50;
	init_y = 25;
	this.snakelength = snakelength;
	console.debug("minblock is %s px, then width is %s minblocks,height is %s minblocks",minblock,x,y);

	
	//snake object

	var map = new Map(x, y);
	this.color = color;
	this.length = length;
	this.init = function(){
		console.debug("init snake");
		snakebody = Array();
		for(i = 0 ; i < this.snakelength ; i++){
			map.set(i + init_x,init_y,1);
			snakebody[i] = Array();
			snakebody[i]["x"] = init_x + i;
			snakebody[i]["y"] = init_y;
		}
		this.repaint();


	}
	this.repaint = function(){
		console.debug("repaint canvas");
		for(i = 0 ; i < map.x ; i++){
			for(j = 0 ; j < map.y ; j++){
				if(map.get(i,j) == 1){
					ctx.fillStyle = this.color;
					console.debug("reparint x is %s , y is %s",i*minblock,j*minblock);
					ctx.fillRect(i*minblock,j*minblock,minblock,minblock);	
				}
			}
		}
	}
	this.move = function(x){
		
	}
}
