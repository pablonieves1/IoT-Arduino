//API key for Alpha Vantage server that the returns candle data from previous day (stock market data) 
//Finnhub API (more promising with realtime data) 

const char [] FAPIKEY = "" //Finnhub APIKEY for stocks real time date
const char [] AVAPIKEY = "" //Alpha Vantage APIKEY for 
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


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
