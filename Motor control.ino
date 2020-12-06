const double motorPin = 11;
const double potPin = A0;
const double delayTime = 5;
const double maxValue = 1023;
const double minValue = 496;
const double midRange = 0.1;
double val;

void setup()
{
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
}

void loop()
{ 
  
  val = (analogRead(potPin) - minValue) / (maxValue - minValue) + 1;

  Serial.println(analogRead(potPin));
  if(val > 2){
    val = 2;
  }
  if(val < 1){
    val = 1;
  }
  if(val < 1.5 + midRange && val > 1.5 - midRange){
    val = 1.5; 
  }
  else

  
  Serial.println(val);
  digitalWrite(motorPin, HIGH);
  delayMicroseconds(val * 1000);
  
  digitalWrite(motorPin, LOW);
  delayMicroseconds(1000 * (delayTime - val));
}
