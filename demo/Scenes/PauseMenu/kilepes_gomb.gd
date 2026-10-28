class_name KilepesGomb
extends Button

func _on_pressed() -> void:
	SignalHub.emit_kilepes()
