#pragma once

#include <godot_cpp/classes/character_body2d.hpp>


namespace godot {

    class Player : public CharacterBody2D {
        GDCLASS(Player, CharacterBody2D)

    private:
        double gravity;
        bool jump_signal;
    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();

        void _process(double delta);
        void jump();
    };
}