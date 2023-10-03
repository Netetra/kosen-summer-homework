#include <LiquidCrystal.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>

double calculate_discomfort_index(double temp, double humid);
void led_set_color(int red, int green, int blue);
void print_lcd(String first_line, String second_line);

const int
DHT11_DATA_PIN = 0,
LED_PIN = 2,
LCD_WIDTH = 16,
LCD_HEIGHT = 2,
LCD_RS_PIN = 4,
LCD_ENABLE_PIN = 16,
LCD_D4_PIN = 17,
LCD_D5_PIN = 5,
LCD_D6_PIN = 18,
LCD_D7_PIN = 19;

LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
DHT dht(DHT11_DATA_PIN, DHT11);
Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);
  dht.begin();
  pixels.begin();
}

void loop() {
  double temp;
  double humid;
  double discomfort_index;
  char temp_line_buf[32];
  char humid_line_buf[32];

  print_lcd("Waiting...", "");
  led_set_color(0, 0, 0);
  delay(2000);

  while (true) {
    temp = dht.readTemperature();
    humid = dht.readHumidity();

    if (isnan(temp) || isnan(humid)) {
      print_lcd("Error!", "Restarting...");
      return;
    }

    discomfort_index = calculate_discomfort_index(temp, humid);

    if (discomfort_index <= 55) {
      led_set_color(0, 0, 128);
    }
    else if (55 < discomfort_index && discomfort_index <= 60) {
      led_set_color(0, 32, 128);
    }
    else if (60 < discomfort_index && discomfort_index <= 70) {
      led_set_color(128, 128, 128);
    }
    else if (70 < discomfort_index && discomfort_index <= 75) {
      led_set_color(128, 32, 32);
    }
    else if (75 < discomfort_index && discomfort_index <= 80) {
      led_set_color(128, 16, 16);
    }
    else if (80 < discomfort_index && discomfort_index <= 85) {
      led_set_color(128, 8, 8);
    }
    else {
      led_set_color(128, 0, 0);
    }

    sprintf(temp_line_buf,  "Temp: %.1lf'C",  temp);
    sprintf(humid_line_buf, "Humid: %.1lf%%", humid);
    print_lcd(temp_line_buf, humid_line_buf);

    delay(1000);
  }
}

double calculate_discomfort_index(double temp, double humid) {
  return 0.81 * temp + 0.01 * humid * (0.99 * temp - 14.3) + 46.3;
}

void led_set_color(int red, int green, int blue) {
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.show();
}

void print_lcd(String first_line, String second_line) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(first_line);
  lcd.setCursor(0, 1);
  lcd.print(second_line);
}
