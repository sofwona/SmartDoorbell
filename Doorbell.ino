#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>

//You should get Auth Token in the Blynk App
//Go to the Project Settings (nut icon)
char auth[]= "e91c67ddbfa5487b8d055427dbe7608f";

/*IPAddress server_ip (46, 101, 143, 255);
byte arduino_mac[] = {0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED};
IPAddress arduino_ip (192, 168, 1, 120);
IPAddress dns_ip (192, 168, 1, 254);
IPAddress gateway_ip (192, 168, 1, 254);
IPAddress subnet_mask (255, 255, 255, 0);*/


SimpleTimer timer;

WidgetLCD lcd(V1);

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth/*, server_ip, 8442, arduino_ip, dns_ip, gateway_ip, subnet_mask, arduino_mac*/);

  while (Blynk.connect() == false) {
    //wait until connected
  }
}
void notifyOnButtonPress ()
{
  //invert state, since button is "Active Low"
  int isButtonPressed = !digitalRead (2);
  if (isButtonPressed){
    BLYNK_LOG("Button is Pressed");

    Blynk.notify("Please open up! Somebody is at the door!");
    lcd.clear();//Use it to clear the LCD Widget
    lcd.print(4, 0, "Open");//use: (position X: 0-15, position Y: 0-1, "Message you want to print")
    lcd.print(4, 1, "The Door!");
  }
}

void emailOnButtonPress ()
{
  int isButtonPressed = !digitalRead (2);//Invert state, since button is "Active LOW"
  if (isButtonPressed)//You can write any condition to trigger e-mail sending
  {
    BLYNK_LOG("Button is pressed"); //This can be seen in the Serial Monitor
    Blynk.email("hassan.muhashamy@gmail.com", "Subject: Doorbell", "Please open up! Somebody is at the door!");
    lcd.clear();//use it to clear the LCD Widget
    lcd.print(4, 0, "Open"); //use: (position X: 0-15, position Y: 0-1, "Message you want to print")
    lcd.print(4, 1, "The Door!");
    
  }
}

void loop (){
  //put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
  
} 

