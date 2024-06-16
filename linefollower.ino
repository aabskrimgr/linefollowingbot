// Define pins for IR sensors
#define ir1 2  
#define ir2 3 
#define ir3 4 

// Define pins for motor control
#define leftmotor1 6 
#define leftmotor2 7  
#define rightmotor1 9 
#define rightmotor2 8 

// Define pins for ultrasonic sensor
#define echo 12 
#define trig 11 

// Define pins for PWM control
#define pwm1 5 
#define pwm2 10 

int ms = 190; // Motor speed
double x, distance; // Variables to store the ultrasonic sensor reading and calculated distance

void setup() {
    // Set IR sensor pins as inputs
    pinMode(ir1, INPUT); 
    pinMode(ir2, INPUT); 
    pinMode(ir3, INPUT); 
    
    // Set motor control pins as outputs
    pinMode(leftmotor1, OUTPUT); 
    pinMode(leftmotor2, OUTPUT); 
    pinMode(rightmotor1, OUTPUT); 
    pinMode(rightmotor2, OUTPUT); 

    // Set ultrasonic sensor pins
    pinMode(trig, OUTPUT); 
    pinMode(echo, INPUT); 

    // Initialize serial communication for debugging
    Serial.begin(9600); 
}

void loop() {
    // Trigger the ultrasonic sensor
    digitalWrite(trig, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 

    // Read the echo pulse duration
    x = pulseIn(echo, HIGH); 
    // Calculate the distance in cm
    distance = x * 0.034 / 2; 
    // Print the distance to the serial monitor
    Serial.println(distance); 

    // Read the states of the IR sensors
    int l = !digitalRead(ir1); 
    int m = !digitalRead(ir2); 
    int r = !digitalRead(ir3); 

    // If the distance is greater than 20 cm, navigate using the IR sensors
    if (distance > 20) {
        // Decision-making based on IR sensor readings
        if ((l == 0) && (m == 0) && (r == 0)) Stop(); 
        else if ((l == 0) && (m == 1) && (r == 0)) forward(); 
        else if ((l == 0) && (m == 0) && (r == 1)) SturnRight();  
        else if ((l == 1) && (m == 0) && (r == 0)) SturnLeft();
        else if ((l == 0) && (m == 1) && (r == 1)) turnRight(); 
        else if ((l == 1) && (m == 1) && (r == 0)) turnLeft();  
        else if ((l == 0) && (m == 0) && (r == 0)) Back(); 
    } else { 
        // If an obstacle is detected within 20 cm, stop the robot
        Stop(); 
    } 
}

// Function to move the robot forward
void forward() { 
    analogWrite(pwm1, ms); // Set speed for left motor
    analogWrite(pwm2, ms); // Set speed for right motor
    digitalWrite(leftmotor1, HIGH);  
    digitalWrite(leftmotor2, LOW); 
    digitalWrite(rightmotor1, HIGH); 
    digitalWrite(rightmotor2, LOW);  
} 

// Function to slightly turn the robot left
void SturnLeft() { 
    analogWrite(pwm1, ms); // Set speed for left motor
    analogWrite(pwm2, ms); // Set speed for right motor
    digitalWrite(leftmotor1, LOW); 
    digitalWrite(leftmotor2, HIGH); 
    digitalWrite(rightmotor1, HIGH); 
    digitalWrite(rightmotor2, LOW); 
} 

// Function to turn the robot left
void turnLeft() {  
    analogWrite(pwm1, ms); // Set speed for left motor
    analogWrite(pwm2, ms); // Set speed for right motor
    digitalWrite(leftmotor1, LOW); 
    digitalWrite(leftmotor2, LOW); 
    digitalWrite(rightmotor1, HIGH); 
    digitalWrite(rightmotor2, LOW); 
} 

// Function to slightly turn the robot right
void SturnRight() {
    analogWrite(pwm1, ms); // Set speed for left motor
    analogWrite(pwm2, ms); // Set speed for right motor
    digitalWrite(leftmotor1, HIGH); 
    digitalWrite(leftmotor2, LOW); 
    digitalWrite(rightmotor1, LOW); 
    digitalWrite(rightmotor2, HIGH); 
} 

// Function to turn the robot right
void turnRight() { 
    analogWrite(pwm1, ms); // Set speed for left motor
    analogWrite(pwm2, ms); // Set speed for right motor
    digitalWrite(leftmotor1, HIGH); 
    digitalWrite(leftmotor2, LOW); 
    digitalWrite(rightmotor1, LOW); 
    digitalWrite(rightmotor2, LOW); 
}  

// Function to stop the robot
void Stop() { 
    digitalWrite(leftmotor1, LOW); 
    digitalWrite(leftmotor2, LOW); 
    digitalWrite(rightmotor1, LOW);  
    digitalWrite(rightmotor2, LOW); 
}  

// Function to move the robot backward
void Back() { 
    analogWrite(pwm1, 75); // Set speed for left motor
    analogWrite(pwm2, 75); // Set speed for right motor
    digitalWrite(leftmotor1, LOW); 
    digitalWrite(leftmotor2, HIGH); 
    digitalWrite(rightmotor1, LOW); 
    digitalWrite(rightmotor2, HIGH); 
}
//NOTE: The bot path was white in black plain surface
