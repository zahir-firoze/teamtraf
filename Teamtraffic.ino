#include "Particle.h"
#include "softap_http.h"
//#include "ChainableLED.h"
//#define NUM_LEDS 1
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);
bool hasped;
//ChainableLED leds(D2,D3, NUM_LEDS);
void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  //leds.setColorRGB(0, 0, 255, 0);
  Serial.begin(9600);
  //Serial.println("Serial up");
  System.set(SYSTEM_CONFIG_SOFTAP_PREFIX, "TeamTraffic");
  WiFi.listen();

}
void loop(){
  //Serial.println("Serial loop");
  if (hasped) {
    //leds.setColorRGB(0, 255, 0, 0);
    digitalWrite(D4,LOW);
    digitalWrite(D5,HIGH);
    delay(25*1000);
    hasped = false;
  }
  digitalWrite(D5,LOW);
  digitalWrite(D4,HIGH);
  delay(25*1000);
}

void myPages(const char* url, ResponseCallback* cb, void* cbArg, Reader* body, Writer* result, void* reserved) {
      if (!stricmp(url, "/traffic_info")) {
        // send the response code 200, the mime type "text/html"
        cb(cbArg, 0, 200, "text/html", nullptr);
        // send the page content
        result->write("<p>Has pedestrian: ");
        result->write(hasped? "Yes": "No");
        result->write("</p>");
        return;
      }
      // send the response code 200, the mime type "text/html"
      cb(cbArg, 0, 200, "text/html", nullptr);
      // send the page content
      result->write("<h2>hello world!</h2>");
      hasped = true;
}

STARTUP(softap_set_application_page_handler(myPages, nullptr));
