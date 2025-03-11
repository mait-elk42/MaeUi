#include "include/MaeUI/Application.hpp"

#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1000

//class GameObject {
//private:
//
//public:
//	GameObject (  ) {
//
//	}
//};
//
//Vector2 Lerp(Vector2 start, Vector2 end, float t) {
//    return (Vector2){ start.x + t * (end.x - start.x), start.y + t * (end.y - start.y) };
//}


//class Application {
//    Camera2D camera {};
//public:
//    Application(const int width, const int height, const std::string& windowTitle ) {
//        SetTraceLogLevel(LOG_NONE);
//        InitWindow(width, height,windowTitle.c_str());
//        InitPhysics();
//        camera = {
//            (Vector2) {0, 0},
//            (Vector2) {0, 0},
//            0.0f,
//            1.0f
//        };
//        SetTargetFPS(60);
//        SetPhysicsTimeStep(1.0f / 60.0f);
//    }
//
//	void render () {
//    	BeginDrawing();
//    		ClearBackground(WHITE);
//    	EndDrawing();
//    }
//
//	bool isButtonPressed (const KeyboardKey keyboard_key ) {
//    	return IsMouseButtonPressed(keyboard_key);
//    }
//	bool isButtonPressed (const MouseButton mouse_button ) {
//    	return IsMouseButtonPressed(mouse_button);
//    }
//
//	bool stillAlive() {
//    	render();
//	    return !WindowShouldClose();
//    }
//
//	~Application() {
//    	ClosePhysics();
//    	CloseWindow();
//    }
//};

int main(  ) {

    Application game(300, 300, std::string("RedBall"));

	while ( game.stillAlive() ) {
		if ( game.isButtonPressed(KEY_ESCAPE) ) break;
	}

    return 0;

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

	SetPhysicsGravity(0.0f, 2.0f);
	while (!WindowShouldClose()) {
		if ( IsKeyDown(KEY_A) )
			player->velocity.x = -0.3;
		if ( IsKeyDown(KEY_D) )
			player->velocity.x = 0.3;

		if ( !(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) ) {
			player->velocity.x = 0;
		}

		if ( IsKeyPressed(KEY_SPACE) )
			player->velocity.y = -0.9f;

		BeginDrawing();
            ClearBackground(BLACK);
            // DrawRectangle(100, 100, 100, 100, RED);
            Vector2 points[10];
            points[0] = (Vector2) {100, 100};
            points[1] = (Vector2) {200, 100};
            points[2] = (Vector2) {200, 200};
            points[3] = (Vector2) {170, 130};
            points[4] = (Vector2) {100, 100};
            DrawLineStrip(points, 5, GREEN);
            // DrawTriangleLines(
            //     (Vector2) {0, 0},
            //     (Vector2) {100, 0},
            //     (Vector2) {100, 100},
            //     YELLOW);

            BeginMode2D(camera);
//            camera.target = Lerp(camera.target, (Vector2) { player->position.x - (SCREEN_WIDTH / 2.0f), player->position.y - (SCREEN_HEIGHT / 2.0f) }, GetFrameTime() * 20.0f);
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

