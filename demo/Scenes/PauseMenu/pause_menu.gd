extends Control


func _on_vissza_gomb_pressed() -> void:
	SignalHub.emit_vissza_a_jatekba()


func _on_kilepes_gomb_pressed() -> void:
	SignalHub.emit_kilepes()
