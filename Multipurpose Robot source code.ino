
char s; //Serial get
int motorSpd = 100;

//Define Ultrasonic Sensor Pin
const int trigPinR = A0;
const int echoPinR = A1;
const int trigPinF = A2;
const int echoPinF = A3;
const int trigPinL = A4;
const int echoPinL = A5;

int inputBtn = 2; //Mode Change Switch
int count=0;
boolean state = true;  

//Define motor operation pin
int lmF = 3;
int lmB = 4;
int lmE = 5;

int rmE = 6;
int rmF = 7;
int rmB = 8;

// IR sensor input to detect line
int leftIR = 9;
int rightIR = 10;
int leftIRstatus = 0;
int rightIRstatus = 0;

//Define LED to Identify mode
int lfEnable = 11;
int htEnable = 12;


void setup() {
 
  Serial.begin(9600);

//Define Ultrasonic SensorPin Mode
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
 //Define State USed Pin Mode
  pinMode(inputBtn, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
//Define L298N Motor Driver PinMode
  pinMode(lfEnable, OUTPUT);
  pinMode(htEnable, OUTPUT);
  digitalWrite(lfEnable, LOW);
  digitalWrite(lfEnable, LOW);

  pinMode(lmE, OUTPUT);
  pinMode(lmB, OUTPUT);
  pinMode(lmF, OUTPUT);

  pinMode(lmF, OUTPUT);
  pinMode(lmB, OUTPUT);
  pinMode(lmE, OUTPUT);

//motor status initialise
  analogWrite(lmE, motorSpd);
  digitalWrite(lmF, LOW);
  digitalWrite(lmB, LOW);

  digitalWrite(rmF, LOW);
  digitalWrite(rmB, LOW);
  analogWrite(lmE, motorSpd);
  }


void loop() {

    switch (stateCount())
    {
    case 1: 
      digitalWrite(htEnable, LOW);
      digitalWrite(lfEnable, LOW);
      androidControl();
    break;
    case 2: 
      digitalWrite(htEnable, LOW);
      digitalWrite(lfEnable, HIGH);
      lineFlower();

    break;
    case 3: 
      digitalWrite(htEnable, HIGH);
      digitalWrite(lfEnable, LOW);
      humanTrack();

    break;
    default: 
      digitalWrite(htEnable, HIGH);
      digitalWrite(lfEnable, HIGH);
      stopMovement();
    break;
    }

}


 int stateCount(){
    
  if (!digitalRead(inputBtn) && state){  
    count++;  
    state = false;  
    delay(100);  
    if (count>3){
        count=0;
       }
  }  
  if (digitalRead(inputBtn))  
  {  
    state = true;  
    delay(100);  
  }  
  return count;
 }  

//to move forward
void goForward(){
      Serial.println("Going Forward");

      // analogWrite(lmE, motorSpd);
      // analogWrite(rmE, motorSpd);

      digitalWrite(lmF, HIGH);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, HIGH);
      digitalWrite(rmB, LOW);

}

// to move reverse
void goBackward(){
      Serial.println("Going Reverse");
      
      analogWrite(lmE, motorSpd);
      analogWrite(rmE, motorSpd);

      digitalWrite(lmF, LOW);
      digitalWrite(lmB, HIGH);
      digitalWrite(rmF, LOW);
      digitalWrite(rmB, HIGH);   
}

//  to tren left
void turnLeft(){
      Serial.println("Turinig Left");
      analogWrite(lmE, 255);
      analogWrite(rmE, 255);

      digitalWrite(lmF, LOW);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, HIGH);
      digitalWrite(rmB, LOW);
}

// to turn right
void turnRight(){
      Serial.println("Turinig Right");

      analogWrite(lmE, 255);
      analogWrite(rmE, 255);

      digitalWrite(lmF, HIGH);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, LOW);
      digitalWrite(rmB, LOW);
}

// to forward left
void forwardLeft(){
      Serial.println("Turinig Forward Left");

      analogWrite(lmE, motorSpd/2);
      analogWrite(rmE, motorSpd);

      digitalWrite(lmF, HIGH);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, HIGH);
      digitalWrite(rmB, LOW);
}

// to forward right
void forwardRight(){
      Serial.println("Turinig Forward Left");

      analogWrite(lmE, motorSpd);
      analogWrite(rmE, motorSpd/2);

      digitalWrite(lmF, HIGH);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, HIGH);
      digitalWrite(rmB, LOW);
}

// to backward left
void backwardLeft(){
      Serial.println("Turinig Backward Left");

      analogWrite(lmE, motorSpd/2);
      analogWrite(rmE, motorSpd);

      digitalWrite(lmF, LOW);
      digitalWrite(lmB, HIGH);
      digitalWrite(rmF, LOW);
      digitalWrite(rmB, HIGH);
}

