#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>

#define PS2_DAT 12 // MISO  19
#define PS2_CMD 13 // MOSI  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18

#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13
#define PWM_CHANNEL7 14
#define PWM_CHANNEL8 15

PS2X ps2x;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWMMotors(int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8)
{
  char dbg_str[61];
  sprintf(dbg_str,"C1: %d\tC2: %d\tC3: %d\tC4: %d\tC5: %d\tC6: %d\tC7: %d\tC8: %d",c1,c2,c3,c4,c5,c6,c7,c8);
  Serial.println(dbg_str);

  pwm.setPWM(PWM_CHANNEL1, 0, c1);
  pwm.setPWM(PWM_CHANNEL2, 0, c2);
  pwm.setPWM(PWM_CHANNEL3, 0, c3);
  pwm.setPWM(PWM_CHANNEL4, 0, c4);
  pwm.setPWM(PWM_CHANNEL5, 0, c5);
  pwm.setPWM(PWM_CHANNEL6, 0, c6);
  pwm.setPWM(PWM_CHANNEL7, 0, c7);
  pwm.setPWM(PWM_CHANNEL8, 0, c8);
}

void setup() {
  Serial.begin(115200);

  Wire.begin();
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  setPWMMotors(0, 0, 0, 0, 0, 0, 0, 0);
  
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}

bool PS2control()
{
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0;

  setPWMMotors(c1, c2, c3, c4, c5, c6, c7, c8);
  return 1;
}

void loop() {
  ps2x.read_gamepad(0, 0);
  PS2control();
}
