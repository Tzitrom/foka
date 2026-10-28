extends CharacterBody2D

@export var gravity: float = 981.0
@export var acceleration: float = 100.0
@export var jump_velocity: float = -400.0
@export var max_speed: float = 500.0
@export_range(0.0, 1.0) var friction: float = 0.8

@onready var texture_sprite: Sprite2D = $textura


func _physics_process(delta: float) -> void:
	velocity.y += gravity * delta

	if is_on_floor() and Input.is_action_pressed("ugras"):
		jump()

	var direction := Input.get_axis("balra", "jobbra")
	if absf(velocity.x) <= max_speed:
		velocity.x += direction * acceleration

	velocity.x = clampf(velocity.x, -max_speed, max_speed)
	if direction == 0.0:
		velocity.x *= friction

	move_and_slide()

	var mouse_offset := get_global_mouse_position().x - global_position.x
	if mouse_offset > 0.0:
		texture_sprite.flip_h = false
	elif mouse_offset < 0.0:
		texture_sprite.flip_h = true


func jump() -> void:
	velocity.y += jump_velocity
