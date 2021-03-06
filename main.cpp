//	##########################################################
//	By Philip Murgatroyd, building on an infrastructure created by
//  Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//	A C++ Application
//	MZ001
//
//  Kind of a strategy game, mainly created to practice C++
//
//	##########################################################

#include <iostream>
#include <string>
#include "OGLUtil.h"
#include "Army.h"
#include "Town.h"
#include <GL/freeglut.h>
#include <vector>
using namespace std;

/****************************** PROTOTYPES ******************************/
void checkKeyPress();
void initOpenGL();
int setViewport( int width, int height );
void renderScene();
void DrawSquare(float xPos, float yPos, float zPos, float red, float green, float blue);

/****************************** GLOBAL VARIABLES ******************************/
SDL_Event event;                // declare an SDL event
bool isRunning;                 // main loop state

SDL_Window* displayWindow;
SDL_Renderer* displayRenderer;
SDL_RendererInfo displayRendererInfo;

Army **thisarmy = new Army*;
//Town **Towns = new Town*[9];
//vector<Town> Towns(9);
const int townsize = 9;
Town towns[townsize];

// background colour starts with sand
float r = 0.8f;
float g = 0.8f;
float b = 0.5f;

int range = 25;

/****************************** MAIN METHOD ******************************/
int main(int argc, char**argv)
{
    glutInit(&argc, argv);

    // instantiate n Armys
    Army thisarmy = Army(101, 30, 0);

    // instantiate n Towns
    /*Towns.at(0) = Town(1, 30, 0, "One");
    Towns.at(1) = Town(2, 15, 10, "Two");
    Towns.at(2) = Town(3, 15, -10, "Three");
    Towns.at(3) = Town(4, 0, 0, "Four");
    Towns.at(4) = Town(5, 0, 20, "Five");
    Towns.at(5) = Town(6, 0, -20, "Six");
    Towns.at(6) = Town(7, -15, 10, "Seven");
    Towns.at(7) = Town(8, -15, -10, "Eight");
    Towns.at(8) = Town(9, -30, 0, "Nine");*/

    towns[0] = Town(1, 30, 0, "One");
    towns[1] = Town(2, 15, 10, "Two");
    towns[2] = Town(3, 15, -10, "Three");
    towns[3] = Town(4, 0, 0, "Four");
    towns[4] = Town(5, 0, 20, "Five");
    towns[5] = Town(6, 0, -20, "Six");
    towns[6] = Town(7, -15, 10, "Seven");
    towns[7] = Town(8, -15, -10, "Eight");
    towns[8] = Town(9, -30, 0, "Nine");


    for (int i = 0; i < townsize; i++)
    {
      cout << "Setting up neighbours for town " << i << endl;
      for (int j = 0; j < townsize; j++)
      {
        if (i != j)
        {
          int dx = towns[i].getX() - towns[j].getX();
          float distx = abs(dx) * abs(dx);
          int dy = towns[i].getY() - towns[j].getY();
          float disty = abs(dy) * abs(dy);
          float distance = sqrt(distx + disty);
          if (distance < range)
          {
            towns[i].addNeighbour(j);
          }
        }
      }
    }

    cout<<"*********************** Begin SDL OpenGL ***********************"<<endl;

    cout<<"-------- Using OpenGL 3.0 core "<<endl;
    // Use OpenGL 3.1 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // set states
    isRunning = true;

    // initialise SDL Video out
    cout<<"-------- Initialise SDL"<<endl;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        cout<<"Unable to initialise SDL: "<<SDL_GetError()<<endl;
        exit(1);
    }

    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_OPENGL, &displayWindow, &displayRenderer);

    SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
    // Check that we have OpenGL
    if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 ||
        (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
        /*TODO: Handle this. We have no render surface and not accelerated. */
    }

    // Sets title bar
    SDL_SetWindowTitle(displayWindow, "OpenGL OOP Integration");

    // init the OpenGl window
    initOpenGL();

    // setup viewport
    setViewport(800, 800);


    // --------------------- SIMULATION BLOCK
    cout<<"------- SIMULATION BLOCK STARTED"<<endl;
    // Simulation main loop is defined here
    // note that without using GLUT, we are now able to control
    // everything which runs within the loop using our own implementation

    int frameRate = 1000 / 60;
    Uint32 timeStart = SDL_GetTicks();

    while (isRunning) {
        checkKeyPress();

        // The while loop runs too quickly on most systems which can hang
        // most machines. The code below keeps the update consistent
        // increase the frameRate above to slow down the simulation
        if (SDL_GetTicks() >= timeStart + frameRate)
        {
          timeStart = SDL_GetTicks();
          //cout<<"timestart:"<<timeStart<<endl;

          // ------------------ START ALL UPDATES AND RENDERING HERE

          // gradually change the background color to white
          glClearColor(r, g, b, 1.0f);

          // render the scene
          renderScene();

          // call Army's functions
          thisarmy.update();
          thisarmy.render();

          for (int i = 0; i < townsize; i++)
          {
            towns[i].update();
            towns[i].render(towns);
          }

          // Update window with OpenGL rendering
          SDL_GL_SwapWindow(displayWindow);

          // ------------------ END ALL UPDATES AND RENDERING HERE

        }
    }

    cout<<"------- SIMULATION BLOCK ENDED"<<endl;

    // clear the screen to default
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    cout<<"------- Cleaning Up Memory"<<endl;

    // Destroy window
    SDL_DestroyWindow(displayWindow);
    displayRenderer = NULL;
    displayWindow = NULL;
    cout<<"------- Objects in Memory Destroyed"<<endl;

    SDL_Quit();

   return 0;
}

