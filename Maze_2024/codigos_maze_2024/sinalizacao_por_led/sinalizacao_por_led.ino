int red, yellow, green;

void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
   
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(!digitalRead(6)){
    red = 1;
    delay(300);
  }else{
    red = 0;
  }

  if(!digitalRead(7)){
    yellow = 1;
    delay(300);
  }else{
    yellow = 0;
  }

  if(!digitalRead(8)){
    green = 1;
    delay(300);
  }else{
    green = 0;
  }|

  if(red){
    digitalWrite(2, 1);
  }else{
    digitalWrite(2, 0);
  }

  if(yellow){
    digitalWrite(3, 1);
  }else{
    digitalWrite(3, 0);
  }

  if(green){
    digitalWrite(4, 1);
  }else{
    digitalWrite(4, 0);
  }

  Serial.print("Vermeho = ");
  Serial.println(red);
  delay(500);

}
