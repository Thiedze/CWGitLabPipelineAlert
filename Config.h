// LED config
#define DATA_PIN 3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 30
#define BRIGHTNESS 100

// wifi config
const char* ssid = "IoT";

//gitlab config
const char* host = "gitlab.com";
const int httpsPort = 443;

const String apiVersion = "/api/v4";
const String projectId = "4359271";
const int projectCount = 1;

enum PipelineState { UNKNOWN, FAILED, RUN, PASSED };

// update config
const int updateDelayMillis = 50000;
long lastUpdateMillis = 0;