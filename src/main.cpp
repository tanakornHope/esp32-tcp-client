#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
// Use WiFiClient class to create TCP connections
WiFiClient client;

int incommingCount = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  // WiFiMulti.addAP("Orbi The Gentry", "Virus@coth");
  WiFiMulti.addAP("Hope's Hotspot", "0813556103");

  Serial.println();
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  const uint16_t port = 43000;
  const char *host = "52.163.210.190"; // ip or dns

  Serial.print("Connecting to ");
  Serial.println(host);

  while (!client.connect(host, port))
  {
    Serial.println("Connection failed.");
    Serial.println("Waiting 5 seconds before retrying...");
    delay(5000);
    return;
  }
  client.print("This message comes from ESP32 client.");

  delay(500);
}

void loop()
{
  // This will send a request to the server
  // uncomment this line to send an arbitrary string to the server
  // uncomment this line to send a basic document request to the server
  // client.print("GET /index.html HTTP/1.1\n\n");

  int maxloops = 0;

  // wait for the server's reply to become available
  /* while (!client.available() && maxloops < 1000)
  {
    maxloops++;
    delay(1); //delay 1 msec
  } */
  if (client.available() > 0)
  {
    // read back one line from the server
    incommingCount++;
    String line = client.readStringUntil('\r');
    Serial.printf("%s\n", line.c_str());
    char *buffer;
    asprintf(&buffer, "This message comes from ESP32 client %d", incommingCount);
    client.print(buffer);
  }
  else
  {
    // Serial.println("client.available() timed out ");
  }

  // client.stop();
  // delay(1000);
}