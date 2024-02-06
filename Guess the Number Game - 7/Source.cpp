#include <iostream>   // Include the necessary header files for input/output operations
#include <cstdlib>    // Include the necessary header files for general-purpose functions
#include <ctime>      // Include the necessary header files for time-related functions
#include <vector>     // Include the necessary header files for vectors
#include <stdexcept>  // Include the necessary header files for standard exception classes

using namespace std;  // Use the standard namespace to simplify code readability

class AdvancedNumberGuesser {  // Define a class named AdvancedNumberGuesser
private:
    int secretNumber;         // Declare a private integer variable to store the secret number
    int previousGuess;        // Declare a private integer variable to store the previous guess
    int attempts;             // Declare a private integer variable to store the number of attempts
    bool hintsEnabled;        // Declare a private boolean variable to indicate if hints are enabled
    int score;                // Declare a private integer variable to store the player's score
    int maxAttempts;          // Declare a private integer variable to store the maximum number of attempts allowed
    vector<int> previousGuesses;  // Declare a private vector to store previous guesses

    int generateRandomNumber(int min, int max) {  // Declare a private function to generate a random number
        return rand() % (max - min + 1) + min;    // Generate a random number within the specified range
    }

    void updateScore() {  // Declare a private function to update the player's score
        if (attempts % 2 == 0) {
            score -= 50;   // Decrease the score by 50 if the number of attempts is even
        }
        else {
            score -= 30;   // Decrease the score by 30 if the number of attempts is odd
        }
    }

public:
    AdvancedNumberGuesser() {  // Constructor for the AdvancedNumberGuesser class
        srand(time(0));  // Seed the random number generator with the current time
        secretNumber = generateRandomNumber(1, 100);  // Generate a random secret number between 1 and 100
        previousGuess = 0;  // Initialize the previous guess to 0
        attempts = 0;       // Initialize the number of attempts to 0
        hintsEnabled = true;  // Enable hints by default
        score = 1000;        // Initialize the score to 1000
        maxAttempts = 10;     // Set the maximum number of attempts allowed to 10

        cout << "Welcome to the Advanced Number Guesser!" << endl;  // Display a welcome message
        cout << "Try to guess the secret number between 1 and 100." << endl;  // Provide instructions
        cout << "You can enter '0' to get a hint." << endl;  // Explain the hint feature
        cout << "You can also disable hints by entering '-1'." << endl;  // Explain how to disable hints
        cout << "Your score changes dynamically with each attempt, and there are only " << maxAttempts << " allowed." << endl;  // Explain scoring
    }

    void provideHint() {  // Function to provide a hint to the player
        if (!hintsEnabled) {
            cout << "Hints are currently disabled." << endl;  // Notify if hints are disabled
            return;
        }
        if (attempts == 0) {
            cout << "Need at least one guess prior to getting a hint." << endl;  // Notify if no previous guess
            return;
        }
        int difference = abs(previousGuess - secretNumber);  // Calculate the difference between guesses
        if (difference >= 20) {
            cout << "Hint: You are far from the secret number." << endl;  // Provide a hint based on the difference
        }
        else if (difference >= 10) {
            cout << "Hint: You are getting closer to the secret number." << endl;  // Provide a hint based on the difference
        }
        else {
            cout << "Hint: You are very close to the secret number." << endl;  // Provide a hint based on the difference
        }
    }

    void displayPreviousGuesses() {  // Function to display previous guesses
        if (!previousGuesses.empty()) {
            cout << "Previous guesses: ";
            for (int guess : previousGuesses) {
                cout << guess << " ";  // Display each previous guess
            }
            cout << endl;
        }
    }

    void playGame() {  // Function to play the number guessing game
        do {
            cout << "Attempts left: " << maxAttempts - attempts << " | Score: " << score << endl;  // Display attempts and score
            cout << "Enter your guess: ";

            int guess;
            
            try {
         
                cin >> guess;  // Read the player's guess from the console

                if (cin.fail()) {  // Check for input failure
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    throw runtime_error("Invalid input. Please enter a valid number.");  // Throw a runtime error
                }

                if ((guess < 1 || guess > 100) && (guess != 0 && guess != -1)) {  // Check for valid guess range
                    throw out_of_range("Invalid guess. Please enter a number between 1 and 100.");  // Throw an out_of_range exception
                }
                
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << endl;  // Display an error message
                continue;  // Continue to the next iteration of the loop
            }
            system("cls");  // Clear the console screen
            if (guess != 0 && guess != -1) {
                attempts++;  // Increment the number of attempts
                previousGuesses.push_back(guess);  // Add the guess to the vector of previous guesses
                updateScore();  // Update the player's score
            }

            if (guess == secretNumber) {
                cout << "Congratulations! You guessed the correct number in " << attempts << " attempts." << endl;  // Display a success message
                cout << "Your final score is: " << score << endl;  // Display the final score

            }
            else if (guess == 0) {
                provideHint();  // Provide a hint if the player requests one
            }
            else if (guess == -1) {
                hintsEnabled = false;  // Disable hints if the player chooses to
                cout << "Hints are now disabled. Continue guessing." << endl;  // Display a message indicating that hints are disabled

            }
            else if (guess < 1 || guess > 100) {
                cout << "Invalid guess. Please enter a number between 1 and 100." << endl;  // Display an error message for an invalid guess range
            }
            else if (guess < secretNumber && attempts < maxAttempts) {
                cout << "Too low. Try again!" << endl;  // Display a message indicating that the guess is too low
            }
            else if (guess > secretNumber && attempts < maxAttempts) {
                cout << "Too high. Try again!" << endl;  // Display a message indicating that the guess is too high
            }

            displayPreviousGuesses();  // Display the vector of previous guesses
            if (guess != 0 && guess != -1) {
                previousGuess = guess;  // Update the previous guess
            }
        } while (previousGuess != secretNumber && attempts < maxAttempts);  // Continue the loop until the correct number is guessed or maximum attempts are reached
        if (previousGuess != secretNumber) {
            cout << "You lost! The secret number was: " << secretNumber << endl;  // Display a message indicating that the player lost
            cout << "Your final score is: " << score << endl;  // Display the final score
        }
    }
};

int main() {
    AdvancedNumberGuesser advancedGame;  // Create an instance of the AdvancedNumberGuesser class
    advancedGame.playGame();  // Call the playGame method to start the game

    return 0;  // Return 0 to indicate successful program execution
}

