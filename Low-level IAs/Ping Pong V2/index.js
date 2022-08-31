let canvas = document.getElementById("Canvas");
let dibujar = canvas.getContext("2d");
let L = 100/700;
let learning_rate = 0.01;
let count = 0;
class ball{
  r = 10;
  x = 750/2;
  y = 750/2;
  vx = 0;
  vy = 0;
  h = 0.943;
  red = 255*Math.random() + 1
  green = 255*Math.random() + 1
  blue = 255*Math.random() + 1
  constructor(){
    this.x = 700*Math.random()+1;
    this.y = 750*Math.random()+1;
    this.vx = 0.8;
    this.vy = 1.5;
  }
  mover(){
    this.x = this.x + this.vx;
    this.y = this.y + this.vy;
    if(this.x < 0 || this.x > 700){
      this.vx = -this.vx;
    }
    if(this.y < 0 || this.y > 900){
     this.vy = -this.vy;
     this.x = 450*Math.random()+1;
     this.y = 450*Math.random()+1;
    }
  }

  mostrar(){
   circle(this.x, this.y, this.r, `rgb(${this.red}, ${this.green}, ${this.blue})`);
  }
}
class player{
  contador = 0;
  w1 = [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]];
  dw1 = [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]];
  b1 = [0,0 ,0 ,0];
  db1 = [0,0 ,0 ,0];
  w2 = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
  dw2 = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];
  b2 = [0, 0, 0, 0];
  db2 = [0, 0, 0, 0];
  w3 = [0, 0, 0, 0];
  dw3 = [0, 0, 0, 0];
  b3 = 0;
  db3 = 0;
  Z1 = [0, 0, 0, 0];
  Z2= [0, 0, 0, 0];
  Z3= 0;
  a1= [0, 0, 0, 0];
  X = [1, 0, 1];
  a2= [0, 0, 0, 0];
  a3= 0;
  red = 255*Math.random() + 1
  green = 255*Math.random() + 1
  blue = 255*Math.random() + 1

  constructor(px, py){
    this.x = px;
    this.y = py;
   for(let i = 0; i < 4; i++){
    this.b1[i] = 2*Math.random() - 1;
    this.b2[i] = 2*Math.random() - 1;
    this.w3[i] = 2*Math.random()-1;
    this.b3 = 2*Math.random() -1;
    for(let j =0; j < 4; j++){
      this.w2[i][j] = 2*Math.random()-1;
    }
    for(let j = 0; j < 3; j++){
      this.w1[i][j] = 2*Math.random()-1;
    }
   }
  }
  x = 400;
  y = 850;
  mostrar(){
    rect(this.x, this.y, `rgb(${this.red}, ${this.green}, ${this.blue})`);
  }

  calcular(other, other2){
    this.X[0] = other.x/700;
    this.X[1] = other2.x/700;
    this.X[2] = this.x/700;
    for(let j = 0; j<4; j++){
     let suma = 0;
     for(let k = 0; k < 3; k++){
       suma = suma + this.w1[j][k]*(this.X[k]);
     }
      this.Z1[j] = suma + this.b1[j];
    }

    for(let i = 0; i < 4; i++){
      let suma = 0;
      for(let j = 0; j<4; j++){
       suma = suma + this.w2[i][j]*tanh(this.Z1[j]);
      }
      this.Z2[i] = suma + this.b2[i];
    }
    let suma = 0;
    for(let i = 0; i < 4; i++){
     suma = suma + this.w3[i]*tanh(this.Z2[i]);
    }
    this.Z3 = suma + this.b3;
    this.a3 = tanh(this.Z3)*10/800;
    return (this.a3);
  }
  backpropagation(){
    count = count + 1;
    let kr = [0, 0, 0, 0];
    for(let i = 0; i < 4; i++){
      let suma = 0;
    for(let k  = 0; k<4; k++){
      suma = suma + this.w3[k]*(1 - tanh(this.Z2[k])*tanh(this.Z2[k]))*this.w2[k][i];
    }
    kr[i] = suma;
  }

    this.db3 = ( this.a3 + L/2 + this.X[2] - this.X[0])*(1- tanh(this.Z3)*tanh(this.Z3));
    for(let i = 0; i < 4; i++){
    this.dw3[i] = (this.a3 + L/2 + this.X[2] - this.X[0])*(1- tanh(this.Z3)*tanh(this.Z3))*tanh(this.Z2[i]);
    this.db2[i] = (this.a3 + L/2 + this.X[2] - this.X[0])*(1-tanh(this.Z3)*tanh(this.Z3))*(1-tanh(this.Z2[i])*tanh(this.Z2[i]))*(this.w3[i]);
      for(let j = 0; j < 4; j++){
        this.dw2[i][j] = (this.a3 + L/2 + this.X[2] - this.X[0])*(1-tanh(this.Z3)*tanh(this.Z3))*(1-tanh(this.Z2[i])*tanh(this.Z2[i]))*(this.w3[i])*tanh(this.Z1[j]);
        //this.dw2[i][j] = 0;
      }
      for(let j = 0; j<3; j++){
        this.dw1[i][j] = (this.a3 + L/2 + this.X[2] - this.X[0])*(1-tanh(this.Z3)*tanh(this.Z3))*kr[i]*(1-tanh(this.Z1[i])*tanh(this.Z1[i]))*this.X[j];
        this.db1[i] = (this.a3 + L/2 + this.X[2] - this.X[0])*(1-tanh(this.Z3)*tanh(this.Z3))*kr[i]*(1-tanh(this.Z1[i])*tanh(this.Z1[i]));
      }
    }
    
    for(let i = 0; i < 4; i++){
      this.b1[i] = this.b1[i] - learning_rate*this.db1[i];
      this.b2[i] = this.b2[i] - learning_rate*this.db2[i];
      this.w3[i] = this.w3[i] - learning_rate*this.dw3[i];
      for(let j = 0; j < 3; j++){
        this.w1[i][j] = this.w1[i][j] - learning_rate*this.dw1[i][j];
      }
      for(let j = 0; j< 4; j++){
        this.w2[i][j] = this.w2[i][j] - learning_rate*this.dw2[i][j];
      }
    }
    this.b3 = this.b3 - learning_rate*this.db3;
  }
  mover(){
    this.x = this.x + this.a3*700;
  }


  collide(other){
    if((Math.abs(other.y - this.y) <= 10)&&(Math.abs(other.x - this.x - 50) <= 50)){
    other.vy = -(other.vy);
    this.contador++;
    other.vx = 0.8*3*(2*Math.random() - 1);
    }
  }

}


