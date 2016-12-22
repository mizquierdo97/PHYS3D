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
	App->audio->Init();
	App->audio->PlayMusic("Music.ogg");
	App->audio->LoadFx("Colision2.wav");
	App->audio->LoadFx("Coin.wav");
	App->camera->Move(vec3(1.0f, 200.0f, -100.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//Big Sphere
	Big_Sphere = new Sphere(10);
	Big_Sphere->SetPos(-23.5, 60, -70);

	b_sphere = App->physics->AddBody(*Big_Sphere, 1000.f);
	b_sphere->collision_listeners.add(this);
	b_sphere->body->setGravity({ 0,0,0 });

	Cube* bb_cube = new Cube(30, 10, 1);
	bb_sensor = App->physics->AddBody(*bb_cube, 0.f);
	bb_sensor->SetPos(20, 10, -220);

	bb_sensor->SetAsSensor(true);
	bb_sensor->collision_listeners.add(this);

	bb_wall = App->physics->AddBody(*bb_cube, 0.f);
	bb_wall->SetPos(-15, 40, -80);

	//Constrains
	cons_1 = new Cube(0.5, 10, 10);
	cons_1->SetPos(-25, 14, -270);
	b_cons_1 = App->physics->AddBody(*cons_1, 1.f);
	
	pivot_1 = new Cube(1, 1, 1);
	pivot_1->SetPos(-25, 18, -270);
	b_pivot_1 = App->physics->AddBody(*pivot_1, 0.f);

	cons_2 = new Cube(0.5, 10, 10);
	cons_2->SetPos(-45, 14, -290);
	b_cons_2 = App->physics->AddBody(*cons_2, 1.f);

	pivot_2 = new Cube(1, 1, 1);
	pivot_2->SetPos(-45, 18, -290);
	b_pivot_2 = App->physics->AddBody(*pivot_2, 0.f);

	cons_3 = new Cube(0.5, 10, 10);
	cons_3->SetPos(-65, 14, -270);
	b_cons_3 = App->physics->AddBody(*cons_3, 1.f);

	pivot_3 = new Cube(1, 1, 1);
	pivot_3->SetPos(-65, 18, -270);
	b_pivot_3 = App->physics->AddBody(*pivot_3, 0.f);
	
	App->physics->AddConstraintHinge( *b_pivot_1, *b_cons_1, {0,0,0 }, { 0,5,0 }, { 0,0,1 }, { 0,0,1 },true);	
	App->physics->AddConstraintHinge(*b_pivot_2, *b_cons_2, { 0,0,0 }, { 0,5,0 }, { 0,0,1 }, { 0,0,1 }, true);
	App->physics->AddConstraintHinge(*b_pivot_3, *b_cons_3, { 0,0,0 }, { 0,5,0 }, { 0,0,1 }, { 0,0,1 }, true);

	////


	
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
	
	
	for (int i = 0; i < Coins.Count(); i++) {
		if (Coins[i].active == true) {
			Coins[i].coin->Render();
		}
		
	}

	b_sphere->body->applyCentralForce({ 0,0,-100 });
	//Constrains
	b_cons_1->body->applyForce({ 0,0,100 }, {0, 20, 0});
	b_cons_2->body->applyForce({ 0,-100,0 }, { 0, 20, 0 });
	b_cons_3->body->applyForce({ 0,-100,0 }, { 0, 20, 0 });

	mat4x4 m;

	b_cons_1->GetTransform(&m);
	cons_1->transform = m;
	cons_1->Render();
	b_cons_2->GetTransform(&m);
	cons_2->transform = m;
	cons_2->Render();
	b_cons_3->GetTransform(&m);
	cons_3->transform = m;
	cons_3->Render();
	////



	//Render ground
	for (int i = 0; i < ground_vector.Count(); i++) {
		ground_vector[i].Render();
	}
	

	//Big Sphere
	b_sphere->GetTransform(&m);
	Big_Sphere->transform = m;	
	Big_Sphere->Render();
	
	


	Render();
	return UPDATE_CONTINUE;
}



void ModuleSceneIntro::Render() {

	auto temp = walls_vector[0];
	for (int i = 0; i < walls_vector.Count(); i++) {
		static float R = 0;
		static float c_R = 0;
		static float G = 1.5;
		static float c_G = 2;
		static float B = 4;
		static float c_B = 4;

		R = R + 0.0001f;
		c_R = sin(R);

		G = G + 0.0001f;
		c_G = sin(G);

		B = B + 0.0001f;
		c_B = sin(B);


		Color MyWallColor = Color(c_R, c_G, c_B, 1.f);
		walls_vector[i].color = MyWallColor;
		walls_vector[i].Render();

	}
}

void ModuleSceneIntro::Restart()
{
	for (int i = 0; i < Coins.Count(); i++) {
		mat4x4 m;
		b_sphere->SetPos(-23.5, 60, -70);
		b_sphere->body->setGravity({ 0, 0, 0 });
		b_sphere->body->setAngularVelocity({ 0,0,0 });
		b_sphere->body->setLinearVelocity({ 0,0,0 });
		App->player->vehicle->body->setAngularVelocity({ 0,0,0 });
		App->player->vehicle->body->setLinearVelocity({ 0,0,0 });
		App->player->vehicle->SetTransform(&App->player->initial_trans);
		App->camera->Move(vec3(0.0f, 20.0f, -20.0f));
		App->player->score = 0;
		
		b_cons_1->body->setLinearVelocity({ 0,0,0 });
		b_cons_1->body->setAngularVelocity({ 0,0,0 });

		b_cons_2->body->setLinearVelocity({ 0,0,0 });
		b_cons_2->body->setAngularVelocity({ 0,0,0 });

		b_cons_3->body->setLinearVelocity({ 0,0,0 });
		b_cons_3->body->setAngularVelocity({ 0,0,0 });
		

		App->player->start_ticks = SDL_GetTicks();
		Coins[i].sensor->GetTransform(&m);
		if (Coins[i].active == false) {
			Coins[i].sensor->SetPos(m[12], m[13] + 20, m[14]);
			Coins[i].active = true;
		}
	}

}


void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	bool is_wall = true;
	
	static int cont = 0;
	if (body1 == App->player->vehicle || body2 == App->player->vehicle) {
		
		
		for (int i = 0; i < Coins.Count(); i++) {
			if (body1 == Coins[i].sensor || body2 == Coins[i].sensor) {

				mat4x4 m;
				Coins[i].sensor->GetTransform(&m);
				Coins[i].sensor->SetPos(m[12], m[13] - 20, m[14]);
				Coins[i].active = false;
				App->player->score += 100;
				App->audio->PlayFx(2);
				is_wall = false;
			}

		}
		if (body1 == bb_sensor || body2 == bb_sensor) {
			bb_wall->SetPos(-50, 40, 80);
			b_sphere->body->activate();
			b_sphere->body->setGravity({ 0,-100,0 });
			
		}
		if (is_wall == true ) {
			if (App->player->vehicle->GetKmh() > 20) {
				App->audio->PlayFx(1);
				is_wall = false;
				
			}
		}
	
	}
	
	if (body1 == b_sphere || body2 == b_sphere) {
		if(body1 == App->player->vehicle || body2 == App->player->vehicle) {
			Restart();
		}
	}

	
	
	
}







