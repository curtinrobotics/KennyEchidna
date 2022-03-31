#include <kenny_hardware_interface.h>
int main(int argc, char** argv)
{
    ros::init(argc, argv, "kenny_hardware_interface");
    ros::CallbackQueue ros_queue;

    ros::NodeHandle nh;
    nh.setCallbackQueue(&ros_queue);
    kenny_hardware_interface::KennyHardwareInterface rhi(nh);

    ros::MultiThreadedSpinner spinner(0);
    spinner.spin(&ros_queue);
    return 0;
}