//************************************************************
//
// has OTA support and can be updated remotely
//
//************************************************************
#include <painlessMesh.h>
#include "src/Network/Network.hpp"
#include "src/BoardAddress/BoardAddress.hpp"
#include "src/Motor/Motor.hpp"
#include "src/RemoteControl/RemoteControl.hpp"

Scheduler userScheduler; // to control your personal task

Task taskRemoteControl(TASK_SECOND * 1, TASK_FOREVER, &RemoteControl::run);
Task taskMotorControl(0, TASK_FOREVER, &Motor::run);

void setup()
{
  Serial.begin(115200);

  BoardAddress::init();

  if (BoardAddress::isRemoteControl)
  {
    RemoteControl::init();

    userScheduler.addTask(taskRemoteControl);
    taskRemoteControl.enable();
  }
  else
  {
    Motor::init();

    userScheduler.addTask(taskMotorControl);
    taskMotorControl.enable();
  }

  Network::init(&userScheduler);
}

void loop()
{
  // it will run the user scheduler as well
  Network::run();
}
