#include <avr.io/h>

//mettre les bons #include

enum instruction {

	begin = 0x01,
	wait = 0x02,
	startLED = 0x44,
	stopLED = 0x45,
	playSound = 0x48,
	stopSound = 0x09,
	stopMotorA = 0x60
	stopMotorB = 0x61,
	moveForward = 0x62,
	moveBackward = 0x63,
	turnRight = 0x64,
	turnLeft = 0x65,
	startLoop = 0xC0,
	stopLoop = 0xC1,
	end = 0xff,
};

void initialisation()
{
	//appeler init LED
	//appeler init motor
	//appeler init memoire
	//init ports pour haut-parleur

	//faire allumer LED rouge pendant 2 secondes pour verifier init
}

void instructions() {

	//switch case
}

int main() {

	initialisation();

	if (instruction == begin)
		bool isBegin = true;

	if (isBegin) {
		instructions();
	}
}