// Motor
const double MOTOR_PIN = 11;
const double MOTOR_MAX_DIG_DELAY = 5; // Miliseconds
const double OUTPUT_MAX_VALUE = 2;
const double OUTPUT_MIN_VALUE = 1;

// Potentiometer / Controller
const double POT_PIN = A0;
const double POT_MAX_VALUE = 1023;
const double POT_MIN_VALUE = 496;

// Other
const double DEADBAND = 0.1; // From 0 to 1
const bool DEBUG = true;

double potVal;
double outputVal;


void setup()
{
  if (DEBUG) Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop()
{
  potVal = analogRead(POT_PIN);
  outputVal = changeRange(potVal, POT_MIN_VALUE, POT_MAX_VALUE, OUTPUT_MIN_VALUE, OUTPUT_MAX_VALUE);
  outputVal = max(min(outputVal, OUTPUT_MAX_VALUE), OUTPUT_MIN_VALUE);
  outputVal = addDeadband(potVal, OUTPUT_MIN_VALUE, OUTPUT_MAX_VALUE, DEADBAND);

  if (DEBUG) {
    Serial.print("Potentiometer Value: "); Serial.println(potVal);
    Serial.print("Output Value: "); Serial.println(outputVal);
  }

  digitalWrite(MOTOR_PIN, HIGH);
  delay(outputVal);
  
  digitalWrite(MOTOR_PIN, LOW);
  delay(MOTOR_MAX_DIG_DELAY - outputVal);
}


/**
 * @brief 
 * 
 * @param value the current value in the input range
 * @param min min value of the input range
 * @param max max value of the input range
 * @param outputMin
 * @param outputMax 
 * @return the value relative to the output range
 */
double changeRange(double value, double min, double max, double outputMin, double outputMax) {
  return (((value - min) * (outputMax - outputMin)) / (max - min)) + outputMin;
}


/**
 * @brief 
 * 
 * @param value the input / controller value
 * @param min the minimum value of the range
 * @param max the maximum value of the range
 * @param deadband decimal number from 0 to 1
 * @return the output value after calculating the deadband
 */
double addDeadband(double value, double min, double max, double deadband) {
  if (deadband == 0) return value;
  deadband = deadband * (max - min);
  double middle = (max + min) / 2.0;
  return abs(value - (max - min)) <= deadband ? deadband : value > middle ?
    changeRange(value, middle + deadband, max, middle, max) : changeRange(value, min, middle - deadband, min, middle);
}