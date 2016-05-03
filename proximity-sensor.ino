/* 17/06/15 CS ingenium-prox-keyboard-encoderv1.0
     
   Much of this code stolen from
   http://www.arduino.cc/en/Tutorial/Ping

   And mashed together with PT Keyboard Encoder v2   
 */
 
#define VERSION "ingenium-prox-keyboard-encoderv1.0"

#define KEY01  ' '
#define KEY02  KEY_LEFT_ARROW
#define KEY03  KEY_RIGHT_ARROW
#define KEY04  'x' 


      
boolean pressed1 ;

// ping Ultrasonic sensor attached to pin7, led for visual feedback of threshold breech on pin4
const int pingPin = 7;
const int ledPin = 4;
 
//set keyboard trigger threshold in cm
int threshold = 30;

void setup() {
  // initialize serial communication:
  delay(1000);
  Serial.begin(9600);
  Serial.println(VERSION);
  pinMode(ledPin, OUTPUT);
  
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
 x x 
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  

  if((cm <= threshold) & (pressed1 == false) )   {
    Keyboard.write(KEY01);
    Serial.print("sending keypress");
    Serial.println();
    digitalWrite(ledPin, HIGH);
    pressed1 = true;
    Serial.println (pressed1);   }    // send keypress + change press state
    
  if((cm > threshold) && (pressed1 == true)) {
    Keyboard.write(KEY04);
    Serial.print("sending release keypress");
    Serial.println();
    
  }
  
  if (cm > threshold ) {
    pressed1 = false;  
  }
  delay(100);
  digitalWrite(ledPin, LOW);
}



long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
} 
