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

- kenny_description
    - package containing description of Kenny
- kenny_gazebo
    - package for simulating kenny in gazebo
- kenny_moveit_config
- kennycpp
    - package for interfacing with hardware
- kenny_control
    - contains hardware interface, teleoperation, etc.