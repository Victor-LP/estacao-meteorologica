// bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <stdio.h>

DHT dht(2, DHT22);
Adafruit_BMP280 bmp;
int ana_0,ana_1;
float pressao,alt,tensao,temp,umid,VLDR,RLDR,lum;
bool first_time = true;
LiquidCrystal_I2C lcd(0x27,16,2);
byte mais_menos[] = {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00000,
  B11111,
  B00000
};
byte cedilha[] = {
  B00000,
  B01110,
  B10000,
  B10000,
  B10001,
  B01110,
  B00100,
  B01100
};
byte o_acentuado[] = {
  B00100,
  B01000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000
};
byte a_nasal[] = {
  B01010,
  B00101,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
  B00000
};
byte sol[] = {
  B00000,
  B00000,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00000
};
byte bom[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};
byte noite[] = {
  B00000,
  B00000,
  B01100,
  B00110,
  B00010,
  B00110,
  B01100,
  B00000
};

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.begin(9600);
  bmp.begin(0x76);
  dht.begin();
  lcd.createChar(0, mais_menos);
  lcd.createChar(1, cedilha);
  lcd.createChar(2,o_acentuado);
  lcd.createChar(3,a_nasal);
  lcd.createChar(4,sol);
  lcd.createChar(5,bom);
  lcd.createChar(6,noite);
  analogReference(INTERNAL);
}

void loop(){
  if (first_time) {
    lcd.setCursor(0,0);
    lcd.print("Esta");
    lcd.write(1);
    lcd.write(3);
    lcd.print("o");
    lcd.setCursor(0,1);
    lcd.print("Meteorol");
    lcd.write(2);
    lcd.print("gica");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Instrumenta");
    lcd.write(1);
    lcd.write(3);
    lcd.print("o");
    lcd.setCursor(0,1);
    lcd.print("e Medi");
    lcd.write(1);
    lcd.write(3);
    lcd.print("o");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ca");
    lcd.write(1);
    lcd.print("a Meteoros");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BrunoB,GabrielM");
    lcd.setCursor(0,1);
    lcd.print("VictorL");
    delay(3000);
    lcd.clear();
    first_time = false;
  }
  //Ler e exibir Pressão
  alt= bmp.readAltitude(1013.25);
  pressao=bmp.readPressure();
  pressao=pressao/100;
  lcd.setCursor(0,0);
  lcd.print("Press");
  lcd.write(3);
  lcd.print("o");
  lcd.setCursor(0,1);
  lcd.print(pressao,2);  // Escreve no LCD
  lcd.print(" ");
  lcd.write(0);
  lcd.print("0.12");
  lcd.print(" hPa");
  delay(3000);
  //Altitude
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Altitude");  // posiciona o cursor
  lcd.setCursor(0,1);
  lcd.print(alt,1);  // Escreve no LCD
  lcd.print(" ");
  lcd.write(0);
  lcd.print("1.0");
  lcd.print(" m");  // Escreve no LCD
  delay(3000);

  //Ler e exibir Temperatura
  ana_0 = analogRead(A0);
  tensao = ana_0*(1.1/1024);
  temp = tensao*100;
  temp = temp*0.98+0.45;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura");
  lcd.setCursor(0,1);
  lcd.print(temp,1);
  lcd.print(" ");
  lcd.write(0);
  lcd.print("0.5");
  lcd.print(" ");
  lcd.write(byte(223));  // código do caractere "°"
  lcd.print("C");
  delay(3000);

  //Ler e exibir umidade
  umid = dht.readHumidity();
  umid = umid*0.74-9.83;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidade relativa");
  lcd.setCursor(0, 1);
  lcd.print(umid,1);
  lcd.print(" ");
  lcd.write(0);
  lcd.print("2.0");
  lcd.print(" %");
  delay(3000);

  //Ler e exibir Luminosidade
  ana_1 = analogRead(A1);
  VLDR = ana_1*1.1/1024.0;
  RLDR = VLDR/(3.3 - VLDR)*45900;
  lum = pow(10,-1.386*log10(RLDR)+6.693);
  if (lum>=1000){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luminosidade");
  lcd.setCursor(0, 1);
  lcd.print(lum,2);
  lcd.print(" lx ");
  lcd.write(4);
  delay(3000);
  }
  else if (lum>=300){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luminosidade");
  lcd.setCursor(0, 1);
  lcd.print(lum,2);
  lcd.print(" lx ");
  lcd.write(5);
  delay(3000);
  }
  else{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Luminosidade");
  lcd.setCursor(0, 1);
  lcd.print(lum,2);
  lcd.print(" lx ");
  lcd.write(6);
  delay(3000);
  }

  lcd.clear();
}