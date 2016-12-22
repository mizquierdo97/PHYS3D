#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

struct Points {
	Sphere* coin;
	PhysBody3D* sensor;
	bool active;

};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateMap();

	void AddWall(int x, int z, btScalar width, float rot);
	void AddGround(int x, int z, int width, int height,int angle, Color color = Black);
	void AddCoin(int x, int y, int z);

	void Walls();
	void Coin();
	void Ramps();
	void Ground();

	void Render();
	void Restart();

public:



	Cube* cons_1;
	Cube* cons_2;
	Cube* cons_3;

	PhysBody3D* b_cons_1;
	PhysBody3D* b_cons_2;
	PhysBody3D* b_cons_3;
	
	Cube* pivot_1;
	Cube* pivot_2;
	Cube* pivot_3;

	PhysBody3D* b_pivot_1;
	PhysBody3D* b_pivot_2;
	PhysBody3D* b_pivot_3;

	PhysBody3D* bb_sensor;
	PhysBody3D* bb_wall;

	p2DynArray<Cube> walls_vector;
	p2DynArray<Points> Coins;
	p2DynArray<Cube> ground_vector;
	PhysBody3D* b_sphere;
	Sphere* Big_Sphere;

	PhysBody3D* final_sensor;

	PhysBody3D* slow_sensor1;
	Cube* slow1;
	PhysBody3D* slow_sensor2;
	Cube* slow2;
	PhysBody3D* slow_sensor3;
	Cube* slow3;
	
};
