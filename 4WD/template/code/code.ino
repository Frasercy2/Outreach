#define LeftPinSpeedEna 5     // Pin for controlling speed (ENA) of the motor driver board
#define RightPinSpeedEnb 6    // Pin for controlling speed (ENB) of the motor driver board
int PinLeftBackwards = 2;     // Pin for controlling turning (IN1) of the motor driver board
int PinLeftForward = 4;       // Pin for controlling turning (IN2) of the motor driver board
int PinRightBackwards = 7;    // Pin for controlling turning (IN3) of the motor driver board
int PinRightForwards = 8;     // Pin for controlling turning (IN4) of the motor driver board

void setup()
{
  pinMode(PinLeftBackwards, OUTPUT);   // Pin 2
  pinMode(PinLeftForward, OUTPUT);     // Pin 4
  pinMode(PinRightBackwards, OUTPUT);  // Pin 7
  pinMode(PinRightForwards, OUTPUT);   // Pin 8
  pinMode(LeftPinSpeedEna, OUTPUT);    // Pin 5 (PWM)
  pinMode(RightPinSpeedEnb, OUTPUT);   // Pin 6 (PWM)
  
}

void loop()
{
  go_forward(150); 
  delay(2000); // milliseconds
  stopp();
  // Edit here to complete the circuit
}

void go_forward(unsigned char speed_val)  // speed_val: 0~255
{
  digitalWrite(PinRightBackwards, HIGH); 
  digitalWrite(PinRightForwards, LOW);
  digitalWrite(PinLeftBackwards, HIGH);
  digitalWrite(PinLeftForward, LOW);
  analogWrite(LeftPinSpeedEna, speed_val);
  analogWrite(RightPinSpeedEnb, speed_val);
}

void go_backward(unsigned char speed_val)  // speed_val: 0~255
{
  digitalWrite(PinRightBackwards, LOW);
  digitalWrite(PinRightForwards, HIGH);
  digitalWrite(PinLeftBackwards, LOW);
  digitalWrite(PinLeftForward, HIGH);
  analogWrite(LeftPinSpeedEna, speed_val);
  analogWrite(RightPinSpeedEnb, speed_val);
}

void rotate_left(unsigned char speed_val)  // speed_val: 0~255
{
  digitalWrite(PinRightBackwards, HIGH);
  digitalWrite(PinRightForwards, LOW);
  digitalWrite(PinLeftBackwards, LOW);
  digitalWrite(PinLeftForward, HIGH);
  analogWrite(LeftPinSpeedEna, speed_val);
  analogWrite(RightPinSpeedEnb, speed_val);
}

void rotate_right(unsigned char speed_val)  // speed_val: 0~255
{
  digitalWrite(PinRightBackwards, LOW);
  digitalWrite(PinRightForwards, HIGH);
  digitalWrite(PinLeftBackwards, HIGH);
  digitalWrite(PinLeftForward, LOW);
  analogWrite(LeftPinSpeedEna, speed_val);
  analogWrite(RightPinSpeedEnb, speed_val);
}

void stopp()  // Stop the motors
{
  digitalWrite(PinRightBackwards, HIGH);
  digitalWrite(PinRightForwards, HIGH);
  digitalWrite(PinLeftBackwards, HIGH);
  digitalWrite(PinLeftForward, HIGH);
}
