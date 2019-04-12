/*
Afleveringsopgave 3
02318 - C Programmering

Gruppe 32

Magnus Brandt Sløgedal
s103185
*/


//standard indput and output
#include <stdio.h>
//includes boolean type
#include <stdbool.h>
//include limits constants
#include <limits.h>

//contains functions used to verify user input
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//used to do the sleep timer that shows error messages
//as we need a non standard function we have to check what OS we're working on
//if _WIN32 exists, then the code is running on windows, if it's not we use the unix syntaxt instead
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif // _WIN32

#define MAX_INPUT_LENGTH 256

//#define TEST_   //TODO: Remove this to remove test data

//Structure to represent the institutes
typedef struct Institute
{
	char name[MAX_INPUT_LENGTH];
	int number;
} INSTITUTE;

//define struct TA, this is a datastucture that holds all data about a single TA.
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
	INTEGER, STRING, STUDENTNR, INSTITUTENR, BOOL_0_1

} inputType;

//wait for the specified time, primarily to show error messages for a few seconds
//takes a number of miliseconds to wait
void napTime(int time)
{
#ifdef _WIN32 //if we're on a windows mashine
	Sleep(time); //sleep for x miliseconds
#else	
	usleep(time * 1000);  //usleep is in microseconds to we hav to multiply by 1000
#endif // _WIN32

}

//custon input function, to validate user input.
//takes an array to store the return data in, and the type of data to validate for.
//returns FALSE if input fails to validate, and TRUE if it does.
bool getUserInput(char resultArray[], inputType x)
{
	//temporary string buffer.
	char inputChar[MAX_INPUT_LENGTH];


	//generic error check, fgets returns a NULL pointer on error so if fgets does'nt validate we have a problem
	if (!fgets(inputChar, sizeof inputChar, stdin))
	{
		fprintf(stderr, "Read error, feel free to panic");
		exit(-1);
	}
	//check if we have an end of file char, if not, then the user input is to long for the buffer.
	if (!strchr(inputChar, '\n'))
	{
		//empty the rest of the buffer
		while (fgets(inputChar, sizeof inputChar, stdin));
		fprintf(stderr, "Error input is to long,  (input > %d)", MAX_INPUT_LENGTH);
		napTime(1000); //sleep for 1 seconds
		//return 0 as the input is not valid
		return false;
	}

	//check if the string is an integer
	if (x == INTEGER || x== STUDENTNR || x == INSTITUTENR  || x == BOOL_0_1)
	{
		//pointer (char) used to hold the next value after a sucessfull conversion
		char *check;
		//attempt to convert the string to a long and thento an integer, strtol -> int
		int tmp = (int)strtol(inputChar, &check, 10);

		//check the value of the check variable, if it's a whitespace or a 0, then we sucesfully converted the entire string.
		if (!(isspace(*check) || *check == 0))
		{
			fprintf(stderr, "Error input is not an integer");
			napTime(1000); //sleep for 1 seconds
			return false;
		}
			
	}
	//special case for studentnr.
	if (x == STUDENTNR)
	{
		//check length = 6
		int temp = (int)strtol(inputChar, NULL, 10);
		if (temp < 100000 || temp > 999999)
		{
			fprintf(stderr, "Error input must be six digits in the format : XXXXXX");
			napTime(1000); //sleep for 1 seconds
			return false;
		}
	}
	//special case for Institute nr.
	if (x == INSTITUTENR)
	{
		//check between 1 and 25
		int temp = (int)strtol(inputChar, NULL, 10);
		if (temp < 1 || temp > 25)
		{
			fprintf(stderr, "Error please select a nr. between 1-25");
			napTime(1000); //sleep for 1 seconds
			return false;
		}
	}
	//special case for boolean integers
	if (x == BOOL_0_1)
	{
		//check between 0 and 1
		int temp = (int)strtol(inputChar, NULL, 10);
		if (temp < 0 || temp > 1)
		{
			fprintf(stderr, "Error please input 0 or 1");
			napTime(1000); //sleep for 1 seconds
			return false;
		}
	}


	//we have now passed all relevant checks, we copy the data to the output array and return true
	strcpy(resultArray, inputChar);
	return true;
}


void printTotalSickLeave(TA students[], int counter)
{
	double work = 0;
	double sick = 0;

	//loop all students
	for (int i = 0; i < counter; i++)
	{
		//summ both work and sickLeave
		work = work + students[i].workHours;
		sick = sick + students[i].sickLeave;
	}
	//calculate percentage
	double leavePercentage = (sick / work) * 100;

	//print to screen
	printf("Total Sick Leave is at:   %5.2f%%\n", leavePercentage);
}

