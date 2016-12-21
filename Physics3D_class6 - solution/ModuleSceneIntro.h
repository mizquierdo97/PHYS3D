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
	void AddGround(int x, int z, int width, int height,int angle);
	void AddCoin(int x, int y, int z);

	void Walls();

	void Render();
	void Restart();

public:

	btHingeConstraint* hinge;
	Cube* door;
	PhysBody3D* b_door;
	Cube* pivot;
	PhysBody3D* b_pivot;

	Cube plane;
	p2DynArray<Cube> walls_vector;
	p2DynArray<Points> Coins;
	p2DynArray<Cube> ground_vector;
	PhysBody3D* b_sphere;
	Sphere* Big_Sphere;
};
