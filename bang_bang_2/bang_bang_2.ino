//Thermistor
int ThermistorPin = 0;
int Vo;
float R1 = 2200;
float logRt, Rt;
float Tk, Tf, Tc;
float A = 1.245666056e-03, B = 2.715623937e-04, C = 1.007238670e-07;

//L298N
#define in1 10
#define in2 11
int rotDirection = 1; //direction 0=CW 1=CCW
int rotSpeed = 100; //speed 0-100%
int pwmOutput = 0;
int set_point = 80;
int output = 0;

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //set initial totation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() {
  if (getTempF() > set_point){
    sendL298N_nodir(100);
    output = 100;
  }
  else if (getTempF() < set_point){
    sendL298N_nodir(-100);
    output = -100;
  }
  else{
    sendL298N_nodir(0);
    output = 0;
  }
  delay(30);
  Serial.print(set_point);
  Serial.print(" | ");
  Serial.print(output);
  Serial.print(" | ");
  Serial.println(getTempF());
  
}

void sendL298N_nodir(int spd){
    pwmOutput = map(abs(spd), 0, 100, 0, 255); //map rotation speed from 0-100% to 0-255 pwm

  if(spd < 0){
    //Serial.println("CW");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(in2, pwmOutput);
  }
  if(spd > 0){
    //Serial.println("CCW");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(in1, pwmOutput);
  }
  //delay(100);
}

void printTemp(){
  Vo = analogRead(ThermistorPin);
  Rt = R1* (1023.0 / (float)Vo - 1.0);
  logRt = log(Rt);
  Tk = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  Tc =  Tk - 273.15; //Kelvin to Celcius
  Tf = (Tc * 1.8) + 32.0;
  
  Serial.print("Temp: ");
  Serial.print(Tf);
  Serial.print(" F | ");
  Serial.print(Tc);
  Serial.println(" C");
}

float getTempK(){
  Vo = analogRead(ThermistorPin);
  Rt = R1* (1023.0 / (float)Vo - 1.0);
  logRt = log(Rt);
  Tk = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));  // Steinhart and Hart Equation. T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  //Tc =  Tk - 273.15; //Kelvin to Celcius
  //Tf = (Tc * 1.8) + 32.0;
  return(Tk);
}

float getTempC(){
  Tk = getTempK();
  Tc =  Tk - 273.15; //Kelvin to Celcius
  //Tf = (Tc * 1.8) + 32.0;
  return(Tc);
}

float getTempF(){
  Tc =  getTempC();
  Tf = (Tc * 1.8) + 32.0;
  return(Tf);
}
