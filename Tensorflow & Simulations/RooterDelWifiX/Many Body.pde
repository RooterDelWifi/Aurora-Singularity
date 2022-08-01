int n = 700;
float dt = 0.00004;
float t;
objeto[] bola = new objeto[n];

void setup(){
size(1280, 720, P2D);
frameRate(1000);
for(int i = 0; i < n; i++){
bola[i] = new objeto();
}
}

void draw(){
background(0);
for(int i = 0; i < n; i++){
  for(int j = 0; j < n; j++){
     if(i != j){
      bola[i].resolver(bola[j]);
     }
  }
}

for(int i = 0; i < n; i++){
bola[i].mostrar();
}
t = t + dt;
text("tiempo:  " + t, 640, 720); 
//ellipse(640, 360, 10, 10);
}
class objeto{
int k = int(random(0, 2));
float x = random(0, 1280);
float radio = 10;
float y = random(0, 720);
float M = 2*pow(10, 6);
float vx = random(-100, 100)*0;
float vy = random(-100, 100)*0;
float[] F = {0, 0, 0, 0};
int r = int(random(0, 255));
int g = int(random(0, 255));
int b = int(random(0, 255));
int kiss1, kiss2, kiss3, kiss4 = 0;
float G = 1;
//float G = 100;
//float  M = ;
//float M = 10000000;

 void resolver(objeto other1){
  if(dist(x, y, other1.x, other1.y) > 8){
   F[0] = vx;
   F[1] = (-G*M/( pow((pow(x - other1.x, 2) + pow(y - other1.y, 2)), 1.5) ))*(x - other1.x);
   F[2] = vy;
   F[3] = (-G*M/( pow((pow(x - other1.x, 2) + pow(y - other1.y, 2)), 1.5) ))*(y - other1.y);
   
   
     if((x < 0)&&(kiss1 == 0)){
     vx = -vx;
     kiss1 = 1;
    }
    if((x > 0)&&(kiss1 == 1)){
     kiss1 = 0;
    }
    if((x > 1280)&&(kiss2 == 0)){
      vx = -vx;
      kiss2 = 1;
    }
    if((x < 1280)&&(kiss2 == 1)){
      kiss2 = 0;
    }
    
      if((y < 0)&&(kiss3 == 0)){
     vy = -vy;
     kiss3 = 1;
    }
    if((y > 0)&&(kiss3 == 1)){
     kiss3 = 0;
    }
    if((y > 720)&&(kiss4 == 0)){
      vy = -vy;
      kiss4 = 1;
    }
    if((y < 720)&&(kiss4 == 1)){
      kiss4 = 0;
    }
    
    
    if( abs(vx) >200){
    vx = vx/2;
    }
   if(abs(vy) > 200){
    vy = vy/2;
    }
    
   x += F[0]*dt;
   vx += F[1]*dt;
   y += F[2]*dt;
   vy += F[3]*dt;
  }
   }

 
 void mostrar(){
   if(x < 1280){
     if(x > 0){
 fill(vy + vx, vx - vy, pow(pow(vx, 2) + pow(vy, 2), 0.5));
 ellipse(x, y, radio, radio);
 fill(255);
     }
   }
 }
}