// to backward right
void backwardRight(){
      Serial.println("Turinig Backward Left");

      analogWrite(lmE, motorSpd);
      analogWrite(rmE, motorSpd/2);

      digitalWrite(lmF, LOW);
      digitalWrite(lmB, HIGH);
      digitalWrite(rmF, LOW);
      digitalWrite(rmB, HIGH);
}

//to stop movment
void stopMovement(){
      Serial.println("Robot Stoped!!!");

      digitalWrite(lmF, LOW);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, LOW);
      digitalWrite(rmB, LOW);           
}

//  line follower to tren left
void LFturnLeft(){
      analogWrite(lmE, 255);
      analogWrite(rmE, 255);

      digitalWrite(lmF, LOW);
      digitalWrite(lmB, HIGH);
      digitalWrite(rmF, HIGH);
      digitalWrite(rmB, LOW);
}

//line follower  to turn right
void LFturnRight(){

      analogWrite(lmE, 255);
      analogWrite(rmE, 255);

      digitalWrite(lmF, HIGH);
      digitalWrite(lmB, LOW);
      digitalWrite(rmF, LOW);
      digitalWrite(rmB, HIGH);
}


//To find distance using ultrasonic sensor

int frontDistance(){
  int distance;
  long duration;

    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinF, LOW);
    duration = pulseIn(echoPinF, HIGH);
    distance = duration * 0.034 / 2; //distance in cm
    return distance;
}

int leftDistance(){
  int distance;
  long duration;

    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    duration = pulseIn(echoPinL, HIGH);
    distance = duration * 0.034 / 2; //distance in cm
    return distance;
}

int rightDistance(){
  int distance;
  long duration;

    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
    duration = pulseIn(echoPinR, HIGH);
    distance = duration * 0.034 / 2; //distance in cm
    return distance;
}

//to track obstracle
void humanTrack(){
  int frontSensor = frontDistance();
  int leftSensor = leftDistance();
  int rightSensor = rightDistance();

  
   if(frontSensor<=5 || leftSensor<=5 ||rightSensor<=5){
      goBackward();
    }
   else if((frontSensor>5 && frontSensor<15) || (leftSensor>5 && leftSensor<15) || (rightSensor>5 && rightSensor<15)){
      stopMovement();
      Serial.println("Object between stop range");
    }
   else if( frontSensor>100 && leftSensor>100 && rightSensor>100){
      stopMovement();
      Serial.println("Object out of range");
   }
   else{
          if(frontSensor<leftSensor && frontSensor<rightSensor){
              analogWrite(lmE, 100+frontSensor);
              analogWrite(rmE, 100+frontSensor);

              goForward();
            }
          else if(leftSensor<frontSensor && leftSensor<rightSensor){
              analogWrite(lmE, 200);
              analogWrite(rmE, 200);
              turnLeft();
          }
          else if(rightSensor<frontSensor && rightSensor<leftSensor){
              analogWrite(lmE, 200);
              analogWrite(rmE, 200);
              turnRight();
          }
    }
   }



//to use as line flower robot 
void lineFlower(){
    motorSpd = 70;
    analogWrite(lmE, motorSpd);
    analogWrite(rmE, motorSpd);

    if((digitalRead(rightIR) == 0)&&(digitalRead(leftIR) == 0)){goForward();}  

    else if((digitalRead(rightIR) == 1)&&(digitalRead(leftIR) == 0)){LFturnRight();}   

    else if((digitalRead(rightIR) == 0)&&(digitalRead(leftIR) == 1)){LFturnLeft();}  

    else if((digitalRead(rightIR) == 1)&&(digitalRead(leftIR) == 1)){stopMovement();} 
}

// to control robot using smartphone
void androidControl(){
    if(Serial.available() > 0){
    s = Serial.read();

    switch(s){
      case 'F':
        goForward();
        break;

      case 'B':
        goBackward();
        break;

      case 'L':
        turnLeft();
        break;

      case 'R':
        turnRight();
        break;

      case 'G':
        forwardLeft();
        break;
    
      case 'I':
        forwardRight();
        break;

      case 'H':
        backwardLeft();
        break;
    
      case 'J':
        backwardRight();
        break;

      case 'S':
        stopMovement();
        break;

      case '1':
        motorSpd = 25;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '2':
        motorSpd = 50;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '3':
        motorSpd = 75;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '4':
        motorSpd = 100;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '5':
        motorSpd = 12;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '6':
        motorSpd = 150;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '7':
        motorSpd = 175;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '8':
        motorSpd = 200;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;

      case '9':
        motorSpd = 255;
        analogWrite(lmE, motorSpd);
        analogWrite(rmE, motorSpd);
        break;
     default: 
      Serial.println("AndroidBot Stoped!!!");
      stopMovement();
    break;


    }
  }
}

