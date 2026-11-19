extends Node2D

@onready var pause_menu: Control = $UILayer/PauseMenu
@onready var settings_menu: Control = $UILayer/SettingsMenu
@onready var player: Player = $Pausable/Player
@onready var debug: Label = $UILayer/Debug

func _ready() -> void:
	SignalHub.kilepes_megnyomva.connect(kilepes_a_jatekbol)
	SignalHub.vissza_a_jatekba.connect(vissza_a_jatekba)
	SignalHub.restart.connect(vissza_a_jatekba)
	SignalHub.settings.connect(beallitasok)

func _physics_process(_delta: float) -> void:
	debug.text = "Pozicio: %d, %d\nSebesseg: %d, %d\nUgrik: %s\nDouble Jump: %s\nDash: %s\nWall Climb: %s\nIrany: %d\ntud_dash: %s\nUgrasok: %d\nCoyote Time: %d" % [
		player.position.x, 
		player.position.y, 
		player.velocity.x, 
		player.velocity.y,
		player.in_air,
		player.double_jump_unlocked,
		player.dash_unlocked,
		player.wall_climb_unlocked,
		player.irany,
		player.tud_dash,
		player.ugrasok,
		player.coyote_szamolo,
		]

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("escape", false):
		if pause_menu.visible:
			unpause()
		else:
			pause()

func vissza_a_jatekba() -> void:
	unpause()

func kilepes_a_jatekbol() -> void:
	get_tree().quit()

func pause() -> void:
	settings_menu.hide()
	pause_menu.show()
	get_tree().paused = true

func unpause() -> void:
	pause_menu.hide()
	get_tree().paused = false

func beallitasok() -> void:
	pause_menu.hide()
	settings_menu.show()
