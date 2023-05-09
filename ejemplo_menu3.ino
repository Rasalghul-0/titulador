#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
float fV;
float fpH;
float fT;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'A','B','C','D'},
  {'3','6','9','#'},
  {'2','5','8','0'},
  {'1','4','7','*'}
};
byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,0);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Bienvenido"));
  display.setCursor(0,15);             // Start at top-left corner
  display.print(F("Titulador"));
  display.display();
  delay(1000);
  
  
}

char tecla;
byte menu=0;
  
void loop(){ 
 //Obtengo el valor entero de la temperatura u el pH por promedio
  fT=0;
  fV=0;
  for (byte i=0;i<20;i++){
    fV=analogRead(A0)+fV;
    delay(50);

  //Obtengo el valor promedio de las 20 mediciones
  fV=fV/20.0;
  fV=fV*5.0/1023.0;
  fpH=-5.70*fV+21,7;

}
  tecla = customKeypad.getKey();

  //Entrada a menus
  switch(menu){
    case 0: menu_0(); accion_0();   break;
    case 1: menu_1(); accion_1();   break;
    case 2: menu_2(); accion_2();   break;
    case 3: menu_3(); accion_3();   break;
    case 4: menu_4(); accion_4();   break;
  }

}

void menu_0(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("On>1"));
  display.setCursor(62,0);
  display.print(F("Off>2"));
  display.setCursor(0,16);
  display.print(F("Next>0  "));
  display.display();
}


void accion_0(){ 
  if(tecla == '1') digitalWrite(13,HIGH);
  if(tecla == '2') digitalWrite(13,LOW);
  if(tecla == '0') menu=1;
}

void menu_1(){
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("Ca=A  Ti=B"));
  display.setCursor(0,16);
  display.print(F("back #"));
  display.display();
  }
  
void accion_1(){ 
  if(tecla == 'A') menu=2;
  if(tecla == 'B') menu=3;
  if(tecla == '#') menu=0;
  }

void menu_2(){
 display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("CapH>1"));
  display.setCursor(62,0);
  display.print(F("CaB>2"));
  display.setCursor(0,16);
  display.print(F("back># "));
  display.setCursor(0,16);
  display.print(F("next>0 "));
  display.display();
  }

void accion_2(){ 
  if(tecla == '#') menu=menu-1;
  if(tecla == '1') ;
  if(tecla == '2') ;
  if(tecla == '0') menu=menu+1; 
}

void menu_3(){
   display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("Ti>1"));
  display.setCursor(62,0);
  display.print(F("Q>2"));
  display.setCursor(0,16);
  display.print(F("back># "));
  display.setCursor(0,16);
  display.display();
}

void accion_3(){ 
  if(tecla == '#') menu=menu-1;
  if(tecla == '1') display.print(fpH);
  if(tecla == '2') menu=4;
 
}
void menu_4(){
   display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print(F("Up>1"));
  display.setCursor(62,0);
  display.print(F("Low>2"));
  display.setCursor(0,16);
  display.print(F("back># "));
  display.setCursor(0,16);
  display.display();
}
void accion_4(){ 
  if(tecla == '#') menu=menu-1;
  if(tecla == '1') ;
  if(tecla == '2') ;
  }
