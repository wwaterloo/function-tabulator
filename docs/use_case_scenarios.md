# Use Case Scenarios

Actor: **Student** (the user of the program).

## UC1. Input data
**Goal:** set the parameters a, b, h, n for the calculation.
**Precondition:** the program is running and the main menu is displayed.

**Main flow:**
1. The user selects option 1 "Input data".
2. The program offers a choice of input method: keyboard or file.
3. The user selects a method (UC1.1 or UC1.2).
4. The program verifies the data (UC3).
5. The program reports that the data was entered successfully and returns to the main menu.

**Alternative flows:**
- 2a. The user enters a non-existent option or a letter: the program displays an error message and returns to the main menu.

**Result:** the data is stored in the program and ready for calculation.

### UC1.1. Input from Keyboard
**Main flow:**
1. The program prompts for a, b, h, n one by one.
2. The user enters a value.
3. The program verifies each value immediately after it is entered.

**Alternative flows:**
- 2a. The value is not a number: the program displays "Wrong data" and asks for this value again.
- 2b. b < a, h ≤ 0, n is not an integer, n < 2 or n > 10000: the program displays an error message and asks for the value again.
- 2c. The user enters `q`: the input is cancelled and the program returns to the main menu.

### UC1.2. Input from File
**Main flow:**
1. The program asks for the file name.
2. The user enters the name (for example, `input.txt`).
3. The program reads 4 numbers (a, b, h, n) and displays them on the screen.

**Alternative flows:**
- 3a. The file cannot be opened: the program displays an error message and returns to the main menu.
- 3b. The data format in the file is invalid: the program displays an error message and returns to the main menu.
- 3c. The data fails verification (UC3): the program reports an error and the data is not loaded.

## UC3. Verify the correctness of the data
Performed automatically as part of UC1 ("include" relationship).

**Validation rules:**
- a, b, h, n are numbers;
- b ≥ a;
- h > 0;
- n is an integer and 2 ≤ n ≤ 10000.

**Extension:** if at least one rule is violated, "Print Error if incorrect" is executed, i.e. the program displays an error message.

## UC2. Calculate result
**Goal:** calculate the function value for each x from a to b with step h.
**Precondition:** the data has been entered and verified (UC1 completed successfully).

**Main flow:**
1. The user selects option 2 "Calculate result".
2. The program calculates y for each x (x = a, a+h, a+2h, … ≤ b).
3. The program displays a table of x and y in the console (UC2.1).
4. The program saves all results to the file `results.txt` (UC2.2).
5. The program returns to the main menu.

**Alternative flows:**
- 1a. The data has not been entered yet: the program displays the message "you must input the data first" and returns to the main menu.
- 2a. x = 0: the value is not calculated, and a division-by-zero message is written to `results.txt`.
- 2b. The result is too large (infinity): it is marked as Infinity in the table and in the file.

### UC2.1. Show result from each step
The program displays a table of x and y in the console. To avoid overloading the screen, only the first step, the last step and every 1000th step are shown.

### UC2.2. Save result in file
The program writes all results to `results.txt` and notifies the user. Each new calculation overwrites the file.

## UC4. Exit
**Main flow:**
1. The user selects option 3 "Exit".
2. The program displays "Exiting program. Goodbye!" and terminates.