void PrintMissingTACourse(TA students[], int counter)
{
	int completedTA = 0;
	//loop all students, as TA course = 1 for completed course we can simply sum them all up
	for (int i = 0; i < counter; i++)
		completedTA = completedTA + students[i].taCourse;

	//claculate missing
	double missingTA = counter - completedTA;

	//calculate percentage of all students
	double percentage = (missingTA / (double)counter) * 100;

	//print to screen
	printf("A total of %5.2f%% students have not completed the TA Course\n", percentage);
}

void printAllInstituteData(TA students[], int counter, INSTITUTE institutes[])
{
	//create an int array = 25 institutes
	int data[25] = { 0 };
	//loop all students
	for (int i = 0; i < counter; i++)
	{
		//for each institute sum work hours and add to the array
		data[students[i].institute.number-1] += (students[i].workHours - students[i].sickLeave);
	}

	//print to screen
	printf("%-10s %-35s %-10s\n", "Inst. NR","Inst. Navn","total TA timer");
	printf("------------------------------------------------------------\n");

	for (int i = 0; i < 25; i++)
	{
		printf("%-10d %-35s %-10d\n", institutes[i].number, institutes[i].name, data[i]);
	}
}
#ifdef TEST_
// test method, adds data to the array
int addTestData(TA students[], INSTITUTE institutes[])
{
	//add nine TA's
	for (int i = 0; i < 9; i++)
	{
		TA temp; //temporary stuct

		temp.studentNr = 123456 + (10 * i);				//studentnr.
		strcpy(temp.name, "testStudent");				//name
		temp.institute = institutes[i % 3];				//assign an institute
		temp.workHours = 100 - (i * 2);					//work Hours
		temp.sickLeave = 5 + i;							//sick Leave
		temp.taCourse = i % 2;							//TA Course

		students[i] = temp; //add the new TA to the array
	}
	//return 9, to be used as the counter
	return 9;
}
#endif // TEST_

//print funktion, recieves an array of TA's, and number of students to print.
void printDataInList(TA students[], int listSize)
{
	//prints the headder for the data
	printf("%-8s%-15s%-18s%-35s%-11s%-11s%-11s%-11s\n", "Index", "Studentnumber", "Name", "Institute", "Inst. Nr", "WorkHours", "SickLeave", "TA_Course");
	printf("---------------------------------------------------------------------------------\n");
	for (int i = 0; i < listSize; i++)
	{
		//prints each TA in list form, with all data
		printf("%-8d%-15d%-18s%-35s%-11d%-11d%-11d%-11d\n", (i+1), students[i].studentNr, students[i].name, students[i].institute.name, students[i].institute.number,
			students[i].workHours, students[i].sickLeave, students[i].taCourse);
	}
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

//given institute nr, prints all attached TA's for that institute and a total billable hours.
void printInstituteData(TA students[], INSTITUTE institutes[], int counter)
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
	char inputChar[MAX_INPUT_LENGTH];

	//select institute, we do this in a do/while loop so we can continue asking till we have a valid input.
	do
	{
		system("cls");
		printf(">>select institute<<\n");
		for (int i = 0; i < 25; i++) //instituteList is constant so we know its size
		{
			printf("%-8d %-35s\n", institutes[i].number, institutes[i].name);
		}
		printf(">");
		
	} while (!getUserInput(inputChar, INSTITUTENR));
	
	int instNr = 0;
	sscanf(inputChar, "%d", &instNr);

	//loop all students, check if they belong to the selected institute, and add to sum. 
	for (int j = 0; j < counter; j++)
	{
		if (students[j].institute.number == instNr)
		{
			sumTimer = sumTimer + students[j].workHours - students[j].sickLeave;
			toPrint[toPrintCounter] = students[j];
			toPrintCounter++;
		}
	}
	printf("\n");
	printf("Total TA Hours for: %d %s is: %d \n",institutes[instNr-1].number, institutes[instNr-1].name, sumTimer);

	printDataInList(toPrint, toPrintCounter);

	//free the malloc
	free(toPrint);
}

//prints all data in the main data array
void printAllData(TA students[], int counter)
{
	//as printDataInList prints all the TA's we give it, all we need to do is give it all the data. 
	printDataInList(students, counter);
}

//asks for input for a single student, then prints that students info
void printSingleTA(TA students[], int counter)
{
	//ask the user to select a student
	char inputChar[MAX_INPUT_LENGTH];
	do
	{
		system("cls");
		printf(">>select student by Student nr.<<\n");
		printf(">");

	} while (!getUserInput(inputChar, STUDENTNR));
	int inputStudentNr = 0;
	sscanf(inputChar, "%d", &inputStudentNr);


	//create array for the single student, no malloc here as we know at
	//compile-time how long an array for one student should be
	TA singleStudent[1];
	bool studentFound = false;
	//find that student in the array
	for (int i = 0; i < counter; i++)
	{
		if (students[i].studentNr == inputStudentNr)
		{
			singleStudent[0] = students[i];
			studentFound = true;
		}		
	}
	//check if we found something
	if (!studentFound)
		printf("Studentnr: %d, not found in database\n", inputStudentNr);
	else
	{
		//prinst data for the selected student
		printDataInList(singleStudent, 1);
	}
}

