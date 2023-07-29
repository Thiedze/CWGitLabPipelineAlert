const bool WIFI_DEBUG_LOG_ON = false && GLOBAL_DEBUG_LOG_ON;

void setupWifi() {
  if (WIFI_DEBUG_LOG_ON) {
    Serial.print("attempting to connect to network: ");
    Serial.println(ssid);
  }

  WiFi.begin(ssid, pass);

  delay(10000);

  if (WIFI_DEBUG_LOG_ON) {
    Serial.println("you're connected to the network");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP());

    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);
    Serial.println("---------------------------------------");
  }
}
