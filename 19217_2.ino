#include <Arduino.h>
const int adcPin = A0;

// calculate your own m using ph_calibrate.ino
// When using the buffer solution of pH4 for calibration, m can be derived as:
// m = ( pH9.9  - pH7.5) / (Vph9.9 - Vph7.5)
/*  ( 9.9 - 7.5 ) / ( 2.227 - 2.212 ) = ( 22.4299065 )*/
/*const float m = -5.436;*/
const float m = 22.4299065;

int x = 0;
int last = 0;
int redVB = 2;
int greenVB = 3;
int vbPin = 6;

//int pH_Value;
//float VoltagePH;
int redPH = 4;
int greenPH = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (redPH, OUTPUT);
  pinMode (greenPH, OUTPUT);
//  pinMode(pH_Value, INPUT);
  pinMode(vbPin, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  phReading();
  vibReading();
}
void phReading()
{
  float Po = analogRead(adcPin) * 5.0 / 1024;
  float phValue = 9.9 - (2.227 - Po) * m;
  Serial.print("ph value = "); Serial.println(phValue);
  delay(5000);
  //  pH_Value = analogRead(A0);
  //  VoltagePH = pH_Value * (5.0 / 1023.0);
  //  Serial.println(VoltagePH);
  if (phValue >= 7.5)
  {
    digitalWrite (greenPH, HIGH);
    digitalWrite (redPH, LOW);
  }
  else if (phValue <= 9.5 )
  {
    digitalWrite (redPH, LOW);
    digitalWrite(greenPH, HIGH);
  }
  else if (phValue >= 10)
  {
    digitalWrite (redPH, HIGH);
  }
}

void vibReading()
{
  int digitalVal = digitalRead(vbPin);
  if (digitalVal == HIGH)
  {
    if (last == 0)
    {
      x++;
    }
    else
    {
      x = 0;
    }
    last = 1;
  }
  else
  {
    if (last == 1)
    {
      x++;
    }
    else
    {
      x = 0;
    }
    last = 0;
  }
  Serial.println(x);
  delay(1000);
  if (x > 150)
  {
    digitalWrite (greenVB, LOW);
    digitalWrite (redVB, HIGH);
  }
  else if (x >= 100)
  {
    digitalWrite (redVB, LOW);
    digitalWrite(greenVB, HIGH);
  }
  else
  {
    digitalWrite (redVB, HIGH);
    digitalWrite(greenVB, LOW);
  }
}
