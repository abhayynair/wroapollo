#include <Servo.h>


///////MOTOR DRIVER PINS///////////

int in1 = 24;
int in2 = 25;
int enA = 2;

int in3 = 26;
int in4 = 27;
int enB = 3;


/////////

int sped = 225;
int low_Sped = 225;
int k = 0;

#define echo1Pin 11
#define trig1Pin 10
#define echo2Pin 5
#define trig2Pin 4
#define echo3Pin 7
#define trig3Pin 6

long duration1, duration2, duration3;
int distance1, distance2, distance3;



Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int center_Pos = 50;   // variable to store the servo position

void setup() {
  
  pinMode(13, OUTPUT);
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  
  pinMode(trig3Pin, OUTPUT);
  pinMode(echo3Pin, INPUT);
  
  Serial.begin(115200);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo objects
  myservo.write(center_Pos);
  delay(500);
//  myservo.write(0);
//  delay(500);
//  myservo.write(center_Pos);
//  delay(500);
  myservo.write(100);
  delay(500);
  myservo.write(center_Pos);
  
  
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
//  delay(1000);
//  digitalWrite(13, HIGH);
//  delay(1000);
//  digitalWrite(13, LOW);
  delay(500);

//  myservo.write(0);
//  delay(1000);
//  move_Straight();
//  delay(1500);
//  myservo.write(55);
//  analogWrite(enA, 0);
//  analogWrite(enB, 0);
  

}

void loop() {


  
  while(k<12){
//    delay(1000);

    digitalWrite(trig1Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);
    duration1 = pulseIn(echo1Pin, HIGH);
    distance1 = duration1 * 0.034 / 2;

    digitalWrite(trig2Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2Pin, LOW);
    duration2 = pulseIn(echo2Pin, HIGH);
    distance2 = duration2 * 0.034 / 2;

    digitalWrite(trig3Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig3Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig3Pin, LOW);
    duration3 = pulseIn(echo3Pin, HIGH);
    distance3 = duration3 * 0.034 / 2;

//    myservo.write(center_Pos);
    if(distance3 >= 100){
      move_Straight();
    } else {
      move_Slow();
    }
    
//    delay(500);
//    Serial.print("The front Distance Is:");
//    Serial.println(distance3);
//
//    Serial.print("right Distance: ");
//    Serial.println(distance2);
//    
//    Serial.print("left Distance: ");
//    Serial.println(distance1);  
//    Serial.println(" ");

    if (distance3 <= 50 && (distance2 == 0 || distance2 > 100) && distance3 > 0) {
    
//      Serial.print("Turning Right \n ");
//      
//      Serial.print("Front Distance: ");
//      Serial.println(distance3);
//      Serial.print("right Distance: ");
//      Serial.println(distance2);

      myservo.write(0);
      delay(850);
      myservo.write(center_Pos);
//      delay(100);8
      k++;
      if (k==12){
        final_Stage();
      }  
   
    }else{
      if (distance1 < 15 && distance1 != 0) {
      
//        Serial.print("(Away)Left Distance: ");
//        Serial.println(distance1);
        
        myservo.write(20);
//        delay(10);
//        myservo.write(center_Pos); 
        
      }
//      else if (distance1 > 25 && distance1 != 0) {
//      
//        Serial.print("(Towards)Left Distance: ");
//        Serial.println(distance1);
        
//        myservo.write(80);
//        delay(50);
//        myservo.write(center_Pos); 
//      }
      else if (distance2 < 20 && distance2 != 0) {
      
//        Serial.print("(Away)Right Distance: ");
//        Serial.println(distance2);
        
        myservo.write(80);
//        delay(50);
      }
      else{
        myservo.write(center_Pos);
      }
    }
  }
  
  analogWrite(enA, 0);
  analogWrite(enB, 0);
//  Serial.println("DONE");
}

void move_Straight(){
  
  analogWrite(enA, sped);
  analogWrite(enB, sped);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
//  delay(10);
  
}

void move_Slow(){
  
  analogWrite(enA, low_Sped);
  analogWrite(enB, low_Sped);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}

void final_Stage(){
  int starttime, endtime, loopcount;
  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <=1000) // do this loop for up to 1000mS
  {
  // code here
    if (distance1 < 15 && distance1 != 0) {
      myservo.write(20);
    }
//    else if (distance1 > 25 && distance1 != 0) {
//      myservo.write(80);
//    }
    else if (distance2 < 20 && distance2 != 0) {
      myservo.write(80);
    }
    else{
      myservo.write(center_Pos);
    }
      
    loopcount = loopcount+1;
    endtime = millis();
  }
//  serial.print (loopcount,DEC);
}
