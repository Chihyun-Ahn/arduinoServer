int a = 1001;
String b = "01";  
String c = "dd";

void setup()
{
  Serial.begin(9600);  
}

void loop() // 반복
{
  c = String(a+b);
  Serial.println(c);
  delay(1000);
}  