//add a single student to the data array.
void addTA(TA students[], int counter, INSTITUTE institutes[])
{

	TA temp; //temporary TA to store input data

	//we take 6 different options, we dont ask for institutename as that is definde by inst. number
	int i = 0;
	while (i < 6) //loop all 6 options, not using for-loop as this is a conditional increment
	{
		char inputChar[256];
		if (i == 0)
		{
			system("cls");
			printf("\n********************************************************\n");
			printf("**Add new TA**\n\n");
			printf("Input Name: ");
			if (getUserInput(inputChar, STRING)) //correct input
			{
				//remove trailing newline
				char cleanedString[MAX_INPUT_LENGTH];
				sscanf(inputChar, " %s", cleanedString);
				//add to struct
				strcpy(temp.name, cleanedString);
				i++;
			}
		}
		else if (i == 1)
		{
			system("cls");
			printf("\n********************************************************\n");
			printf("**Add new TA**\n\n");
			printf("Input Name: %s\n", temp.name);
			printf("Input Student Nr: ");
			if (getUserInput(inputChar, STUDENTNR)) //correct input
			{
				//casts input to integer, and store in the data array
				sscanf(inputChar, "%d", &temp.studentNr);
				i++;
			}

		}
		else if (i == 2)
		{
			system("cls");
			printf("\n********************************************************\n");
			printf("**Add new TA**\n\n");
			printf("Input Name: %s\n", temp.name);
			printf("Input Student Nr: %d\n", temp.studentNr);
			printf("Input Institute Nr: ");
			if (getUserInput(inputChar, INSTITUTENR)) //correct input
			{
				//casts input to integer, get the coresponding institute
				int instNR = 0;
				sscanf(inputChar, "%d", &instNR);
				temp.institute = institutes[instNR - 1]; //adjust for arrayindexing
				i++;
			}
		}
		else if (i == 3)
		{
			system("cls");
			printf("\n********************************************************\n");
			printf("**Add new TA**\n\n");
			printf("Input Name: %s\n", temp.name);
			printf("Input Student Nr: %d\n", temp.studentNr);
			printf("Input Institute Nr: %d  - %s\n", temp.institute.number, temp.institute.name);
			printf("Input Work Hours: ");
			if (getUserInput(inputChar, INTEGER)) //correct input
			{
				//casts input to integer, store in temp
				sscanf(inputChar, "%d", &temp.workHours);
				i++;
			}
		}
		else if (i == 4)
		{
			system("cls");
			printf("\n********************************************************\n");
			printf("**Add new TA**\n\n");
			printf("Input Name: %s\n", temp.name);
			printf("Input Student Nr: %d\n", temp.studentNr);
			printf("Input Institute Nr: %d  - %s\n", temp.institute.number, temp.institute.name);
			printf("Input Work Hours: %d\n", temp.workHours);
			printf("Input Sick Leave: ");
			if (getUserInput(inputChar, INTEGER)) //correct input
			{
				//casts input to integer, store in temp
				sscanf(inputChar, "%d", &temp.sickLeave);
				i++;
			}
		}
		else if (i == 5)
		{
			system("cls");
			printf("\n********************************************************\n");
			printf("**Add new TA**\n\n");
			printf("Input Name: %s\n", temp.name);
			printf("Input Student Nr: %d\n", temp.studentNr);
			printf("Input Institute Nr: %d  - %s\n", temp.institute.number, temp.institute.name);
			printf("Input Work Hours: %d\n", temp.workHours);
			printf("Input Sick Leave: %d\n", temp.sickLeave);
			printf("Input TA course 1 = yes, 0 = no: ");
			if (getUserInput(inputChar, BOOL_0_1)) //correct input
			{
				//casts input to integer, store in temp
				sscanf(inputChar, "%d", &temp.taCourse);
				i++;
			}
		}
	}
	//assign the input to the array
	students[counter] = temp;
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
	printf(":: 6 ::    Print Total Leave percentage\n");
	printf(":: 7 ::    Print percentage missing TA course\n");
	printf(":: 8 ::    Print All TA Hours for all Institutes\n");
	printf(":: x ::    Exit\n");
}

//quick method to break the flow of the program and await a user input.
void enterContinue()
{
	printf("Press >Enter< to continue . . .");
	fflush(stdout);
	getchar();
}


