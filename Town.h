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

#ifndef TOWN_H
#define TOWN_H

#include "OGLUtil.h"
#include "Object.h"

/****************************** PROTOTYPES ******************************/
class Town: public Object
{
protected:
	Vector3f 	vPos;    // position of the object
  int food;   // amount of food stored in Town
	string name; // name of Town

public:
  // ------------------- constructors destructors
  Town();
  Town(int _id, float origX, float origY, float origZ, string tname);
  ~Town();

  // ------------------- update functions
  void render();
  void update();

  // ------------------- Town functions
  void autonomy();

  // ------------------- movement functions
  Vector3f getPosition();

  // ------------------- visual representation function
  void DrawObject(float red, float green, float blue);
	void DrawName(float red, float green, float blue);
};

#endif
