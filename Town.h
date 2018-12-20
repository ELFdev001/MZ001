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
#include <GL/freeglut.h>
#include <vector>

/****************************** PROTOTYPES ******************************/
class Town: public Object
{
protected:
	int x;
	int y;
  int food;   // amount of food stored in Town
	string name; // name of Town
	std::vector<int> neighbours;

public:
  // ------------------- constructors destructors
  Town();
  Town(int _id, float origX, float origY, string tname);
  ~Town();

  // ------------------- update functions
  void render(vector<Town> towndata);
  void update();

  // ------------------- Town functions
	void addNeighbour(int neigh);
	vector<int> getNeighbours();
	void printtown();

  // ------------------- movement functions
  int getX();
	int getY();

  // ------------------- visual representation function
  void DrawObject(float red, float green, float blue);
	void DrawName(float red, float green, float blue, string *namestr);
	void DrawLinks(float red, float green, float blue, vector<Town> towndata);

};

#endif
