
#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo myservo;

/////MOTOR DRIVER PINS/////
int in1 = 24; 
int in2 = 25;
int enA = 2;

int in3 = 26;
int in4 = 27;
int enB = 3;
///////////////////////////

//////ULTRASONIC//////
#define echo1Pin 11
#define trig1Pin 10
#define echo2Pin 5
#define trig2Pin 4
#define echo3Pin 7
#define trig3Pin 6
long duration1, duration2, duration3;
int distance1, distance2, distance3;
///////////////////////////

int sped = 225;
int low_Sped = 225;
int counts = 0;
int center_Pos = 110;
int flagg = 1;

void setup() {
  
  Serial.begin(115200); //pixy baud rate
  pinMode(13, OUTPUT);
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  
  pinMode(trig3Pin, OUTPUT);
  pinMode(echo3Pin, INPUT);
  
  myservo.attach(9);
  myservo.write(center_Pos);
  delay(500);
  myservo.write(160);
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
  delay(500);


  pixy.init();          //setup pixy
  pinMode(enA, OUTPUT); //motor control components
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
}

void loop() {
//  delay(1000);
  while(counts < 4){
    
    if(counts == 4) {
      digitalWrite (enA, LOW);
      digitalWrite (enB, LOW);
    }else{ move_Straight();}
  
    digitalWrite(trig1Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);
    duration2 = pulseIn(echo1Pin, HIGH);
    distance2 = duration2 * 0.034 / 2;
  
    digitalWrite(trig2Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2Pin, LOW);
    duration1 = pulseIn(echo2Pin, HIGH);
    distance1 = duration1 * 0.034 / 2;
  
    digitalWrite(trig3Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig3Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig3Pin, LOW);
    duration3 = pulseIn(echo3Pin, HIGH);
    distance3 = duration3 * 0.034 / 2;
  
    Serial.print("The front Distance Is:");
    Serial.println(distance3);
  
    Serial.print("left Distance: ");
    Serial.println(distance1);
    
    Serial.print("right Distance: ");
    Serial.println(distance2);  
    Serial.println(" ");
    
    pixy.ccc.getBlocks();
    if (distance3 <= 70 && (distance1 == 0 || distance1 > 100) && distance3 > 0 && pixy.ccc.blocks[0].m_signature != 1 && pixy.ccc.blocks[0].m_signature != 2) {
  
      pixy.ccc.blocks[0].print();
      Serial.print("Turning Right \n ");
      
      Serial.print("Front Distance: ");
      Serial.println(distance3);
      Serial.print("left Distance: ");
      Serial.println(distance1);
  
      myservo.write(160);
      delay(850);
      myservo.write(center_Pos);
  //    delay(100);
      counts++;
      if (counts==4){
        final_Stage();
      }  
  
    }else{
      if (distance2 < 15 && distance2 != 0) {
      
        Serial.print("(Away)Right Distance: ");
        Serial.println(distance2);
        
        myservo.write(140);
  //      delay(10);
        
      }
      else if (distance1 < 20 && distance1 != 0) {
      
        Serial.print("(Away)Left Distance: ");
        Serial.println(distance1);
        
        myservo.write(80);
  //      delay(50);
      }
      else if (flagg == 1){
        myservo.write(center_Pos);
      }
    }
  
    if( pixy.ccc.numBlocks) {
      float dist;
  //    float dist = 1368.3 / pixy.ccc.blocks[0].m_width; //conversion rate
      
      Serial.print("Distance to the nearest block detected is: ");
      Serial.println(dist);
      
  
      if (pixy.ccc.blocks[0].m_x < 300 && pixy.ccc.blocks[0].m_y > 100) { 
      
        //signature 1 is RED
        if (pixy.ccc.blocks[0].m_signature == 1) {  
  
          flagg = 0;
          Serial.println("Detected RED Block Details");
          pixy.ccc.blocks[0].print();
          Serial.println("");
          Serial.println("Turning Left");
          
          myservo.write(60);
          delay(500);
  //        myservo.write(center_Pos);
  
          Serial.println("Done");
  
        }
        
        //signature 2 is GREEN
        if (pixy.ccc.blocks[0].m_signature == 2) {
          
          flagg = 0;
          Serial.println("Detected GREEN Block Details");
          pixy.ccc.blocks[0].print();
          Serial.println("");           
          Serial.println("Turning Right");
          
          myservo.write(160);
          delay(500);
  //        myservo.write(center_Pos);
  
          Serial.println("Done");
  
        }
      }
      else {
        flagg = 1;
  //      myservo.write("center_Pos");
      }
    }
    else {
        flagg = 1;
  //      myservo.write("center_Pos");
      }
  }
  analogWrite(enA, LOW);
  analogWrite(enB, LOW);
}

void move_Straight(){
  
  analogWrite(enA, sped);
  analogWrite(enB, sped);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
 //delay(10);
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
    if (distance2 < 15 && distance2 != 0) {
      myservo.write(160);
    }
    else if (distance1 < 20 && distance1 != 0) {
      myservo.write(60);
    }
    else{
      myservo.write(center_Pos);
    }
      
    loopcount = loopcount+1;
    endtime = millis();
  }
  //serial.print (loopcount,DEC);
}
