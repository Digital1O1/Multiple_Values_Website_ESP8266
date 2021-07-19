#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include "index.h" //Our HTML webpage contents with javascripts
#define LED 5      //On board LED

ESP8266WebServer server(80);

int count; // global counter for diagnostics

//SSID and Password of your WiFi router
const char *ssid = "ATT7RT97i2";
const char *password = "f3y436pwzu6y";

//===================================================================
// This routine is executed when you open a browser at the IP address
//===================================================================
void handleRoot()
{
  String s = MAIN_page;             //Display HTML contents
  server.send(200, "text/html", s); //Send web page
}

void value1()
{ // This function is called by the script to update the sensor value, in this example random data!
  String randomNum_value = String((float)random(1, 300) / 10, 2);
  server.send(200, "text/plain", randomNum_value); //Send sensor reading when there's a client ajax request
}

void value2()
{                                                                          // This function is called by the script to update the sensor value, in this example random data!
  server.send(200, "text/plain", String((float)random(501, 523) / 10, 2)); //Send sensor reading when there's a client ajax request
}

void value3()
{                                                                              // This function is called by the script to update the sensor value, in this example random data!
  server.send(200, "text/plain", String((float)random(10161, 10169) / 10, 2)); //Send sensor reading when there's a client ajax request
}
void handleLED()
{
  String ledState = "OFF";
  String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.print("LED State : ");
  Serial.println(t_state);
  if (t_state == "1")
  {
    digitalWrite(LED, HIGH); //LED ON
    ledState = "ON";         //Feedback parameter
  }
  else
  {
    digitalWrite(LED, LOW); //LED OFF
    ledState = "OFF";       //Feedback parameter
  }

  server.send(200, "text/plane", ledState); //Send web page
}
void setup(void)
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);        // Connect to your wifi
  WiFi.begin(ssid, password); // Start the Wi-Fi services

  //Onboard LED port Direction output
  pinMode(LED, OUTPUT);

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.print(".");
  } // Wait for WiFi to connect
  Serial.println("\nConnected to : " + String(ssid));
  Serial.print("Use IP address: ");
  Serial.println(WiFi.localIP()); //IP address assigned to your ESP
  //----------------------------------------------------------------
  server.on("/", handleRoot); // This displays the main webpage, it is called when you open a client connection on the IP address using a browser
  server.on("/setLED", handleLED);
  server.on("/value1", value1); // To update Temperature called by the function getSensorData
  server.on("/value2", value2); // To update Humidity called by the function getSensorData
  server.on("/value3", value3); // To update Pressure called by the function getSensorData
  //----------------------------------------------------------------
  server.begin(); // Start the webserver
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient(); // Keep checking for a client connection
  if (millis() % 5000 == 0)
  {
    count++;
    Serial.println(count);
  } // Display a serial diagnostic print to check its running
  delay(1);
}