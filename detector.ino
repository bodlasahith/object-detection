
/*
  This program uses ultrasonic waves to detect objects 0.5 meters in front of the user
  using a buzzer for feedback
*/

const int trigpin = 8; // the wave transmitter pin attaches to pin 8
const int echopin = 7; // the receiver pin attaches to pin 7
const int buzzpin = 5; // the active buzzer SNG pin attaches to pin 5
int n = 600; // the time taken to complete a minute of ultrasonic wave recordings
int count = 0; // the number of times an object obstructed the ultrasonic sensor

int pulse; // the incoming ultrasonic wave after being transmitted
int distance; // the calculated distance threshold for buzzer activation

void setup() {
  // specifying baud rate
  Serial.begin(9600);

  // set up the pins for the ultrasonic waves trig for sending waves and echo for receiving waves)
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  // set up pins for sending signals to the buzzer
  pinMode(buzzpin, OUTPUT);
}

void loop() {
  for (int j = 0; j < n; j++) {
    // tells the ultrasonic chip to transmit a wave
    digitalWrite(trigpin, HIGH);
    // continue transmission for 5 milliseconds
    delay(5);
    // end transmission
    digitalWrite(trigpin, LOW);

    // method "pulseIn" comes from [5]
    pulse = pulseIn(echopin, HIGH); 

    // formula for distance comes from [5]
    distance = (pulse / 2) / 29.1;

    // if the objects is within 0.5 meters of the ultrasonic chip, the buzzer will create a sound
    if (distance <= 50 && distance >= 0) {
      digitalWrite(buzzpin, LOW);
      count++; // adds to the number of objects that pass in front of the user
    }
    else {
      digitalWrite(buzzpin, HIGH);
    }

    // program takes a short break before taking the next detection
    delay(95);
  }

  // shows the number of objects passed 0.5 meters in front of the user in the last minute
  Serial.print("Number of objects passed in front: ");
  Serial.print(count);

  // the buzzer beeps the number of times an object passed in front in the last minute
  // (useful for people who can't see, and can be interchangeable for different periods)
  for (int k = 0; k < count; k++) {
    digitalWrite(buzzpin, HIGH);
    delay(50);
    digitalWrite(buzzpin, LOW);
    delay(300);
  }

  // resets counter for the next minute
  count = 0;
}