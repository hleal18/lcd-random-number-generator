#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define COLUMNS 16
#define ROWS 2

const uint8_t select_button = D1;
const uint8_t up_button = D2;
const uint8_t down_button = D3;
const uint8_t next_button = D4;

LiquidCrystal_I2C lcd(0x38, COLUMNS, ROWS);

void first_row_mesage(const char *message);
void first_row_mesage(unsigned int number);
void second_row_message(const char *message);
void second_row_message(unsigned int number);
void complete_message(const char *message);
void clear_row(uint8_t row);
void wait_for_button(uint8_t button);

void initiate_game();
void select_range();
void show_next_number(unsigned int number, uint8_t index);
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
    initiate_game();
}

void initiate_game()
{
    first_row_mesage("Presione para");
    second_row_message("iniciar");
    wait_for_button(select_button);
    select_range();
}

void select_range()
{
    unsigned int selected_number = 0;
    first_row_mesage("Elija la cantidad");
    second_row_message("de numeros ->");
    wait_for_button(next_button);
    first_row_mesage("Cantidad:");
    second_row_message(selected_number);
    while (!digitalRead(next_button))
    {
        if (digitalRead(up_button))
        {
            selected_number++;
            second_row_message(selected_number);
            delay(250);
        }
        else if (digitalRead(down_button))
        {
            selected_number--;
            second_row_message(selected_number);
            delay(250);
        }
    }
    delay(250);
    Serial.println("Numero seleccionado:");
    Serial.println(selected_number);

    if (selected_number <= 0)
        return;

    unsigned int numeros[selected_number];
    randomSeed(millis());
    bool found = true;
    // fill the array with values
    for (unsigned int i = 0; i < selected_number; i++)
    {
        while (found)
        {
            numeros[i] = random(1, selected_number + 1);
            for (unsigned int j = 0; j < i; j++)
            {
                if (numeros[j] == numeros[i])
                {
                    found = true;
                    break;
                }
                else if (j == i - 1)
                {
                    found = false;
                }
            }
            if (i == 0)
            {
                found = false;
            }
        }
        found = true;
    }

    // shuffle the array
    // explained on: https://stackoverflow.com/questions/32413209/shuffle-an-array-in-arduino-software
    // const size_t array_size = sizeof(numeros) / sizeof(numeros[0]);
    // for (size_t i = 0; i < array_size - 1; i++)
    // {
    //     size_t j = random(0, array_size - i);

    //     // swap the values between i and j index
    //     int t = numeros[i];
    //     numeros[i] = numeros[j];
    //     numeros[j] = t;
    // }

    do
    {
        for (unsigned int i = 0; i < selected_number; i++)
        {
            show_next_number(numeros[i], i + 1);
            wait_for_button(next_button);
        }
        first_row_mesage("Terminar? - N");
        second_row_message("Repetir? - S");
    } while (!digitalRead(next_button));
}

void first_row_mesage(const char *message)
{
    clear_row(0);
    lcd.setCursor(0, 0);
    lcd.print(message);
}

void first_row_mesage(unsigned int number)
{
    clear_row(0);
    lcd.setCursor(0, 0);
    lcd.write(number);
}

void second_row_message(const char *message)
{
    clear_row(1);
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void second_row_message(unsigned int number)
{
    clear_row(1);
    lcd.setCursor(0, 1);
    lcd.print(number);
}

void complete_message(const char *message)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println(message);
}

void clear_row(uint8_t row)
{
    lcd.setCursor(0, row);
    for (int i = 0; i < COLUMNS; i++)
    {
        lcd.print(" ");
    }
}

void show_next_number(unsigned int number, uint8_t index)
{
    first_row_mesage("Numero: ");
    lcd.print(index);
    second_row_message(number);
}

void wait_for_button(uint8_t button)
{
    while (!digitalRead(button))
        ;
    delay(250);
}