void ModuleSceneIntro::CreateMap() {
		
	Walls();
	Ramps();
	Coin();
	Ground();

}



void ModuleSceneIntro::Walls() {


	// ________________________ WALLS________________________//

	//START BACK WALL
	AddWall(0, -20, 12, 0);


	AddWall(10, 30, 50, 1);
	AddWall(5, 87, 10, -2);
	AddWall(-86, 93, 90, 0);

	AddWall(-191, 85, 10, -1.7);
	AddWall(-196, 79, 10, 0.2);
	AddWall(-225, 59, 50, 0);
	AddWall(-284, 55, 10, -0.2);
	AddWall(-309, 35, 25, -0.4);

	AddWall(-255, 83, 50, 0);
	AddWall(-316, 78, 13, -0.2);
	AddWall(-337, 61, 19, -0.5);


	// -----------------------------//
	//CURVA RARA
	AddWall(-226, 115, 13, 0.3);
	AddWall(-243, 122, 7, 0);
	AddWall(-254, 117, 7, 2);
	AddWall(-258, 105, 7, 1);
	//END CURVA RARA

	AddWall(-277, 105, 7, 1);
	AddWall(-286, 123, 15, -2);
	AddWall(-308, 135, 13, 0);
	AddWall(-334, 95, 43, 1.4);

	//AddWall(-210, 135, 15, -2);
	AddWall(-240, 148, 30, 0.1);
	AddWall(-297, 153, 30, 0);
	AddWall(-334, 143, 15, 2);
	AddWall(-354, 99, 43, 1.4);
	AddWall(-367, 45, 20, 1);

	AddWall(-348, 45, 10, 1);

	AddWall(-363, 20, 20, 0.8);
	AddWall(-327, 13, 5, -1);
	AddWall(-325, 4, 5, 0.7);
	AddWall(-351, -8, 15, -2.2);

	AddWall(-341, -43, 25, 1);
	AddWall(-304, -1, 20, 0);

	AddWall(-276, 20, 16, 1);
	AddWall(-280, 2, 5, 3.4);

	AddWall(-256, 20, 16, 1);
	AddWall(-256, -20, 25, 1);
	AddWall(-253, -48, 5, -2);
	AddWall(-218, -52, 32, 0);
	AddWall(-218, -67, 32, 0);
	AddWall(-186, -60, 11, 1);
	AddWall(-253, -71, 5, 2);
	AddWall(-285, -75, 30, 0);

	AddWall(-317, -79, 5, 2);
	AddWall(-341, -82, 16, 1);
	AddWall(-320, -90, 8, 1);

	// ROTONDA
	AddWall(-278, -40, 15, 1);
	AddWall(-318, -40, 15, 1);

	AddWall(-281, -22, 5, -2);
	AddWall(-315, -22, 5, 2);

	AddWall(-281, -58, 5, 2);
	AddWall(-315, -58, 5, -2);

	AddWall(-298, -18, 15, 0);
	AddWall(-298, -62, 15, 0);
	// END ROTONDA

	//FIXING i & k


	////////////////////////////////////////////////////////////                AQUI
	/*AddWall(-310, 2, -175, 38, -1);
	AddWall(-290, 2, -175, 38, -1);*/

	AddWall(-326, -116, 27, -2);
	AddWall(-305, -117, 25, -2);


	// -----------------------------//

	AddWall(-45, 40, 25, 1);
	AddWall(-51, 8, 10, 2);
	AddWall(-62, 8, 10, -2);
	AddWall(-68, 40, 25, 1);
	AddWall(-57, 65, 12, 0);

	int i = 85;
	AddWall(-45 - i, 40, 25, 1);
	AddWall(-51 - i, 8, 10, 2);
	AddWall(-62 - i, 8, 10, -2);
	AddWall(-68 - i, 40, 25, 1);
	AddWall(-57 - i, 65, 12, 0);


	AddWall(-10, 20, 40, 1);
	AddWall(-15, 64, 7, -2);
	AddWall(-23, 64, 7, 2);
	AddWall(-27, 29, 30, 1);
	AddWall(-33, -9, 10, 2);
	AddWall(-60, -17, 20, 0);
	AddWall(-87, -9, 10, -2);
	AddWall(-93, 29, 30, 1);

	i = 82;
	AddWall(-15 - i, 64, 7, -2);
	AddWall(-23 - i, 64, 7, 2);
	AddWall(-27 - i, 29, 30, 1);
	AddWall(-33 - i, -9, 10, 2);
	AddWall(-60 - i, -17, 20, 0);
	AddWall(-87 - i, -9, 10, -2);
	AddWall(-93 - i, 29, 30, 1);

	//ADD

	AddWall(-111 - i, 117, 30, -2);
	AddWall(-123 - i, 100, 13, -2.9);

	///Obstacles
	AddWall(-20, 86, 7, 1);
	AddWall(-60, 72, 7, 1);
	AddWall(-80, 86, 7, 1);
	AddWall(-101, 74, 5, 1);
	AddWall(-140, 86, 7, 1);




	/////


	// --------
	 i = -90;
	int k = -160;
	
	AddWall(-220 + i, -60 + k, 10, 1);
	AddWall(-200 + i, -60 + k, 10, 1);

	AddWall(-256 + i, -118 + k, 60, 2);
	AddWall(-242 + i, -135 + k, 55, 2);

	AddWall(-185 + i, -90 + k, 25, -2);
	AddWall(-194 + i, -110 + k, 25, -2);
	AddWall(-154 + i, -130 + k, 25, 0);
	AddWall(-150 + i, -110 + k, 20, 0);

	AddWall(-121 + i, -142 + k, 15, -2);
	AddWall(-121 + i, -98 + k, 15, 2);
	AddWall(-72 + i, -86 + k, 40, 0);
	AddWall(-72 + i, -154 + k, 40, 0);
	AddWall(-23 + i, -98 + k, 15, -2);
	AddWall(-23 + i, -142 + k, 15, 2);

	AddWall(-110 + i, -129 + k, 12, -2);
	AddWall(-110 + i, -110 + k, 12, 2);
	AddWall(-72 + i, -101 + k, 30, 0);
	AddWall(-72 + i, -139 + k, 30, 0);
	AddWall(-35 + i, -129 + k, 12, 2);
	AddWall(-35 + i, -110 + k, 12, -2);
	AddWall(0 + i, -130 + k, 14, 0);
	AddWall(0 + i, -110 + k, 14, 0);

	AddWall(17 + i, -134 + k, 5, -2);
	AddWall(17 + i, -106 + k, 5, 2);
	AddWall(50 + i, -138 + k, 30, 0);
	AddWall(50 + i, -102 + k, 30, 0);
	AddWall(84 + i, -134 + k, 51, 2);
	AddWall(84 + i, -106 + k, 5, -2);
	AddWall(93 + i, -101 + k, 10, 2);

	//--------------------------//
	
	AddWall(99 + i, -74 + k, 20, 1);
	AddWall(78 + i, -26 + k, 35, -2);
	AddWall(92 + i, -18 + k, 25, -2);

	//DCH
	AddWall(56 + i, 15 + k, 30, 1);
	AddWall(77 + i, 23 + k, 22, 1);
	AddWall(92 + i, 93 + k, 35, 2);  // PARED RARA BOLA RODANTE
	AddWall(104 + i, 80 + k, 45, 2);
	AddWall(113 + i, 132 + k, 12, 1);
	AddWall(140 + i, 134 + k, 10, 1);


	//IZQ
	AddWall(115 + i, -74 + k, 20, 1);
	AddWall(124 + i, -42 + k, 15, 2);
	AddWall(113 + i, -30 + k, 10, 2);
	AddWall(119 + i, -2 + k, 20, 1);
	AddWall(133 + i, -10 + k, 20, 1);

	AddWall(139 + i, 18 + k, 10, 2);
	AddWall(131 + i, 34 + k, 24, 2);
	AddWall(158 + i, 34 + k, 24, -2);
	AddWall(151 + i, 18 + k, 10, -2);
	AddWall(172 + i, 0 + k, 20, 1);
	AddWall(157 + i, -10 + k, 20, 1);

	AddWall(165 + i, -35 + k, 30, -2);
	AddWall(178 + i, -27 + k, 10, -2);
	AddWall(184 + i, 5 + k, 40, 1);
	AddWall(157 + i, 80 + k, 45, -2);
	AddWall(190 + i, -45 + k, 20, 2);
	AddWall(200 + i, 5 + k, 40, 1);
	AddWall(173 + i, 80 + k, 55, -2);

	//--------------------------//

	//END
	AddWall(113 + i, 210 + k, 40, 1);
	AddWall(140 + i, 210 + k, 40, 1);
	

	AddWall(67 + i, 60 + k, 20, 2);

}

