#include <stdio.h> // import the standard io library

int main() { // main function
    int end = 0; // creates an exit variable
    while (!end) { // while end variable isn't 1 loop
        int score; // creates a score varaible
        printf("Enter 0 or 1 to STOP\nEnter the NFL score: "); // asks user for a score
        scanf("%d", &score); // reads in the user input
        if (score <= 1) { //score is less than 1 so end program
            end = 1; //set end equal to 1
            printf("Exiting Program..."); // print that the program is ending
        } else { // score is greater than 1
            for (int td_2pt = 0; td_2pt <= score; td_2pt += 8) { // loop over possible touchdown plus 2 points values
                for (int td_1pt = 0; td_1pt <= score; td_1pt += 7) { // loop over possible touuchdown plus 1 point values
                    for (int td = 0; td <= score; td += 6) { // loop over possible touchdown values
                        for (int fg = 0; fg <= score; fg += 3) { // loop over possible field goal values
                            for (int safety = 0; safety <= score; safety += 2){ // loop over possible saefty values
                                if (td_2pt + td_1pt + td + fg + safety == score) { // checks if all current values add up to the score
                                    printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n", td_2pt/8, td_1pt/7, td/6, fg/3, safety/2); // print the current combination
                                } // end of if statement
                            } // end of safety for loop
                        } // end of field goal for loop
                    } // end of touchdown for loop
                } // end of touchdown plus 1 point for loop
            } // end of touchdown plus 2 points for loop
        } // end of else statement     
    } //end of while loop
    return 0; // return 0
} // end of main function
