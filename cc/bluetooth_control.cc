#include <AccelStepper.h>
#define dirPin0 2
#define stepPin0 3
#define dirPin1 4
#define stepPin1 5
#define motorInterfaceType 1

//SoftwareSerial1 Bluetooth(A8, 38); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)I used TX0, RX0 instead
// Define the stepper motors and the pins the will use
AccelStepper LeftWheel(motorInterfaceType, stepPin0, dirPin0);
AccelStepper RightWheel(motorInterfaceType, stepPin1, dirPin1);

int wheelSpeed = 1500;
int dataIn, m;

//int lw[50], rw[50]; // for storing positions/steps
void setup() {
	// Set initial seed values for the steppers
	LeftWheel.setMaxSpeed(3000);
	RightWheel.setMaxSpeed(3000);
	Serial1.begin(9600);
	// Bluetooth.begin(38400); // Default baud rate of the Bluetooth module
	Serial1.setTimeout(1);
	delay(20);
}
	
void loop() {
	// Check for incoming data
	if (Serial1.available() > 0) {
		dataIn = Serial1.read(); // Read the data
		if (dataIn == '0') {
		m = 0;
		}
		if (dataIn == '1') {
		m = 1;
		}
		if (dataIn == '2') {
		m = 2;
		}
		if (dataIn == '3') {
		m = 3;
		}
		if (dataIn == '4') {
		m = 4;
		}
		// Set speed
		if (dataIn >= 16) {
			wheelSpeed = dataIn * 10;
			Serial1.println(wheelSpeed);
		}
	}
	if (m == 1) {
		moveForward();
	}
	if (m == 2) {
		moveBackward();
	}
	if (m == 3) {
		turnLeft();
	}
	if (m == 4) {
		turnRight();
	}
	if (m == 0) {
		stopMoving();
	}
	
	LeftWheel.runSpeed();
	RightWheel.runSpeed();
}

void moveForward() {
	LeftWheel.setSpeed(wheelSpeed);
	RightWheel.setSpeed(wheelSpeed);
}

void moveBackward() {
	LeftWheel.setSpeed(-wheelSpeed);
	RightWheel.setSpeed(-wheelSpeed);
}

void turnLeft() {
	LeftWheel.setSpeed(wheelSpeed);
	RightWheel.setSpeed(0);
}

void turnRight() {
	RightWheel.setSpeed(wheelSpeed);
	LeftWheel.setSpeed(0);
}

void stopMoving() {
	LeftWheel.setSpeed(0);
	RightWheel.setSpeed(0);
}