void ModuleSceneIntro::Coin()
{
	AddCoin(3, 10, 2);

}

void ModuleSceneIntro::Ground()
{
	///
	AddGround(-82, 37, 188, 115, 0,Black);
	AddGround(-240, 71, 130, 23, 0);
	AddGround(-266, 0, 20, 70, 0);

	AddGround(-268, 115, 20, 30, 0);
	AddGround(-260, 130, 50, 15, 0);
	AddGround(-300, 144, 55, 18, 0);
	AddGround(-243, 140, 65, 18, 10);

	AddGround(-330, 135, 27, 17, -52);
	AddGround(-345, 95, 20, 85, 19);
	//Square
	AddGround(-299, -38, 85, 73, 0);

	AddGround(-221, -60, 71, 15, 0);

	//Retocar
	AddGround(-330, -82, 21, 30, 0);

	//25º
	AddGround(-287, 65, 30, 20, -25);
	AddGround(-313, 68, 30, 20, -23);
	AddGround(-317, 42, 50, 20, -44);
	AddGround(-334, 50, 40, 20, -52);

	AddGround(-358, 50, 30, 20, -90);
	AddGround(-354, 25, 30, 20, -103);
	AddGround(-345, 20, 30, 35, -90);
	AddGround(-338, 10, 20, 35, -20);
	AddGround(-345, 0, 20, 33, -40);

	//-----------------// PARCHES ESQUINAS

	AddGround(-278, -1, 8, 10, 53);
	AddGround(-255, -50, 6, 10, -40);
	AddGround(-255, -69, 6, 10, 40);
	AddGround(-319, -77, 6, 10, 40);

	//-----------------// PARCHES ESQUINAS UP

	AddGround(-257, 120, 8, 13, 40);
	AddGround(-283, 126, 9, 30, -37);

	//CAMINO CURVA RARA PRINCIPIO
	AddGround(-197, 109, 16, 73, -37);
	AddGround(-190, 89, 5, 15, -32);
	AddGround(-213, 114, 15, 55, -55);

	// CAMINO 2a parte cicuito antes rampa
	AddGround(-315, -117, 16, 62, -37);

	// CAMINO 2a parte cicuito despues rampa
	AddGround(-300, -220, 20, 20, 0);

	//Rampa a la nada
	AddGround(-334, -280, 22, 132, 37);

	//cuadrado grande 2a parte
	AddGround(-135, -273, 85, 330, 90);
	//cuadrado grande final
	AddGround(38, -126, 145, 220, 0);

	//Rampa final
	AddGround(36, 15, 27, 8, 0, Final5);
	AddGround(36, 23, 27, 8, 0, Final6);
	AddGround(36, 31, 27, 8, 0, Final7);
	AddGround(36, 39, 27, 8, 0, Final1);
	AddGround(36, 47, 27, 8, 0, Final2);
	AddGround(36, 55, 27, 8, 0, Final3);
	AddGround(36, 63, 27, 8, 0, Final4);
	AddGround(36, 71, 27, 8, 0, Final5);
	AddGround(36, 79, 27, 8, 0, Final6);
	AddGround(36, 87, 27, 8, 0, Final7);
	AddGround(36, 95, 27, 8, 0, Final1);
	AddGround(36, 103, 27, 8, 0, Final2);
	AddGround(36, 111, 27, 8, 0, Final3);
	AddGround(36, 119, 27, 8, 0, Final4);
	AddGround(36, 127, 27, 8, 0, Final5);
	AddGround(36, 135, 27, 8, 0, Final6);
	AddGround(36, 143, 27, 8, 0, Final7);

}

