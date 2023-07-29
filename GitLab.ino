const bool GITLAB_DEBUG_LOG_ON = false && GLOBAL_DEBUG_LOG_ON;

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, host, httpsPort);

String GetResponse(String url) {
  client.get(url + "/pipelines");

  int statusCode = client.responseStatusCode();

  if (statusCode >= 200 && statusCode < 240) {
    String response = client.responseBody();
    return response;
  } else {
    Serial.println("error on request: " + String(statusCode));
    return "";
  }
}

PipelineState getPipelineStatus(String url) {
  if (GITLAB_DEBUG_LOG_ON) {
    Serial.println("start getting status");
  }
  String response = GetResponse(url);

  if (GITLAB_DEBUG_LOG_ON) {
    Serial.println("end getting status");
  }
  return convertResponse(response);
}

PipelineState convertResponse(String response) {
  if (GITLAB_DEBUG_LOG_ON) {
    Serial.println("start converting response");
  }
  DynamicJsonDocument jsonBuffer(2048);
  deserializeJson(jsonBuffer, response);

  int id = jsonBuffer[0]["id"];
  const char* status = jsonBuffer[0]["status"];

  if (GITLAB_DEBUG_LOG_ON) {
    Serial.println("id: " + id);
  }
  Serial.println("status: " + String(status));

  PipelineState result = UNKNOWN;
  if (strcmp(status, "success") == 0) {
    result = PASSED;
  } else if (strcmp(status, "failed") == 0) {
    result = FAILED;
  } else if (strcmp(status, "running") == 0) {
    result = RUN;
  }

  if (GITLAB_DEBUG_LOG_ON) {
    Serial.println("end converting response");
    Serial.println("---------------------------------------");
  }
  // return result;
  return FAILED;
}
