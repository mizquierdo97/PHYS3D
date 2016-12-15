#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

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


	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);
	
	plane.SetPos(0, -1, 0);
	plane.Scale(1000, 1, 1000);
	plane.color = MyColor2;

	App->physics->AddBody(plane,0.f);
	
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
	//p.axis = true;
	s.Render();
	plane.Render();
	btVector3 offset(0,0,0);
	offset = offset.rotate(btVector3({1,0,0}),30);


	Render();
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

	//START BACK WALL
	AddWall(0, 2, -20, 12, 0);


	AddWall(10, 2, 30, 50, 1);	
	AddWall(5, 2, 87, 10, -2);
	AddWall(-86, 2, 93, 90, 0);
	AddWall(-181, 2, 101, 10, -2);
	AddWall(-191, 2, 85, 10, -1.7);
	AddWall(-196, 2, 79, 10, 0.2);
	AddWall(-225, 2, 59, 50, 0);
	AddWall(-284, 2, 55, 10, -0.2);
	AddWall(-309, 2, 35, 25, -0.4);

	AddWall(-255, 2, 83, 50, 0);
	AddWall(-316, 2, 78, 13, -0.2);
	AddWall(-337, 2, 61, 19, -0.5);


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
		
	AddWall(-210, 2, 135, 15, -2);
	AddWall(-240, 2, 148, 30, 0.1);
	AddWall(-297, 2, 153, 30, 0);
	AddWall(-334, 2, 143, 15, 2);
	AddWall(-354, 2, 99, 43, 1.4);
	AddWall(-367, 2, 45, 20, 1);

	AddWall(-348, 2, 45,10, 1);

	AddWall(-363, 2, 20, 20, 0.8);
	AddWall(-327, 2, 13, 5, -1);
	AddWall(-325, 2, 4, 5, 0.7);
	AddWall(-351, 2, -8, 15, -2.2);

	AddWall(-341, 2, -43, 25, 1);
	AddWall(-304, 2, -1, 20, 0);

	AddWall(-276, 2, 20, 16, 1);
	AddWall(-280, 2, 2, 5, 3.4);

	AddWall(-256, 2, 20, 16, 1);
	AddWall(-256, 2, -20, 25, 1);
	AddWall(-253, 2, -48, 5, -2);
	AddWall(-218, 2, -52, 32, 0);
	AddWall(-218, 2, -67, 32, 0);
	AddWall(-186, 2, -60, 11, 1);
	AddWall(-253, 2, -71, 5, 2);
	AddWall(-285, 2, -75, 30, 0);

	AddWall(-317, 2, -79, 5, 2);
	AddWall(-341, 2, -82, 16, 1);
	AddWall(-320, 2, -90, 8, 1);

	// ROTONDA
	AddWall(-278, 2, -40, 15, 1);
	AddWall(-318, 2, -40, 15, 1);

	AddWall(-281, 2, -22, 5, -2);
	AddWall(-315, 2, -22, 5, 2);

	AddWall(-281, 2, -58, 5, 2);
	AddWall(-315, 2, -58, 5, -2);

	AddWall(-298, 2, -18, 15, 0);
	AddWall(-298, 2, -62, 15, 0);
	// END ROTONDA

	//FIXING i & k

	AddWall(-325, 2, -150, 38, -1.5);
	AddWall(-305, 2, -150, 38, -1.5);



	// -----------------------------//
	
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




void ModuleSceneIntro::AddWall(int x, int y, int z, btScalar width, float rotation) {

	

	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);


	btCollisionShape* wall = new btBoxShape(btVector3({ width,3,0.5 }));
	wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, rotation, 0, 1), btVector3(x, 3, z)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, wall, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	App->physics->world->addRigidBody(fallRigidBody);
	/*
	Cube Wall;
	Wall.size = vec3(width, 3,0.51);
	Wall.SetPos(x, y, z);

	walls_vector.PushBack(Wall);
	*/
	
	Cube r_wall(width*2, 6, 1);
	fallRigidBody->getWorldTransform().getOpenGLMatrix(&r_wall.transform);
	btQuaternion q = fallRigidBody->getWorldTransform().getRotation();
	r_wall.color = MyColor;
	walls_vector.PushBack(r_wall);
	
}

void ModuleSceneIntro::Render() {

	auto temp = walls_vector[0];
	for (int i = 0; i < walls_vector.Count(); i++) {
		walls_vector[i].Render();
	}
}
