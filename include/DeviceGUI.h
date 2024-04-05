#pragma once

#include <stdint.h>

class DisplayDriver;
class IClientBase;

/**
 * @brief DeviceGUI - this class hierarchy implements the view part of MVC
 *
 */
class DeviceGUI
{
  public:
    DeviceGUI(DisplayDriver *driver);
    virtual ~DeviceGUI();
    virtual void init(IClientBase *client);
    virtual void task_handler(void);
    virtual bool sleep(int16_t pin) { return false; }
    virtual void addNode(void) {}

  protected:
    DisplayDriver *displaydriver;
};
