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


//define struct TA
typedef struct Student
{
	char name[50];
	char instituteName[50];

	int instituteNr;
	int studentNr;
	int workHours;
	int sickLeave;
	int taCourse;
} TA;


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
//TODO: make tis work by name aswell
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
	char inputChar[256];
	fgets(inputChar, 256, stdin);
	int i = 0;
	sscanf(inputChar, "%d", &i);

	//loop all students, check if they belong to the selected institute, and add to sum. 
	for (int j = 0; j < counter; j++)
	{
		if (array[j].instituteNr == i)
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
void printAllData(int array[], int counter)
{
	//as printDataInList prints all the TA's we give it, all we need to do is give it all  the data. 
	printDataInList(array, counter);
}

//asks for input for a single student, then prints that students info
void printSingleTA(TA array[])
{
	//ask the user to select a student 
	//TODO: make this work with studentnr, and maybe name.
	system("cls");
	printf(">>select student<<\n");
	char inputChar[256];
	fgets(inputChar, 256, stdin);
	int i = 0;
	sscanf(inputChar, "%d", &i);

	TA singleStudent[1];
	singleStudent[0] = array[i];

	//prinst data for the selected student
	printDataInList(singleStudent, 1);

}

void addTA(TA array[], int counter)
{
	//helper array, lets me print in a loop TODO: Extend, automated input of institute name
	char texts[5][20] = { "studentnumber","institute","workHours","sickLeave","TACourse"};
	system("cls");
	printf("\n********************************************************\n");
	printf("**Add new TA**\n\n");

	for (int i = 0; i < COLS; i++)
	{
		//gets input from user
		printf("Input %s :", texts[i]);
		char inputChar[256];
		fgets(inputChar, 256, stdin);
		//casts input to integer, and store in the data array
		sscanf(inputChar, "%d", &array[counter][i]);
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
		printf("%-10d%-18d%-15s%-15s%-15d%-15d%-15d%-15d\n", i, array[i].studentNr, array[i].name, array[i].instituteName, array[i].instituteNr, 
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
		char inputChar[256];
		fgets(inputChar, 256, stdin);

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
			printf("institute    : %d \n", studentDataArray[counter].instituteName);
			printf("institute nr : %d \n", studentDataArray[counter].instituteNr);
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