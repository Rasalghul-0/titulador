
float fV;
float fpH;
float fT;
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
char pulsacion;  //Reconoce y almacena la tecla pulsada
int contador = 1; //Cuenta el nivel del menu en el que se esta
const byte ROWS = 4; // numero de filas
const byte COLS = 4;// numero de columnas
char keys[ROWS][COLS] ={


};  

byte rowPins[ROWS] ={}; //conexion del teclado al arduino filas
byte colPins[COLS] ={}; //conexion del teclado al arduino columnas
Keypad Teclado1 = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //Configura el teclado
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); // se prende la luz de la pantalla 
  intro_0(); //mensaje inicial
}

void loop() {
//Funciones del menu
  pulsacion = Teclado1.getKey();
  if (pulsacion != 0){
    lcd.clear();
    delay(100);
    
  }
  if(contador == 4){ calibracion();accion_cali();}
  if(contador == 3){ menu_3();accion_3();}
  if(contador == 2){ menu_2();accion_2();}
  if(contador == 1){ menu_1();accion_1();}

   //Obtengo el valor entero de la temperatura u el pH por promedio
  fT=0;
  fV=0;
  for (byte i=0;i<20;i++){
    fT=analogRead(A1)+fT;
    fV=analogRead(A0)+fV;
    delay(50);
  }
  //Obtengo el valor promedio de las 20 mediciones ¿ambiente?
  fT=fT/20.0;
  //Convierto T de °F a °C
  fT=fT/10.0;
  fT=(fT-32.0)*5.0/9.0;
  lcd.print("T val:");
  lcd.setCursor(4,0);
  lcd.print(fT);
  delay(3000);

  //Obtengo el valor promedio de las 20 mediciones
  fV=fV/20.0;
  fV=fV*5.0/1023.0;
  fpH=-5.70*fV+21,7;
  lcd.print("pH val:");
  lcd.setCursor(8, 0);
  lcd.print(fpH);
  delay(3000);
}
void intro_0(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Willkommen  ");
  lcd.setCursor(1, 1);
  lcd.print("Titrator  ");
  delay(5000);
  lcd.clear();
}

void menu_1(){
  lcd.setCursor(0,0);
  lcd.print("On   >1  ");
  lcd.setCursor(10,0);
  lcd.print("Off   >2  ");
  lcd.setCursor(0,1);
  lcd.print("Next  >0  ");
}
void accion_1(){ 
  if(pulsacion == '1') digitalWrite(12,HIGH);
  if(pulsacion == '2') digitalWrite(12,LOW);
  if(pulsacion == '0') contador=2;
}
void menu_2(){ 
   lcd.setCursor(0,0);
   lcd.print("Next >1   ");
   lcd.setCursor(8,0);
   lcd.print("calibracion >2");
   lcd.setCursor(0, 5);
   lcd.print("menu_1 >0"  );
   
}
void accion_2(){ 
  if(pulsacion == '1') contador=3;
  if(pulsacion == '2') contador=4;
  if(pulsacion == '0') contador=1;
}

void calibracion(){
  lcd.setCursor(0,0);
  lcd.print("pH_cali >1" );
  lcd.setCursor(5,0);
  lcd.print("bomba_cali >2" );
  lcd.setCursor(0,1);
  lcd.print("menu_2 >#" );
  lcd.setCursor(8,0);
  lcd.print("menu_1 >*" );
  
}

void accion_cali(){
  if(pulsacion == '1') //calibracion del pH 
  if(pulsacion == '2') //caliubracion de la bomba 
  if(pulsacion == '#') contador=2
  if(pulsacion == '*') contador=1
}
  
void menu_3(){
  lcd.setCursor(0,0);
  lcd.print("medir pH y T >1" );
  lcd.setCursor(0,1);
  lcd.print("menu_2 >#" );
  lcd.setCursor(8,0);
  lcd.print("menu_1 >*" );
}
void accion_3(){
  if(pulsacion == '1') // ¿Como mostramos el resultado de pH y T?
  if(pulsacion == '#') contador=2
  if(pulsacion == '*') contador=1
}
