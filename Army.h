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

#ifndef ARMY_H
#define ARMY_H

#include "OGLUtil.h"
#include "Object.h"

/****************************** PROTOTYPES ******************************/
class Army: public Object
{
protected:
	Vector3f 	vPos;    // position of the object

public:
  // ------------------- constructors destructors
  Army();
  Army(int _id, float origX, float origY, float origZ);
  ~Army();

  // ------------------- update functions
  void render();
  void update();

  // ------------------- Army functions
  void autonomy();

  // ------------------- movement functions
  Vector3f getPosition();

  // ------------------- visual representation function
  void DrawObject(float red, float green, float blue);
};

#endif
