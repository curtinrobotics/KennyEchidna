#include <sstream>
#include <kenny_hardware_interface/kenny_hardware_interface.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_urdf.h>
#include <joint_limits_interface/joint_limits_rosparam.h>
#include <kennycpp/kenny.h>

using namespace hardware_interface;
using joint_limits_interface::JointLimits;
using joint_limits_interface::SoftJointLimits;
using joint_limits_interface::PositionJointSoftLimitsHandle;
using joint_limits_interface::PositionJointSoftLimitsInterface;

namespace kenny_hardware_interface
{
    // Constructor
    KennySystemHardwareInterface::KennySystemHardwareInterface(ros::NodeHandle& nh) : nh_(nh) {
        init();
        controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));

        nh_.param("/kenny/hardware_interface/loop_hz", loop_hz_, 0.1);

        ROS_DEBUG_STREAM_NAMED("constructor","Using loop freqency of " << loop_hz_ << " hz");
        
        ros::Duration update_freq = ros::Duration(1.0/loop_hz_);
        non_realtime_loop_ = nh_.createTimer(update_freq, &KennySystemHardwareInterface::update, this);
    }

    // Destructor - ~ marks destructor
    KennySystemHardwareInterface::~KennySystemHardwareInterface() {
        // any clean up needed - closing file, freeing memory, etc.
    }

    void KennySystemHardwareInterface::init() {
        // Get joint names
        nh_.getParam("/kenny/hardware_interface/joints", joint_names_);
        if (joint_names_.size() == 0)
		{
		  ROS_FATAL_STREAM_NAMED("init","No joints found on parameter server for controller. Did you load the proper yaml file?");
		}
        num_joints_ = joint_names_.size();

        // Resize vectors
        joint_position_.resize(num_joints_);
        joint_velocity_.resize(num_joints_);
        joint_effort_.resize(num_joints_);
        joint_position_command_.resize(num_joints_);
        joint_velocity_command_.resize(num_joints_);
        joint_effort_command_.resize(num_joints_);

        // Initialize Controller 
        for (int i = 0; i < num_joints_; ++i) 
        {
            kennycpp::Joint joint = kenny.getJoint(joint_names_[i]);

            ROS_DEBUG_STREAM_NAMED("constructor","Loading joint name: " << joint.name);

            nh_.getParam("/kenny/joint_offsets/" + joint.name, joint.angleOffset);
			nh_.getParam("/kenny/joint_read_ratio/" + joint.name, joint.readRatio);
			kenny.setJoint(joint);

             // Create joint state interface
            JointStateHandle jointStateHandle(joint.name, &joint_position_[i], &joint_velocity_[i], &joint_effort_[i]);
            joint_state_interface_.registerHandle(jointStateHandle);

            // Create position joint interface
            JointHandle jointPositionHandle(jointStateHandle, &joint_position_command_[i]);
            JointLimits limits;
            SoftJointLimits softLimits;

            if (getJointLimits(joint.name, nh_, limits) == false) {
				ROS_ERROR_STREAM("Cannot set joint limits for " << joint.name);
			} 
            else {
				PositionJointSoftLimitsHandle jointLimitsHandle(jointPositionHandle, limits, softLimits);
				positionJointSoftLimitsInterface.registerHandle(jointLimitsHandle);
			}

            // Create velocity joint interface
            //JointHandle jointVelocityHandle(jointStateHandle, &joint_velocity_command_[i]);
            //effort_joint_interface_.registerHandle(jointVelocityHandle);

            // Create effort joint interface
			JointHandle jointEffortHandle(jointStateHandle, &joint_effort_command_[i]);
		    effort_joint_interface_.registerHandle(jointEffortHandle);;
        }

        registerInterface(&joint_state_interface_);
        registerInterface(&position_joint_interface_);
        registerInterface(&effort_joint_interface_);
        registerInterface(&positionJointSoftLimitsInterface);
    }

    void KennySystemHardwareInterface::update(const ros::TimerEvent& e) {
        _logInfo = "\n";
		_logInfo += "Joint Position Command:\n";
		for (int i = 0; i < num_joints_; i++)
		{
			std::ostringstream jointPositionStr;
			jointPositionStr << joint_position_command_[i];
			_logInfo += "  " + joint_names_[i] + ": " + jointPositionStr.str() + "\n";
		}

		elapsed_time_ = ros::Duration(e.current_real - e.last_real);

		read();
		controller_manager_->update(ros::Time::now(), elapsed_time_);
		write(elapsed_time_);

		//ROS_INFO_STREAM(_logInfo);
    }

    void KennySystemHardwareInterface::read() {
		_logInfo += "Joint State:\n";
		for (int i = 0; i < num_joints_; i++)
		{
			kennycpp::Joint joint = kenny.getJoint(joint_names_[i]);

			if (joint.getActuatorType() == ACTUATOR_TYPE_MOTOR)
			{
				joint_position_[i] = joint.readAngle();

				std::ostringstream jointPositionStr;
				jointPositionStr << joint_position_[i];
				_logInfo += "  " + joint.name + ": " + jointPositionStr.str() + "\n";
			}

			kenny.setJoint(joint);
		}}
    }

    void KennySystemHardwareInterface::write(ros::Duration elapsed_time)
	{
		positionJointSoftLimitsInterface.enforceLimits(elapsed_time);

		_logInfo += "Joint Effort Command:\n";
		for (int i = 0; i < num_joints_; i++)
		{
			kennycpp::Joint joint = kenny.getJoint(joint_names_[i]);
			//if (joint_effort_command_[i] > 1) joint_effort_command_[i] = 1;
			//if (joint_effort_command_[i] < -1) joint_effort_command_[i] = -1;

			double effort = joint_effort_command_[i];
			uint8_t duration = 15;

			if (joint.getActuatorType() == 1) { // servo
				double previousEffort = joint.getPreviousEffort();
				effort += previousEffort;
			}
			
			joint.actuate(effort, duration);

			std::ostringstream jointEffortStr;
			jointEffortStr << joint_effort_command_[i];
			_logInfo += "  " + joint.name + ": " + jointEffortStr.str() + "\n";
		}
	}}
}