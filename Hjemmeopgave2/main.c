/*
Afleveringsopgave 3
02318 - C Programmering

Gruppe 32

Magnus Brandt Sløgedal
s103185

Mathias Nyberg Lundahl
s184750
*/


//standard indput and output
#include <stdio.h>
//includes boolean type
#include <stdbool.h>
//include limits constants
#include <limits.h>


#define MAX_INPUT_LENGTH 256


//Structure to represent the institutes
typedef struct Institute
{
	char name[MAX_INPUT_LENGTH];
	int number;
}INSTITUTE;
//define struct TA, this is a datastucture that holds all the about a single TA.
typedef struct Student
{
	char name[MAX_INPUT_LENGTH];
	INSTITUTE institute;
	int studentNr;
	int workHours;
	int sickLeave;
	int taCourse;
} TA;

//used to clearly show what data we're receiving from the user
typedef enum inputType 
{
	INTEGER, STRING, STUDENTNR

} inputType;


//custon input function, to validate user input.
//takes an array to store the data in, the length of that array, and the type of data to validate for.
//returns FALSE if input fails to validate, and TRUE if it does.
bool getUserInput(char resultArray[], int arrayLenght, inputType x)
{
	//temporary string buffer.
	char inputChar[MAX_INPUT_LENGTH];


	//generic error check, fgets returns a NULL pointer on error so if fgets does'nt validate we have a problem
	if (!fgets(inputChar, sizeof inputChar, stdin))
	{
		printf("Read error, feel free to panic");
		exit(-1);
	}
	//check if we have an end of file char, if not, then the user input is to long for the buffer.
	if (!strchr(inputChar, '\n'))
	{
		//empty the rest of the buffer
		while (fgets(inputChar, sizeof inputChar, stdin));
		printf("Error input is to long,  (input > %d)", MAX_INPUT_LENGTH);
		//return 0 as the input is not valid
		return false;
	}


	//check if the string is an integer
	if (x = INTEGER || STUDENTNR)
	{
		//pointer (char) used to hold the next value after a sucessfull conversion
		char *check;
		//attempt to convert the string to a long and thento an integer, strtol -> int
		int tmp = (int)strtol(inputChar, &check, 10);

		//check the value of the check variable, if it's a whitespace or a 0, then we sucesfully converted the entire string.
		if (!(isspace(*check) || *check == 0))
		{
			printf("Error input is not an integer");
			return false;
		}
			
	}
	//special case for studentnr.
	if (x = STUDENTNR)
	{
		//check length = 6
		int temp = (int)strtol(inputChar, NULL, 10);
		if (temp < 100000 || temp > 999999)
		{
			printf("Error Student nr is to long");
			return false;
		}
	}







	//default state, the input is a string.
	//we have now passed all relevant checks, we copy the data to the output array and return true
	strcpy(resultArray, inputChar);
	return true;
}

//test method, adds data to the array TODO: comment out when done!!
int addTestData(TA array[])
{
	//add nine TA's
	for (int i = 0; i < 9; i++)
	{
		TA temp; //temporary stuct

		temp.studentNr = 123456 + (10 * i);				//studentnr.
		strcpy(temp.name, "testStudent");				//name
		temp.institute.number = i % 3;						//institutenr.
		if(i % 3 == 0 )
			strcpy(temp.institute.name, "institute 1");	//institute name
		else if (i % 3 == 1)
			strcpy(temp.institute.name, "institute 2");
		else if (i % 3 == 2)
			strcpy(temp.institute.name, "institute 3");
		temp.workHours = 100 - (i * 2);					//work Hours
		temp.sickLeave = 5 + i;							//sick Leave
		temp.taCourse = i % 2;							//TA Course

		array[i] = temp; //add the new TA to the array
	}	
	//return 9, to be used as the counter
	return 9;
}

