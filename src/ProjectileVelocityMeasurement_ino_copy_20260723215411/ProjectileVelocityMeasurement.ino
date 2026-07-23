/*
 * ==============================================================
 * Projectile Velocity Measurement System
 * --------------------------------------------------------------
 * Author   : Gavisht Karkara
 * Version  : v1.0
 * Year     : 2026
 *
 * Description:
 * Measures projectile velocity using two optical gates.
 * ESP32 records the travel time between Gate A and Gate B
 * with microsecond precision and displays the velocity on
 * an SH1106 OLED display.
 *
 * Formula:
 *      Velocity = Distance / Time
 *
 * Hardware:
 *  - ESP32 DevKit V1
 *  - SH1106 OLED Display (128x64)
 *  - Two Optical Gates
 *
 * ==============================================================
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// =====================================================
// OLED
// =====================================================

Adafruit_SH1106G display(128, 64, &Wire, -1);

// =====================================================
// Pin Definitions
// =====================================================

constexpr uint8_t GATE_A_PIN = 18;
constexpr uint8_t GATE_B_PIN = 19;

constexpr uint8_t SDA_PIN = 21;
constexpr uint8_t SCL_PIN = 22;

// =====================================================
// Constants
// =====================================================

constexpr float GATE_DISTANCE_METERS = 0.15f;

constexpr unsigned long DISPLAY_TIME_MS = 5000;
constexpr unsigned long MIN_VALID_TIME_US = 100;
constexpr unsigned long MAX_VALID_TIME_US = 5000000;

// =====================================================
// Firmware Info
// =====================================================

const char* firmwareVersion = "v1.0";

// =====================================================
// Variables
// =====================================================

bool measurementInProgress = false;

unsigned long gateATime = 0;

int previousGateAState;
int previousGateBState;

// =====================================================
// Display Functions
// =====================================================

void showSplashScreen()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(5,10);
  display.println("Projectile Velocity");

  display.setCursor(25,25);
  display.println("Measurement");

  display.setCursor(45,40);
  display.println("System");

  display.setCursor(35,55);
  display.print("FW ");
  display.print(firmwareVersion);

  display.display();

  delay(2000);
}

void showReadyScreen()
{
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("Projectile Velocity");

  display.setCursor(0,18);
  display.println("Status:");

  display.setCursor(55,18);
  display.println("READY");

  display.setCursor(0,40);
  display.println("Waiting for Gate A");

  display.display();
}

void showMeasuringScreen()
{
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("Measurement Started");

  display.setCursor(0,25);
  display.println("Waiting for Gate B...");

  display.display();
}

void showVelocity(float velocity, unsigned long travelTime)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("Velocity");

  display.setTextSize(2);
  display.setCursor(0,18);
  display.print(velocity,1);
  display.print(" m/s");

  display.setTextSize(1);

  display.setCursor(0,46);
  display.print("Time : ");
  display.print(travelTime);
  display.print(" us");

  display.setCursor(0,56);
  display.print("Dist : 15 cm");

  display.display();
}

void showError(const char* message)
{
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.println("ERROR");

  display.setCursor(0,20);
  display.println(message);

  display.display();

  delay(2000);
}

// =====================================================
// Setup
// =====================================================

void setup()
{
  Serial.begin(115200);

  pinMode(GATE_A_PIN, INPUT);
  pinMode(GATE_B_PIN, INPUT);

  Wire.begin(SDA_PIN, SCL_PIN);

  display.begin(0x3C, true);

  previousGateAState = digitalRead(GATE_A_PIN);
  previousGateBState = digitalRead(GATE_B_PIN);

  showSplashScreen();
  showReadyScreen();

  Serial.println();
  Serial.println("=====================================");
  Serial.println("Projectile Velocity Measurement");
  Serial.print("Firmware : ");
  Serial.println(firmwareVersion);
  Serial.println("System Ready");
  Serial.println("=====================================");
}

// =====================================================
// Main Loop
// =====================================================

void loop()
{
  int currentGateAState = digitalRead(GATE_A_PIN);
  int currentGateBState = digitalRead(GATE_B_PIN);

  // ---------------------------------------------------
  // Detect Gate A
  // ---------------------------------------------------

  if (!measurementInProgress &&
      currentGateAState != previousGateAState)
  {
    measurementInProgress = true;

    gateATime = micros();

    showMeasuringScreen();

    Serial.println();
    Serial.println("Gate A Triggered");
  }

  // ---------------------------------------------------
  // Detect Gate B
  // ---------------------------------------------------

  if (measurementInProgress &&
      currentGateBState != previousGateBState)
  {
    unsigned long gateBTime = micros();

    unsigned long travelTime = gateBTime - gateATime;

    if (travelTime < MIN_VALID_TIME_US)
    {
      showError("False Trigger");

      Serial.println("False Trigger");

      measurementInProgress = false;

      showReadyScreen();

      return;
    }

    if (travelTime > MAX_VALID_TIME_US)
    {
      showError("Timeout");

      Serial.println("Measurement Timeout");

      measurementInProgress = false;

      showReadyScreen();

      return;
    }

    float velocity =
      GATE_DISTANCE_METERS /
      (travelTime / 1000000.0f);

    // ---------------- Serial Output ----------------

    Serial.println("------------------------------");

    Serial.print("Travel Time : ");
    Serial.print(travelTime);
    Serial.println(" us");

    Serial.print("Velocity    : ");
    Serial.print(velocity,3);
    Serial.println(" m/s");

    Serial.println("------------------------------");

    showVelocity(velocity, travelTime);

    delay(DISPLAY_TIME_MS);

    measurementInProgress = false;

    showReadyScreen();
  }

  previousGateAState = currentGateAState;
  previousGateBState = currentGateBState;

  delay(1);
}