//API key for Alpha Vantage server that the returns candle data from previous day (stock market data) 
//Finnhub API (more promising with realtime data) 

const char* FAPIKEY = ""; //Finnhub APIKEY for stocks real time date
const char* AVAPIKEY = "";//Alpha Vantage APIKEY for 
//Finnhub query sample for Apple
// "https://finnhub.io/api/v1/quote?symbol=AAPL&token=APIKEY"
// ----> {"c":218.27,"d":4.17,"dp":1.9477,"h":218.84,"l":211.28,"o":211.56,"pc":214.1,"t":1742587200}

//Response Attributes:
//c :Current price
//d: Change
//dp: Percent change
//h: High price of the day
//l: Low price of the day
//o: Open price of the day
//pc: Previous close price

//BTC "https://finnhub.io/api/v1/quote?symbol=BINANCE:BTCUSDT&token=APIKEY"
//ETH "https://finnhub.io/api/v1/quote?symbol=BINANCE:ETHUSDT&token=APIKEY"
//SPY "https://finnhub.io/api/v1/quote?symbol=INDEX:SPX&token=APIKEY"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 2

const char* ssid = ""; //WIFI name (I think it has to have 2.4GHz enabled)
const char* password = ""; //WIFI password

const char* finnhubQuery1 = "https://finnhub.io/api/v1/quote?symbol=";
const String finnhubQuery2 = "&token=" + String(FAPIKEY);

//Creating an array of the tickers that you want to display
const int numSymbols = 6;
String symbols[numSymbols] = {"SPY", "XLK", "VT", "BINANCE:BTCUSDT", "BINANCE:ETHUSDT", "GLDM"};

const size_t capacity = JSON_OBJECT_SIZE(8); //Number of objetcts that will be extracted from the JSON
StaticJsonDocument<capacity> doc;


//LED display for my setup. A strip of RGB leds with 64 columns and 8 rows.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(64, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //LED strip object definition
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[2]);

  //WIFI setup
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected!");
  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(10);
  matrix.setTextColor(colors[2]);
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  matrix.print(F("INTERNET?"));
  matrix.show();

  delay(1500);
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  matrix.print(F("CONECTADO!"));
  matrix.show();


}


void loop() {
  // put your main code here, to run repeatedly:
  matrix.setTextColor(colors[0]);
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure();

    for (const auto& symbol : symbols)  //Iterate over teh symbols
    {
      String data = "";
      String printsymbol = "";
      String query = finnhubQuery1 + symbol + finnhubQuery2;
      http.begin(client, query);
      int httpCode = http.GET();

      if (httpCode > 0)
      {
        data = http.getString();
        http.end();
        DeserializationError error = deserializeJson(doc, data);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }

        float currentPrice = doc["c"];
        String percentChange = doc["dp"];
        percentChange.remove(percentChange.length() - 1, 1); //remove last character


        Serial.print("The  current price of " + symbol + " is: $");
        Serial.println(currentPrice);
        Serial.print("Change: ");
        Serial.print(percentChange);
        Serial.println("%");

        if (percentChange[0] != '-')
        {percentChange = "+" + percentChange;
        matrix.setTextColor(colors[1]);}
        
        if (symbol == "BINANCE:BTCUSDT")
        {printsymbol = "BTC";}
        else if (symbol == "BINANCE:ETHUSDT")
        {printsymbol = "ETH";}
        if (symbol == "SPY")
        {printsymbol = "SPY";}
        else if (symbol == "XLK")
        {printsymbol = "XLK";}
        else if (symbol == "VT")
        {printsymbol = "VT";}
        else if (symbol == "GLDM")
        {printsymbol = "GLDM";}
        
        
        String screenPrint1 = printsymbol + ": $" + currentPrice;
        String screenPrint2 = percentChange + "%";

        for (int x = 64; x > -135; x--){
        matrix.fillScreen(0); 
        matrix.setCursor(x, 0);   
        matrix.print(screenPrint1 + " " + screenPrint2); 
  

        Serial.print(x);
        matrix.show();
        delay(40);
        }    


      }


      delay(100); //Delay between each display
      
      

    
    }
  }
}
