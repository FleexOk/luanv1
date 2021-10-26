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

//Includes del termómetro IR
#include <Wire.h>
#include <Adafruit_MLX90614.h>
//Includes 4 digitos
#include <TM1637Display.h>
//IA Del sistema
#include <TimerOne.h> //Foreach
#include <NewPing.h>

//Conexiones
const byte triggerUS = 12;
const byte echoUS = 11;
const byte dioTM = 10;
const byte clkTM = 9;
const byte buz = 7;
const byte engine = 6;
const byte green = 5;
const byte red = 4;
const byte reps = 10;

//Libraries cfig
TM1637Display display(clkTM, dioTM);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
NewPing sonar(triggerUS, echoUS, 200); //Trigger, Echo y Distancia

int uS, dis;

void setup() 
{
    Serial.begin(9600);
    mlx.begin();
    display.setBrightness(5);
    pinMode(buz, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
}
void loop()
{                 
    uS = sonar.ping_median();
    dis = uS / US_ROUNDTRIP_CM;
    if(dis < 25 && dis > 1){
        float t = 0;
        for(int i = 0; i < reps+1; i++){
          t+=mlx.readObjectTempC();
        }
        display.setBrightness(5);
        float temp = t/10;
        display.showNumberDec(temp);
        //Expulsar gel > Mover el motor
        if(temp > 40){
          
          if(temp > 150){
            Serial.print("MLX mal conectado");
            digitalWrite(buz, HIGH);
            delay(1500);
            digitalWrite(buz, LOW);
          }
          display.showNumberDec(1111);
          digitalWrite(red, HIGH); 
          for(int i = 0; i < 6; i++){
            digitalWrite(buz, HIGH); 
            delay(100);
            digitalWrite(buz, LOW); 
            delay(50);
          }
          digitalWrite(red, LOW);
        } else {
          digitalWrite(green, HIGH); 
          delay(1500);
          digitalWrite(green, LOW);
        }
        display.setBrightness(0);
        delay(2500);
    }
    display.showNumberDec(0000);
    delay(100);
}
