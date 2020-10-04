#include "MAX30100_PulseOximeter.h"
#include <U8g2lib.h>
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
bool initialized=false;
int average_beat=0;
int average_SpO2=0;
int number_of_measures = 0;
int max_number_of_measures = 100;
int fallen_measures = 0;
int normality_threshold = 50;

boolean beat = false;
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void init_display() 
{
  if (not initialized) 
  {
    u8g2.clearBuffer();
    u8g2.setCursor(24,12);
    u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);
    u8g2.sendBuffer(); 
    initialized=true;
  }
}

void onBeatDetected()
{
  beat = true;
}

void display_status(String status)
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);
  u8g2.setCursor(1,12);  
  u8g2.print("Status:");
  u8g2.setCursor(10,30);  
  u8g2.print(status);
  u8g2.sendBuffer();
}


void display_beat() {
  u8g2.setFont(u8g2_font_cursor_tf);
  u8g2.setCursor(20,12);
  if (beat) {
    u8g2.print("_");
  } else {
    u8g2.print("^");  
  }
}

void display_place_finger() {
  display_status("Place finger!");
}

void display_values()
{
  u8g2.clearBuffer();
  display_beat();
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);
  u8g2.setCursor(65,12);  
  u8g2.print(average_beat);
  u8g2.print(" Bpm");
  u8g2.setCursor(0,30);
  u8g2.print("SpO2 ");
  u8g2.setCursor(65,30);  
  u8g2.print(average_SpO2);
  u8g2.print("%"); 
  u8g2.sendBuffer();
}

void display_starting() {
  display_status("Starting.");
  delay(300);
  display_status("Starting..");
  delay(300);
  display_status("Starting...");
  delay(300);
}

void init_pox() {
  if (!pox.begin()) {
    display_status("FAILED");
    for(;;);
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void setup()
{
  u8g2.begin();
  init_display();
  display_starting();
  delay(500);
  init_pox();
  display_place_finger();
}
 
void loop()
{
  // Make sure to call update as fast as possible
  pox.update();
  //    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
  if (number_of_measures >= max_number_of_measures) {
    average_beat = average_beat / number_of_measures;
    average_SpO2 = average_SpO2 / number_of_measures;

    if (average_SpO2 > normality_threshold && average_beat > normality_threshold) {
      display_values(); 
      beat = false;
      fallen_measures = 0;
    } else {
      fallen_measures++;
      if (fallen_measures > 10) {
        display_place_finger();
      }
    }
    number_of_measures = 0;
  }
  average_beat += pox.getHeartRate();
  average_SpO2 += pox.getSpO2();
  number_of_measures++;
        //tsLastReport = millis();
    //}

}
