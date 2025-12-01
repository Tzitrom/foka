#pragma once //minden header elejen legyen ott pls

#include <godot_cpp/classes/character_body2d.hpp>
#include "ballparent.h"
#include "player.h"

using namespace godot; // ok here (project uses this style)

class Ball : public CharacterBody2D {
    GDCLASS(Ball, CharacterBody2D)

protected:
    static void _bind_methods();

public:
    Ball();
    ~Ball();

    void _ready() override;
    void _process(double delta) override;

private:
    BallParent* ball_parent = nullptr;
    Player* player = nullptr;

    double elapsed = 0.0;   // elapsed time for interpolation
    double speed = 0.5;     // cycles per second
};