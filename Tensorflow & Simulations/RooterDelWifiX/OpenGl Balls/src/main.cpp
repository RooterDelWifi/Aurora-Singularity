#include <C:\Users\Root\Desktop\OPENGL\OpenGl\include\glad\glad.h>
#include <C:\Users\Root\Desktop\OPENGL\OpenGl\include\GLFW\glfw3.h>
#include <C:\Users\Root\Desktop\OPENGL\OpenGl\include\glm\glm\glm.hpp>
#include <C:\Users\Root\Desktop\OPENGL\OpenGl\include\glm\glm\gtc\matrix_transform.hpp>
#include <C:\Users\Root\Desktop\OPENGL\OpenGl\include\glm\glm\gtc\type_ptr.hpp>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
int U = getpid();
float dt = 1;
int Frames = 0;

const float PI = 3.1415926535897932384626433832795;
const float rotation = glm::radians(45.0);
float RESOLUTION = 0.01;
int l = floor(2*PI/RESOLUTION) + 1;

GLuint VAO,VBO,EBO;

//La pelota como tal
class Bola{
  public:
    float radio;
    int contador3 = 0;
    int contador2 = 0;
    int contador1 = 0;
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec2 pos = glm::vec2(0);
    glm::vec2 vel = glm::vec2(2*(rand()%2) - 1, 2*(rand()%2) - 1);
    glm::vec3 CoLor;
    glm::mat4 view = glm::mat4(1.0f);
    float Fx;
    float Fy;

  Bola(){
    U = U + 1;
    srand(U*time(NULL)*getpid());
    float red = rand()%255 + 10;
    float green = rand()%255 + 10;
    float blue = rand()%255 + 10;
    float radio = 1;
    float x = 2*(rand()%400 - 200);
    float y = 2*(rand()%400 - 200);
    this->CoLor = glm::vec3(red/255, green/255, blue/255);
    this->radio = (radio/800)*10;
    model = glm::scale(model, glm::vec3(this->radio, this->radio, this->radio));
    pos = glm::vec2(x, y);
    view = glm::translate(view, glm::vec3(this->pos.x/960, this->pos.y/540, 0.0f));

  }
  void Mostrar(){
    this->pos += this->vel*dt;
    if((this->pos.x > 960 || this->pos.x < -960)&&(contador1 == 0)){
      this->vel.x = -this->vel.x;
      contador1 = 1;
    }
    if((this->pos.y > 540 || this->pos.y < -540)&&(contador2 == 0)){
      this->vel.y = -this->vel.y;
      contador2 = 1;
    }
    if((this->pos.x < 960 || this->pos.x > -960)&&(contador1 == 1)){
      contador1 = 0;
    }
    if((this->pos.y < 540 || this->pos.y > -540)&&(contador2 == 1)){
      contador2 = 0;
    }
    this->view = glm::translate(this->view, glm::vec3(this->vel.x*dt/960, this->vel.y*dt/540, 0.0f));
    glDrawElements(GL_TRIANGLES, l*3, GL_UNSIGNED_INT, 0);
  }
  void Collide(Bola &bola2){
    if((pow(pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2), 0.5) < 10)&&(pow(pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2), 0.5) > 0)){
    float d = pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2);
    this->vel = this->vel -  (((this->vel - bola2.vel)*(this->pos - bola2.pos))/(d))*(this->pos - bola2.pos);
    bola2.vel = bola2.vel +  (((bola2.vel - this->vel)*(bola2.pos - this->pos))/(d))*(this->pos - bola2.pos); 
    this->vel.x += 10*((this->pos.x - bola2.pos.x)/(pow(pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2), 1.5)));
    this->vel.y += 10*((this->pos.y - bola2.pos.y)/(pow(pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2), 1.5)));
    bola2.vel.x += -10*((this->pos.x - bola2.pos.x)/(pow(pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2), 1.5)));
    bola2.vel.y += -10*((this->pos.y - bola2.pos.y)/(pow(pow(this->pos.x - bola2.pos.x, 2) + pow(this->pos.y - bola2.pos.y, 2), 1.5)));
    }
  }

  private:
   void Calcular(Bola other){
    this->vel.x += (2*rand()%2 - 1)*(rand()%10)*((this->pos.x - other.pos.x)/(pow(pow(this->pos.x - other.pos.x, 2) + pow(this->pos.y - other.pos.y, 2), 1.5)))*dt;
    this->vel.y += (2*rand()%2 - 1)*(rand()%10)*((this->pos.y - other.pos.y)/(pow(pow(this->pos.x - other.pos.x, 2) + pow(this->pos.y - other.pos.y, 2), 1.5)))*dt;
    this->vel.x += (2*rand()%2 - 1)*(rand()%10)*((this->pos.x - other.pos.x)/(pow(pow(this->pos.x - other.pos.x, 2) + pow(this->pos.y - other.pos.y, 2), 1.5)))*dt;
    this->vel.y += (2*rand()%2 - 1)*(rand()%10)*((this->pos.y - other.pos.y)/(pow(pow(this->pos.x - other.pos.x, 2) + pow(this->pos.y - other.pos.y, 2), 1.5)))*dt;
  }
};
const int n = 800;
Bola bola[n];

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec2 Pos;\n"
"uniform mat4 Transform; \n"
"void main()\n"
"{\n"
"   gl_Position = Transform * vec4(Pos, 0.0f, 1.0f);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 COLOR;"
"void main()\n"
"{\n"
"   color = COLOR; \n"
"}\n\0";

