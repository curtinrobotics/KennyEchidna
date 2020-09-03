#include "ros/ros.h"
#include <stdexcept>
#include <kennycpp/kenny.h>
#include <kennycpp/segment.h>
#include <kennycpp/joint.h>

namespace tr1cpp
{
	Kenny::Kenny()
	{
        // define kenny joints

        // ---------------------------------------------------------- TODO

		//base
        base.joints[0].name = "joint_base_wheel_left";
        base.joints[0].setMotorId(9);
        base.joints[1].name = "joint_base_wheel_right";
        base.joints[1].setMotorId(10);
        // base.joints[2].name = "joint_base_reel";
        // base.joints[2].setMotorId(11);

		// arm
        arm.joints[0].name = "joint_reel_link1";
        arm.joints[0].setMotorId(1);
        arm.joints[1].name = "joint_link1_link2";
        arm.joints[1].setMotorId(2);
        arm.joints[2].name = "joint_link2_link3";
        arm.joints[2].setMotorId(3);
		
        // Camera
        camera.joints[0].name = "joint_camera_z_rotation";
        camera.joints[0].setMotorId(4);
        camera.joints[1].name = "joint_camera_y_rotation";
        camera.joints[1].setMotorId(5);
	}

	Kenny::~Kenny()
	{

	}

	Joint Kenny::getJoint(std::string jointName)
	{
        // Searching through all Kenny's joints for jointName
		int numJointsBase = sizeof(base.joints) / sizeof(base.joints[0]);
		for (int i = 0; i < numJointsBase; i++)
		{
			if (base.joints[i].name == jointName)
			{
				return base.joints[i];
			}
		}

		int numJointsArm = sizeof(torso.joints) / sizeof(torso.joints[0]);
		for (int i = 0; i < numJointsArm; i++)
		{
			if (torso.joints[i].name == jointName)
			{
				return torso.joints[i];
			}
		}

		int numJointsCamera = sizeof(armRight.joints) / sizeof(armRight.joints[0]);
		for (int i = 0; i < numJointsCamera; i++)
		{
			if (armRight.joints[i].name == jointName)
			{
				return armRight.joints[i];
			}
		}

		throw std::runtime_error("Could not find joint with name " + jointName);
	}

    /* Update Kenny's joint with the same name as the argument joint */
	void Kenny::setJoint(Joint joint)
	{
		bool foundJoint = false;

		int numJointsBase = sizeof(base.joints) / sizeof(base.joints[0]);
		for (int i = 0; i < numJointsBase; i++)
		{
			if (base.joints[i].name == joint.name)
			{
				foundJoint = true;
				base.joints[i] = joint;
			}
		}

		int numJointsArm = sizeof(torso.joints) / sizeof(torso.joints[0]);
		for (int i = 0; i < numJointsArm; i++)
		{
			if (torso.joints[i].name == joint.name)
			{
				foundJoint = true;
				arm.joints[i] = joint;
			}
		}

		int numJointsCamera = sizeof(armRight.joints) / sizeof(armRight.joints[0]);
		for (int i = 0; i < numJointsCamera; i++)
		{
			if (armRight.joints[i].name == joint.name)
			{
				foundJoint = true;
				camera.joints[i] = joint;
			}
		}

		if (foundJoint == false)
		{
			throw std::runtime_error("Could not find joint with name " + joint.name);
		}
	}
}