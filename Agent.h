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

#ifndef AGENT_H
#define AGENT_H

#include "OGLUtil.h"
#include "Object.h"

/****************************** PROTOTYPES ******************************/
class Agent: public Object
{
protected:
	Vector3f 	vPos;    // position of the object

public:
  // ------------------- constructors destructors
  Agent();
  Agent(int _id, float origX, float origY, float origZ, float speed);
  ~Agent();

  // ------------------- update functions
  void render();
  void update();

  // ------------------- agent functions
  void autonomy();

  // ------------------- movement functions
  Vector3f getPosition();

  // ------------------- visual representation function
  void DrawObject(float red, float green, float blue);
};

#endif
