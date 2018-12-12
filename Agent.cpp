//	##########################################################
//	By Philip Murgatroyd, building on an infrastructure created by
//  Eugene Ch'ng | www.complexity.io | 2018
//	Email: genechng@gmail.com
//	----------------------------------------------------------
//
//  The Agent class prototype derives from Object
//  Prototype details are decoupled in Agent.h
//  Decoupling codes make it very easy to manage programmatically
//	##########################################################

#include "OGLUtil.h"
#include "Agent.h"

Agent::Agent(): Object(-1)
{
	vPos.x = 0.0f;
	vPos.y = 0.0f;
	vPos.z = 0.0f;
}

Agent::Agent(int _id, float origX, float origY, float origZ, float speed): Object(_id)
{
  // setting standard movement, rotation speed
	vPos.x = origX;
	vPos.y = origY;
	vPos.z = origZ;
}

Agent::~Agent()
{
  cout<<"Agent destroyed!"<<endl;
}

void Agent::render()
{
	// ** glIdentity must be called here so that
	// the matrix transform is reset to identity matrix made to this agent
	// so that it doesn't affect all other agents later
	// try removing this and see
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		DrawObject(1.0f, 1.0f, 1.0f);
}

void Agent::update()
{
	autonomy();
}

void Agent::autonomy()
{

}

Vector3f Agent::getPosition()
{
	return Vector3f(vPos.x, vPos.y, vPos.z);
}

void Agent::DrawObject(float red, float green, float blue)
{
	glColor3f(red, green, blue);

	glLineWidth(3.0f);
	glBegin(GL_TRIANGLES);				// draw the triangle
		// right
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		// left
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		// back
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		// under
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
	glEnd();
	glLineWidth(0.2f);
}
