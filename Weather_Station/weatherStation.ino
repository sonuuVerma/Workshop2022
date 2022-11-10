/*
 **
 ***Weather Station 
 **
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

bool statusBMP = false; // for BMP status
bool statusBME = false;

Adafruit_BME280 bme; // uses I2C communication protocol by default

Adafruit_BMP280 bmp; // I2C



void setup() {
  
  Serial.begin(115200);// to start serial communication not needed to display any thing on screen but for debugging purposes on serial monitor.
    
  statusBME = bme.begin(0x76);// address 0*76 passed to .begin method to start communication with bme sensor
  statusBMP = bmp.begin(0x76);// address 0*76 passed to .begin method to start communication with bme sensor

  
  if (statusBME) {
  Serial.println("BME sensor found");
  } 
  else if(statusBMP)
  {
  Serial.println("BMP280 sensor found");
    }
  else
  {
    Serial.println("Could not find a valid sensor, check wiring!");
  }

/*oled_setup*/
 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}


void printValues()
{
  float t = bme.readTemperature();
  float h = bme.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from sensor!");
  }

  //clear display
  display.clearDisplay();

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);//To display the º symbol, we use the Code Page 437 font.
  display.write(167);//º symbol corresponds to character 167.
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %"); 
  
  display.display();// need to call display object to actually dispaly something on screen    
}

void printValuesbmp()
{
  float t = bmp.readTemperature();
  float p = bmp.readPressure()/100;
  if (isnan(p) || isnan(t)) {
    Serial.println("Failed to read from sensor!");
  }

  //clear display
  display.clearDisplay();

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);//To display the º symbol, we use the Code Page 437 font.
  display.write(167);//º symbol corresponds to character 167.
  display.setTextSize(2);
  display.print("C");
  
  // display Pressure
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Pressure: ");
  display.setTextSize(1);
  display.setCursor(0, 45);
  display.print(p);
  display.print(" hPa"); 
  
  display.display();// need to call display object to actually dispaly something on screen    
}

void loop() {

  if(statusBME){
   printValues();
  }
  else if(statusBMP)
  {
    printValuesbmp();
  }
  else
  {
    Serial.println("no data fetch");
  }
  delay(1000);
  }