//Parametrizar la superficie
void parametrizar(float xy[], unsigned int indexof[])
{
 int i = 0;
 float r = 1;
 for(float theta = 0; theta <= 2*PI; theta+= RESOLUTION)
 {
  xy[2*i + 2] = r*cos(theta)/1.777;
  xy[2*i + 3] = r*sin(theta);
  i++;
 }
 for(int n = 0; n + 2 <= l; n++){
  indexof[3*n] = 0;
  indexof[3*n + 1] = n + 1;
  indexof[3*n + 2] = n + 2;
 }
 xy[i*2] = r*cos(0);
 xy[i*2 + 1] = r*sin(0); 
}

//nada importante
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
 glViewport(0, 0, width, height);
}


int main()
{
    //Inicializar OPENGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   float vertices[l*2 + 2] = {
    };
   unsigned int index[l*3] ={
   };
    parametrizar(vertices, index);
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Bolas dot exe", NULL, NULL);
    if(window == NULL)
    {
      std::cout <<"Failed to create GLFW Window"<<std::endl;
      glfwTerminate();
      return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 1920, 1080);

    //Compilar Vertices
    GLuint shaderProgram = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Compilar Colores
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    //atributes

    //Vertex array element to use
    glBindVertexArray(VAO);
    //Vertex Buffer Objet to use (container)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    //Element Buffer Object inDExsU OFFF
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    //Positions
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (const void*)0);
    //Colors 7w7
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glUseProgram(shaderProgram);
    //Las Bolas!

    //Bola bola = Bola(-200, 0.0, 2.0, 200, 100, 50);
    //Bola bola2 = Bola(200, 0.0, 3.0, 100, 50, 200);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
      //glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glUseProgram(shaderProgram);

      glEnable(GL_DEPTH_TEST);
      glBindVertexArray(VAO);
      GLuint TRANSFORM = glGetUniformLocation(shaderProgram, "Transform"); 
      GLuint COLOR = glGetUniformLocation(shaderProgram, "COLOR");

      for(int i = 0; i < n; i++){
      glUniform4f(COLOR, bola[i].CoLor.x, bola[i].CoLor.y, bola[i].CoLor.z, 1.0);
      glUniformMatrix4fv(TRANSFORM, 1, GL_FALSE, glm::value_ptr(bola[i].view * bola[i].model));
      bola[i].Mostrar();
      }
      //std::cout<<sizeof(bola)<<std::endl;
      //std::cout<<bola[0].x<<std::endl;
            //Fisica O(x**2)
     if(Frames%1 == 0){
      for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
          if(i != j){
            bola[i].Collide(bola[j]);
          }
        }
      }
     }

      Frames++;
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
   return 0;
}