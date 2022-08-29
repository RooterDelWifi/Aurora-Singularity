let canvas = document.getElementById("Canvas");
let dibujar = canvas.getContext("2d");
let bolas = []
let Encendido = false;
const G = 1;
const M = Math.pow(10, 6);
let Ms = 1;
let n = 0;
let i = 1;
let dt = 0.00001;
let GravityONs = false;
let vmax = 300;

class ball{
  F0 = 0;
  F1 = 0;
  F2 = 0; 
  F3 = 0;
  r = 5;
  x = 750/2;
  y = 750/2;
  vx = 0;
  vy = 0;
  red = 255*Math.random() + 1
  green = 255*Math.random() + 1
  blue = 255*Math.random() + 1

  constructor(){
    this.x = 750*Math.random()+1;
    this.y = 750*Math.random()+1 ;
    this.vx = 12*Math.random()-1;
    this.vy = 12*Math.random()-1;
  }

  mover(){
    this.x = this.x + this.vx*i*dt;
    this.y = this.y + this.vy*i*dt;
    if(this.x < 0 || this.x > 750){
      this.vx = -this.vx;
    }
    if(this.y < 0 || this.y > 750){
     this.vy = -this.vy;
    }
    if(this.vy >= vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
    if(this.vx >= vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
    if(this.vy <= -vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
    if(this.vx <= -vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
  }

  resolver(other){
    if(Math.sqrt(Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2)) > 20){
     this.F0 = this.vx;
     this.F1 = (-G*Ms/( Math.pow((Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2)), 1.5) ))*(this.x - other.x);
     this.F2 = this.vy;
     this.F3 = (-G*Ms/( Math.pow((Math.pow(this.x - other.x, 2) + Math.pow(this.y - other.y, 2)), 1.5) ))*(this.y - other.y);
      
    if(this.vy >= vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
    if(this.vx >= vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
    if(this.vy <= -vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
    if(this.vx <= -vmax){
      this.vy = this.vy/2;
      this.vx = this.vx/2;
    }
     this.x += this.F0*dt*i;
     this.vx += this.F1*dt*i;
     this.y += this.F2*dt*i;
     this.vy += this.F3*dt*i;
     if(this.x < 0 || this.x > 750){
      this.vx = -this.vx;
    }
    if(this.y < 0 || this.y > 750){
     this.vy = -this.vy;
    }
    }
  }

  mostrar(){
    circle(this.x, this.y, this.r, `rgb(${this.red}, ${this.green}, ${this.blue})`);
  }


}
function circle(x, y, r, color){
   dibujar.fillStyle = color;
   dibujar.beginPath();
   dibujar.arc(x, y, r, 0, 2*Math.PI);
   dibujar.fill();
}
function background(color){
 dibujar.fillStyle = color;
 dibujar.beginPath();
 dibujar.moveTo(0, 0);
 dibujar.lineTo(750, 0);
 dibujar.lineTo(750, 750);
 dibujar.lineTo(0, 750);
 dibujar.fill();
}
function SystemStart(){
 n = Number(document.getElementById("number").value);
 for(let i = 0; i < n; i++){
 bolas.push(new ball())
 }
 Encendido = true;
}
function NextFrame(){
background("black");
 if(GravityONs){
 for(let i = 0; i < n; i++){
  bolas[i].mover();
  bolas[i].mostrar();
 }
 }else{
  Gravity();
 function Gravity(){
  for(let i = 0; i < n; i++){
    bolas[i].mostrar();
  for(let j = 0; j < n; j++){
    if(i != j){
    bolas[i].resolver(bolas[j]);
    }
  }
 }
 }
}
}
function Pause(){
  if(i == 1){
    i = 0;
    document.getElementById("pnumber").innerHTML = "Continue";
  }else{
    i = 1;
    document.getElementById("pnumber").innerHTML = "Pause"
  }
}
function Grav(){
  Ms = Number(document.getElementById("mass").value)*M;
}
function GravityON(){
 if(GravityONs == true){
  GravityONs = false;
 }else{
  GravityONs = true;
 }
}
function Reset(){
for(let k = 0; k < n; k++){
  bolas.pop();
  vmax = 300;
  Ms = 1;
}
}
function Speed(){
  vmax = Number(document.getElementById("speed").value)
}

if(Encendido = true){
 setInterval(NextFrame, 1)
}
