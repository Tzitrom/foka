extends GDExample

func _on_position_changed(node: Object, new_pos: Vector2) -> void:
	print("A " + node.get_class() + " új pozíciója: " + str(new_pos))
