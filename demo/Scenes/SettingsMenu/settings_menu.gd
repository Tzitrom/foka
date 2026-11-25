extends Control


func _on_doublejump_gomb_toggled(toggled_on: bool) -> void:
	SignalHub.emit_double_jump_toggle(toggled_on)

func _on_dash_gomb_toggled(toggled_on: bool) -> void:
	SignalHub.emit_dash_toggle(toggled_on)

func _on_wallclimb_gomb_toggled(toggled_on: bool) -> void:
	SignalHub.emit_wall_climb_toggle(toggled_on)
