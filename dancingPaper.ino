//************************************************************
//
// has OTA support and can be updated remotely
//
//************************************************************
#include <painlessMesh.h>
#include "src/Network/Network.hpp"
#include "src/BoardAddress/BoardAddress.hpp"
#include "src/Motor/Motor.hpp"

Scheduler userScheduler; // to control your personal task


//Task taskModeMotorControl(TASK_SECOND * 1, TASK_FOREVER, &Motor::run);

void setup()
{
  Serial.begin(115200);

  BoardAddress::init();
  Motor::init();
  Network::init(&userScheduler);

  // userScheduler.addTask(taskSendMessage);
  // userScheduler.addTask(taskModeMotorControl);

  // //if(digitalRead(SENSE_CONTROLLER_PIN) == LOW)
  // taskModeController.enable();
  // //else
  // taskModeMotorControl.enable();

  // taskSendMessage.enable();
}

void loop()
{
  // it will run the user scheduler as well
  Network::run();
  Motor::run();
}
