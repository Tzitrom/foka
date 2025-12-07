#pragma once //minden header elejen legyen ott pls

#include <godot_cpp/classes/character_body2d.hpp>
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

    Vector2 target;
private:
    float speed = 500.0f;

};