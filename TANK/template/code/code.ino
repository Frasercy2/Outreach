#define MotorLeft_Ctrl 13  //define the direction control pin of the left motor
#define MotorLeft_PWM 11   //define the PWM control pin of the left motor
#define MotorRight_Ctrl 12  //define the direction control pin of the right motor
#define MotorRight_PWM 3    //define the PWM control pin of the right motor
#define SCL_Pin  A5  //Set clock pin to A5
#define SDA_Pin  A4  //Set data pin to A4
unsigned char CY2[] = {0x00, 0x7e, 0x42, 0x42, 0x00, 0x02, 0x04, 0x78, 0x04, 0x02, 0x00, 0x66, 0x72, 0x4a, 0x46, 0x00}; // This is the logo


void setup() {
  Serial.begin(9600);
  pinMode(SCL_Pin,OUTPUT);
  pinMode(SDA_Pin,OUTPUT);
 
  pinMode(MotorLeft_Ctrl, OUTPUT);
  pinMode(MotorLeft_PWM, OUTPUT);
  pinMode(MotorRight_PWM, OUTPUT);
  pinMode(MotorRight_Ctrl, OUTPUT);
}

void loop() {
  matrix_display(CY2); // Ignore this line, it adds the logo.

  car_front(185, 250);
  delay(1000);
  car_Stop();
  delay(1000);
  // Add code on to here to complete track.

}

/***************the function to run the motor***************/
void car_front(unsigned char Left_Motor_Speed, unsigned char Right_Motor_Speed) {
  analogWrite(MotorRight_PWM, Right_Motor_Speed); // pass the speed to the right motor
  digitalWrite(MotorRight_Ctrl, LOW);
  digitalWrite(MotorLeft_Ctrl, LOW);
  analogWrite(MotorLeft_PWM, Left_Motor_Speed); // pass the speed to the left motor
}

void car_back(unsigned char Left_Motor_Speed, unsigned char Right_Motor_Speed) {
  digitalWrite(MotorRight_Ctrl, HIGH);
  analogWrite(MotorRight_PWM, Right_Motor_Speed);
  digitalWrite(MotorLeft_Ctrl, HIGH);
  analogWrite(MotorLeft_PWM, Left_Motor_Speed);
}

void car_left(unsigned char Left_Motor_Speed, unsigned char Right_Motor_Speed) {
  digitalWrite(MotorRight_Ctrl, LOW);
  analogWrite(MotorRight_PWM, Right_Motor_Speed);
  digitalWrite(MotorLeft_Ctrl, HIGH);
  analogWrite(MotorLeft_PWM, Left_Motor_Speed);
}

void car_right(unsigned char Left_Motor_Speed, unsigned char Right_Motor_Speed) {
  digitalWrite(MotorRight_Ctrl, HIGH);
  analogWrite(MotorRight_PWM, Right_Motor_Speed);
  digitalWrite(MotorLeft_Ctrl, LOW);
  analogWrite(MotorLeft_PWM, Left_Motor_Speed);
}

void car_Stop() {
  digitalWrite(MotorRight_Ctrl, LOW);
  analogWrite(MotorRight_PWM, HIGH);
  digitalWrite(MotorLeft_Ctrl, LOW);
  analogWrite(MotorLeft_PWM, HIGH);
}

void car_t_left(unsigned char Left_Motor_Speed, unsigned char Right_Motor_Speed) {
  digitalWrite(MotorRight_Ctrl, LOW);
  analogWrite(MotorRight_PWM, Right_Motor_Speed);
  digitalWrite(MotorLeft_Ctrl, LOW);
  analogWrite(MotorLeft_PWM, Left_Motor_Speed);
}

void car_t_right(unsigned char Left_Motor_Speed, unsigned char Right_Motor_Speed) {
  digitalWrite(MotorRight_Ctrl, LOW);
  analogWrite(MotorRight_PWM, Right_Motor_Speed);
  digitalWrite(MotorLeft_Ctrl, LOW);
  analogWrite(MotorLeft_PWM, Left_Motor_Speed);
}





// ************************ Ignore this Code ******************************* //


// the function for dot matrix display
void matrix_display(unsigned char matrix_value[])
{
  IIC_start();  // use the function of the data transmission start condition
  IIC_send(0xc0);  //select address
  
  for(int i = 0;i < 16;i++) //pattern data has 16 bits
  {
     IIC_send(matrix_value[i]); //convey the pattern data
  }

  IIC_end();   //end the transmission of pattern data  
  IIC_start();
  IIC_send(0x8A);  //display control, set pulse width to 4/16 s
  IIC_end();
}

//the condition to start conveying data
void IIC_start()
{
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
}
//Convey data
void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)  //Each byte has 8 bits 8bit for every character
  {
      digitalWrite(SCL_Pin,LOW);  // pull down clock pin SCL_Pin to change the signal of SDA
      delayMicroseconds(3);
      if(send_data & 0x01)  //set high and low level of SDA_Pin according to 1 or 0 of every bit
      {
        digitalWrite(SDA_Pin,HIGH);
      }
      else
      {
        digitalWrite(SDA_Pin,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(SCL_Pin,HIGH); //pull up the clock pin SCL_Pin to stop transmission
      delayMicroseconds(3);
      send_data = send_data >> 1;  // detect bit by bit, shift the data to the right by one
  }
}

//The sign of ending data transmission
void IIC_end()
{
  digitalWrite(SCL_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
}
//******************************************************