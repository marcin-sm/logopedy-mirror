//This example will use a static IP to control the switching of a relay. Over LAN using a web browser. 
//A lot of this code have been resued from the example on the ESP8266 Learning Webpage below. 
//http://www.esp8266learning.com/wemos-webserver-example.php

//CODE START 
//1
#include <ESP8266WiFi.h>

// Below you will need to use your own WIFI informaiton.
//2
const char* ssid = "UPC62DAB45"; //WIFI Name, WeMo will only connect to a 2.4GHz network.
const char* password = "Q85kaeduQdfb"; //WIFI Password

//defining the pin and setting up the "server"
//3
int relayPin = D2; // The Shield uses pin 1 for the relay
WiFiServer server(80);
IPAddress ip(192, 168, 0, 31); // where xx is the desired IP Address
IPAddress gateway(10, 0, 0, 1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network


// void setup is where we initialize variables, pin modes, start using libraries, etc. 
//The setup function will only run once, after each powerup or reset of the wemos board.
//4
void setup() {
  Serial.begin(115200);
  delay(10);
 

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  // Connect to WiFi network
  //5
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  //Trying to connect it will display dots
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

//void loop is where you put all your code. it is a funtion that returns nothing and will repeat over and over again
//6
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  //Match the request, checking to see what the currect state is
  int value = LOW;
  if (request.indexOf("/relay=ON") != -1) {
    digitalWrite(relayPin, LOW);
    value = LOW;
  } 
  if (request.indexOf("/relay=OFF") != -1){
    digitalWrite(relayPin, HIGH);
    value = HIGH;
  }
  // Return the response, build the html page
  //7
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("<center><font size='27'>Relay is now: ");
 
  if(value == HIGH) {
    client.print("Engaged (ON)");  
  } else {
    client.print("Disengaged (OFF)");
  }
  client.println("</font><br><br><br> <h1> <font size='100'>");
  client.println("<a href=\"/relay=ON\">ON</a> <br><br><br>");
  client.println("<a href=\"/relay=OFF\">OFF</a><br>");
  client.println("</mark></a></p><\h1></font></center></html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}//END
