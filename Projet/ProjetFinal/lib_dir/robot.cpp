 #include "robot.h"

//Constructeur robot
ROBOT::ROBOT()
{
    MOTOR motor;
    LED led;
    MEMORY memory;
    SOUND speaker;
}

//Séquence de départ avec LED et moteurs
 void ROBOT::startingSequence()
 {
    led.colorRed();
    speaker.introSong();
    led.colorGreen();
    motor.moveStraight(100);
    _delay_ms(500);
    motor.stop();
    _delay_ms(200);
    motor.moveBack(100);
    _delay_ms(500);
    led.noColor();
    motor.stop();
    _delay_ms(3000);
 }

//Fonction qui fait attendre 25ms fois l'opérande
void ROBOT::wait(uint8_t operand)
{
    for (uint8_t i = 0; i < operand; i++)
    {
        _delay_ms(25);
    }
}

//Allume la LED d'une couleur selon l'opérande
void ROBOT::turnLED(uint8_t operand)
{
    if (operand == 1)
        led.colorGreen();
    else if (operand == 2)
        led.colorRed();
    else if (operand == 3)
        led.colorAmber();
}

//Pour commencer une boucle
void ROBOT::startLoop(uint8_t operand)
{
    address = PC;
    localCounter = operand;
    localCounter--;
}

//Pour terminer la boucle
void ROBOT::endLoop()
{
    if (localCounter > 0)
    {
        PC = address;
        localCounter--;
    }
}

//Lorsque l'instruction de fin (fin) est lu, la boucle de la sequence s'arrete et une musique est jouée
void ROBOT::end()
{
    isBegin = false;
    speaker.outroSong();
}

//Liste des instructions et leur valeur en hexa (BYTECODE)
enum instruction 
{
    dbt = 0x01, //Début
    att = 0x02, //Attendre
    dal = 0x44, //Allumer la del
    det = 0x45, //Eteindre la del
    sgo = 0x48, //Jouer la sonorité
    sar = 0x09, //Arreter la sonorité
    mar = 0x61, //Arreter les moteurs
    mav = 0x62, //Avancer
    mre = 0x63, //Reculer
    trd = 0x64, //Tourner à droite
    trg = 0x65, //Tourner à gauche
    dbc = 0xC0, //Début boucle
    fbc = 0xC1, //Fin boucle
    fin = 0xFF  //Fin du programme
};

//Interprétation des instructions en BYTECODE a notre robot
void ROBOT::doInstructions(uint8_t valueInstruction)
{
    switch (valueInstruction)
    {
        case att:
            wait(operand);
            break;

        case dal:
            turnLED(operand);
            break;

        case det:
            led.noColor();
            break;

        case sgo:
            speaker.playSound(operand);
            break;

        case sar:
            speaker.stopSound();
            break;

        case mar:
            motor.stop();
            break;

        case mav:
            motor.moveStraight(motor.intToPercentage(operand));
            break;

        case mre:
            motor.moveBack(motor.intToPercentage(operand));
            break;

        case trd:
            motor.turn(50, 0);
            break;

        case trg:
            motor.turn(0, 50);
            break;

        case dbc:
            startLoop(operand);
            break;
        
        case fbc:
            endLoop();
            break;

        case fin:
            end();
            break;

        default:
            break;
    }
}

//Vérifie si l'instruction est dbt, si oui : séquence de départ
void ROBOT::start()
{
    if (valueInstruction == instruction::dbt)
    {
        isBegin = true;
        startingSequence();
    }
}

//Lecture des instructions et opérandes en mémoire
void ROBOT::readMemory()
{
    memory.lecture(PC, &valueInstruction);
    PC++;
    memory.lecture(PC, &operand);
    PC++;
}

//Séquence a inclure dans le main
//Lit le bytecode en mémoire jusqu'a temps de trouver l'instruction de début (dbt), puis commence les instructions
void ROBOT::sequence()
{
    while (true)
    {
        readMemory();

        start();

        while (isBegin)
        {
            readMemory();
            doInstructions(valueInstruction);
        }
    }
}