#ifndef GHOST_PROS__V5_GLOBALS_HPP
#define GHOST_PROS__V5_GLOBALS_HPP

#include <map>

#include "pros/apix.h"
#include "ghost_v5/serial/v5_serial_node.hpp"
#include "ghost_v5/motor/v5_motor_interface.hpp"
#include "ghost_common/v5_robot_config_defs.hpp"
namespace v5_globals
{
    extern uint32_t last_cmd_time;
    extern uint32_t cmd_timeout_ms;
    extern uint32_t loop_frequency;
    extern bool run;

    extern pros::Controller controller_main;

    extern pros::Mutex actuator_update_lock;

    extern std::map<std::string, std::shared_ptr<ghost_v5::V5MotorInterface>> motors;
    extern std::map<std::string, std::shared_ptr<pros::Rotation>> encoders;

    extern const pros::controller_analog_e_t joy_channels[4];
    extern const pros::controller_digital_e_t joy_btns[12];

    extern pros::ADIDigitalOut adi_ports[8];
    extern pros::Mutex digitial_out_lock;
    extern std::vector<bool> digital_out_cmds;

    // Serial Port
    extern ghost_v5::V5SerialNode serial_node_;

} // namespace v5_globals

#endif // GHOST_PROS__V5_GLOBALS_HPP