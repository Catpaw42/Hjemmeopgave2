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

	//find the best and worst totals.
	for (int i = 0; i < counter; i++)
	{
		int j = array[i].workHours - array[i].sickLeave;
		if (j > bestSum)
			bestSum = j; //update best sum

		if (j < worstSum)
			worstSum = j; //update worst sum			
	}
	// clear previous menu
	system("cls");
	//find the students that those sums apply to
	printf(">>Best TA, totaling : %d work hours<<\n\n", bestSum);
	printf("%-10s%-18s%-15s%-15s%-15s%-15s\n", "index", "studentnumber", "institute", "work hours", "sick leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int j = 0; j < counter; j++)
	{
		if ((array[j][2] - array[j][3]) == bestSum)
		{
			printf("%-10d%-18d%-15d%-15d%-15d%-15d\n", j, array[j][0], array[j][1], array[j][2], array[j][3], array[j][4]);
		}
	}
	printf("\n\n\n");
	printf(">>Worst TA, totaling : %d work hours\n\n", worstSum);
	printf("%-10s%-18s%-15s%-15s%-15s%-15s\n", "index", "studentnumber", "institute", "work hours", "sick leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int j = 0; j < counter; j++)
	{
		if ((array[j][2] - array[j][3]) == worstSum)
		{
			printf("%-10d%-18d%-15d%-15d%-15d%-15d\n", j, array[j][0], array[j][1], array[j][2], array[j][3], array[j][4]);
		}
	}

}

void printInstituteData(int array[], int counter)
{
	//select institute
	system("cls");
	printf(">>select institute\n<<");
	char inputChar[256];
	fgets(inputChar, 256, stdin);
	int i = 0;
	sscanf(inputChar, "%d", &i);


	int sumTimer = 0;
	//loop all students, check if they belong to the selected institute, and add to sum. 
	printf("%-10s%-18s%-15s%-15s%-15s%-15s\n", "index", "studentnumber", "institute", "work hours", "sick leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int j = 0; j < counter; j++)
	{
		if (array[j][1] == i)
		{
			sumTimer = sumTimer + array[j][2] - array[j][3];
			printf("%-10d%-18d%-15d%-15d%-15d%-15d\n", j, array[j][0], array[j][1], array[j][2], array[j][3], array[j][4]);
		}
	}
	printf("\n");
	printf("Total TA Hours: %d \n", sumTimer);
}

void printAllData(int array[], int counter)
{
	system("cls");
	//prints all the data in the studentDataArray up til "counter"
	printf("%-10s%-18s%-15s%-15s%-15s%-15s\n", "index", "studentnumber", "institute", "work hours", "sick leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int i = 0; i < counter; i++)
	{
		printf("%-10d%-18d%-15d%-15d%-15d%-15d\n", i, array[i][0], array[i][1], array[i][2], array[i][3], array[i][4]);
	}

}

void printSingleTA(int array[])
{
	//ask the user so select a student
	system("cls");
	printf(">>select student<<\n");
	char inputChar[256];
	fgets(inputChar, 256, stdin);
	int i = 0;
	sscanf(inputChar, "%d", &i);
	//prinst data for the selected student
	printf("%-10s%-18s%-15s%-15s%-15s%-15s\n", "index", "studentnumber", "institute", "work hours", "sick leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	printf("%-10d%-18d%-15d%-15d%-15d%-15d\n", i, array[i][0], array[i][1], array[i][2], array[i][3], array[i][4]);

}

void addTA(int array[], int counter)
{
	//helper array, lets me print in a loop
	char texts[5][20] = { "studentnumber","institute","workHours","sickLeave","TACourse" };
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
void printDataInList(int toPrint[], TA array[])
{
	printf("%-10s%-18s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Index", "Studentnumber","Name", "Institute", "Inst. Nr", "Work Hours", "Sick Leave", "TA Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int j = 0; j < (sizeof(toPrint)/sizeof(toPrint[0])); j++)
	{
		int i = toPrint[j];

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