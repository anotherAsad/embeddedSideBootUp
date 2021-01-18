int main(){
	// Setup
	char recv;
	init();
	Serial.begin(9600);
	Serial.write("1234");
	// Loop
	while(1){
		recv = Serial.read();
		recv = recv == '9' ? '0' : recv + 1;
		Serial.write(recv);
		delay(1000);
	}
}
