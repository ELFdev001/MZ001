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

Town::Town(): Object(-1)
{
  vPos.x = 0.0f;
	vPos.y = 0.0f;
	vPos.z = 0.0f;
  food = 0;
}

Town::Town(int _id, float origX, float origY, float origZ): Object(_id)
{
  // setting position
	vPos.x = origX;
	vPos.y = origY;
	vPos.z = origZ;
  food = 0;
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
		glVertex3f(0.5f, 0.0f, 0.5f);
		glVertex3f(-0.5f, 0.0f, 0.5f);
		glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
	glEnd();
	glLineWidth(0.2f);
}
