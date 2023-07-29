#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <Thread.h>

#include "FastLED.h"

#include "Config.h"
#include "Secrets.h"

const bool GLOBAL_DEBUG_LOG_ON = true;

PipelineState state = UNKNOWN;

void failedBlinkCallback() {
  if (state == FAILED) {
    if (GLOBAL_DEBUG_LOG_ON) {
      Serial.println("failedBlinkCallback");
    }
    failedBlink();
  }
}

void runningBlinkCallback() {
  if (state == RUN) {
    if (GLOBAL_DEBUG_LOG_ON) {
      Serial.println("runningBlinkCallback");
    }
    runningBlink();
  }
}

void passedBlinkCallback() {
  if (state == PASSED) {
    if (GLOBAL_DEBUG_LOG_ON) {
      Serial.println("passedBlinkCallback");
    }
    passedBlink();
  }
}

void wifiBlinkCallback() {
  if (WiFi.status() != 3) {
    if (GLOBAL_DEBUG_LOG_ON) {
      Serial.println("wifiBlinkCallback");
    }
    wifiBlink();
  }
}


/*
Thread wifiThread(wifiBlinkCallback, 10, 0, MILLIS);
Thread statusThread(checkPipelineStatusCallback, 20000, 0, MILLIS);
Thread failedThread(failedBlinkCallback, 350, 0, MILLIS);
Thread runningThread(runningBlinkCallback, 3000, 0, MILLIS);
Thread passedThread(passedBlinkCallback, 20000, 0, MILLIS);
*/

Thread wifiThread = Thread();
Thread statusThread = Thread();
Thread failedThread = Thread();
Thread runningThread = Thread();
Thread passedThread = Thread();

String requestUrl;


void setup() {
  Serial.begin(9600);

  while (!Serial) {}

  delay(5000);

  setupLeds();
  setupWifi();

  requestUrl = ConvertUrl();

  wifiThread.onRun(wifiBlinkCallback);
  wifiThread.setInterval(10);

  statusThread.onRun(checkPipelineStatusCallback);
  statusThread.setInterval(20000);

  failedThread.onRun(failedBlinkCallback);
  failedThread.setInterval(350);

  runningThread.onRun(runningBlinkCallback);
  runningThread.setInterval(3000);

  passedThread.onRun(passedBlinkCallback);
  passedThread.setInterval(20000);
}

void checkPipelineStatusCallback() {
  if (GLOBAL_DEBUG_LOG_ON) {
    Serial.println("checkPipelineStatusCallback");
    Serial.print("wifi status: " + String(WiFi.status()));
    Serial.println(" url: " + requestUrl);
  }

  if (WiFi.status() == 3 && requestUrl.length() > 0) {
    state = getPipelineStatus(requestUrl);

    /*switch (state) {
      case FAILED:
        // Serial.println("failed");
        handleTicker(failedTicker, runningTicker, passedTicker);
        break;
      case RUN:
        // Serial.println("running");
        handleTicker(runningTicker, failedTicker, passedTicker);
        break;
      case PASSED:
        // Serial.println("passed");
        handleTicker(passedTicker, failedTicker, runningTicker);
        break;
    }*/
  }
}

void loop() {
  if (statusThread.shouldRun()) {
    statusThread.run();
  }

  if (failedThread.shouldRun()) {
    failedThread.run();
  }

  if (runningThread.shouldRun()) {
    runningThread.run();
  }

  if (passedThread.shouldRun()) {
    passedThread.run();
  }

  if (wifiThread.shouldRun()) {
    wifiThread.run();
  }
}