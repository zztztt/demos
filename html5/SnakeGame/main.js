function start(){
	console.debug("start snakegame"); 
	snakegame = new SnakeGame("snakegame");
	setInterval("snakegame.go()",100);
}
function SnakeGame(id){
	id = "snakegame"
	var c = document.getElementById(id);
	this.ctx = c.getContext("2d");
	/**/
	this.minblock = 8;
	this.wpx = c.offsetWidth;
	this.hpx = c.offsetHeight;
	console.info("width is %s , height is %s",this.wpx, this.hpx);
	width = this.wpx / this.minblock;
	height = this.hpx / this.minblock;
	console.info("width is %s , height is %s",width, height);
	this.direction = 37;
	this.snake = new Snake("#FF0000",3);
	this.food =null;
	this.repaint();
}
SnakeGame.prototype.repaint = function(){
	this.ctx.clearRect(0,0,this.wpx,this.wpx);
	var size = this.minblock;
	for(i = 0 ; i < this.snake.body.length ; i++){
		this.ctx.fillRect(this.snake.body[i].x * size,this.snake.body[i].y * size,size,size);
	}
	if(this.food){
		this.ctx.fillRect(this.food.x * size,this.food.y * size,size,size);
	}
}


SnakeGame.prototype.go = function(){
	if(this.snake.isdie()){
		alert("game over");
	}
	if(this.food == null){
		var x = Math.floor(Math.random() * width);
		var y = Math.floor(Math.random() * height);
		this.food = {"x":x,"y":y};
		console.info(this.food);
	}else if(this.food.x == this.snake.body[0].x && this.food.y == this.snake.body[0].y){
		this.snake.eat();
		this.food = null;
	}
	this.snake.move(this.direction);
	this.repaint();
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
	this.init(5,5);
	this.direction = 37;

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
	console.debug(this.body);
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
Snake.prototype.move = function(x){
	this.body.unshift(this.body.pop());
	var temp;
	switch(x){
		case 38:
			temp = (this.body[1].y - 1 + height) % height;
			if(temp == this.body[1].y){
				console.debug("can not move as this");
			}else{
				this.body[0].y = temp;
				this.body[0].x = this.body[1].x;
			}
			break;
		case 39:
			temp = (this.body[1].x + 1) % width;
			if(temp == this.body[1].x){
				console.debug("can not move as this");
			}else{
				this.body[0].x = temp;
				this.body[0].y = this.body[1].y;
			}
			break;
		case 40:
			temp = (this.body[1].y + 1) % height;
			if(temp == this.body[1].y){
				console.debug("can not move as this");
			}else{
				this.body[0].y = temp;
				this.body[0].x = this.body[1].x;
			}
			break;
		case 37:
			temp = (this.body[1].x - 1 + width) % width;
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
}
/**
 * 吃完后就要发育了
*/
Snake.prototype.eat = function(){
	this.body.push({"x":this.body[0].x,"y":this.body[0].y});
	//this.length = this.body.length;
	console.debug(this.body);
}
Snake.prototype.isdie = function(){
	for(i = 1; i < this.body.length ; i++){
		if(this.body[0].x == this.body[i].x && this.body[0].y == this.body[i].y){
			console.info("the snake is die");
			return true;
		}
	}
	return false;
}
/* end snake*/


document.onkeyup = function(event){
	if(event.keyCode>=37 && event.keyCode<=40 && (Math.abs(event.keyCode - snakegame.direction) != 2)){
		snakegame.direction = event.keyCode;
		//console.info(snakegame.snake.body);
	}
}








