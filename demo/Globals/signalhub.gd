extends Node

signal kilepes_megnyomva
signal vissza_a_jatekba
signal restart
signal settings
signal double_jump_toggle(fazis: bool)
signal dash_toggle(fazis: bool)
signal wall_climb_toggle(fazis: bool)

### Pause Menu
### /-----------------\
func emit_kilepes() -> void:
	kilepes_megnyomva.emit()

func emit_vissza_a_jatekba() -> void:
	vissza_a_jatekba.emit()

func emit_restart() -> void:
	restart.emit()

func emit_settings() -> void:
	settings.emit()
### \----------------/

### Settings Menu
### /-----------------\
func emit_double_jump_toggle(fazis: bool) -> void:
	double_jump_toggle.emit(fazis)

func emit_dash_toggle(fazis: bool) -> void:
	dash_toggle.emit(fazis)

func emit_wall_climb_toggle(fazis: bool) -> void:
	wall_climb_toggle.emit(fazis)
### \----------------/
