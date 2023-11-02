const bool LED_DEBUG_LOG_ON = false && GLOBAL_DEBUG_LOG_ON;

CRGB leds[NUM_LEDS];
int brightness = 1;

int steps = 16;
int fadeAmount = (256 / steps); // 256 / Steps

bool areLedsOff = true;

void setupLeds() {
  Serial.begin(9600);

  if (LED_DEBUG_LOG_ON) {
    Serial.println("setup leds");
  }
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalPixelString);
  FastLED.setBrightness(BRIGHTNESS);
  setFailed();
  if (LED_DEBUG_LOG_ON) {
    Serial.println("---------------------------------------");
  }
}

void failedBlink() {
  if (LED_DEBUG_LOG_ON) {
    Serial.println("failedBlink");
  }

  if (areLedsOff) {
    setFailed();
  } else {
    cleanUp();
  }
  areLedsOff = !areLedsOff;
}

void runningBlink() {
  if (LED_DEBUG_LOG_ON) {
    Serial.println("runningBlink");
  }

  if (areLedsOff) {
    setRunning();
  } else {
    cleanUp();
  }
  areLedsOff = !areLedsOff;
}

void passedBlink() {
  if (LED_DEBUG_LOG_ON) {
    Serial.println("passedBlink");
  }

  setPassed();
  areLedsOff = !areLedsOff;
}

void wifiBlink() {
  if (LED_DEBUG_LOG_ON) {
    Serial.println("wifiBlink");
  }

  if (WiFi.status() != 3) {
    waitOnConnection();
  }
}

void cleanUp() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void setFailed() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

void setRunning() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Yellow;
  }
  FastLED.show();
}

void setPassed() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
  }
  FastLED.show();
}

void waitOnConnection() {
  if (LED_DEBUG_LOG_ON) {
    Serial.println("wait on connection");
  }

  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= steps || brightness >= (256 - steps)) fadeAmount = -fadeAmount;

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Cyan;
    leds[i].fadeToBlackBy(brightness);
    FastLED.show();
  }
}