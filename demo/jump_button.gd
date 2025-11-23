extends jumpButton



func _on_pressed() -> void:
	print("I am the Button.")
	emit_signal("jump")
