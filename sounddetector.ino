/*
Program for particle argon to detect sound and distance for dog barking alarm
Using sound detector and ultra sonic sensor
*/


// Initialise variables and pins
int aPin = A0;
int dPin = 3;
int echoPin = 8;
int trigPin = 7;
int tCount = 0;
int tSend = 3000;
int dValue = 0;
float sValue = 0;


void setup() {
// Set up pins
  pinMode (aPin, INPUT);
  pinMode (dPin, INPUT);
  pinMode (echoPin, INPUT);
  pinMode (trigPin, OUTPUT);

}

void myHandler(const char *event, const char *data) {
  // Handle the integration response
}

void loop() {

// Read sound value and record highest value
  
  float sound = analogRead(aPin)*(5.0/1023.0);
  sValue = max(sValue,sound);

// Send out ping and calucuate distance with ultra sonic sensor
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
// Update value to record smallest value when not 0
  if (sValue = 0)
  {
      sValue = distance;
  }
  else if (sValue < distance > 0)
  {
      sValue = distance;
  }
  

//count up by 1 incrementally
  tCount ++;
  
// when count reaches the threshold to send it wil publish values to cloud and reset the values.
  if (tCount % tSend)
  {
    Particle.publish("sound", String(sValue), PRIVATE);
    Particle.publish("distance", String(dValue), PRIVATE);
    tCount = 0;
    sValue = 0;
    dValue = 0;
  }
  
}

