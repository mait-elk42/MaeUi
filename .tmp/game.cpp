#include <iostream>
#include <raylib.h>
#include <physac.h>
#include <raymath.h>


#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1000


Vector2 Lerp(Vector2 start, Vector2 end, float t) {
	return (Vector2){
		start.x + (end.x - start.x) * t,
		start.y + (end.y - start.y) * t
	};
}


int main(  ) {
	SetTraceLogLevel(LOG_NONE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RedBall");

	InitPhysics();
    SetTargetFPS(60);
    SetPhysicsTimeStep(1.0f / 60.0f);
    Camera2D camera = {
        (Vector2) {0, 0},
        (Vector2) {0, 0},
        0.0f,
        1.0f
    };

	PhysicsBody player = CreatePhysicsBodyCircle((Vector2){500, 500}, 25.0f, 1.0f);

    PhysicsBody box = CreatePhysicsBodyRectangle(((Vector2){500, 600}), 300, 100, 1.0f);

	PhysicsBody ground = CreatePhysicsBodyRectangle(((Vector2){400, 800}), 1000, 50, 0.0f);


	Image img = LoadImage("test.png");
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);

	SetPhysicsGravity(0.0f, 2.0f);
	while (!WindowShouldClose()) {

		if ( IsKeyDown(KEY_A) )
			player->velocity.x = -0.3;
		if ( IsKeyDown(KEY_D) )
			player->velocity.x = 0.3;

		if ( !(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) )
			player->velocity.x = 0;

		if ( IsKeyPressed(KEY_SPACE) )
			player->velocity.y = -0.9f;

		BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(texture, 100, 100, GREEN);

            BeginMode2D(camera);
            camera.target = Lerp(camera.target, (Vector2) { player->position.x - (SCREEN_WIDTH / 2.0f), player->position.y - (SCREEN_HEIGHT / 2.0f) }, GetFrameTime() * 20.0f);
                DrawCircle(player->position.x, player->position.y, 25.0f, RED);

                DrawRectanglePro((Rectangle){box->position.x, box->position.y, 300, 100}, (Vector2){150, 50}, box->orient * 180 / PI, YELLOW);

                DrawRectangle(ground->position.x - 500, ground->position.y - 25, 1000, 50, BLUE);
            EndMode2D();
		EndDrawing();
	}

	ClosePhysics();
	CloseWindow();
	return 0;
}

