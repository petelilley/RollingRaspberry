#include <RollingRaspberry/basic/robot.h>
#include <RollingRaspberry/network/nt_handler.h>

Robot::Robot() {
  NTHandler::get()->get_rasp_table()->PutBoolean("IsRunning", true);
}

Robot::~Robot() {
  NTHandler::get()->get_rasp_table()->PutBoolean("IsRunning", false);
}

void Robot::robot_process() {
  for (Subsystem* s : subsystems) {
    s->send_feedback();
  }
  vision.process();
}

void Robot::auto_init() {
  reset(NTHandler::MatchMode::AUTO);
}

void Robot::auto_process() { }

void Robot::teleop_init() {
  reset(NTHandler::MatchMode::TELEOP);
}

void Robot::teleop_process() { }

void Robot::disabled_init() {
  reset(NTHandler::MatchMode::DISABLED);
}

void Robot::disabled_process() { }

void Robot::test_init() {
  reset(NTHandler::MatchMode::TEST);
}

void Robot::test_process() { }

void Robot::reset(NTHandler::MatchMode mode) {
  for (Subsystem* s : subsystems) {
    s->reset_to_mode(mode);
  }
}
