int ThermistorPin = 0;
int Vo;
float R1 = 2200;
float logRt, Rt;
float Tk, Tf, Tc;

//B57861S0202F040
//5C = 4581
//25C = 2000
//45C = 960.3
//https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
float A = 1.245666056e-03, B = 2.715623937e-04, C = 1.007238670e-07;

//float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;
//float T,logRt,Tf,Tc;
//
//float Thermistor(int Vo) {
// logRt = log(10000.0*((1024.0/Vo-1))); 
// T = (1.0 / (A + B*logRt + C*logRt*logRt*logRt));  // We get the temperature value in Kelvin from this Stein-Hart equation
// Tc = T - 273.15;                     // Convert Kelvin to Celcius
// Tf = (Tc * 1.8) + 32.0;              // Convert Kelvin to Fahrenheit
// return T;
//}

void setup() {
  Serial.begin(9600);
}

void loop() {
//  float ADC;
//
//  ADC = analogRead(ThermistorPin);
//  Thermistor(ADC);
//  // put your main code here, to run repeatedly:
//  Serial.print("Temperature: ");
//  Serial.println(Tf);
//  //Serial.println("℉");
//  delay(100);
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