void checkKeyPress()
{
  // SDL events polling here
  while(SDL_PollEvent(&event) != 0)
  {
      // Close the window X
      if(event.type == SDL_QUIT) isRunning = false;

      // ** we have removed all controls for the Army now
      if ( event.type == SDL_KEYDOWN )
      {
        // if escape key is pressed
        if ( event.key.keysym.sym == SDLK_ESCAPE ) isRunning = false;

        // --------------------------- KEYDOWN HANDLER
        if ( event.key.keysym.sym == SDLK_RIGHT )
        {
          // creature->rotateRight(0.9f);
        }

        if ( event.key.keysym.sym == SDLK_LEFT )
        {
          // creature->rotateLeft(0.9f);
        }

        if ( event.key.keysym.sym == SDLK_UP )
        {
          // creature->moveForward(0.01f);
        }

        if ( event.key.keysym.sym == SDLK_DOWN )
        {
          // creature->moveBackward(0.01f);
        }
      }

      // --------------------------- KEYUP HANDLER
      if (event.type == SDL_KEYUP)
      {
        // if ( event.key.keysym.sym == SDLK_UP ) creature->stopForward();
        // if ( event.key.keysym.sym == SDLK_DOWN ) creature->stopBackward();
      }
  }
}

// A general OpenGL initialization function that sets all initial parameters
void initOpenGL()
{
  cout<<"-------- Initialise OpenGL"<<endl;
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   // This Will Clear The Background Color To Black
  glClearDepth(1.0);                      // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LEQUAL);                   // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);                // Enables Depth Testing
  glShadeModel(GL_SMOOTH);                // Enables Smooth Color Shading
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ); // Nicest perspective calculations
}

// Reset our viewport after a window resize
int setViewport( int width, int height )
{
    cout<<"-------- Setting OpenGL Viewport"<<endl;
    GLfloat ratio;

    // prevent divide by zero
    if ( height == 0 ) { height = 1; }

    // calculate ratio
    ratio = ( GLfloat )width / ( GLfloat )height;

    // Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    // specify which matrix is the current matrix
    // GL_PROJECTION means that we are applying all matrix to the PROJECTION MATRIX
    glMatrixMode(GL_PROJECTION);

    // Reset The Projection Matrix, generally done before we do anything to the matrix
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    // gluPerspective(	GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // use glu function to set a camera looking at
    // void gluLookAt(	GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
   	//                  GLdouble centerX, GLdouble centerY, GLdouble centerZ,
   	//                  GLdouble upX, GLdouble upY, GLdouble upZ);
    // the units below essentially looks down on a map view
    // putting the eye 80 units above the origin
    // looking at target at -10 units below the origin (looking down)
    // up vector is Z
    gluLookAt(0.0f, 0.0f, 80.0f, 0.0f, -0.01f, -10.0f, 0.0f, 0.0f, 1.0f);

    // now switch to the MODELVIEW MATRIX so that we can control (transform)
    // everything we draw (rectangles, etc.)
    glMatrixMode(GL_MODELVIEW);

    /* Reset The View */
    glLoadIdentity( );

    return 1;
}

void renderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen | depth buffer
  glLoadIdentity();                                   // Reset the matrix

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}
