#include "DeviceGUI.h"
#include "DisplayDriver.h"
#include "lvgl.h"
#include "ui.h" // this is the lvgl ui generated by squareline editor; set build flag -I to its location in the platformio.ini variant
#include "Arduino.h"  // Serial

DeviceGUI::DeviceGUI(DisplayDriver* driver) : displaydriver(driver) {
}

void DeviceGUI::init(IClientBase* client) {
    Serial.println("UI init...");
    ui_init();
}

void DeviceGUI::task_handler(void) { 
    displaydriver->task_handler();
};
