extends Node

signal kilepes_megnyomva
signal vissza_a_jatekba
signal restart

func emit_kilepes() -> void:
	kilepes_megnyomva.emit()

func emit_vissza_a_jatekba() -> void:
	vissza_a_jatekba.emit()

func emit_restart() -> void:
	restart.emit()