void worstBestTA(TA array[], int counter)
{
	int bestSum = 0;
	int worstSum = INT_MAX;


	//manually allocate a new array for Best TA, limit by counter so we can store ALL the TA's if needed
	TA *bestTA;
	bestTA = malloc(counter * sizeof(TA));
	if (bestTA == NULL)
	{
		printf("Error!! Malloc of BestTA failed.");
		exit(1);
	}
	int bestTACounter = 0;

	//manually allocate a new array for Worst TA, limit by counter so we can store ALL the TA's if needed
	TA *worstTA;
	worstTA = malloc(counter * sizeof(TA));
	if (worstTA == NULL)
	{
		printf("Error!! Malloc of worstTA failed.");
		exit(1);
	}
	int worstTACounter = 0;


	//find the best and worst totals.
	for (int i = 0; i < counter; i++)
	{
		int j = array[i].workHours - array[i].sickLeave;
		if (j > bestSum)
			bestSum = j; //update best sum

		if (j < worstSum)
			worstSum = j; //update worst sum			
	}


	//find the students that BestSum applies to, and store them in a separate array
	for (int j = 0; j < counter; j++)
		if ((array[j].workHours - array[j].sickLeave) == bestSum)
		{
			bestTA[bestTACounter] = array[j];
			bestTACounter++;
		}

	//find the students that worstSum applies to, and store them in a separate array
	for (int j = 0; j < counter; j++)
		if ((array[j].workHours - array[j].sickLeave) == worstSum)
		{
			worstTA[worstTACounter] = array[j];
			worstTACounter++;
		}

	//use PrintDataInList to print the results
	printf(">>Best TA, totaling : %d work hours<<\n\n", bestSum);
	printDataInList(bestTA, bestTACounter);

	printf("\n\n\n");
	printf(">>Worst TA, totaling : %d work hours\n\n", worstSum);
	printDataInList(worstTA, worstTACounter);

	
	//free the malloc
	free(bestTA);
	free(worstTA);

}

//given institute nr or name, prints all attached TA's for that institute and a total billable hours.
//TODO: make this work by name aswell
void printInstituteData(TA array[], int counter)
{
	//manually allocate a new array, limit by counter so we can store ALL the TA's if needed
	TA *toPrint;
	toPrint = malloc(counter * sizeof(TA));
	if (toPrint == NULL)
	{
		printf("Error!! Malloc of toPrint failed.");
		exit(1);
	}
	int toPrintCounter = 0;
	int sumTimer = 0;


	//TODO: print a list of the institutes here, by name.
	//select institute
	system("cls");
	printf(">>select institute\n<<");
	char inputChar[MAX_INPUT_LENGTH];
	getUserInput(inputChar, MAX_INPUT_LENGTH, INTEGER);
	int i = 0;
	sscanf(inputChar, "%d", &i);

	//loop all students, check if they belong to the selected institute, and add to sum. 
	for (int j = 0; j < counter; j++)
	{
		if (array[j].institute.number == i)
		{
			sumTimer = sumTimer + array[j].workHours - array[j].sickLeave;
			toPrint[toPrintCounter] = array[j];
			toPrintCounter++;
		}
	}
	printf("\n");
	printf("Total TA Hours: %d \n", sumTimer);

	printDataInList(toPrint, toPrintCounter);

	//free the malloc
	free(toPrint);
}

//prints all data in the main data array
void printAllData(TA array[], int counter)
{
	//as printDataInList prints all the TA's we give it, all we need to do is give it all the data. 
	printDataInList(array, counter);
}

//asks for input for a single student, then prints that students info
void printSingleTA(TA array[])
{
	//ask the user to select a student 
	//TODO: make this work with studentnr, and maybe name.
	system("cls");
	printf(">>select student<<\n");
	char inputChar[MAX_INPUT_LENGTH];
	getUserInput(inputChar, MAX_INPUT_LENGTH, STUDENTNR);
	int i = 0;
	sscanf(inputChar, "%d", &i);

	//create array for the single student, no malloc here as we know at
	//compile-time how long an array for one student should be
	TA singleStudent[1];
	singleStudent[0] = array[i];

	//prinst data for the selected student
	printDataInList(singleStudent, 1);

}

//add a single student to the data array.
void addTA(TA array[], int counter)
{
	//helper array, lets me print in a loop TODO: Extend, automated input of institute name
	system("cls");
	printf("\n********************************************************\n");
	printf("**Add new TA**\n\n");

	TA temp; //temporary TA to store input data

	for (int i = 0; i < 7; i++)
	{
		char inputChar[256];
		if (i = 0)
		{
			printf("Input Name :");
			if (getUserInput(inputChar, MAX_INPUT_LENGTH, STRING)) //correct input
			{
				strcpy(temp.name, inputChar);
			}
			else //invalid input
			{
				//reduce i by one, this forces the loop to ask for the same input again
				i--;
				printf("Invalid Input \n");
			}
		}
		else if (i = 1)
		{
			printf("Input Student Nr :");
			if (getUserInput(inputChar, MAX_INPUT_LENGTH, STUDENTNR)) //correct input
			{
				//casts input to integer, and store in the data array
				sscanf(inputChar, "%d", &temp.studentNr);
			}
			else //invalid input
			{
				//reduce i by one, this forces the loop to ask for the same input again
				i--;
				printf("Invalid Input, must be six digits the format: XXXXXX \n");
			}
		}
		else if (i = 2)
		{
			printf("Input Institute Nr :");
			if (getUserInput(inputChar, MAX_INPUT_LENGTH, INTEGER)) //correct input
			{
				//casts input to integer, and store in the data array
				sscanf(inputChar, "%d", &temp.institute.number);
			}
			else //invalid input
			{
				//reduce i by one, this forces the loop to ask for the same input again
				i--;
				printf("Invalid Input, must be integer \n");
			}
		}
		else if (i = 3)
		{
			printf("Input Work Hours :");
			if (getUserInput(inputChar, MAX_INPUT_LENGTH, INTEGER)) //correct input
			{

			}
			else //invalid input
			{
				//reduce i by one, this forces the loop to ask for the same input again
				i--;
				printf("Invalid Input, must be integer \n");
			}
		}
		else if (i = 4)
		{
			printf("Input Sick Leave :");
			if (getUserInput(inputChar, MAX_INPUT_LENGTH, INTEGER)) //correct input
			{

			}
			else //invalid input
			{
				//reduce i by one, this forces the loop to ask for the same input again
				i--;
				printf("Invalid Input, must be integer \n");
			}
		}
		else if (i = 5)
		{
			printf("Input TA course 1=yes, 2 = no :");
			if (getUserInput(inputChar, MAX_INPUT_LENGTH, INTEGER)) //correct input
			{

			}
			else //invalid input
			{
				//reduce i by one, this forces the loop to ask for the same input again
				i--;
				printf("Invalid Input, must be integer \n");
			}
		}
		


		//assign the inputted values to the array
		array[counter] = temp;
	}
}

