const bool URL_DEBUG_LOG_ON = false && GLOBAL_DEBUG_LOG_ON;

String ConvertUrl() {
  String url = apiVersion + "/projects/" + projectId;
  if (URL_DEBUG_LOG_ON) {
    Serial.println(url);
    Serial.println("---------------------------------------");
  }
  return url;
}