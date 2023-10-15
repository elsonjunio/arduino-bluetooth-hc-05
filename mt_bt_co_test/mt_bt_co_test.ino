#include <SoftwareSerial.h>

//AT+UART=9600,1,0 To use 9600 need to chage BAUD. The command AT+BAUD4 does not work. (UART and BAUD must be equal)
//AT+UART=38400,1,0 <- Using that
//https://www.youtube.com/watch?v=90JYo5e9eIk


const long BAUD = 38400; // 9600

int ATMod = A0;
int BTHON = A1;

SoftwareSerial BTHC05(12, 11); // RX, TX


void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  BTHC05.begin(BAUD);

  pinMode(ATMod, OUTPUT);
  pinMode(BTHON, OUTPUT);

  Serial.setTimeout(100);

  Serial.println("Starting");

}

void loop() {
  // put your main code here, to run repeatedly:

  String command_sr;

  if (Serial.available() > 0){
    command_sr = Serial.readString();
    Serial.println("received command:" + command_sr);

    if (command_sr.equalsIgnoreCase("conf+\r\n")){
      digitalWrite(ATMod, HIGH);
    }

    if (command_sr.equalsIgnoreCase("conf-\r\n")){
      digitalWrite(ATMod, LOW);
    }

    if (command_sr.equalsIgnoreCase("on\r\n")){
      digitalWrite(BTHON, HIGH);
    }

    if (command_sr.equalsIgnoreCase("off\r\n")){
      digitalWrite(BTHON, LOW);
    }

    if (command_sr.startsWith("AT")){
      Serial.println("at command:" + command_sr);
      BTHC05.println(command_sr);
    }

  }

  if (BTHC05.available()){
    Serial.write(BTHC05.read());
  }
}
