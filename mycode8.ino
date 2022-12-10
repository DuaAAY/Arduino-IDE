
#define RA8875_INT 4
#define RA8875_CS 10 
#define RA8875_RESET 9

#define RELAY1  33                       
#define RELAY2  35                        
#define RELAY3  37                       
#define RELAY4  39
#define RELAY5  41
#define RELAY6  43

#include <RA8875.h>
#include <Brain.h>
#include <Arduino.h>
#include <String.h>

int a,b;
RA8875 tft = RA8875(RA8875_CS,RA8875_RESET);
Brain brain(Serial);
      
void setup() {
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);

  Serial.println("RA8875 start");
tft.begin(RA8875_480x272);
tft.fillWindow(RA8875_BLACK);
delay(1000);
Serial.begin(9600);
}

void loop() {
  
 long tab[4];
 int ti[2];
  String msg;
  
 if (brain.update()) {
  Serial.println(brain.readCSV());
       if (brain.readSignalQuality() > 100) {
     tft.fillWindow(RA8875_BLACK);
     tft.setCursor(0,30);
     tft.setTextColor(RA8875_RED,RA8875_BLACK);
     tft.println("signal quality low");
}

else{
         tab[0] = map (brain.readMeditation(),0,100,0,1023); 
         tab[1] = map (brain.readHighAlpha(),6000,9000,0,1023);
         tab[2] = map (brain.readAttention(),0,100,0,1023); 
         tab[3] = map (brain.readLowGamma(),70000,90000,0,1023);
         ti[0]=brain.readSignalQuality();
         ti[1]=brain.readAttention();
         ti[2]=brain.readMeditation();
         //lam(ti);
         msg=writeComp(compar(tab,4));
         Print(ti,6,msg);
         delay(4000);
        
}
}
 }

int compar(long* array, int size){  //fcontion to compare the inputs taht we put in an array and return the index of the max 
 int maxIndex = 0;
 int max = array[maxIndex];
 for (int i=1; i< size; i++){
   if (max<array[i]){
     max = array[i];
     maxIndex = i;
   }
 }
 return maxIndex;
}


String writeComp (int val){ // here is a fonction to make the use of the index of the max and use it to create a message to write once onll te reduce the time of computation
  
  String mess;
  switch (val) {

    case 0 :
         mess= String(" Relaxed      "); 
            digitalWrite( RELAY1, 0); 
            digitalWrite( RELAY2, 1);
            digitalWrite( RELAY3, 1);
            digitalWrite( RELAY4, 1);   
            digitalWrite( RELAY5, 1); 
            digitalWrite( RELAY6, 1);   
    break;
    case 1 :    
           mess=String(" awake, power     ");
            digitalWrite( RELAY2, 0);
            digitalWrite( RELAY1, 1); 
            digitalWrite( RELAY3, 1);
            digitalWrite( RELAY4, 1); 
            digitalWrite( RELAY5, 1); 
            digitalWrite( RELAY6, 1);
    break;
    case 2 :
           mess=String(" foucsed, alert     ");
           digitalWrite( RELAY3, 0);
           digitalWrite( RELAY1, 1); 
           digitalWrite( RELAY2, 1);
           digitalWrite( RELAY4, 1); 
           digitalWrite( RELAY5, 1); 
           digitalWrite( RELAY6, 1);
      
    break;
    
    case 3 :   
               mess=String("Multisensing process"); 
             digitalWrite( RELAY4, 0); 
             digitalWrite( RELAY5, 0); 
             digitalWrite( RELAY6, 0); 
             digitalWrite( RELAY3, 1);
             digitalWrite( RELAY1, 1); 
             digitalWrite( RELAY2, 1);
               
                       
    break;
    default: 
   mess=String("Out OF Range ");
   break;}
  
return mess;  
}

void Print(int* ar, int size,String m){
tft.setCursor(30,0);
   tft.setTextColor(RA8875_WHITE);
   tft.setFontScale(0);
   tft.println("Brain states mapping system");

   
  tft.setCursor(0, 30);
  tft.setTextColor(RA8875_YELLOW,RA8875_BLACK);
  tft.print("signal quality :");
  tft.print(ar[0]); //?
  tft.println(" ");
  tft.setTextColor(RA8875_RED,RA8875_BLACK);
    tft.print("Attention      :");   
    tft.print(ar[1]);
    tft.println(" ");
  tft.setTextColor(RA8875_YELLOW,RA8875_BLACK);
    tft.print("Meditation     :");
    tft.print(ar[2]);
    tft.println(" ");
   tft.setTextColor(RA8875_WHITE,RA8875_BLACK);
   tft.setFontScale(0);
   tft.print("state is:        ");
   tft.print(m); 
   delay(3000);
   
   
   
  
  
}


