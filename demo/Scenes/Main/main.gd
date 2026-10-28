extends Node2D

@onready var pause_menu: Control = $PauseMenu
@onready var player: Player = $Jatek/Player

func _ready() -> void:
	SignalHub.kilepes_megnyomva.connect(kilepes_a_jatekbol)
	SignalHub.vissza_a_jatekba.connect(vissza_a_jatekba)

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
