float a, d = 0;
float A = 900;
float B = 900;
float T = 9000;
float resol = 9;
float lx = A/resol;
float ly = B/resol;
float lt = T/resol;
float dx = 1/lx;
float dy = 1/ly;
float dt = 1/lt;
int i = 0;
onda onda = new onda();
float[][][] honda = new float[int(lt)][int(lx)][int(ly)]; 
void setup(){
size(1280, 720, P3D);
//fullScreen(P3D);
noStroke();
//stroke(255);
frameRate(1000);
noFill();
}
void draw(){
background(255);
translate(width/2, height/2);
rotateX(PI/3);
//rotateX(d);
translate(-A/2, -B/2);
honda = onda.Propagar();

if(i < lt - 1){
i++;
for(int y = 0; y < ly - 1; y++){
  beginShape(TRIANGLE_STRIP);
 for(int x = 0; x < lx; x++){ 
  stroke(0);
  // fill((20*honda[i][x][y])/4, abs(20*honda[i][x][y]), abs(20*honda[i][x][y]));
   vertex(x*resol, y*resol, 2*honda[i][x][y]);
   vertex(x*resol, y*resol + resol, 2*honda[i][x][y + 1]);
 }
 endShape();
}
}

d += 0.01;
}
class onda{
float vc = 4;
float[][][] onda = new float[int(lt)][int(lx)][int(ly)];
//float[][] honda0 = new float[int(lx)][int(ly)];

onda(){
for(int i = 0; i < lx; i++){
 for(int j = 0; j < ly; j++){
  onda[0][i][j] = 50*exp((-pow(i, 2) -pow(j, 2))/1)*0;
  onda[1][i][j] = onda[0][i][j] - onda[0][i][j]*dt*0;
 }
}

}
float[][][] Propagar(){
for(int t = 2; t < lt; t++){
for(int i = 1; i < lx - 1; i++){
 for(int j = 1; j < ly - 1; j++){
   onda[t][i][j] = pow((dt/dx)*vc, 2)*(onda[t - 1][i - 1][j] - 2*onda[t - 1][i][j] + onda[t - 1][i + 1][j])  +  pow((dt/dx)*vc, 2)*( onda[t -1][i][j - 1] - 2*onda[t - 1][i][j] + onda[t - 1][i][j + 1]) + 2*onda[t - 1][i][j] - onda[t - 2][i][j];
  //println(lt - t);
  if(i == 50){
  if(j == 50){
  onda[t][i][j] = -100;
  }
  }
  }
 }
}
//honda0 = honda1;
return onda;
}
}
