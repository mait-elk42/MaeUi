//
// Created by mait-elk on 3/11/25.
//

#include <MaeUI/Application.hpp>

Application::Application( const int width, const int height, const std::string& windowTitle ) {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(width, height,windowTitle.c_str());
    InitPhysics();
    camera = {
        (Vector2) {0, 0},
        (Vector2) {0, 0},
        0.0f,
        1.0f
    };
    SetTargetFPS(60);
//    SetPhysicsTimeStep(1.0f / 60.0f);
}

bool Application::isButtonPressed (const KeyboardKey keyboard_key ) {
    return IsMouseButtonPressed(keyboard_key);
}
bool Application::isButtonPressed (const MouseButton mouse_button ) {
    return IsMouseButtonPressed(mouse_button);
}

bool Application::stillAlive() {
    render();
    return !WindowShouldClose();
}

void Application::render () {
    BeginDrawing();
    	ClearBackground(WHITE);
    EndDrawing();
}

Application::~Application() {
//    ClosePhysics();
    CloseWindow();
}