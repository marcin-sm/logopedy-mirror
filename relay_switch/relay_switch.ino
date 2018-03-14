//Przykladowy kod wykorzystujacy statyczny adres IP prostego serwera opartego na ukladzie
//ESP8266 w module WEMOS D1
//Sterowanie mozliwe w zakresie sieci intranet


//zalaczenie bilbioteki mikrokontrolera
#include <ESP8266WiFi.h>

//deklaracja danych koniecznych do uzyskania polaczenia z routerem
const char* ssid = "UPC62DAB45"; 
const char* password = "Q85kaeduQdfb"; 

//okreslenie pinu sprzezonego modulem przekaznika

int relayPin = D2;
WiFiServer server(80);


IPAddress ip(192, 168, 0, 31); // ustawienie statycznego adresu IP
IPAddress gateway(10, 0, 0, 1); // ustawienie pasujacej bramki
IPAddress subnet(255, 255, 255, 0); // ustawienie maski podsieci

// pierwsza charakterystyczna dla mikrokontrolera funkcja incjalizujaca zmienne, predkosci transmisji,
//przeznaczenie wyprowadzen; wykonwana jednokrotnie
void setup() {
  Serial.begin(115200);
  delay(10);
 

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
 
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  //Polaczenie z lokalna siecia WIFI
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet); 
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
  if (!client) {
    return;
  }
 
  // oczekiwanie na informacje o polaczniu
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // odczytanie pierwszej linii zadania
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  //sprawdzenie aktualnego stanu przekaznika i zapamietanie poprzedniego
  int value = LOW;
  if (request.indexOf("/relay=ON") != -1) {
    digitalWrite(relayPin, LOW);
    value = LOW;
  } 
  if (request.indexOf("/relay=OFF") != -1){
    digitalWrite(relayPin, HIGH);
    value = HIGH;
  }
  // przedstawienie odpowiedzi na stronie HTML
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  pusty znak
  client.println("<!DOCTYPE HTML>"); //poczatek struktury HTML
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
  client.println("<a href=\"/relay=TOGGLE\"><img  style='background:url(http://moziru.com/images/makeup-clipart-border-4.png); background-size: 100%'  src='http://www.freeiconspng.com/uploads/power-button-icon-22.png' alt='Toogle'  > </a>");
  client.println("</mark></a></p><\h1></font></center></html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
