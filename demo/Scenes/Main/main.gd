extends Node2D

@onready var pause_menu: Control = $UILayer/PauseMenu
@onready var settings_menu: Control = $UILayer/SettingsMenu
@onready var player: Player = $Pausable/Player
@onready var debug: RichTextLabel = $UILayer/Debug

func _ready() -> void:
	SignalHub.kilepes_megnyomva.connect(kilepes_a_jatekbol)
	SignalHub.vissza_a_jatekba.connect(vissza_a_jatekba)
	SignalHub.restart.connect(vissza_a_jatekba)
	SignalHub.settings.connect(beallitasok)

func _physics_process(_delta: float) -> void:
	debug_text()

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

func debug_text() -> void:
	debug.text = (
		"Position: %d, %d\n" +
		"Velocity: %d, %d\n" +
		"Ugrik: %s\n" +
		"Double Jump: %s\n" +
		"Dash: %s\n" +
		"Wall Climb: %s\n" +
		"Irany: %d\n" +
		"Tud ugrani: %s\n" +
		"Ugrasok: %d\n" +
		"Dashing: %s\n" +
		"Wall Sliding: %s\n" +
		"Wall Climb Szamolo: %f\n" +
		"Coyote Szamolo: %f\n"
	) % [
		player.position.x, player.position.y,
		player.velocity.x, player.velocity.y,
		color_bool(!player.is_on_floor()),
		color_bool(player.double_jump_unlocked),
		color_bool(player.dash_unlocked),
		color_bool(player.wall_climb_unlocked),
		player.irany,
		color_bool(player.tud_ugrani),
		player.ugrasok,
		color_bool(player.dashing),
		color_bool(player.wall_sliding),
		player.wall_climb_szamolo,
		player.coyote_szamolo,
	]
	

func color_bool(value) -> String:
	return "[color=green]true[/color]" if value else "[color=red]false[/color]"
