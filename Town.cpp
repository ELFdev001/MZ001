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
  vPos.x = 0.0f;
	vPos.y = 0.0f;
	vPos.z = 0.0f;
  food = 0;
  name = "";
}

Town::Town(int _id, float origX, float origY, float origZ, string tname): Object(_id)
{
  // setting position
	vPos.x = origX;
	vPos.y = origY;
	vPos.z = origZ;
  food = 0;
  name = tname;
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
}

void Town::update()
{
	autonomy();
}

void Town::autonomy()
{

}

Vector3f Town::getPosition()
{
	return Vector3f(vPos.x, vPos.y, vPos.z);
}

void Town::DrawObject(float red, float green, float blue)
{
	glColor3f(red, green, blue);

	glLineWidth(3.0f);
	glBegin(GL_POLYGON);
		glVertex3f(vPos.x + 0.5f, vPos.y + 0.5f, vPos.z + 0.0f);
		glVertex3f(vPos.x + -0.5f, vPos.y + 0.5f, vPos.z + 0.0f);
		glVertex3f(vPos.x + -0.5f, vPos.y + -0.5f, vPos.z + 0.0f);
    glVertex3f(vPos.x + 0.5f, vPos.y + -0.5f, vPos.z + 0.0f);
	glEnd();
	glLineWidth(0.2f);
}

void Town::DrawName(float red, float green, float blue, string *namestr)
{
  int xadj = 1;
  int yadj = 2;
  glColor3f(red, green, blue);
  glRasterPos2i(vPos.x + xadj, vPos.y + yadj);
  glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*) namestr->c_str());
}
