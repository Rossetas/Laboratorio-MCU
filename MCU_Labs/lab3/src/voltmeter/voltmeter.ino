/*
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
*/

/*
  Marco Vasquez Ovares
  B17032
*/


// biblioteca pantalla LCD Nokia 5110
#include <PCD8544.h>

static PCD8544 lcd;
#define factor 511.5
float voltages[4] = {0.000, 0.000, 0.000, 0.000}; // array para los voltajes de 4 canales
const float ref_Voltaje = 24.00;

const int inputPins[4] = {A0, A1, A2, A3};  // pines de entrada analógica para los 4 canales
const int outputPins[4] = {8, 9, 10, 11};  // pines de salida para los 4 canales

void setup() {
    Serial.begin(9600);

    // configuracion de pines de warning como salidas
    for(int i = 0; i < 4; i++) {
        pinMode(outputPins[i], OUTPUT);
    }

    lcd.begin(); // default resolution is 84x48
    lcd.clear();

    lcd.setCursor(1, 0);
    lcd.print("Welcome");
    lcd.setCursor(1, 1);
    lcd.print("To");
    lcd.setCursor(1, 2);
    lcd.print("Voltmeter");

    attachInterrupt(digitalPinToInterrupt(2), clean_LCD, CHANGE); // ISR
    
    delay(2000);    
}

void clean_LCD() {
    lcd.clear();  
}

void serial_Display(const char *MODE, float voltages[]) {
    float EN = analogRead(A4);
   
    if(EN > factor) {
        Serial.println(MODE);
        for (int i = 0; i < 4; i++) {
            Serial.println(voltages[i]);
        }
    }
}

void lcd_Display(const char *MODE, float voltages[]) {
    lcd.setCursor(0, 0);
    lcd.print(MODE);
    
    for (int i = 0; i < 4; i++) {
        lcd.setCursor(0, i + 1);
        lcd.print("CH");
        lcd.print(i + 1);
        lcd.print(": ");
        lcd.print(voltages[i]);
        lcd.print("  ");
    }
}

float get_RMS(int PIN) {
    const int samples = 1000;
    float tmax = 0.00;

    for(int i = 0; i < samples; i++) {
        float t = analogRead(PIN);
        if(t > tmax) tmax = t;
    }

    float t_rms = ((tmax - factor) * (ref_Voltaje / factor));
    return (t_rms * 0.7071);
}

void AC_mode() {
    // calcular la tensión RMS para cada canal
    for (int i = 0; i < 4; i++) {
        voltages[i] = get_RMS(inputPins[i]);
    }

    warning();
    lcd_Display("AC MODE:", voltages);
    serial_Display("AC MODE", voltages);
}

void DC_mode() {
    // calcular los valores analógicos y calcular el voltaje para cada canal
    for (int i = 0; i < 4; i++) {
        voltages[i] = (analogRead(inputPins[i]) - factor) * (ref_Voltaje / factor);
    }

    warning();
    lcd_Display("DC MODE", voltages);
    serial_Display("DC MODE", voltages);
}

void warning() {
    // encender ls warnings de alto voltaje
    for (int i = 0; i < 4; i++) {
        if(voltages[i] > 20.00 || voltages[i] < -20.00) {
            digitalWrite(outputPins[i], HIGH);
        } else {
            digitalWrite(outputPins[i], LOW);
        }
    }
}

void loop() {
    float switch_ACDC = analogRead(A5);
    if(switch_ACDC < factor) {
        AC_mode();
    } else {
        DC_mode();
    }
}