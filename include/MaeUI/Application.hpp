//
// Created by mait-elk on 3/11/25.
//

#pragma once
#include <iostream>
#include <raylib.h>
#include <physac.h>
#include <string>
#include <vector>

class Application {
    Camera2D camera {};
public:
    Application( const int width, const int height, const std::string& windowTitle );

    bool isButtonPressed (const KeyboardKey keyboard_key );
    bool isButtonPressed (const MouseButton mouse_button );
    bool stillAlive();
    void render ();

    ~Application();
};
