#define Pin_1 A3
#define Pin_2 A4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Pin_1,INPUT);
  pinMode(Pin_2,INPUT);

  digitalWrite(Pin_1,LOW);
  digitalWrite(Pin_2,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(Pin_1));
  Serial.print(digitalRead(Pin_2));
  Serial.print("\n");
  delay(2000);
  
}
