#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/gl.h>
#include <gl/glu.h>

using std::cout;

// A simple two-dimensional point class to make life easy.  It allows you to
// reference points with x and y coordinates instead of array indices) and
// encapsulates a midpoint function.

/* a point data type */
typedef GLfloat point2[2];
/* initial triangle  global variables */
point2 v[]={{-1.0, -0.58}, {1.0, -0.58},
{0.0, 1.15}};
int n = 0; /* number of recursive steps */

void triangle( point2 a, point2 b, point2 c)
/* display one triangle */
{
    glBegin(GL_TRIANGLES);
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int m)
{
    /* triangle subdivision using vertex coordinates */
    point2 v0, v1, v2;
    int j;
    if(m>0)
    {
        for(j=0; j<2; j++) v0[j]=(a[j]+b[j])/2;
        for(j=0; j<2; j++) v1[j]=(a[j]+c[j])/2;
        for(j=0; j<2; j++) v2[j]=(b[j]+c[j])/2;
        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    }
    else(triangle(a,b,c));
    /* draw triangle at end of recursion */
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    divide_triangle(v[0], v[1], v[2], n);
    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (1.0, 1.0, 1.0,1.0);
    glColor3f(0.0,0.0,0.0);
}

int main(int argc, char* argv[]){

  SDL_Init(SDL_INIT_VIDEO); // Init SDL2

  // Create a window. Window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
  SDL_Window *window = SDL_CreateWindow(
    "SDL2/OpenGL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
  );

  // Create an OpenGL context associated with the window.
  SDL_GLContext glcontext = SDL_GL_CreateContext(window);

  init();

  // ... can be used alongside SDL2.
  SDL_Event e;
  //SDL_MouseButtonEvent mbe;
  while(e.key.keysym.scancode!=SDL_SCANCODE_ESCAPE){  // Enter main loop.
    SDL_PollEvent(&e); // Check for events.

    glClear(GL_COLOR_BUFFER_BIT);
    if (e.type == SDL_KEYDOWN)
         {
            if(e.key.keysym.scancode == SDL_SCANCODE_0)
            {
                n++;
            }
            else if(e.key.keysym.scancode == SDL_SCANCODE_1){
                n--;
            }
         }
    display();
    SDL_GL_SwapWindow(window); // Swap the window/buffer to display the result.
    SDL_Delay(10); // Pause briefly before moving on to the next cycle.
  }

  // Once finished with OpenGL functions, the SDL_GLContext can be deleted.
  SDL_GL_DeleteContext(glcontext);

  // Done! Close the window, clean-up and exit the program.
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
