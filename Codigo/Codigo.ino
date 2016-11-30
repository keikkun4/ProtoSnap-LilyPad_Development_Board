/* ProtoSnap LilyPad Plataforma de Desarrollo - Código de Ejemplo
  Por: Pete Lewis
  SparkFun Electronics
  Fecha: 24/8/11
  Licencia: Creative Commons Atribución Compartir Igual v3.0 CC BY-SA 3.0
  http://creativecommons.org/licenses/by-sa/3.0/
  
  Traduccion: Karla L Hdz
  Microcode Company
  Fecha: 30/12/16
  Licencia: Creative Commons Atribución Compartir Igual v3.0 CC BY-SA 3.0
  http://creativecommons.org/licenses/by-sa/3.0/  
  
  Este es un código de ejemplo para la plataforma de desarrollo Protosnap LilyPad.
   Iniciara realizando una secuencia de arranque rápida, parpadeando todos los LEDs, luego entrará en el loop.
   Aqui comprobará si pulsa el botón o cambia de estado el switch y suena o vibra
   Dependiendo de si están comprometidos o no.
   Si ninguno de los dos interruptores está encendido, comprobará el sensor de luz y de temperatura,
   y encendera los ledes si se cumplen los valores correctos. 
   Sostenga su dedo sobre el sensor de luz para encender los LEDs blancos. 
   Intente soplar el sensor de temperatura para encienda el LED rojo.
   Por último, el estado de cada entrada se transmite a través de la línea serie a 9600 baudios.
   Para ver cuáles son los valores, abra el monitor serie (el icono superior derecho con una lupa)
   Y asegúrese de que los baudios estan configurado en 9600.
*/

/* Definicion de pines */
// Ledes: Los ledes blancos estan conectados en 5, 6, A2, A3, A4
int ledPins[] = {5, 6, A2, A4, A3, 9, 10, 11};
int switchPin = 2; 
int buttonPin = A5;
int vibePin = 3;
int buzzerP = 7;
int buzzerN = 12;
int lightSensorPin = A6;
int tempSensorPin = A1;

/* Variables globales */
int light = 100;

void setup()
{
  //SECUENCIA INICIAL DE LEDES
  for(int i=0; i<5; i++)             // Este es un bucle de 5 tiempos
  {  // enciendo el LED blanco       (primeros 5 ledes del arreglo)
    pinMode(ledPins[i], OUTPUT);     // inicializacion de pines
    digitalWrite(ledPins[i], HIGH);  // turno de LED encendido
    delay(250);                      // espera un cuarto de segundo
    digitalWrite(ledPins[i], LOW);   // turno de LED apagado
  }
  for(int i=5;i<8;i++)               // Este es un bucle de 3 tiempos
  {   // El LED RGB parpadea blink the RGB LEDs (ultimos 3 ledes del arreglo)
    pinMode(ledPins[i], OUTPUT);     // inicializacion de pines 
    digitalWrite(ledPins[i], LOW);   // turno de LED RGB encendido
    delay(250);                      // espera un cuarto de segundo
    digitalWrite(ledPins[i], HIGH);  // turno de LED RGB apagado
    // Nota un HIGH en el turno del LED RGB se apaga, LOW se enciende
    // esta al réves de los ledes blancos
  }
  ////////////////////////////////////////////

  //Switch
  pinMode(switchPin, INPUT);      // inicializando el switch
  digitalWrite(switchPin, HIGH);  // inahabilitando la resistencia del pull-up

  //Boton
  pinMode(buttonPin, INPUT);      // inicializando el boton
  digitalWrite(buttonPin, HIGH);  // inahabilitando la resistencia del pull-up

  //Vibrador
  pinMode(vibePin, OUTPUT);       // inicializando el vibrador

  //Bocina
  pinMode(buzzerP, OUTPUT);       // inicializando los pines de la bocina
  pinMode(buzzerN, OUTPUT);

  Serial.begin(9600);             // Bueno se producira informacion en el monitor serie
}

void loop()
{
  //Buzzer
  if(digitalRead(buttonPin) == 0)
  {  // if you press the button, make a short buzz
    digitalWrite(buzzerP, HIGH);
    digitalWrite(buzzerN, LOW);
    delay(1);
    digitalWrite(buzzerP, LOW);
    digitalWrite(buzzerN, HIGH);
  }
  else  // If the button is not pressed go in here
  {
    if(digitalRead(switchPin) == 0)
    {  // If the switch is on, vibrate
      digitalWrite(vibePin, HIGH);
      delay(100);
      digitalWrite(vibePin, LOW); 
    }
    
    ///LIGHT TEST
    if(analogRead(lightSensorPin) < 20){
      //if its dark, turn on all white leds...
      for(int i=0;i<5;i++)
      {
        digitalWrite(ledPins[i], HIGH);
      }
    }
    else{
      // if it's light, turn them off...
      for(int i=0;i<5;i++)
      {
        digitalWrite(ledPins[i], LOW);
      }
    }

    ///TEMP TEST 
    if(analogRead(tempSensorPin) > 215)
    {
      //if the tech puts a little hot air over the temp sensor it will raise to at least 170
      digitalWrite(ledPins[5], LOW); //Turn on red LED - to indicate "hot"
    }
    else{
      digitalWrite(ledPins[5], HIGH);  // turn the red LED off
    }
    
    /* from here on down, we'll just print out the status of every input */
    Serial.print("Switch=");
    Serial.print(digitalRead(switchPin));

    Serial.print("  Temp=");
    Serial.print(analogRead(tempSensorPin));
    
    Serial.print("  Button=");
    Serial.print(digitalRead(buttonPin));

    Serial.print("  Light=");
    Serial.println(analogRead(lightSensorPin)); 
   
  }
}
