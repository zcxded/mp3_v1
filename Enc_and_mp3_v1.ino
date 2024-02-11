


#define CLK 2
#define DT 3
#define SW 4

#include <GyverOLED.h>
#include "GyverEncoder.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
//Encoder enc1(CLK, DT);      // для работы без кнопки
Encoder enc1(CLK, DT, SW);  // для работы c кнопкой
//Encoder enc1(CLK, DT, SW, TYPE2);  // для работы c кнопкой и сразу выбираем тип
//Encoder enc1(CLK, DT, ENC_NO_BUTTON, TYPE2);  // для работы без кнопки и сразу выбираем тип
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX для плеера DFPlayer Mini 
DFRobotDFPlayerMini myDFPlayer;
boolean isPlaying = false; // статус воспроизведения/пауза
// Варианты инициализации:
// Encoder enc;                  // не привязан к пину
// Encoder enc(пин CLK, пин DT);        // энкодер без кнопки (ускоренный опрос)
// Encoder enc(пин CLK, пин DT, пин SW);    // энкодер с кнопкой
// Encoder enc(пин CLK, пин DT, пин SW, тип);  // энкодер с кнопкой и указанием типа
// Encoder enc(пин CLK, пин DT, ENC_NO_BUTTON, тип);  // энкодер без кнопкой и с указанием типа

void setup() {
  mySoftwareSerial.begin(9600); 
  Serial.begin(9600);
  enc1.setType(TYPE1);
  oled.init();  // инициализация
  oled.clear();   // очистить дисплей (или буфер)
  oled.update();  // обновить. Только для режима с буфером! OLED_BUFFER


  delay(1000);
  
  Serial.println();
  Serial.println("DFPlayer Mini Demo");
  Serial.println("Initializing DFPlayer...");
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(300);
  //----Set volume----
  myDFPlayer.volume(15); //Set volume value (0~30).
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  isPlaying = false; // воспроизводим
}

void loop() {
  enc1.tick();
  
  if (enc1.isTurn()) {    
  }
  
  if (enc1.isRight()) {
    if (isPlaying) {
      myDFPlayer.next(); //Next Song
      Serial.println("Next Song..");
    }
    delay(500);
  };
  
  if (enc1.isLeft()) {
    if (isPlaying) {
      myDFPlayer.previous(); 
      Serial.println("Previous Song..");
    }
    delay(500);
  };
  
  if (enc1.isRightH()) {
    if (isPlaying) {
      myDFPlayer.volumeUp(); //Volume Up
      myDFPlayer.volumeUp(); 
      myDFPlayer.volumeUp(); 
      Serial.println("Volume Up..");
    }
    delay(500);
  };
  
  if (enc1.isLeftH()) {
    if (isPlaying) {
      myDFPlayer.volumeDown(); //Volume Down
      myDFPlayer.volumeDown();
      myDFPlayer.volumeDown();
      Serial.println("Volume Down..");
    }
    delay(500);
  };
  
  if (enc1.isClick()) {
     if (isPlaying) { // если было воспроизведение трека
      myDFPlayer.pause(); // пауза
      isPlaying = false; // пауза
      Serial.println("Paused..");
    } else {        // иначе
      isPlaying = true; // воспроизводим==
      myDFPlayer.play(01); //запускаем mp3 с паузы
      Serial.println("Play..");
      
    }
    delay(500);
  };         

  if (enc1.isHolded()) {
    Serial.println("Holded");
  };
}
  