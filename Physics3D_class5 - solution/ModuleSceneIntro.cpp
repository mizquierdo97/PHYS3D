#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 200.0f, -100.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.SetPos(5,5,5);
	
	App->physics->AddBody(s);


	
	CreateMap();

	
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	btVector3 offset(0,0,0);
	offset = offset.rotate(btVector3({1,0,0}),30);



	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}



void ModuleSceneIntro::CreateMap() {

	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);

	// -- RAMPA --

	btCollisionShape* wall = new btBoxShape(btVector3({ 20,3,0.5 }));
	wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, 1), btVector3(15, 0, 48)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, wall, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	App->physics->world->addRigidBody(fallRigidBody);

	/*
	//btCollisionShape* wall2 = new btBoxShape(btVector3({ 20,3,0.5 }));
	//wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState2 =
		new btDefaultMotionState(btTransform(btQuaternion(0, 1, 0, 1), btVector3(-15, 2, 48)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass, fallMotionState2, wall, fallInertia);
	btRigidBody* fallRigidBody2 = new btRigidBody(fallRigidBodyCI2);
	App->physics->world->addRigidBody(fallRigidBody2);
	*/

	

	AddWall(10, 2, 30, 50, 1);	
	AddWall(5, 2, 87, 10, -2);
	AddWall(-86, 2, 93, 90, 0);
	AddWall(-181, 2, 101, 10, -2);
	AddWall(-191, 2, 85, 10, -1.7);
	AddWall(-196, 2, 79, 10, 0.2);
	AddWall(-225, 2, 59, 50, 0);
	AddWall(-284, 2, 55, 10, -0.2);
	AddWall(-300, 2, 44, 10, -0.4);

	AddWall(-255, 2, 83, 50, 0);
	AddWall(-316, 2, 78, 13, -0.2);
	AddWall(-336, 2, 65, 17, -0.4);


	// -----------------------------//
	//CURVA RARA
	AddWall(-226, 2, 115, 13, 0.3);
	AddWall(-243, 2, 122, 7, 0);
	AddWall(-254, 2, 117, 7, 2);
	AddWall(-258, 2, 105, 7, 1);
	//END CURVA RARA

	AddWall(-277, 2, 105, 7, 1);
	AddWall(-286, 2, 123, 15, -2);
	AddWall(-308, 2, 135, 13, 0);
	AddWall(-334, 2, 95, 43, 1.4);

	// -----------------------------//

	
	AddWall(-200, 2, 145, 13, 0.7);
	
	AddWall(-45, 2, 40, 25, 1);
	AddWall(-51, 2, 8, 10, 2);
	AddWall(-62, 2, 8, 10, -2);
	AddWall(-68, 2, 40, 25, 1);
	AddWall(-57, 2, 65, 12, 0);
	
	int i = 85;
	AddWall(-45 - i, 2, 40, 25, 1);
	AddWall(-51 - i, 2, 8, 10, 2);
	AddWall(-62 - i, 2, 8, 10, -2);
	AddWall(-68 - i, 2, 40, 25, 1);
	AddWall(-57 - i, 2, 65, 12, 0);


	AddWall(-10, 2, 20, 40, 1);
	AddWall(-15, 2, 64, 7, -2);
	AddWall(-23, 2, 64, 7, 2);
	AddWall(-27, 2, 29, 30, 1);
	AddWall(-33, 2, -9, 10, 2);
	AddWall(-60, 2, -17, 20, 0);
	AddWall(-87, 2, -9, 10, -2);
	AddWall(-93, 2, 29, 30, 1);

	i = 82;
	AddWall(-15 - i, 2, 64, 7, -2);
	AddWall(-23 - i, 2, 64, 7, 2);
	AddWall(-27 -i, 2, 29, 30, 1);
	AddWall(-33 - i, 2, -9, 10, 2);
	AddWall(-60 - i, 2, -17, 20, 0);
	AddWall(-87 - i, 2, -9, 10, -2);
	AddWall(-93 - i, 2, 29, 30, 1);

	///Obstacles
	AddWall(-20, 2, 86, 7, 1);
	AddWall(-60, 2, 72, 7, 1);
	AddWall(-80, 2, 86, 7, 1);
	AddWall(-101, 2, 74, 5, 1);
	AddWall(-140, 2, 86, 7, 1);

	
	
	
	

	


	//////
	Walls();
	
}


void ModuleSceneIntro::AddWall(int x,int y ,int z ,btScalar width, float rotation) {
	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);


	btCollisionShape* wall = new btBoxShape(btVector3({ width,3,0.5 }));
	wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, rotation, 0, 1), btVector3(x, y, z)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, wall, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	App->physics->world->addRigidBody(fallRigidBody);


}

void ModuleSceneIntro::AddWallP(int x_first, int y_first,int x_second,int y_second, float rotation)
{
	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);

	float l_x = x_second - x_first;
	float l_y = y_second - y_first;
	float length = sqrt(l_x*l_x + l_y*l_y)/2;

	p2Point<float> pos;
	pos.x = (x_first + l_x)/2;
	pos.y = (y_first+ l_y)/2;

	btCollisionShape* wall = new btBoxShape(btVector3({ length,3,0.5 }));
	wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, rotation, 0, 1), btVector3(pos.x, 0, pos.y)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, wall, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	App->physics->world->addRigidBody(fallRigidBody);


}
