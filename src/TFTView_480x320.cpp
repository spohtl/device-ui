#ifdef VIEW_480x320

#include "TFTView_480x320.h"
#include <cstdio>
#include <ctime>
#include <functional>
#include "Arduino.h"
#include "ui.h" // this is the ui generated by lvgl / squareline editor
#include "ViewController.h"

#ifdef USE_X11
#include "X11Driver.h"
#elif defined (LGFX_DRIVER_INC)
#include "LGFXDriver.h"
#include LGFX_DRIVER_INC
#else
#error "Unknown device for view 480x320"
#endif


TFTView_480x320* TFTView_480x320::gui = nullptr;

TFTView_480x320* TFTView_480x320::instance(void) {
    if (!gui) gui = new TFTView_480x320;
    return gui;
}


#ifdef USE_X11
TFTView_480x320::TFTView_480x320() : MeshtasticView(&X11Driver::create(), new ViewController) {
}
#else
TFTView_480x320::TFTView_480x320() : MeshtasticView(new LGFXDriver<LGFX_DRIVER>(screenWidth, screenHeight), 
                                               new ViewController) {
}
#endif

void TFTView_480x320::init(IClientBase* client) {
    Serial.println("TFTView init...");
    displaydriver->init();
    MeshtasticView::init(client);
}

void TFTView_480x320::task_handler(void) {
    MeshtasticView::task_handler();
}

#endif