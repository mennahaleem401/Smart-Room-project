#define red 3
#define yellow 2
#define green 4
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(yellow,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>1){
    String r=Serial.readStringUntil('\n');
  if(r=="green"){
    digitalWrite(green,1);
    Serial.println(r);
    digitalWrite(red,0);
    digitalWrite(yellow,0);
    }
  else if(r=="red"){
    digitalWrite(red,1);
    digitalWrite(green,0);
    digitalWrite(yellow,0);
    Serial.println(r);}
  else if(r=="yellow"){
    digitalWrite(yellow,1);
    digitalWrite(red,0);
    digitalWrite(green,0);
    Serial.println(r);
  }
  }
  
}