void showMenuText()
{
	system("cls"); // clears the screen
	printf("********************************************************\n");
	printf("**Select option**\n\n");
	printf(":: 1 ::    Registrer new TA\n");
	printf(":: 2 ::    Print All info\n");
	printf(":: 3 ::    Print single student\n");
	printf(":: 4 ::    Print institue data\n");
	printf(":: 5 ::    Print best and worst TA\n");
	printf(":: x ::    Exit\n");
}

//quick method to break the flow of the program and await a user input.
void enterContinue()
{
	printf("Press >Enter< to continue . . .");
	fflush(stdout);
	getchar();
}

//print funktion, recieves the data array + a list of the TA's to print.
void printDataInList(TA array[], int listSize)
{
	//prints the headder for the data
	printf("%-10s%-18s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Index", "Studentnumber","Name", "Institute", "Inst. Nr", "Work Hours", "Sick Leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int i = 0; i < listSize; i++)
	{
		//prints each TA in list form, with all data
		printf("%-10d%-18d%-15s%-15s%-15d%-15d%-15d%-15d\n", i, array[i].studentNr, array[i].name, array[i].institute.name, array[i].institute.number,
																array[i].workHours, array[i].sickLeave, array[i].taCourse);
	}
}

void doubleArraySize(TA array[])
{

}

//main menu
void menu()
{
	bool isActive = true;
	//data array full of "struct Student"
	TA studentDataArray[4];
	//counts up what numer of students we have added.
	int counter = 0;

	//shows the menu first time
	showMenuText();

	//main loop, repeatedly shows the menu and listens for input
	while (isActive)
	{

		//gets exactly 255 characters from the input "stdin", saves the last space in the aray for newline.
		char inputChar[MAX_INPUT_LENGTH];
		getUserInput(inputChar, MAX_INPUT_LENGTH, INTEGER);

		showMenuText();
		printf("\n");


		//test if the input is one of the menu options
		if (inputChar[0] == '1')
		{
			//call the funktion with the arraypointer and the counter
			addTA(&studentDataArray, counter);


			//output the result to user
			system("cls");
			printf("added new TA:\n");
			printf("student name : %d \n", studentDataArray[counter].name);
			printf("studentnumber: %d \n", studentDataArray[counter].studentNr);
			printf("institute    : %d \n", studentDataArray[counter].institute.name);
			printf("institute nr : %d \n", studentDataArray[counter].institute.number);
			printf("work hours   : %d \n", studentDataArray[counter].workHours);
			printf("sick leave   : %d \n", studentDataArray[counter].sickLeave);
			printf("TA course    : %d \n", studentDataArray[counter].taCourse);


			//break the flow to alow the user to see the data added
			enterContinue();
			//show the menu again
			showMenuText();
			//remember to increment counter as we have now added to the array
			counter++;
		}

		else if (inputChar[0] == '2')
		{
			printAllData(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
			//show the menu again
			showMenuText();
		}
		else if (inputChar[0] == '3')
		{
			printSingleTA(studentDataArray);
			//break the flow to alow the user to see the data added
			enterContinue();
			//show the menu again
			showMenuText();
		}
		else if (inputChar[0] == '4')
		{
			printInstituteData(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
			//show the menu again
			showMenuText();
		}
		else if (inputChar[0] == '5')
		{
			worstBestTA(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
			//show the menu again
			showMenuText();
		}
		else if (inputChar[0] == 'x')
			isActive = false;
		else
			printf(">>invalid input<<\n");
	}
}

int main()
{
	menu();
	return 0;
}