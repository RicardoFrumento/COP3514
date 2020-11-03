/* Ricardo Digiovanni Frumento U25167829
   COP3514 Project 6
   This program reads a file, one line at a time, and stores part of the information (phone numbers)
   from that line in another file, one line at a time
*/
#include <stdio.h>
#include <string.h>

void extract_phone(char *input, char *phone); //Prototype of the function extract_phone

int main(){

    char nameInput[100]; //This will be used as the buffer for the file being read
    char nameOutput[100]="phone_"; //This will be used as the buffer to the file being created
    char lineInput[10000]; //This will be used as the buffer for the line being read
    char lineOutput[10000]; //This will be used as the buffer for the line being written
    FILE *filePointerInput; //Declaring pointers to files
    FILE *filePointerOutput;

    printf("Enter the file name:\n"); //Asks for the file's name
    fgets(nameInput, 100, stdin);
    strtok(nameInput, "\n"); //Removes the 'new line' character from the string

    filePointerInput = fopen(nameInput, "r"); //Open the file to be read
    strcat(nameOutput, nameInput); //Creates the string to be used as the name for the file to be written
    filePointerOutput = fopen(nameOutput, "w"); //Creates the file to be written
    printf("Output file name: %s\n", nameOutput);

    if(filePointerInput != NULL){ //Checks if the file opened correctly
        while(fgets(lineInput, 10000, filePointerInput)!=NULL){ //Reads one line until it finds an empty line
            extract_phone(lineInput, lineOutput); //Calls the function to extract the desired information
            fputs(lineOutput, filePointerOutput); //Writes the desired information on the file to be written
        }
    }
    else{
        printf("The file did not open correctly!\n"); //Error message if the file did not open correctly
    }
    fclose(filePointerInput); //Closes the file read
    fclose(filePointerOutput); //Closes the file written
    return 0;
}

/* extract phone
   The function uses two pointers to arrays of chars to go through the first array copying only the relevant information to the second array
   *input is the pointer to the first array
   *phone is the pointer to the second array
   count is a variable used to check how many '_' have passed
   The function has no return value because it updates directly in the main function
*/
void extract_phone(char *input, char *phone){
    int count=0; //Declares and initializes the variable count
    while(*input!='\0'){ //Checks for the end of string character
        if(*input=='_')count++; //Increments by one the count variable
        input++; //Goes to the next element of the array
        if(count==2){ //If two '_" have passed starts storing the characters on the second array
            *phone=*input; //Makes the value of the pointer equal
            phone++; //Goes to the next element of the second array
        }
    }
}
