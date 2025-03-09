#include "include/raylib.h"
#include "include/physac.h"
#include <cstdio>

#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1000

class GameObject {
private:
	PhysicsBody	collision;
	float		radius;
	float		width;
	float		height;
	float		density;    

public:
	GameObject ( Vector2 pos, float radius, float density ) {
		this->radius = radius;
		this->height = -1;
		this->width = -1;
		this->density = density;
		this->collision = CreatePhysicsBodyCircle(pos, radius, density);
	}

	GameObject ( Vector2 pos, float width, float height, float density ) {
		this->radius = -1;
		this->height = height;
		this->width = width;
		this->density = density;
		this->collision = CreatePhysicsBodyRectangle(pos, width, height, density);
	}

	void draw() {
		if ( this->collision->shape.type == PHYSICS_CIRCLE ) { 
			DrawCircle(collision->position.x, collision->position.y, 25.0f, RED);
		} else {
			DrawRectangle(collision->position.x - width /2, collision->position.y - height /2, width, height, BLUE);
		}
	}

	PhysicsBody body() {
		return collision;
	}
};

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RedBall");
	InitPhysics();

	GameObject player((Vector2){500, 500}, 25.0f, 1.0f);
	GameObject ground(((Vector2){400, 700}), 500, 100, 0.0f);

	SetPhysicsGravity(0.0f, 0.5f);
	while (!WindowShouldClose()) {
		player.body()->position.x -= 0.1 * (IsKeyDown(KEY_A));
		player.body()->position.x += 0.1 * (IsKeyDown(KEY_D));

		if ( IsKeyPressed(KEY_SPACE) )
			player.body()->velocity.y = -0.5f;
		
		BeginDrawing();
		ClearBackground(BLACK);
		player.draw();
		ground.draw();
		EndDrawing();
	}

	ClosePhysics();
	CloseWindow();
	return 0;
}