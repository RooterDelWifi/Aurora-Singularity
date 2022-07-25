class player{
  float x, y;
  char a, b;
  int I;
  int ks = 1;
  int h =1;
  float bs = 6;
  int colision = 0;
  int kiss1 = 0;
  int kiss2 = 0;
  boolean mover;
  player(float Tempx, float Tempy, char A, char B){
    x = Tempx;
    y = Tempy;
    a = A;
    b = B;  
  }
   player(float Tempx, float Tempy, int p){ 
    x = Tempx;
    y = Tempy; 
    I = p;
  }
   void display(int i){
     //fill((i +o)*ks*255/vs, (i + o)*ks*255/vs, 120);
     fill(255);
     if(i == 0){
      fill(0,120, 150);
    }
     rect(x, y, 150, 10);
   }
   void move(){
     if(keyPressed){
      if(key == a){
      x = x - v;
     }
     if(key == b){
      x = x + v;
     }
     }
   }
   void IA(int i){
     nn Brain = Brains.get(i);
     ball ball = balls.get(i);
     player p2 = p2s.get(i);
      k[i] = Brain.frontPropagate(ball, p2);
      
     if(k[i][1] > 0.5){
       mover = false;
     }
   else{
   mover = true;
   }
      if(mover == true){
      if(i == 0){
       //fill(100, 100, 120);
      //text(k[i][0], 300, 450);
      //text(k[i][1], 400, 450);
      }
      if(k[i][0] < 0.5){
      //bs = 6;
      x = x - bs;
     }
     if(k[i][0] > 0.5){
      //bs = 6;
      x = x + bs;
     }
     if((x < 0)&&(kiss1 == 0)){
     //time[i] = time[i] - 1*dt;
     bs = -bs;
     kiss1 = 1;
    }
    if((x > 0)&&(kiss1 == 1)){
     kiss1 = 0;
    }
    if((x > 700)&&(kiss2 == 0)){
      //time[i] = time[i] - 1*dt;
      bs = -bs;
      kiss2 = 1;
    }
    if((x < 700)&&(kiss2 == 1)){
      kiss2 = 0;
    }
   }
   }
   void collide(ball other, int i){
      ball ball = balls.get(i);
     if( dist(x, y, ball.x, ball.y)<= 20){
      //time[i] = time[i] + 1*dt;
     }
     if(colision == 0){
    if(abs(y + 5 - other.y) <= 5){
     if(abs(x + 75 - other.x) <= 75){
       other.vy = -other.vy;
       time[i] = time[i] + 1;
        colision = 1;
        golpes++;
     }
    }
   }
   if(abs(y + 5 - other.y) >= 5){
     if(abs(x + 75 - other.x) >= 75){
       colision = 0;
     }
    }
   }
   void Muerte(int i){
       if(kss[i] == 1){
       x = 10000;
       y = 10000;
    }
   }
}
