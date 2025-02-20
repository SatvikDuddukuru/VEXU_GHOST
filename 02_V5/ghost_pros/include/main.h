/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2022, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

// Includes
#include "api.h"
#include "pros/apix.h"

#include <map>

#include "ghost_v5/globals/v5_globals.hpp"
#include "ghost_common/v5_robot_config_defs.hpp"

// Global Variables
namespace v5_globals
{
    uint32_t last_cmd_time = 0;
    uint32_t cmd_timeout_ms = 50;
    uint32_t loop_frequency = 10;
    bool run = true;
    pros::Mutex actuator_update_lock;

    pros::Controller controller_main(pros::E_CONTROLLER_MASTER);
    
    ///// MOTOR DEFINITIONS /////
    std::map<std::string, std::shared_ptr<ghost_v5::V5MotorInterface>> motors;
    std::map<std::string, std::shared_ptr<pros::Rotation>> encoders;


    const pros::controller_analog_e_t joy_channels[4] = {
        ANALOG_LEFT_X,
        ANALOG_LEFT_Y,
        ANALOG_RIGHT_X,
        ANALOG_RIGHT_Y};

    const pros::controller_digital_e_t joy_btns[12] = {
        DIGITAL_A,
        DIGITAL_B,
        DIGITAL_X,
        DIGITAL_Y,
        DIGITAL_UP,
        DIGITAL_DOWN,
        DIGITAL_LEFT,
        DIGITAL_RIGHT,
        DIGITAL_L1,
        DIGITAL_L2,
        DIGITAL_R1,
        DIGITAL_R2,
    };

    pros::ADIDigitalOut adi_ports[8] = {
        pros::ADIDigitalOut('A', false),
        pros::ADIDigitalOut('B', false),
        pros::ADIDigitalOut('C', false),
        pros::ADIDigitalOut('D', false),
        pros::ADIDigitalOut('E', false),
        pros::ADIDigitalOut('F', false),
        pros::ADIDigitalOut('G', false),
        pros::ADIDigitalOut('H', false),
    };

    pros::Mutex digitial_out_lock;
    std::vector<bool> digital_out_cmds(8, false);

    // Serial Port
    ghost_v5::V5SerialNode serial_node_("msg", true); // Becomes 109 w Checksum
} // namespace v5_globals

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C"
{
#endif
    void autonomous(void);
    void initialize(void);
    void disabled(void);
    void competition_initialize(void);
    void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
// #include <iostream>
#endif

#endif // _PROS_MAIN_H_
