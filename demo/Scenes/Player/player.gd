class_name Player
extends CharacterBody2D

@export var gravity: float = 1500.0
@export var acceleration: float = 100.0   #a sima elindulásért
@export var jump_velocity: float = 600.0
@export var max_speed: float = 500.0 # ez lehet hogy egy kicsit gyors (500)...
@export_range(0.0, 1.0) var friction: float = 0.8

@onready var textura: Sprite2D = $Textura

var startpos : Vector2 # amikor elindul a program akkor ez a Player kezdőpontja


func _unhandled_input(event: InputEvent) -> void:
	if event.is_action("ugras") and is_on_floor():
		jump()

func _ready() -> void:
	startpos = position

func _physics_process(delta: float) -> void:
	velocity.y += gravity * delta    ## mindig huzza lefele a gravity, tickenként a delta változóval gyorsulva
	
	var direction := Input.get_axis("balra", "jobbra")  # -1.0 és 1.0 közötti szám ahol a teljesen balra a -1.0, teljesen jobbra a 1.0
	if absf(velocity.x) <= max_speed:  # csak addig gyorsul amíg nem vagyunk maxon
		velocity.x += direction * acceleration # a gyorsulást megszorozza 1-el vagy -1-el attől függően hogy merre megyünk
	
	velocity.x = clampf(velocity.x, -max_speed, max_speed) # limiteli a sebességet -max_speed és max_speed között. (A -max_speed a balra mozgás)
	if direction == 0.0: # hogyha nem nyomunk gombot
		velocity.x *= friction # tickenként megszorozza a velocity.xet frictionnal -> lelassítja
		# ha friction = 0 => mintha radíron próbálna csúszni
		# ha friction = 1 => mintha jegen csúszna
	
	move_and_slide()
	
	###
	### var mouse_offset := get_global_mouse_position().x - global_position.x
	### if mouse_offset > 0.0:
	###		textura.flip_h = false			Szerintem ez faszság így utólag nézve
	###elif mouse_offset < 0.0:
	### 	textura.flip_h = true
	###

func jump() -> void:
	velocity.y -= jump_velocity

func die() -> void:
	position = startpos
	
