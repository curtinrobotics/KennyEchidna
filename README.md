# KennyEchidna

## URDF Creation
The joint origin defines the centre of the transform, the visual origin should be the offset from the joint origin.


## Notes
- as camera reel is situated below the top of the prism of arm, so is currently represented as sitting on top of the prism. 
- If running on VMware and gazebo does not launch, turn of graphics driver(?) with `SVGA_VGPU10=0`


## ROS2 Changes
- `package.xml` <build_type>ament_cmake
- source the workspace `source install/setup.bash`



## Packages Structure

https://roboticsbackend.com/package-organization-for-a-ros-stack-best-practices/

<!-- - kenny_description
    - package containing description of Kenny
- kenny_gazebo
    - package for simulating kenny in gazebo
- kenny_moveit_config
- kennycpp
    - package for interfacing with hardware
- kenny_control
    - contains hardware interface, teleoperation, etc. -->


- `kenny_description` 
    - contains the URDF and SDF for Kenny, as well as meshes
    - contains one launch file, purely for testing the URDF. Is not used in production. 
- `kenny_bringup` 
    - contains only launch and config files for kenny
    - Placing all launch files within one package means easy dependency management, and makes the launch files easy to maintain
- `kenny_hw` or `kenny_driver`
    - The hardware abstraction layer
- `kenny_control`
    - centralises all control algorithms for Kenny
    - not always needed, esp. when controllers are too basic
- `kenny_teleop`
    - package to teleoperate a robot from a mount, joystick, etc. 
- `kenny_gzebo`
