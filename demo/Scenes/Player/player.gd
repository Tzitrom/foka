class_name Player
extends CharacterBody2D

@onready var textura: Sprite2D = $Textura


@export var gravity: float = 3200.0
@export var acceleration: float = 1.8 
@export var friction: float = 2200.0

@export var seta_speed: float = 500.0 
@export var max_fall_speed : float = 1200.0
@export var jump_velocity: float = 1400.0
@export var jump_megszakitas : float = 0.0
@export var coyote_time : float = 0.12
@export var jump_buffer_time : float = 0.12

@export var dash_ido: float = 0.2 # a dasheles ideje
@export var dash_speed: float = 1800.0 
@export var dash_cooldown : float = 0.35

@export var wall_slide_speed : float = 150.0
@export var wall_slide_gravitacio : float = 10.0
@export var wall_climb_speed_h : float = 500.0
@export var wall_climb_speed_v : float = 840.0
@export var wall_climb_time : float = 0.12



var startpos : Vector2 # amikor elindul a program akkor ez a Player kezdőpontja
var was_on_floor : bool = false
var dashing : bool = false
var wall_sliding : bool = false

var dash_unlocked : bool = false # ha be van kapcsolva a dash
var double_jump_unlocked : bool = false # ha be van kapcsolva 
var wall_climb_unlocked : bool = false # ha be van kapcsolva

var irany : float = 0.0
var ugrasok : int = 2
var max_ugrasok : int = 1
var tud_dash : bool = false # hogyha lejárt a cooldown

var dash_irany : float = 0.0
var dash_szamolo : float = 0.0 # ez a dashelés közben megy, annak az ideje
var dash_cd_szamolo : float = 0.0
var coyote_szamolo : float = 0.0
var jump_buffer_szamolo : float = 0.0
var wall_climb_szamolo : float = 0.0


func _ready() -> void:
	startpos = position
	SignalHub.restart.connect(die)
	SignalHub.double_jump_toggle.connect(double_jump_kapcsolo)
	SignalHub.dash_toggle.connect(dash_kapcsolo)
	SignalHub.wall_climb_toggle.connect(wall_climb_kapcsolo)

func _physics_process(delta: float) -> void:
	timerek_reset(delta)
	
	var direction = Input.get_axis("balra", "jobbra")  # -1.0 és 1.0 közötti szám ahol a teljesen balra a -1.0, teljesen jobbra a 1.0
	if Input.is_action_just_pressed("dash") and dash_cd_szamolo <= 0.0 and dash_unlocked:
		dash_start(direction)
	if !dash_unlocked and Input.is_action_just_pressed("dash"): print("Dash nincs bekapcsolva")
	
	if dashing:
		velocity = Vector2(irany * dash_speed, 0.0)
		
		dash_szamolo -= delta
		if dash_szamolo <= 0.0:
			dashing = false
			velocity.x *= 0.2
	else:
		vizszintes_mozgas(delta, direction)
		jump(delta)
		gravitacio(delta, direction)
	
	move_and_slide()
	was_on_floor = is_on_floor()

func timerek_reset(delta: float) -> void:
	coyote_szamolo = max(coyote_szamolo - delta, 0.0)
	jump_buffer_szamolo = max(jump_buffer_szamolo - delta, 0.0)
	dash_cd_szamolo = max(dash_cd_szamolo - delta, 0.0)
	wall_climb_szamolo = max(wall_climb_szamolo - delta, 0.0)
	
	if is_on_floor() or (wall_climb_unlocked and is_on_wall()):
		coyote_szamolo = coyote_time
		ugrasok = max_ugrasok
	elif was_on_floor:
		coyote_szamolo = coyote_time
		ugrasok = max_ugrasok

func vizszintes_mozgas(delta: float, direction: float) -> void:
	if wall_climb_szamolo > 0:
		return
	if direction:
		var speed := direction * seta_speed
		
		velocity.x = max(speed + acceleration * delta, speed)
		
		textura.flip_h = velocity.x < 0
		if textura.flip_h: irany = -1 
		if !textura.flip_h: irany = 1 
	else:
		velocity.x *= friction * delta

func jump(_delta: float) -> void:
	if ugrasok > 0 and Input.is_action_just_pressed("ugras"):
		jump_buffer_szamolo = jump_buffer_time
	
	if jump_buffer_szamolo > 0.0 and !is_on_floor() and is_on_wall():
		var wall_irany : float = sign(get_wall_normal().x)
		
		if wall_irany != 0.0:
			velocity.x = wall_irany * wall_climb_speed_h
			velocity.y = -jump_velocity
			wall_climb_szamolo = wall_climb_time
			jump_buffer_szamolo = 0.0
			coyote_szamolo = 0.0
			return
	
	var tud_ugrani : bool = is_on_floor() or coyote_szamolo > 0.0 or ugrasok < max_ugrasok
	
	if jump_buffer_szamolo > 0.0 and ugrasok > 0 and tud_ugrani:
		ugrasok -= 1
		velocity.y = -jump_velocity
		coyote_szamolo = 0.0
		jump_buffer_szamolo = 0.0
	
	if Input.is_action_just_released("ugras") and velocity.y < 0.0:
		velocity.y *= jump_megszakitas

func gravitacio(delta: float, direction: float) -> void:
	if !is_on_floor():
		var aktiv_gravity := gravity
		var fall_limit := max_fall_speed
		
		if is_wall_sliding(direction):
			aktiv_gravity *= wall_slide_gravitacio
			fall_limit = wall_slide_speed
		
		velocity.y = move_toward(velocity.y, fall_limit, aktiv_gravity * delta)

func is_wall_sliding(direction: float) -> bool:
	if is_on_floor() or !is_on_wall() or velocity.y <= 0.0 or !wall_climb_unlocked:
		wall_sliding = false
		return wall_sliding
	
	wall_sliding = abs(direction) > 0.1 and direction * get_wall_normal().x < 0.0
	return wall_sliding

func dash_start(direction: float) -> void:
	if direction == 0.0: # hogyha nem nyomunk semmit akkor arra dashel amerre néz
		direction = -1.0 if textura.flip_h else 1.0
	
	dash_irany = direction
	dash_szamolo = dash_ido
	dash_cd_szamolo = dash_cooldown
	dashing = true
	velocity = Vector2(dash_irany * dash_speed, 0.0)
	
	textura.flip_h = dash_irany < 0.0

func die() -> void:
	position = startpos
	velocity = Vector2.ZERO

func double_jump_kapcsolo(fazis: bool) -> void:
	double_jump_unlocked = fazis
	max_ugrasok = 2 if double_jump_unlocked else 1
func dash_kapcsolo(fazis: bool) -> void:
	dash_unlocked = fazis
func wall_climb_kapcsolo(fazis: bool) -> void:
	wall_climb_unlocked = fazis
