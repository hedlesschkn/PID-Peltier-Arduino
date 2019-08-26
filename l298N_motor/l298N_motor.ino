/*
 * Motor Driver with L298N H bridge
 * 
 * this sketch assumes the motor is connected as follows:
 * OUT1 = Motor +
 * OUT2 = Motor -
 * ENA is jumpered active 
 *    note: the 'correct way to drive an L298N is to 
 *    PWM the enable pin and digitally set IN1 and IN2 HIGH/LOW.
 *    I found you get much more output granularity doing
 *    it this way instead, plus you save one wire.
 * 
 * IN1 to Arduino D10 (pwm)
 * IN2 to Arduino D11 (pwm)
 * GND shared between hbridge and arduino
 */

#define in1 10
#define in2 11

int rotDirection = 1; //direction 0=CW 1=CCW
int rotSpeed = 100; //speed 0-100%
int pwmOutput = 0;

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //set initial totation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() {
  
  pwmOutput = map(rotSpeed, 0, 100, 0, 255); //map totation speed from 0-100% to 0-255 pwm
  if(rotDirection == 0){
    //Serial.println("CW");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(in2, pwmOutput);
  }
  if(rotDirection == 1){
    //Serial.println("CCW");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(in1, pwmOutput);
  }
  delay(100);
}
