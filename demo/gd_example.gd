extends Sprite2D

signal position_changed(node: Node, new_pos: Vector2)

@export var amplitude: float = 10.0
@export var speed: float = 1.0

var time_passed: float = 0.0
var time_emit: float = 0.0


func _process(delta: float) -> void:
	time_passed += speed * delta

	var new_position := Vector2(
		amplitude + amplitude * sin(time_passed * 2.0),
		amplitude + amplitude * cos(time_passed * 1.5)
	)
	position = new_position

	time_emit += delta
	if time_emit > 1.0:
		position_changed.emit(self, new_position)
		time_emit = 0.0
