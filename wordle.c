// by MSx4 || mafiaBoys
// Date Created : 3 Feb 2022 00:43:00 GMT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cs50.h"

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE ==
// right letter, wrong place; WRONG == wrong letter)
#define EXACT 2  // green
#define CLOSE 1  // yellow
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

void usage(char *exce) {
    fprintf(stdout, "Usage: %s wordsize\n", exce);
    exit(1);
}

int main(int argc, string argv[]) {
    // ensure proper usage
    // TODO #1

    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize
    // instead
    if (argc > 1) {
        wordsize = (int)strtoul(*(argv + 1), NULL, 16);

    } else
        usage(*(argv + 0));

    if (wordsize < 5 || wordsize > 8) {
        fprintf(stdout, "Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // open correct file, each file has exactly LISTSIZE words

    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");

    if (wordlist == NULL) {
        printf("Error opening file %s.\n", wl_filename);

        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    int i;
    for (i = 0; i < LISTSIZE; i++) {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));

    // bugs
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN "This is WORDLE50" RESET "\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n",
           guesses, wordsize);

    // main game loop, one iteration for each guess
    for (i = 0; i < guesses; i++) {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);
        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == wordsize * EXACT) {
            won = true;
            break;
        }
    }

    if (won == true) {
        printf("You won!\n");
    }

    return 0;
}

string get_guess(int wordsize) {
    string guess = "";
    do {
        guess = get_string("Input a %d-litters word : ", wordsize);
    } while (strlen(guess) != wordsize);

    return guess;
}

int check_word(string guess, int wordsize, int *status, string choice) {
    int j, i = 0, score = 0;

    // for cheat -> printf("choice : %s\n",choice);

    memset(status, WRONG, sizeof(status) * wordsize);

    while (choice[i] != 0 && i < wordsize) 
    {
        j = 0;
        while (guess[j] != 0 && j < wordsize) 
        {
            if (guess[j] == choice[i]) 
            {
                if (j == i) 
                {
                    status[j] = EXACT;
                    score++;
                } else if (status[j] == WRONG) {
                    status[j] = CLOSE;
                }
            }
            j++;
        }
        i++;
    }

    return score * EXACT;
}

void print_word(string guess, int wordsize, int status[]) {
    int i = 0;
    while (guess[i] != 0 && i < wordsize) 
    {
        switch (status[i]) 
        {
            case EXACT:
                printf(GREEN "%c" RESET, guess[i]);
                break;

            case CLOSE:
                printf(YELLOW "%c" RESET, guess[i]);
                break;

            default:
                printf(RED "%c" RESET, guess[i]);
                break;
        }
        i++;
    }

    printf("\n");
    return;
}
