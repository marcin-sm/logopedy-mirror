#include <ESP8266WiFi.h>        //zalaczenie biblioteki obslugujacej WiFi w module ESP8266

//WARUNKI UPLOADU: D8 -> GND, D9 -> NULL

//deklaracja danych koniecznych do uzyskania polaczenia z routerem
const char* ssid = "UPC62DAB45"; 
const char* password = "Q85kaeduQdfb"; 

//okreslenie pinow sprzezonych z modulami przekaznikow
#define TVRelay D2
#define LightRelay D3
#define Lir D5
#define Rir D6


WiFiServer server(80);

//IPAddress ip(192, 168, 0, 31); // ustawienie statycznego adresu IP
//IPAddress gateway(10, 0, 0, 1); // ustawienie pasujacej bramki
//IPAddress subnet(255, 255, 255, 0); // ustawienie maski podsieci

//definicja stanu w zmiennej globalnej
boolean LightState = LOW;
boolean TVState = LOW;

// pierwsza charakterystyczna dla mikrokontrolera funkcja incjalizujaca zmienne, predkosci transmisji,
//przeznaczenie wyprowadzen; wykonwana jednokrotnie
void setup() {
  Serial.begin(74880);
  delay(10);
 
  pinMode(TVRelay, OUTPUT);
  pinMode(LightRelay, OUTPUT);
  
  pinMode(Lir,INPUT_PULLUP); 
  pinMode(Rir,INPUT_PULLUP);
  
  digitalWrite(TVRelay, HIGH);   
  digitalWrite(LightRelay, HIGH);
  
  //Serial.print(F("Setting static ip to : "));
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
  if (!client && digitalRead(Lir)==HIGH && digitalRead(Rir)==HIGH) {
    return;
  }
 
  // oczekiwanie na informacje o polaczniu
  //Serial.println("new request");
  
  while(!client.available() && digitalRead(Lir)==HIGH && digitalRead(Rir)==HIGH){
    delay(1);
  }
  String request;
  if(digitalRead(Lir)==LOW)
  {
    if(TVState)
    {
      request = "GET /TVRelay=OFF HTTP/1.1 200 OK";
    }
    else
    {
      request = "GET /TVRelay=ON HTTP/1.1 200 OK";
    }
  }
  else if(digitalRead(Rir)==LOW)
  {
    if(LightState)
    {
      request = "GET /LightRelay=OFF HTTP/1.1 200 OK";
    }
    else
    {
      request = "GET /LightRelay=ON HTTP/1.1 200 OK";
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
  
  if (request.indexOf("/TVRelay=ON") != -1) {
    digitalWrite(TVRelay, LOW);
    TVState = HIGH;
    delay(200);
  } 
  if (request.indexOf("/TVRelay=OFF") != -1){
    digitalWrite(TVRelay, HIGH);
    TVState = LOW;
    delay(200);
  }

  if (request.indexOf("/LightRelay=ON") != -1) {
    digitalWrite(LightRelay, LOW);
    LightState = HIGH;
    delay(200);
  } 
  if (request.indexOf("/LightRelay=OFF") != -1){
    digitalWrite(LightRelay, HIGH);
    LightState = LOW;
    delay(200);
  }
  
  // przedstawienie odpowiedzi na stronie HTML
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  pusty znak
  client.println("<!DOCTYPE HTML>"); //poczatek struktury HTML
  client.println("<html>");
 
  client.print("<body bgcolor='#000000'> <center> <font size='25' color='#ffffea'>	<h2>Black Mirror </h2> </font>");
 
  if(LightState == HIGH) {
    client.print("<a href=\"/LightRelay=OFF\"><img  style='background:url(http://moziru.com/images/makeup-clipart-border-4.png); background-size: 100%'  src='https://preview.ibb.co/gEVdVH/button.png'   width = '70%'  > </a>");  
  } else {
    client.print("<a href=\"/LightRelay=ON\"><img  src='https://preview.ibb.co/gEVdVH/button.png'  width = '70%'  > </a>");
  }

  if(TVState == HIGH) {
    client.print("<a href=\"/TVRelay=OFF\"><img  style='background:url(http://moziru.com/images/makeup-clipart-border-4.png); background-size: 100%'  src='https://preview.ibb.co/gEVdVH/button.png'   width = '70%'  > </a>");  
  } else {
    client.print("<a href=\"/TVRelay=ON\"><img  src='https://preview.ibb.co/gEVdVH/button.png'  width = '70%'  > </a>");
  }

  client.println(" </center></body></html>");
 
  delay(1);
  //Serial.println("Client disconnected");
  Serial.println("");
 
}
