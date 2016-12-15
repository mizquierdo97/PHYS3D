
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"


void ModuleSceneIntro::Walls() {

	//BACK FIRST WALL
	
	// --------
	int i = -90;
	int k = -160;
	
	AddWall(-220 + i, 2, -60 + k, 10, 1);
	AddWall(-200 + i, 2, -60 + k, 10, 1);

	AddWall(-256 + i, 2, -118 + k, 60, 2);
	AddWall(-242 + i, 2, -135 + k, 55, 2);

	AddWall(-185 + i, 2, -90 + k, 25, -2);
	AddWall(-194 + i, 2, -110 + k, 25, -2);
	AddWall(-154 + i, 2, -130 + k, 25, 0);
	AddWall(-150 + i, 2, -110 + k, 20, 0);

	AddWall(-121 + i, 2, -142 + k, 15, -2);
	AddWall(-121 + i, 2, -98 + k, 15, 2);
	AddWall(-72 + i, 2, -86 + k, 40, 0);
	AddWall(-72 + i, 2, -154 + k, 40, 0);
	AddWall(-23 + i, 2, -98 + k, 15, -2);
	AddWall(-23 + i, 2, -142 + k, 15, 2);

	AddWall(-110 + i, 2, -129 + k, 12, -2);
	AddWall(-110 + i, 2, -110 + k, 12, 2);
	AddWall(-72 + i, 2, -101 + k, 30, 0);
	AddWall(-72 + i, 2, -139 + k, 30, 0);
	AddWall(-35 + i, 2, -129 + k, 12, 2);
	AddWall(-35 + i, 2, -110 + k, 12, -2);
	AddWall(0 + i, 2, -130 + k, 14, 0);
	AddWall(0 + i, 2, -110 + k, 14, 0);

	AddWall(17 + i, 2, -134 + k, 5, -2);
	AddWall(17 + i, 2, -106 + k, 5, 2);
	AddWall(50 + i, 2, -138 + k, 30, 0);
	AddWall(50 + i, 2, -102 + k, 30, 0);
	AddWall(84 + i, 2, -134 + k, 51, 2);
	AddWall(84 + i, 2, -106 + k, 5, -2);
	AddWall(93 + i, 2, -101 + k, 10, 2);

	//--------------------------//

	AddWall(99 + i, 2, -74 + k, 20, 1);
	AddWall(78 + i, 2, -26 + k, 35, -2);
	AddWall(92 + i, 2, -18 + k, 25, -2);

			//DCH
	AddWall(60 + i, 2, 15 + k, 30, 1);
	AddWall(77 + i, 2, 23 + k, 22, 1);
	AddWall(92 + i, 2, 93 + k, 35, 2);  // PARED RARA BOLA RODANTE
	AddWall(104 + i, 2, 80 + k, 45, 2);
	AddWall(113 + i, 2, 132 + k, 12, 1);
	AddWall(140 + i, 2, 134 + k, 10, 1);


			//IZQ
	AddWall(115 + i, 2, -74 + k, 20, 1);
	AddWall(124 + i, 2, -42 + k, 15, 2);
	AddWall(113 + i, 2, -30 + k, 10, 2);
	AddWall(119 + i, 2, -2 + k, 20, 1);
	AddWall(133 + i, 2, -10 + k, 20, 1);

	AddWall(139 + i, 2, 18 + k, 10, 2);
	AddWall(131 + i, 2, 34 + k, 24, 2);
	AddWall(158 + i, 2, 34 + k, 24, -2);
	AddWall(151 + i, 2, 18 + k, 10, -2);
	AddWall(172 + i, 2, 0 + k, 20, 1);
	AddWall(157 + i, 2, -10 + k, 20, 1);

	AddWall(165 + i, 2, -35 + k, 30, -2);
	AddWall(178 + i, 2, -27 + k, 10, -2);
	AddWall(184 + i, 2, 5 + k, 40, 1);
	AddWall(157 + i, 2, 80 + k, 45, -2);
	AddWall(190 + i, 2, -45 + k, 20, 2);
	AddWall(200 + i, 2, 5 + k, 40, 1);
	AddWall(173 + i, 2, 80 + k, 55, -2);

	//--------------------------//

			//END
	AddWall(113 + i, 2, 210 + k, 40, 1);
	AddWall(140 + i, 2, 210 + k, 40, 1);


}