let bola = new ball();
let player1 = new player(400, 850);
let player2 = new player(400, 50);
function Next(){
  background("black");
  bola.mover();
  bola.mostrar();
  player1.mostrar();
  player1.calcular(bola, player2);
  player1.backpropagation();
  player1.mover();
  player1.collide(bola);
  player2.mostrar();
  player2.calcular(bola, player1);
  player2.backpropagation();
  player2.mover();
  player2.collide(bola);
  MostrarRed(player1);
}
setInterval(Next, 1);
function tanh(x){
  let z = (Math.exp(2*x) - 1)/(Math.exp(2*x) + 1);
  return z;
}
function sig(x){
  let z = 1/(1 + Math.exp(-x));
  return z;
}
function circle(x, y, r, color){
  dibujar.fillStyle = color;
  dibujar.beginPath();
  dibujar.arc(x, y, r, 0, 2*Math.PI);
  dibujar.fill();
}
function circleS(x, y, r, color){
  dibujar.strokeStyle = color;
  dibujar.beginPath();
  dibujar.arc(x, y, r, 0, 2*Math.PI);
  dibujar.stroke();
}
function rect(x, y, color){
 dibujar.fillStyle = color;
 dibujar.beginPath();
 dibujar.rect(x, y, L*800, 10);
 dibujar.fill();
}
function background(color){
dibujar.fillStyle = color;
dibujar.beginPath();
dibujar.moveTo(0, 0);
dibujar.lineTo(800, 0);
dibujar.lineTo(800, 900);
dibujar.lineTo(0, 900);
dibujar.fill();
}

function MostrarRed(uno){
  dibujar.font = "15px Arial";
  dibujar.fillStyle = "white";
  dibujar.fillText("player#2 Score: " + player2.contador, 20, 860);
  dibujar.fillText("player#1 Score: " + player1.contador, 20, 890);
}
