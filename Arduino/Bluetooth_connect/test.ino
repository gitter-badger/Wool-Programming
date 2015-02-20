int led = 9;
int duty = 0;

void setup(){
	pinMode(led, OUTPUT);

	Serial.begin(115200);

	delay(100);
}

void loop(){
	static char recData;
	if (Serial.available()){
		recData = Serial.read();
		Serial.println(recData);
		delay(100);
	}
	if (recData == '0'){
		digitalWrite(led, LOW);
	}
	else if (recData == '1'){
		digitalWrite(led, LOW);
		delay(500);
		digitalWrite(led, HIGH);
		delay(500);
	}
	else if (recData == 'h'){
		analogWrite(led, duty++);
		delay(5);
		if (duty > 200) duty = 0;
	}
	else{
		digitalWrite(led, HIGH);
	}
	delay(1);
}