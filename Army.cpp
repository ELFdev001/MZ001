//	##########################################################
//	By Philip Murgatroyd, building on an infrastructure created by
//  Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//
//  The Army class prototype derives from Object
//  Prototype details are decoupled in Army.h
//  Decoupling codes make it very easy to manage programmatically
//	##########################################################

#include "OGLUtil.h"
#include "Army.h"

Army::Army(): Object(-1)
{
  vPos.x = 0.0f;
	vPos.y = 0.0f;
	vPos.z = 0.0f;
  food = 0;
}

Army::Army(int _id, float origX, float origY, float origZ): Object(_id)
{
  // setting position
	vPos.x = origX;
	vPos.y = origY;
	vPos.z = origZ;
  food = 0;
}

Army::~Army()
{
  cout<<"Army destroyed!"<<endl;
}

void Army::render()
{
	// ** glIdentity must be called here so that
	// the matrix transform is reset to identity matrix made to this Army
	// so that it doesn't affect all other Armies later
	// try removing this and see
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	DrawObject(1.0f, 0.0f, 0.0f);
}

void Army::update()
{
	autonomy();
}

void Army::autonomy()
{

}

Vector3f Army::getPosition()
{
	return Vector3f(vPos.x, vPos.y, vPos.z);
}

void Army::DrawObject(float red, float green, float blue)
{
	glColor3f(red, green, blue);

	glLineWidth(3.0f);
	glBegin(GL_POLYGON);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();
	glLineWidth(0.2f);
}
