extends Node2D

@onready var pause_menu: Control = $UILayer/PauseMenu
@onready var player: Player = $Pausable/Player
@onready var debug: Label = $UILayer/Debug

func _ready() -> void:
	SignalHub.kilepes_megnyomva.connect(kilepes_a_jatekbol)
	SignalHub.vissza_a_jatekba.connect(vissza_a_jatekba)
	SignalHub.restart.connect(vissza_a_jatekba)

func _physics_process(delta: float) -> void:
	debug.text = "Pozicio: %d, %d\nSebesseg: %d, %d" % [
		player.position.x, 
		player.position.y, 
		player.velocity.x, 
		player.velocity.y,
		]

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("escape", false):
		if get_tree().paused:
			vissza_a_jatekba()
		else: pause()

func vissza_a_jatekba() -> void:
	unpause()

func kilepes_a_jatekbol() -> void:
	get_tree().quit()

func pause() -> void:
	pause_menu.show()
	get_tree().paused = true

func unpause() -> void:
	pause_menu.hide()
	get_tree().paused = false
