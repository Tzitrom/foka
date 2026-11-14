class_name Player
extends CharacterBody2D

@onready var textura: Sprite2D = $Textura
@onready var dash_timer: Timer = $DashTimer

@export var gravity: float = 3000.0
@export var acceleration: float = 100.0   #a sima elindulásért
@export var jump_velocity: float = 1200.0
@export var max_walk_speed: float = 500.0 # ez lehet hogy egy kicsit gyors (500)...
@export var max_speed : float = 1000.0
@export var dash_length: float = 1000.0
@export var dash_cooldown: int = 5
@export_range(0.0, 1.0) var friction: float = 0.8


var startpos : Vector2 # amikor elindul a program akkor ez a Player kezdőpontja
var in_air : bool
var tud_dash : bool = false
var tud_double_jump : bool = false
var tud_wall_climb : bool = false
var irany : float = 0.0
var dash_ido : float


func _ready() -> void:
	startpos = position
	SignalHub.restart.connect(die)
	SignalHub.double_jump_toggle.connect(double_jump_kapcsolo)
	SignalHub.dash_toggle.connect(dash_kapcsolo)
	SignalHub.wall_climb_toggle.connect(wall_climb_kapcsolo)

func _physics_process(delta: float) -> void:
	velocity.y += gravity * delta    ## mindig huzza lefele a gravity, tickenként a delta változóval gyorsulva
	
	var direction := Input.get_axis("balra", "jobbra")  # -1.0 és 1.0 közötti szám ahol a teljesen balra a -1.0, teljesen jobbra a 1.0
	if absf(velocity.x) <= max_walk_speed:  # csak addig gyorsul amíg nem vagyunk maxon
		velocity.x += direction * acceleration # a gyorsulást megszorozza 1-el vagy -1-el attől függően hogy merre megyünk
	
	velocity.x = clampf(velocity.x, -max_speed, max_speed) # limiteli a sebességet -max_speed és max_speed között. (A -max_speed a balra mozgás)
	if direction == 0.0: # hogyha nem nyomunk gombot
		velocity.x *= friction # tickenként megszorozza a velocity.xet frictionnal -> lelassítja
		# ha friction = 0 => mintha radíron próbálna csúszni
		# ha friction = 1 => mintha jegen csúszna
	
	move_and_slide()
	in_air = !is_on_floor()
	
	if (!is_zero_approx(velocity.x)):
		textura.flip_h = velocity.x < 0
		irany = clampf(velocity.x, -1.0, 1.0)
	
	dash_ido = dash_timer.time_left
	###
	### var mouse_offset := get_global_mouse_position().x - global_position.x
	### if mouse_offset > 0.0:
	###		textura.flip_h = false			Szerintem ez faszság így utólag nézve
	###elif mouse_offset < 0.0:
	### 	textura.flip_h = true
	###
	
	if Input.is_action_just_pressed("dash"):
		if !tud_dash: print("Dash nincs bekapcsolva")
		else:
			dash()
	if Input.is_action_pressed("ugras") and is_on_floor():
		jump()

func double_jump_kapcsolo(fazis: bool) -> void:
	tud_double_jump = fazis

func dash_kapcsolo(fazis: bool) -> void:
	tud_dash = fazis

func wall_climb_kapcsolo(fazis: bool) -> void:
	tud_wall_climb = fazis

func jump() -> void:
	velocity.y -= jump_velocity

func die() -> void:
	position = startpos
	velocity = Vector2.ZERO

func dash() -> void:  # ez NEM jó >:( javicsd meg
	velocity.x += dash_length * irany
	dash_timer.start(0.5)
	await dash_timer.timeout
	velocity.x = clampf(velocity.x, -max_walk_speed, max_walk_speed)