void ModuleSceneIntro::Ramps()
{
	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);
	// UP(D)
	btCollisionShape* wall = new btBoxShape(btVector3({ 12,15,1 }));
	wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, 0.7), btVector3(-267, 11, 48)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, wall, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
	App->physics->world->addRigidBody(fallRigidBody);

	Cube c_wall(12*2,15*2,1*2);
	fallRigidBody->getWorldTransform().getOpenGLMatrix(&c_wall.transform);
	walls_vector.PushBack(c_wall);
	

	//UP(U)
	btCollisionShape* wall1 = new btBoxShape(btVector3({ 12,15,1 }));
	wall1->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState1 =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, -0.7), btVector3(-268, 11, 88)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI1(mass, fallMotionState1, wall1, fallInertia);
	btRigidBody* fallRigidBody1 = new btRigidBody(fallRigidBodyCI1);
	App->physics->world->addRigidBody(fallRigidBody1);
	Cube c_wall1(12 * 2, 15 * 2, 1 * 2);
	fallRigidBody1->getWorldTransform().getOpenGLMatrix(&c_wall1.transform);
	walls_vector.PushBack(c_wall1);

	// UP(D)
	btCollisionShape* wall2 = new btBoxShape(btVector3({ 14,15,1 }));
	wall2->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState2 =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, 0.7), btVector3(37, 11, -20)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass, fallMotionState2, wall2, fallInertia);
	btRigidBody* fallRigidBody2 = new btRigidBody(fallRigidBodyCI2);
	App->physics->world->addRigidBody(fallRigidBody2);
	Cube c_wall2(14 * 2, 15 * 2, 1 * 2);
	fallRigidBody2->getWorldTransform().getOpenGLMatrix(&c_wall2.transform);
	walls_vector.PushBack(c_wall2);

	//UP(U)
	btCollisionShape* wall3 = new btBoxShape(btVector3({ 14,15,1 }));
	wall3->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState3 =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, -0.7), btVector3(37, 11, 20)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI3(mass, fallMotionState3, wall3, fallInertia);
	btRigidBody* fallRigidBody3 = new btRigidBody(fallRigidBodyCI3);
	App->physics->world->addRigidBody(fallRigidBody3);
	Cube c_wall3(14 * 2, 15 * 2, 1 * 2);
	fallRigidBody3->getWorldTransform().getOpenGLMatrix(&c_wall3.transform);
	walls_vector.PushBack(c_wall3);

	// UP(D)
	btCollisionShape* wall4 = new btBoxShape(btVector3({ 10,15,1 }));
	wall2->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState4 =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, 0.7), btVector3(-300, 11, -200)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI4(mass, fallMotionState4, wall4, fallInertia);
	btRigidBody* fallRigidBody4 = new btRigidBody(fallRigidBodyCI4);
	App->physics->world->addRigidBody(fallRigidBody4);
	Cube c_wall4(10 * 2, 15 * 2, 1 * 2);
	fallRigidBody4->getWorldTransform().getOpenGLMatrix(&c_wall4.transform);
	walls_vector.PushBack(c_wall4);

	//UP(U)
	btCollisionShape* wall5 = new btBoxShape(btVector3({ 10,15,1 }));
	wall3->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState5 =
		new btDefaultMotionState(btTransform(btQuaternion(0.5, 0, 0, -0.7), btVector3(-301, 11, -150)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI5(mass, fallMotionState5, wall5, fallInertia);
	btRigidBody* fallRigidBody5 = new btRigidBody(fallRigidBodyCI5);
	App->physics->world->addRigidBody(fallRigidBody5);
	Cube c_wall5(10 * 2, 15 * 2, 1 * 2);
	fallRigidBody5->getWorldTransform().getOpenGLMatrix(&c_wall5.transform);
	walls_vector.PushBack(c_wall5);

	btCollisionShape* wall6 = new btBoxShape(btVector3({ 20,30,0.5 }));
	wall6->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState6 =
		new btDefaultMotionState(btTransform(btQuaternion(0.7, 0, 0, 1), btVector3(-23.5, 40, -60)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI6(mass, fallMotionState6, wall6, fallInertia);
	btRigidBody* fallRigidBody6 = new btRigidBody(fallRigidBodyCI6);
	App->physics->world->addRigidBody(fallRigidBody6);
	
	


}

void ModuleSceneIntro::AddWall(int x, int z, btScalar width, float rotation) {



	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);


	btCollisionShape* wall = new btBoxShape(btVector3({ width,3,0.5 }));
	wall->calculateLocalInertia(mass, fallInertia);
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, rotation, 0, 1), btVector3(x, 10, z)));
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, wall, fallInertia);
	btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

	App->physics->world->addRigidBody(fallRigidBody);


	Cube r_wall(width * 2, 6, 1);

	fallRigidBody->getWorldTransform().getOpenGLMatrix(&r_wall.transform);
	btQuaternion q = fallRigidBody->getWorldTransform().getRotation();
	r_wall.color = White;

	PhysBody3D* sensor = App->physics->AddBody(r_wall, 0.f);
	sensor->collision_listeners.add(this);

	walls_vector.PushBack(r_wall);

}


void ModuleSceneIntro::AddCoin(int x, int y, int z) {




	Sphere* temp = new Sphere(1.0);
	temp->SetPos(x, y, z);
	Points temp_struct;
	temp_struct.coin = temp;
	temp_struct.active = true;
	temp->color = Yellow;
	PhysBody3D* sensor = App->physics->AddBody(*temp, 0.f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);
	temp_struct.sensor = sensor;
	Coins.PushBack(temp_struct);


}

void ModuleSceneIntro::AddGround(int x, int z, int width, int height, int angle, Color color ) {
	Cube* ground = new Cube(width, 0.5, height);
	ground->SetPos(x, 7, z);
	//ground->Scale(1000, 1, 1000);
	ground->SetRotation(angle, { 0,1,0 });
	ground->color = color;

	PhysBody3D* b_ground = App->physics->AddBody(*ground, 0.f);
	ground_vector.PushBack(*ground);

}
