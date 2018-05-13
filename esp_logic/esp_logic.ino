#include <ESP8266WiFi.h>        //zalaczenie biblioteki obslugujacej WiFi w module ESP8266

//WARUNKI UPLOADU: D8 -> GND, D9 -> NULL

//deklaracja danych koniecznych do uzyskania polaczenia z routerem
const char* ssid = "UPC62DAB45"; 
const char* password = "Q85kaeduQdfb"; 

//okreslenie pinow sprzezonych z modulami przekaznikow

int relayPin = D2;
int relayPin2 = D3;

int sensorPin = D4;
int sensorPin2 = D5;

WiFiServer server(80);

//IPAddress ip(192, 168, 0, 31); // ustawienie statycznego adresu IP
//IPAddress gateway(10, 0, 0, 1); // ustawienie pasujacej bramki
//IPAddress subnet(255, 255, 255, 0); // ustawienie maski podsieci

//definicja stanu w zmiennej globalnej
boolean state = LOW;
boolean state2 = LOW;

// pierwsza charakterystyczna dla mikrokontrolera funkcja incjalizujaca zmienne, predkosci transmisji,
//przeznaczenie wyprowadzen; wykonwana jednokrotnie
void setup() {
  Serial.begin(74880);
  delay(10);
 
  pinMode(relayPin, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  
  pinMode(sensorPin,INPUT_PULLUP); 
  pinMode(sensorPin2,INPUT_PULLUP);
  
  digitalWrite(relayPin, HIGH);   
  digitalWrite(relayPin2, HIGH);
 
  //
  
  Serial.print(F("Setting static ip to : "));
  //Serial.println(ip);
  
  //Polaczenie z lokalna siecia WIFI
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  
  //Proba polaczenia sygnalizowana przez pojawiajace sie w terminalu kropki
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // ustawienie czasu oczekiwania na odpowiedz
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Informacja o rozpoczeciu polaczenia
  server.begin();
  Serial.println("Server started");
 
  // Wyswietlenie podstawowych parametrow polaczenia
  Serial.print("URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

// druga charakterystyczna dla mikrokontrolerow funkcja wykonywana cyklicznie
void loop() {
  // sprawdzanie polaczenia
  WiFiClient client = server.available();
  if (!client && digitalRead(sensorPin)==HIGH && digitalRead(sensorPin2)==HIGH) {
    return;
  }
 
  // oczekiwanie na informacje o polaczniu
  Serial.println("new client");
  while(!client.available() && digitalRead(sensorPin)==HIGH && digitalRead(sensorPin2)==HIGH){
    delay(1);
  }
  String request;
  if(digitalRead(sensorPin)==LOW)
  {
    if(state)
    {
      request = "GET /relay=OFF HTTP/1.1 200 OK";
    }
    else
    {
      request = "GET /relay=ON HTTP/1.1 200 OK";
    }
  }
  else if(digitalRead(sensorPin2)==LOW)
  {
    if(state2)
    {
      request = "GET /relay2=OFF HTTP/1.1 200 OK";
    }
    else
    {
      request = "GET /relay2=ON HTTP/1.1 200 OK";
    }
  }
  else
  {
  // odczytanie pierwszej linii zadania
  request = client.readStringUntil('\r');
  }
  Serial.println(request);
  client.flush();
 
  //sprawdzenie aktualnego stanu przekaznika i zapamietanie poprzedniego
  
  if (request.indexOf("/relay=ON") != -1) {
    digitalWrite(relayPin, LOW);
    state = HIGH;
    delay(200);
  } 
  if (request.indexOf("/relay=OFF") != -1){
    digitalWrite(relayPin, HIGH);
    state = LOW;
    delay(200);
  }

  if (request.indexOf("/relay2=ON") != -1) {
    digitalWrite(relayPin2, LOW);
    state2 = HIGH;
    delay(200);
  } 
  if (request.indexOf("/relay2=OFF") != -1){
    digitalWrite(relayPin2, HIGH);
    state2 = LOW;
    delay(200);
  }
  
  // przedstawienie odpowiedzi na stronie HTML
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  pusty znak
  client.println("<!DOCTYPE HTML>"); //poczatek struktury HTML
  client.println("<html>");
 
  client.print("<body bgcolor='#000000'> <center> <font size='25' color='#ffffea'>	<h2>Black Mirror </h2> </font>");
 
  if(state == HIGH) {
    client.print("<a href=\"/relay=OFF\"><img  style='background:url(http://moziru.com/images/makeup-clipart-border-4.png); background-size: 100%'  src='https://preview.ibb.co/gEVdVH/button.png'   width = '70%'  > </a>");  
  } else {
    client.print("<a href=\"/relay=ON\"><img  src='https://preview.ibb.co/gEVdVH/button.png'  width = '70%'  > </a>");
  }

  if(state2 == HIGH) {
    client.print("<a href=\"/relay2=OFF\"><img  style='background:url(http://moziru.com/images/makeup-clipart-border-4.png); background-size: 100%'  src='https://preview.ibb.co/gEVdVH/button.png'   width = '70%'  > </a>");  
  } else {
    client.print("<a href=\"/relay2=ON\"><img  src='https://preview.ibb.co/gEVdVH/button.png'  width = '70%'  > </a>");
  }

  client.println(" </center></body></html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
