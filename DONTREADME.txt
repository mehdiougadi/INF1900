


class roue 
{
public:
	roue(uint8_t PORT0B,uint8_t PORT1B)
	{
		DDRB = (1 << PORT0B) | (1 << PORT1B);
	}

	//Mouvement de la roue
	forward(uint8_t PORT0B,int pwm)
	{
		PORT0B = 0x00;
		ajustementPwm();
	}
	backward(uint8_t PORT0B,int pwm)
	{
		PORT0B = 0x01;
		ajustementPwm();
	}


private:
	
	//PWM de la roue
	void ajustementPwm(uint8_t valeurPWM) {

		// mise à un des sorties OC1A et OC1B sur comparaison
		// réussie en mode PWM 8 bits, phase correcte
		// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
		// page 130 de la description technique du ATmega324PA)

		OCR1A = 0;
		OCR1B = valeurPWM;

		// division d'horloge par 8 - implique une fréquence de PWM fixe

		TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
		TCCR1B |= (1 << CS11); //prescaler à 8
		TCCR1C |= 0;

	}
};

roue roueGauche(PORTB4, PORTB5);
roue roueDroite(PORTB6, PORTB7);

class motor
{
public:
	motor(roue roueGauche, roue roueDroite)
	{
		GAUCHE = roueGauche;
		DROITE = roueDroite;
	}

	forward(){}
	backward() {}
	turnLeft() {}
	turnRight() {}
private:
	//Attribut
	roue GAUCHE;
	roue DROITE;
};
