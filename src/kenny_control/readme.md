# kenny_control
Package for controlling Kenny


## Contents

- `config`
    - `controllers.yaml` - defines the controllers
    - `hardware.yaml`
    - `joint_limits.yaml` 
- `launch`:
    - `setup.py` - parses urdf, sets robot_model on parameter_server, launches joint publisher, spawns joint controllers
    - `control.launch`: file responsible for launching controller spawners and spawning joint controllers. Sometimes fails to spawn joints. Relaunch and attempt again if so.
    - `keyboard_turtle_teleop.launch`: keyboard teleop of Kenny using turtlebot controls 



