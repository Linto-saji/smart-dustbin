#define TRIG_PIN 2
#define ECHO_PIN 3
#define SERVO_PIN 5

#define OPEN_DISTANCE 15

#define SERVO_OPEN_US 1500    // ~90 degrees
#define SERVO_CLOSE_US 500    // ~0 degrees
#define SERVO_PERIOD 20000    // 20 ms

long duration;
int distance;

void servoPulse(int pin, int pulseWidth) {
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(pin, LOW);
  delayMicroseconds(SERVO_PERIOD - pulseWidth);
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SERVO_PIN, OUTPUT);

  digitalWrite(SERVO_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  // Ultrasonic trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 25000);

  if (duration == 0) {
    distance = 999; // no object detected
  } else {
    distance = duration * 0.034 / 2;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- DIRECT DECISION BASED ON DISTANCE ---
  if (distance < OPEN_DISTANCE) {
    Serial.println("Status: Dustbin Open");
    servoPulse(SERVO_PIN, SERVO_OPEN_US);
  } else {
    Serial.println("Status: Dustbin Closed");
    servoPulse(SERVO_PIN, SERVO_CLOSE_US);
  }
}
