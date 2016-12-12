
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"


void ModuleSceneIntro::Walls() {

	AddWall(-220, 2, -60, 10, 1);
	AddWall(-200, 2, -60, 10, 1);

	AddWall(-256, 2, -118, 60, 2);
	AddWall(-242, 2, -135, 55, 2);

	AddWall(-185, 2, -90, 25, -2);
	AddWall(-194, 2, -110, 25, -2);
	AddWall(-154, 2, -130, 25, 0);
	AddWall(-150, 2, -110, 20, 0);

	AddWall(-121, 2, -142, 15, -2);
	AddWall(-121, 2, -98, 15, 2);
	AddWall(-72, 2, -86, 40, 0);
	AddWall(-72, 2, -154, 40, 0);
	AddWall(-23, 2, -98, 15, -2);
	AddWall(-23, 2, -142, 15, 2);

	AddWall(-110, 2, -129, 12, -2);
	AddWall(-110, 2, -110, 12, 2);
	AddWall(-72, 2, -101, 30, 0);
	AddWall(-72, 2, -139, 30, 0);
	AddWall(-35, 2, -129, 12, 2);
	AddWall(-35, 2, -110, 12, -2);
	AddWall(0, 2, -130, 14, 0);
	AddWall(0, 2, -110, 14, 0);

	AddWall(17, 2, -134, 5, -2);
	AddWall(17, 2, -106, 5, 2);
	AddWall(50, 2, -138, 30, 0);
	AddWall(50, 2, -102, 30, 0);
	AddWall(84, 2, -134, 51, 2);
	AddWall(84, 2, -106, 5, -2);
	AddWall(93, 2, -101, 10, 2);

	AddWall(99, 2, -83, 10, 1);
	AddWall(115, 2, -83, 10, 1);

}