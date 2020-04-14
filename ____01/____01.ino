#include <Ethernet2.h>

byte mac[] = { 0xA8, 0x61, 0x0A, 0xAE, 0x50, 0x49 }; // Your Ethernet Shield MAC Address
IPAddress ip(192, 168, 0, 15);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip, gateway, subnet);
  }
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println ();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=10; i>0; i--)
  {
    Serial.println(i);
    delay(1000);
  }
  
  if ( client.connect("maker.ifttt.com", 80) )
  {
    Serial.println("connected");
    // POST request
    String requestBody = String("{\"value1\":\"Hello, World!\"}");
    int bodyLength = requestBody.length();
    String requestHead1 = "POST /trigger/[EventName]/with/key/[YourKey] HTTP/1.1\r\n" +
                          String("Host: maker.ifttt.com\r\n") +
                          "Content-Type: application/json\r\n";
    String requestHead2 = "Content-Length: " + String(bodyLength) + "\r\n" + "\r\n";
    client.print(requestHead1 + requestHead2 + requestBody);
    delay( 1000 );
    Serial.println("--- request ---");
    Serial.println(requestHead1 + requestHead2 + requestBody);
    Serial.println("---------------");
    Serial.println("Sent message");
  }
  else
  {
    Serial.println("Error: Could not make a TCP connection");
  }
  Serial.println("--- response ---");
  while (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
  Serial.println("----------------");
  if (!client.connected())
  {
    client.stop();
  }
}
