class_name Player
extends CharacterBody2D

@onready var textura: Sprite2D = $Textura
@onready var dash_cd_timer: Timer = $DashCDTimer

@export var gravity: float = 3200.0
@export var acceleration: float = 100.0   #a sima elindulásért
@export var jump_velocity: float = 1000.0
@export var max_speed: float = 500.0 # ez lehet hogy egy kicsit gyors (500)...
@export var dash_speed: float = 1000.0 
@export var dash_cooldown: int = 2
@export var dash_ido: float = 0.2 # a dasheles ideje
@export var coyote_time : float = 1.0
@export_range(0.0, 1.0) var friction: float = 0.8


var startpos : Vector2 # amikor elindul a program akkor ez a Player kezdőpontja
var in_air : bool
var dash_unlocked : bool = false # ha be van kapcsolva a dash
var double_jump_unlocked : bool = false # ha be van kapcsolva 
var wall_climb_unlocked : bool = false # ha be van kapcsolva
var irany : float = 0.0
var dashing : bool = false
var dash_timer : float = 0.0 # ez a dashelés közben megy, annak az ideje
var tud_dash : bool = false # hogyha lejárt a cooldown
var dash_cd_lejart : bool = true
var ugrasok : int = 2
var max_ugrasok : int = 1
var coyote_szamolo : float = 0.0

func _ready() -> void:
	startpos = position
	SignalHub.restart.connect(die)
	SignalHub.double_jump_toggle.connect(double_jump_kapcsolo)
	SignalHub.dash_toggle.connect(dash_kapcsolo)
	SignalHub.wall_climb_toggle.connect(wall_climb_kapcsolo)

func _physics_process(delta: float) -> void:
	
	var direction := Input.get_axis("balra", "jobbra")  # -1.0 és 1.0 közötti szám ahol a teljesen balra a -1.0, teljesen jobbra a 1.0
	if dash_timer == 0:
		velocity.y += gravity * delta    ## mindig huzza lefele a gravity, tickenként a delta változóval gyorsulva
		
		if absf(velocity.x) <= max_speed:  # csak addig gyorsul amíg nem vagyunk maxon
			velocity.x += direction * acceleration # a gyorsulást megszorozza 1-el vagy -1-el attől függően hogy merre megyünk
		velocity.x = clampf(velocity.x, -max_speed, max_speed) # limiteli a sebességet -max_speed és max_speed között. (A -max_speed a balra mozgás)
		
		if direction == 0.0: # hogyha nem nyomunk gombot
			velocity.x *= friction # tickenként megszorozza a velocity.xet frictionnal -> lelassítja
		
		if Input.is_action_just_pressed("ugras"):
			jump()
	
	in_air = !is_on_floor()
	if dash_timer == 0.0 and !tud_dash and !in_air:
		tud_dash = true
	
	if (!is_zero_approx(velocity.x)):
		textura.flip_h = velocity.x < 0
	if textura.flip_h: irany = -1 
	if !textura.flip_h: irany = 1 
	
	if !dash_unlocked and Input.is_action_just_pressed("dash"): print("Dash nincs bekapcsolva")
	if dash_unlocked:
		dash(delta)
		dashing = true
	
	if !in_air and velocity.y >= 0:
		coyote_szamolo = coyote_time
		ugrasok = max_ugrasok
	elif coyote_szamolo > 0.0:
			coyote_szamolo = max(0.0, coyote_szamolo - delta)
			
			if coyote_szamolo > 0.0:
				ugrasok = max(0, ugrasok - 1)
	
	max_ugrasok = 2 if double_jump_unlocked else 1
	
	move_and_slide()


func dash(delta: float) -> void:  # ez NEM jó >:( javicsd meg
	if tud_dash and Input.is_action_just_pressed("dash") and in_air:
		dash_cd_lejart = false
		tud_dash = false
		dash_timer = dash_ido
		velocity.x = dash_speed * irany
		velocity.y = 0
		dash_cd_timer.start(dash_cooldown)
	if dash_timer > 0.0:
		dash_timer = max(0.0, dash_timer - delta)
		if is_on_wall():
			dash_timer = 0.0

func double_jump_kapcsolo(fazis: bool) -> void:
	double_jump_unlocked = fazis
func dash_kapcsolo(fazis: bool) -> void:
	dash_unlocked = fazis
func wall_climb_kapcsolo(fazis: bool) -> void:
	wall_climb_unlocked = fazis

func jump() -> void:
	if ugrasok > 0:
		ugrasok = ugrasok - 1
		velocity.y = -jump_velocity
		coyote_szamolo = 0.0

func die() -> void:
	position = startpos
	velocity = Vector2.ZERO
	dash_cd_timer.stop()

func _on_dash_cd_timer_timeout() -> void:
	tud_dash = true
