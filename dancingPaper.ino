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

void setup()
{
  Serial.begin(115200);

  BoardAddress::init();
  Motor::init();
  Network::init(&userScheduler);

  if (BoardAddress::isRemoteControl)
  {
    RemoteControl::init();

    userScheduler.addTask(taskRemoteControl);
    taskRemoteControl.enable();
  }
}

void loop()
{
  // it will run the user scheduler as well
  Network::run();
  Motor::run();
}
