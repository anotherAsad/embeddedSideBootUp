#include <SoftwareSerial.h>
#define  TRCK_INCR_CONDITION tracker == 0 && recv == 's' || tracker == 1 && recv == 'n' || tracker == 2 && recv == 'p'

SoftwareSerial mySerial(2, 3); // RX, TX

uint8_t tracker, indx;
char recvStr[27];
char recv;

struct dataPacket{
	uint8_t PacketType;
	uint8_t Address;
	uint32_t data[5];	// {Roll+Pitch, Yaw+NULL, Roll'+Pitch', Yaw'+NULL, EulerAngleCaptureTime}
	uint16_t Checksum;
};

int main(){
	// Setup
	init();
	Serial.begin(115200);
	mySerial.begin(115200);
	tracker = indx = 0;
	struct dataPacket* pkt;
	// Loop
	while(1){
		recv = mySerial.read();
		if(recv == -1)	// actually, not necessary.
			continue;
		// tracker control
		if(TRCK_INCR_CONDITION){
			tracker++;
			continue;
		}
		else if(tracker != 3){	// in case the "snp" string is not received.
			tracker = 0;
			continue;
		}
		// Parsing Section
		recvStr[indx++] = recv;
		if(indx == 24){
			indx = tracker = 0;
			pkt = (struct dataPacket*)recvStr;
			// print routine
			Serial.print("Packet Type: ");
			Serial.println(pkt->PacketType, HEX);
			Serial.print("Start Address: ");
			Serial.println(pkt->Address, HEX);
			for(int i=0; i<5; i++){
				Serial.print("Data");
				Serial.print(i, DEC);
				Serial.print(": ");
				Serial.println(pkt->data[i], HEX);
			}
			Serial.print("Checksum: ");
			Serial.println(pkt->Checksum, DEC);
			Serial.println("\n\n");
		}
	}
}
