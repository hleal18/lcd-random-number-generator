#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// A4 -> SDA
// A5 -> SCL

const uint8_t select_button = 5;
const uint8_t up_button = 6;
const uint8_t down_button = 7;
const uint8_t next_button = 8;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void first_row_mesage(const char* message);
void second_row_message(const char* message);

void initiate_game();
void select_range();
void show_next_number();
void end_game();

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(select_button, INPUT);
    pinMode(up_button, INPUT);
    pinMode(down_button, INPUT);
    pinMode(next_button, INPUT);

    lcd.init();
    lcd.backlight();
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (digitalRead(select_button))
    {
        Serial.println("Boton 1 oprimido");
        first_row_mesage("Boton 1 oprimido");
    }
    if (digitalRead(up_button))
    {
        Serial.println("Boton 2 oprimido");
        second_row_message("Boton 2 oprimido");
    }
    if (digitalRead(down_button))
    {
        Serial.println("Boton 3 oprimido");
        first_row_mesage("Boton 3 oprimido");
    }
    if (digitalRead(next_button))
    {
        Serial.println("Boton 4 oprimido");
        second_row_message("Boton 4 oprimido");
    }
}

void first_row_mesage(const char* message)
{
    lcd.setCursor(0, 0);
    lcd.flush();
    lcd.print(message);
}

void second_row_message(const char* message)
{
    lcd.setCursor(0, 1);
    lcd.flush();
    lcd.print(message);
}