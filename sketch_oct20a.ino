/*---------------------------Owners of the Software-------------------------------
Melnechuk Juan
Nuñez Lucas

---Créditos totales, escuela de robótica de Misiones-----------------------------



    __    __  _____    _   __       _    _____
   / /   / / / /   |  / | / /      | |  / <  /
  / /   / / / / /| | /  |/ /       | | / // / 
 / /___/ /_/ / ___ |/ /|  /        | |/ // /  
/_____/\____/_/  |_/_/ |_/         |___//_/   
                                              



*/

// GND = TIERRA; 5V = POSITIVO = VCC;

//Includes del termómetro IR
#include <Wire.h>
#include <Adafruit_MLX90614.h>
//Includes 4 digitos
#include <TM1637Display.h>
//IA Del sistema
#include <TimerOne.h> //Foreach
#include <NewPing.h>

TM1637Display display(9, 10);


Adafruit_MLX90614 mlx = Adafruit_MLX90614();

NewPing sonar(12, 11, 200); //Trigger, Echo y Distancia
int uS, dis;

void setup() //Iniciamos la placa y sus componentes
{
    Serial.begin(9600);
    display.setBrightness(5);
}
void loop() {
  int uS = sonar.ping_median() / US_ROUNDTRIP_CM;
  if (uS < 20 && uS > 1)
  {
    Serial.print("llego");
    float temp = mlx.readObjectTempC();
    display.showNumberDec(temp);
    
  }
  delay(300);
}










  
