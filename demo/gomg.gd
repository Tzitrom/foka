extends Button


func _ready() -> void:
	host_button = get_node<Button>("Gomg");
	host_button connect("pressed", Callable(this, "_on_host_pressed"));
