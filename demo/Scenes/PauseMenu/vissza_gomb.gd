class_name VisszaGomb
extends Button

func _on_pressed() -> void:
	SignalHub.emit_vissza_a_jatekba()
