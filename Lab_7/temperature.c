#include <stdio.h> //include stdio library
#include <string.h> //include string library

float celsius_to_fahrenheit (float celsius) { //converts given celsius to farhenheit
    return (9.0/5.0)*celsius + 32; // return the fahrenheit value
} // end of celsius_to_fahrenheit function

float fahrenheit_to_celsius (float fahrenheit) { // converts given fahrenheit to celsius
    return (5.0/9.0)*(fahrenheit-32); // return the celsius value
} // end of fahrenheit_to_celsius function

float celsius_to_kelvin (float celsius) { // converts given celsius to kelvin
    return celsius + 273.15; // return the kelvin value
} // end of celsius_to_kelvin function

float kelvin_to_celsius(float kelvin){ //converts given kelvin to celsius
    return kelvin - 273.15; // return the celsius value
} // end of kelvin_to_celsius function

void print_weather_stats(float current_temp) { // takes a temperature in kelvin and prints the advice for certain temperatures
    current_temp = kelvin_to_celsius(current_temp); // converts the kelvin temperature to celsius
    if (current_temp < 0) { // checks if temperature is less than 0
        printf("\nIt is freezing outside stay inside"); // prints that it is freezing outside
    } else if (current_temp < 10) { // checks if temperature is less than 10
        printf("\nIt is cold outside wear a jacket"); // print thst you should wear a jacket
    } else if (current_temp < 25) { // checks if temperature is less than 25
        printf("\nIt is a nice day you should go outside"); // prints that you should go outside
    } else if (current_temp < 35) { // checks if temperature is less than 35
        printf("\nIt is hot outside stay in the shade"); // prints that it is hot outside
    } else { // temperature is 35 or greater
        printf("\nIt is extremely hot stay inside"); // prints that it is extremely hot
    } // end of if statement
} // end of print_weather_stats function

int is_valid_scale(const char *s) { // takes a string and checks if it is a valid temperature scale
    return strcmp(s, "Fahrenheit") == 0 || strcmp(s, "Celsius") == 0 || strcmp(s, "Kelvin") == 0; // returns True if the string is a valid temperature scale
} // end of is_valid_scale function

int main() { // main function
    float temperature; // creates a temperature varaible
    float converted_temp; // creates a converted_temp variable
    char scale[100]; // creates a string for storing the input scale
    char conversion[100]; // creats a string for storing the conversion scale
    printf("Enter temperature value: "); // asks user to enter temperature value
    scanf("%f", &temperature); // reads in entered temperature value
    printf("\nChoose the temperature scale of the input value (Fahrenheit, Celsius, or Kelvin): "); // asks user to enter the input scale
    scanf("%s", scale); // reads in entered user input scale
    while (!(is_valid_scale(scale))) { // iterates until a valid scale is entered
        printf("Invalid scale entered\nEnter valid input tempterature scale (Fahrenheit, Celsius, or Kelvin): "); // prints that the scale is invalid
        scanf("%s", scale); // read in new user scale
    } // end of while loop
    float kelvin_temperature; // create a kelvin temperature variable
    if (strncmp(scale, "Fahrenheit", 10) == 0) { // checks if the scale is in fahrenheit
        kelvin_temperature = fahrenheit_to_celsius(temperature); // converts fahrenheit value  to celsius
        kelvin_temperature = celsius_to_kelvin(kelvin_temperature); // converts celsius value to kelvin
    } else if (strncmp(scale, "Celsius", 7) == 0) { // checks if the scals is in celsius
        kelvin_temperature = celsius_to_kelvin(temperature); // converts celsius to kelvin
    } else { // scale is in kelvin
        kelvin_temperature = temperature; // assigns kelvin temperature to entered temperature value
    } // end of if statement
    while (kelvin_temperature < 0) { // loops until a temperature that is greater than 0 kelvin is entered
        printf("temperature enter is below 0 kelvin\nEnter a valid temperature"); // prints that ths user enetered an invalid temperature
        scanf("%f", &temperature); // reads in the user temperature
        if (strncmp(scale, "Fahrenheit", 10) == 0) { // checks if the scale is in fahrenheit
            kelvin_temperature = fahrenheit_to_celsius(temperature); // converts fahrenheit to celsius
            kelvin_temperature = celsius_to_kelvin(kelvin_temperature); // converts celsius to kelvin
        } else if (strncmp(scale, "Celsius", 7) == 0) { // checks if the scale is in celsius
            kelvin_temperature = celsius_to_kelvin(temperature); // converts celsius to kelvin
        } else { // scale is in kelvin
            kelvin_temperature = temperature; // sets kelvin_temperature equal to temperature
        } // end of else statement
    } // end of while loop
    printf("\nChoose the conversion target (Fahrenheit, Celsius, or Kelvin): "); // asks the user to choose the scale to convert to
    scanf("%s", conversion); // reads in conversion scale entered by user
    while (!is_valid_scale(conversion) || strcmp(conversion, scale) == 0 ) { // loops until a valid conversion scale is entered
        printf("Invalid conversion scale entered\nEnter valid  conversion scale (Fahrenheit, Celsius, or Kelvin): "); // asks the user to enter another conversion scale
        scanf("%s", conversion); // reads in the new conversion scale
    } // end of while loop
    if (strncmp(scale, "Fahrenheit", 10) == 0) { // chekcs if input scale is fahrenheit
        converted_temp = fahrenheit_to_celsius(temperature); // converts temperature to celsius
        if (strncmp(conversion, "Kelvin", 6) == 0) { // checks if conversion scale is kelvin
            printf("Converted temperature is %f Kelvin", kelvin_temperature); // prints the converted temperature in kelvin
        } else { // conversion scale is in celsius
            printf("Converted temperature is %f Celsius", converted_temp); // prints the converted temperature in celsius
        } // end of else statement
    } else if (strncmp(scale, "Celsius", 7) == 0) { // checks if input scale is in celsius
        if (strncmp(conversion, "Fahrenheit", 10) == 0) { // checks if conversion scale is in fahrenheit
            converted_temp = celsius_to_fahrenheit(temperature); // converts temperature to fahrenheit
            printf("Converted temperature is %f Fahrenheit", converted_temp); // prints converted temperature in fahrenheit
        } else { // conversion scale is in kelvin
            printf("converted temperature is %f Kelvin", kelvin_temperature); // prints converted temperature in kelvin
        } // end of else statement
    } else { // input scale is in kelvin
        converted_temp = kelvin_to_celsius(temperature); // convert temperature to celsius
        if (strncmp(conversion, "Celsius", 7) == 0) { // check if converision scale is in celsius
            printf("Converted temperature is %f Celsius", converted_temp); // print converted temperature in celsius
        } else { // conversion scale is in fahrenheit
            converted_temp = celsius_to_fahrenheit(converted_temp); // convert temperature to fahrenheit
            printf("Converted temperature is %f Fahrenheit", converted_temp); // prints converted temperature in fahrenheit
        } // end of else statement
    } // end of if statement
    print_weather_stats(kelvin_temperature); // prints advice depending on the temperature
} // end of main function