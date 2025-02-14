//  This file contains a structure and functions for limiting and monitoring the FPS
//  Used when binary frames opened as video



#ifndef FPS_LIMITER
#define FPS_LIMITER
#include <Arduino.h>

struct FPSLimiter {
    unsigned long lastFrameTime = 0;
    unsigned long lastTime = 0;    
    unsigned long frameCount = 0;   
    unsigned long fps = 0;         
    int targetFPS;

    FPSLimiter(int fps) {
        targetFPS = fps; 
    }

    bool shouldRenderFrame() {
        unsigned long frameTime = 1000 / targetFPS;
        if (millis() - lastFrameTime < frameTime) {
            yield();
            return false; 
        }
        lastFrameTime = millis();
        return true; 
    }

    void updateFPS() {
        frameCount++;
        if (millis() - lastTime >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTime = millis();
            Serial.print("FPS: ");
            Serial.println(fps);
        }
    }
};




#endif