//if we hit the limit of the array, we extend it.
//should be called with the address(&) of the array, and the current length
int doubleArraySize(TA **students, int length)
{
	//double the length value
	int newLength = length * 2;
	//reallocate to the new array size
	*students = realloc(*students, newLength * sizeof(TA));
	if (students == NULL) //check if the realloc was sucessfull
	{
		printf("Error!! Realloc of studentDataArray failed.");
		exit(1);
	}
	//return the new length of the array.
	printf("sucesfully increased size to: %d", newLength);
	return newLength;
}

//main menu
void menu()
{
	bool isActive = true;

	//manually allocate an array for TA's
	int studentDataArrayLength = 10;
	TA *studentDataArray;

	studentDataArray = malloc(studentDataArrayLength * sizeof(TA));
	if (studentDataArray == NULL)
	{
		printf("Error!! Malloc of studentDataArray failed.");
		exit(1);
	}

	//list of Institutes
	const INSTITUTE instituteList[] = {	{ .number = 1,  .name = "DTU Aqua"},
										{ .number = 2,  .name = "DTU Bioengeneering" },
										{ .number = 3,  .name = "DTU Biosustain" },
										{ .number = 4,  .name = "Center for Oil and Gas - DTU" },
										{ .number = 5,  .name = "DTU Chemical engineering" },
										{ .number = 6,  .name = "DTU Chemistry" },
										{ .number = 7,  .name = "DTU Civil Engineering" },
										{ .number = 8,  .name = "DTU Compute" },
										{ .number = 9,  .name = "DTU Diplom" },
										{ .number = 10, .name = "DTU Electrical Engineering" },
										{ .number = 11, .name = "DTU Energy" },
										{ .number = 12, .name = "DTU Entepeneurship" },
										{ .number = 13, .name = "DTU Environment" },
										{ .number = 14, .name = "National Food Institute" },
										{ .number = 15, .name = "DTU Fotonik" },
										{ .number = 16, .name = "DTU Health Tech" },
										{ .number = 17, .name = "DTU Learn for Life" },
										{ .number = 18, .name = "DTU Management" },
										{ .number = 19, .name = "DTU Mechanical Engineering" },
										{ .number = 20, .name = "DTU Nanolab" },
										{ .number = 21, .name = "DTU Nutech" },
										{ .number = 22, .name = "DTU Physics" },
										{ .number = 23, .name = "DTU Space" },
										{ .number = 24, .name = "DTU Vet" },
										{ .number = 25, .name = "DTU Wind Energy"}
									  };

	
	//counts up what numer of students we have added.
	int counter = 0;

#ifdef TEST_
	//adds test data, and sets the counter for number of studenst added
	counter = addTestData(studentDataArray, instituteList);
#endif // TEST_

	//main loop, repeatedly shows the menu and listens for input
	while (isActive)
	{
		showMenuText();

		//gets exactly 255 characters from the input "stdin", saves the last space in the aray for newline.
		char inputChar[MAX_INPUT_LENGTH];
		getUserInput(inputChar, STRING);
		printf("\n");

		//test if the input is one of the menu options
		if (inputChar[0] == '1')
		{

			//check if the array still has room
			if (studentDataArrayLength - counter <= 2) //only 2 spots left
				studentDataArrayLength = doubleArraySize(&studentDataArray, studentDataArrayLength);

			//call the funktion with the arraypointer and the counter
			addTA(studentDataArray, counter, instituteList);


			//output the result to user
			system("cls");
			printf("added new TA:\n");
			printf("student name : %s \n", studentDataArray[counter].name);
			printf("studentnumber: %d \n", studentDataArray[counter].studentNr);
			printf("institute    : %s \n", studentDataArray[counter].institute.name);
			printf("institute nr : %d \n", studentDataArray[counter].institute.number);
			printf("work hours   : %d \n", studentDataArray[counter].workHours);
			printf("sick leave   : %d \n", studentDataArray[counter].sickLeave);
			printf("TA course    : %d \n", studentDataArray[counter].taCourse);

			//remember to increment counter as we have now added to the array
			counter++;

			//break the flow to alow the user to see the data added
			enterContinue();
		}

		else if (inputChar[0] == '2')
		{
			printAllData(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == '3')
		{
			printSingleTA(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == '4')
		{
			printInstituteData(studentDataArray, instituteList, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == '5')
		{
			worstBestTA(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == '6')
		{
			printTotalSickLeave(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == '7')
		{
			PrintMissingTACourse(studentDataArray, counter);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == '8')
		{
			printAllInstituteData(studentDataArray, counter, instituteList);
			//break the flow to alow the user to see the data added
			enterContinue();
		}
		else if (inputChar[0] == 'x')
			isActive = false;
		else
		{
			printf(">>invalid input<<\n");
			napTime(500);
		}	
	}
	//free the malloc
	free(studentDataArray);
}

int main()
{
	menu();
	return 0;
}