//	##########################################################
//	By Philip Murgatroyd, building on an infrastructure created by
//  Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//
//  The Town class prototype derives from Object
//  Prototype details are decoupled in Town.h
//  Decoupling codes make it very easy to manage programmatically
//	##########################################################

#include "OGLUtil.h"
#include "Town.h"
#include <GL/freeglut.h>

Town::Town(): Object(-1)
{
  x = 0.0f;
	y = 0.0f;
  food = 0;
  name = "";
  range = 25;
}

Town::Town(int _id, float origX, float origY, string tname): Object(_id)
{
  // setting position
	x = origX;
	y = origY;
	food = 0;
  name = tname;
  *neighbours[5];
  neighcount = 0;
  range = 25;
}

Town::~Town()
{
  cout<<"Town destroyed!"<<endl;
}

void Town::render()
{
	// ** glIdentity must be called here so that
	// the matrix transform is reset to identity matrix made to this Town
	// so that it doesn't affect all other Armies later
	// try removing this and see
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	DrawObject(0.0f, 0.0f, 0.0f);
  DrawName(1.0f, 1.0f, 1.0f, &name);
  DrawLinks(1.0f, 1.0f, 1.0f);
}

void Town::update()
{

}

void Town::setupneigh(Town alltowns[], int size)
{
  for (int i = 0; i < size; i++)
  {
    if (Town::getDistance(&alltowns[i]) < range)
    {
      if (alltowns[i].getX() != x && alltowns[i].getY() != y) {
        neighbours[neighcount] = &alltowns[i];
        neighcount++;
      }
    }
  }
}

int Town::getX()
{
  return x;
}

int Town::getY()
{
  return y;
}

float Town::getDistance(Town *fartown)
{
  float distx = (fartown->getX() - x) ^2;
  float disty = (fartown->getY() - y) ^2;
  float distance = sqrt(distx - disty);
  return distance;
}

void Town::DrawObject(float red, float green, float blue)
{
	glColor3f(red, green, blue);

	glLineWidth(3.0f);
	glBegin(GL_POLYGON);
		glVertex3f(x + 0.5f, y + 0.5f, 0.0f);
		glVertex3f(x + -0.5f, y + 0.5f, 0.0f);
		glVertex3f(x + -0.5f, y + -0.5f, 0.0f);
    glVertex3f(x + 0.5f, y + -0.5f, 0.0f);
	glEnd();
	glLineWidth(0.2f);
}

void Town::DrawLinks(float red, float green, float blue)
{
  glColor3f(red, green, blue);

  glLineWidth(3.0f);

  for (int i = 0; i < neighcount; i++)
  {
    glBegin(GL_LINES);
      glVertex3f(x, y, 0.0f);
      glVertex3f(neighbours[i]->getX(), neighbours[i]->getY(), 0.0f);
    glEnd();
  }

  glLineWidth(0.2f);
}

void Town::DrawName(float red, float green, float blue, string *namestr)
{
  int xadj = 1;
  int yadj = 2;
  glColor3f(red, green, blue);
  glRasterPos2i(x + xadj, y + yadj);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) namestr->c_str());
}
