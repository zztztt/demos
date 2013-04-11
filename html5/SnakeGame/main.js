
function start(){
	snake = new Snake("#FF0000",3);
	direction = 37;
}
function move(x){

}

/* begin snake*/

/**
 * Snake 对象,会动会长长
 * param color 
 * param length
 */
function Snake(color, length){
	this.color = color;
	this.length = length;
	this.body = Array();
	
	var c=document.getElementById("snakegame");
	this.ctx=c.getContext("2d");
	this.c_width = c.offsetWidth;
	this.c_height = c.offsetHeight;
	this.minblock = 8;
	this.areaWidth = this.c_width / this.minblock;
	this.areaHeight = this.c_height / this.minblock;
	this.init(5,5);
	this.food = null;
	this.direction = 37;
	this.food = {x:Math.random * (this.areaWidth - 1), y:Math.random * (this.areaHeight - 1)};
	
}
/**
 * Snake 初始化位置
 * param x
 * param y 
 */
Snake.prototype.init = function(x, y){
	for(i = 0 ; i < this.length ; i++){
		var bodyblock = {"x":x+i,"y":y};
		this.body.push(bodyblock);
	}
}
/**
 * 移动方向后的位置
 * param : x  1:north 2:east 3:south 4:west
 *    38
 *	  ||
 *37==()==39
 *	  ||
 *	  40	
 */    
Snake.prototype.move = function(){
	/**
	 *
	 */
	this.body.unshift(this.body.pop());
	var temp;
	switch(this.direction){
		case 38:
			temp = (this.body[1].y - 1 + this.areaHeight) % this.areaHeight;
			if(temp == this.body[1].y){
				console.debug("can not move as this");
			}else{
				this.body[0].y = temp;
				this.body[0].x = this.body[1].x;
			}
			break;
		case 39:
			temp = (this.body[1].x + 1) % this.areaWidth;
			if(temp == this.body[1].x){
				console.debug("can not move as this");
			}else{
				this.body[0].x = temp;
				this.body[0].y = this.body[1].y;
			}
			break;
		case 40:
			temp = (this.body[1].y + 1) % this.areaHeight;
			if(temp == this.body[1].y){
				console.debug("can not move as this");
			}else{
				this.body[0].y = temp;
				this.body[0].x = this.body[1].x;
			}
			break;
		case 37:
			temp = (this.body[1].x - 1 + this.areaWidth) % this.areaWidth;
			if(temp == this.body[1].x){
				console.debug("can not move as this");
			}else{
				this.body[0].x = temp;
				this.body[0].y = this.body[1].y;
			}
			break;
		default:
			break;
	}
	console.debug(this.body);
	this.repaint();
}
/**
 * 吃完后就要发育了
 */
Snake.prototype.eat = function(){
	this.body.push({"x":this.body[0].x,"y":this.body[0].y});
	//this.length = this.body.length;
	console.debug(this.body);
}
Snake.prototype.repaint = function(){
	this.ctx.clearRect(0,0,this.c_width,this.c_height);
	var size = this.minblock;
	for(i = 0 ; i < this.body.length ; i++){
		this.ctx.fillRect(this.body[i].x * size,this.body[i].y * size,size,size);
	}
}
/* end snake*/


document.onkeyup = function(event){
	if(event.keyCode>=37 && event.keyCode<=40 && (Math.abs(event.keyCode - direction) != 2)){
		direction = event.keyCode;
		snake.direction = direction;
		snake.move();
	}
}








