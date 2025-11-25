/*
 * Institute: Toronto Metropolitan University
 * Course: CPS188-052
 * Name: Isaac Zheng
 * Date Created: March 12, 2024
 * Date Submitted: March 31, 2024
 * Description: Term Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 1000
#define MAX_ROWS 3192
#define NUM_MONTHS 12
#define NUM_CENTURIES 4
#define NUM_YEARS 266

//Function that determines the yearly land temperature averages for each year between 1760-2015
void
calculateYearlyAverages(int years[], double averLandTemps[], double yearlyLandAverages[]){
	
	//Declare the variables
	double totalTemps;
	int monthCount = 0, averCount = 0;
	
	//For loop that runs through each row in entire file
	for (int i = 0; i < MAX_ROWS; i++){
		
		//
		if (years[i] >= 1760 && years[i] <= 2015){
			
			totalTemps += averLandTemps[i];
			monthCount++;
			
			//
			if (monthCount == NUM_MONTHS){
				
				yearlyLandAverages[averCount] = totalTemps / NUM_MONTHS;
				averCount++;
				
				totalTemps = 0;
				monthCount = 0;
				
			}
			
		}

	}
	
}
	
//Function that determines the average land temperatures for each century from 1760-2015
void
calculateCenturyAverages(int years[], int months[], double averLandTemps[], double centuryLandAverages[]){
	
	//Declare the variables
	double totalTemps;
	int averCount = 0;
	
	//For loop that runs through each row in entire file	
	for (int i = 0; i < MAX_ROWS; i++){
		
		//
		if (years[i] >= 1760 && years[i] <= 2015){
			
			totalTemps += averLandTemps[i];
			
			if (years[i] == 1799 && months[i] == 12){
				
				//Denominator has a +1 to include the subtracted year 
				//The denominator is multiplied by 12 to convert into months
				centuryLandAverages[averCount] = totalTemps / (((1799-1760)+1)*12); 
				averCount++;
				totalTemps = 0;
				
			}
			else if (years[i] == 1899 && months[i] == 12){
				
				centuryLandAverages[averCount] = totalTemps / (((1899-1800)+1)*12);
				averCount++;
				totalTemps = 0;
				
			}
			else if (years[i] == 1999 && months[i] == 12){
				
				centuryLandAverages[averCount] = totalTemps / (((1999-1900)+1)*12);
				averCount++;
				totalTemps = 0;
				
			}
			else if (years[i] == 2015 && months[i] == 12){
				
				centuryLandAverages[averCount] = totalTemps / (((2015-2000)+1)*12);
				averCount++;
				totalTemps = 0;
				
			}
			
		}
		
	}
	
}

//Function that determines the monthly average land temperature for all years combined from 1900-2015
void
calculateMonthlyAverages(int years[], int months[], double averLandTemps[], double monthlyLandAverages[]){
	
	//For loop that runs through each row in entire file	
	for (int i = 0; i < MAX_ROWS; i++){
		
		//Checks if the years lie between 1900 and 2015
		if (years[i] >= 1900 && years[i] <= 2015){
			
			//Switch case statement that checks for the month
			switch (months[i]){
				case 1:
					monthlyLandAverages[0] += averLandTemps[i]; //Add the average temp of that month
					break;
				case 2:
					monthlyLandAverages[1] += averLandTemps[i];
					break;
				case 3:
					monthlyLandAverages[2] += averLandTemps[i];
					break;
				case 4:
					monthlyLandAverages[3] += averLandTemps[i];
					break;
				case 5:
					monthlyLandAverages[4] += averLandTemps[i];
					break;
				case 6:
					monthlyLandAverages[5] += averLandTemps[i];
					break;
				case 7:
					monthlyLandAverages[6] += averLandTemps[i];
					break;
				case 8:
					monthlyLandAverages[7] += averLandTemps[i];
					break;
				case 9:
					monthlyLandAverages[8] += averLandTemps[i];
					break;
				case 10:
					monthlyLandAverages[9] += averLandTemps[i];
					break;
				case 11:
					monthlyLandAverages[10] += averLandTemps[i];
					break;
				case 12:
					monthlyLandAverages[11] += averLandTemps[i];
					break;
			}	
				
		}
				
	}
	
	//Calculate the average temp of the month
	//For loop runs through the array
	for (int i = 0; i < 12; i++){
		monthlyLandAverages[i] /= (2015-1900+1); //The +1 is to include the year 1900 when subtracting
	}
	
}

//Main Function
int
main(void)
{
	
	/* CSV File Reader Code: */
	
	//Declare the variables
	FILE *globalTempsFile;
	char row[MAX_CHAR];
	int years[MAX_ROWS-1], months[MAX_ROWS-1], days[MAX_ROWS-1];
	double averLandTemps[MAX_ROWS-1], averLandTempsUnc[MAX_ROWS-1];
	double maxLandTemps[MAX_ROWS-1], maxLandTempsUnc[MAX_ROWS-1];
	double minLandTemps[MAX_ROWS-1], minLandTempsUnc[MAX_ROWS-1];
	double averLandOceanTemps[MAX_ROWS-1], averLandOceanTempsUnc[MAX_ROWS-1];
	
	//Open the file
	globalTempsFile = fopen("GlobalTemperatures.csv", "r");
	
	//Check if the csv file is readable or exists
	if (globalTempsFile == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return (0);
	}
	
	//Get the first row of the csv file to read and skip the header
	fgets(row, sizeof(row), globalTempsFile);
	
	//Set the index value to 0
	int index = 0;
	
	//Run a while loop to scan the entire csv file
	while (fgets(row, sizeof(row), globalTempsFile) != NULL){
		
		//Split the csv string into a token
		char *yearString = strtok(row, "-");
		char *monthString = strtok(NULL, "-");
		char *dayString = strtok(NULL, ",");
		char *averLandTempString = strtok(NULL, ",");
		char *averLandTempUncString = strtok(NULL, ",");
		char *maxLandTempString = strtok(NULL, ",");
		char *maxLandTempUncString = strtok(NULL, ",");
		char *minLandTempString = strtok(NULL, ",");
		char *minLandTempUncString = strtok(NULL, ",");
		char *averLandOceanTempString = strtok(NULL, ",");
		char *averLandOceanTempUncString = strtok(NULL, ",");
		
		//Convert the variables char type to their respective variable type
		years[index] = atoi(yearString);
		months[index] = atoi(monthString);
		days[index] = atoi(dayString);
		averLandTemps[index] = atof(averLandTempString);
		averLandTempsUnc[index] = atof(averLandTempUncString);
		maxLandTemps[index] = atof(maxLandTempString);
		maxLandTempsUnc[index] = atof(maxLandTempUncString);
		minLandTemps[index] = atof(minLandTempString);
		minLandTempsUnc[index] = atof(minLandTempUncString);
		averLandOceanTemps[index] = atof(averLandOceanTempString);
		averLandOceanTempsUnc[index] = atof(averLandOceanTempUncString);
		
		//Increment the index
		index+=1;
			
	}
	
	
	/* Question Solving Codes: */
	
	//Question 1:
	//Declare the variables
	double yearlyLandAverages[2015-1760];
	int yearsC = 1760;
	
	//Calls function to calculate the average yearly land temperature
	calculateYearlyAverages(years, averLandTemps, yearlyLandAverages);
	
	//Print the resulted yearly land temperature
	printf("~Average Yearly Land Temperature~\n");
	for (int i = 0; i < (2015-1760+1); i++){ //Add 1 to include the subtracted year
		printf("%d %.2f\n" , yearsC, yearlyLandAverages[i]);
		yearsC+=1;
	}	

	//Question 2:
	//Declare the variables
	double centuryLandAverages[NUM_CENTURIES-1]; //Subtract 1 to account for index 0
	
	//Calls function to calculate the average century temperature
	calculateCenturyAverages(years, months, averLandTemps, centuryLandAverages);
	
	//Print the resulted average century temperature
	printf("\n~Average Land Temperature For Each Century~\n");
	printf("18th Century (1760-1799): %.2f\n", centuryLandAverages[0]);
	printf("19th Century (1800-1899): %.2f\n", centuryLandAverages[1]);
	printf("20th Century (1900-1999): %.2f\n", centuryLandAverages[2]);
	printf("21th Century (2000-2015): %.2f\n", centuryLandAverages[3]);
	
	//Question 3:
	//Declare the variabels
	double monthlyLandAverages[NUM_MONTHS-1]; //Subtract 1 to account for index 0
	char monthName[12][11] = {"January", 
		"February", 
		"March", 
		"April", 
		"May", 
		"June", 
		"July", 
		"August", 
		"September", 
		"October", 
		"November", 
		"December"};
	
	//Calls the function to calculate the monthly average land temperature
	calculateMonthlyAverages(years, months, averLandTemps, monthlyLandAverages);
	
	//Print the resulted average monthly land temperature
	printf("\n~Average Monthly Land Temperature~\n");
	for (int i = 0; i < NUM_MONTHS; i++){
		printf("%s: %.2f\n", monthName[i], monthlyLandAverages[i]);
	}
	
	//Question 4:
	//Declare the variables
	double hotTempM, coldTempM;
	int hotYearM, coldYearM, hotMonthM, coldMonthM;
	
	//Determine the hottest and coldest months
	hotTempM = averLandTemps[0]; //Set a temporary max value
	coldTempM = averLandTemps[0]; //Set a temporary min value
	for (int i = 1; i < MAX_ROWS; i++){
		if (averLandTemps[i] > hotTempM){
			hotTempM = averLandTemps[i];
			hotYearM = years[i];
			hotMonthM = months[i];
		}
		else if (averLandTemps[i] < coldTempM){
			coldTempM = averLandTemps[i];
			coldYearM = years[i];
			coldMonthM = months[i];
		}
	}
	
	//Print the resulted hottest and coldest months
	printf("\n~Hottest and Coldest Month~\n");
	printf("Hotteset Month Recorded: %d-0%d (Temperature: %.2f)\n", hotYearM, hotMonthM, hotTempM);
	printf("Coldest Month Recorded: %d-0%d (Temperature: %.2f)\n", coldYearM, coldMonthM, coldTempM);
	
	//Question 5:
	//Declare the variables
	double hotTempY, coldTempY;
	int hotYearY, coldYearY;
	
	//Determine the hottest and coldest year based on our answer for question 1
	hotTempY = yearlyLandAverages[0];
	coldTempY = yearlyLandAverages[0];
	for (int i = 1; i < (2015-1760+1); i++){ //Add 1 to include the subtracted year
		if (yearlyLandAverages[i] > hotTempY){
			hotTempY = yearlyLandAverages[i];
			hotYearY = years[((1760-1750)+i)*12];
		}
		else if (yearlyLandAverages[i] < coldTempY){
			coldTempY = yearlyLandAverages[i];
			coldYearY = years[((1760-1750)+i)*12];
		}
	}
	
	//Print the resulted hottest and coldest year
	printf("\n~Hottest and Coldest Year~\n");
	printf("Hottest Year: %d (Temperature: %.2f)\n", hotYearY, hotTempY);
	printf("Coldest Year: %d (Temperature: %.2f)\n", coldYearY, coldTempY);
	
	//Question 6
	//Declare the variables
	FILE *dataFileQ6;
	
	//Open the question 6 data file to be written on
	dataFileQ6 = fopen("CPS188_Q6_DataFile.txt", "w");
	
	//Check if the file exists or is readable
	if (dataFileQ6 == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return(0);
	}
	
	//Create the headers for the file
	fprintf(dataFileQ6, "Year YearlyTemperatures\n");
	
	//Write the data in the file
	for (int i = 0; i < (2015-1760+1); i++){ //Add 1 to include the subtracted year
		fprintf(dataFileQ6, "%d %.2lf\n", years[((1760-1750)+i)*12], yearlyLandAverages[i]);
	}
	
	//Close the data file
	fclose(dataFileQ6);
	
	//Question 7
	//Declare the variables
	FILE *dataFileQ7;
	
	//Open the question 7 data file to be written on
	dataFileQ7 = fopen("CPS188_Q7_DataFile.txt", "w");
	
	//Check if the file exists or is readable
	if (dataFileQ7 == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return(0);
	}
	
	//Create the headers for the file
	fprintf(dataFileQ7, "Years 19thAverageTemp 20th AverageTemp\n");
	
	//Write the data in the file
	for (int i = 0; i < (2015-1760+1); i++){ //Add 1 to include the subtracted year
		if (years[((1760-1750)+i)*12] >= 1800 && years[((1760-1750)+i)*12] <= 1899){
			fprintf(dataFileQ7, "%d ", (years[((1760-1750)+i)*12]-1800));
			fprintf(dataFileQ7, "%.2lf ", yearlyLandAverages[i]);
			fprintf(dataFileQ7, "%.2lf\n", yearlyLandAverages[i+100]);
		}
	}
	
	//Close the data file
	fclose(dataFileQ7);
	
	//Question 8
	//Declare the variables
	FILE *dataFileQ8;
	double averMaxLandTemp[2015-1850], averMinLandTemp[2015-1850];
	double totalMaxTemps, totalMinTemps;
	int monthCountQ8 = 0, averCountQ8 = 0;
	
	//Open the question 8 data file to be written on
	dataFileQ8 = fopen("CPS188_Q8_DataFile.txt", "w");
	
	//Check if the file exists or is readable
	if (dataFileQ8 == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return(0);
	}
	
	//Create the headers for the file
	fprintf(dataFileQ8, "Years LandTemp LandMaxTemp LandMinTemp\n");
	
	//Determine the average max and min values
	for (int i = 0; i < MAX_ROWS; i++){
		if (years[i] >= 1850 && years[i] <= 2015){
			totalMaxTemps += maxLandTemps[i];
			totalMinTemps += minLandTemps[i];
			monthCountQ8++;
			if (monthCountQ8 == NUM_MONTHS){
				averMaxLandTemp[averCountQ8] = totalMaxTemps / NUM_MONTHS;
				averMinLandTemp[averCountQ8] = totalMinTemps / NUM_MONTHS;
				averCountQ8++;
				totalMaxTemps = 0;
				totalMinTemps = 0;
				monthCountQ8 = 0;
			}
		}
	}
	
	//Write the data in the file
	for (int i = 0; i < (2015-1850+1); i++){ //Add 1 to include the subtracted year
		if (years[((1850-1750)+i)*12] >= 1850 && years[((1850-1750)+i)*12] <= 2015){
			fprintf(dataFileQ8, "%d ", (years[((1850-1750)+i)*12]));
			fprintf(dataFileQ8, "%.2lf ", yearlyLandAverages[(1850-1760)+i]);
			fprintf(dataFileQ8, "%.2lf ", averMaxLandTemp[i]);
			fprintf(dataFileQ8, "%.2lf\n", averMinLandTemp[i]);
		}
	}
	
	//Close the data file
	fclose(dataFileQ8);
	
	//Question 9
	//Declare the variables
	FILE *dataFileQ9;
	FILE *dataFileMaxQ9;
	FILE *dataFileMinQ9;
	double centuryMaxAverages[NUM_CENTURIES-2], centuryMinAverages[NUM_CENTURIES-2];
	double totalTempsMax, totalTempsMin;
	
	//Open the question 9 data file to be written on
	dataFileQ9 = fopen("CPS188_Q9_DataFile.txt", "w");
	dataFileMaxQ9 = fopen("CPS188_Q9_MaxDataFile.txt", "w");
	dataFileMinQ9 = fopen("CPS188_Q9_MinDataFile.txt", "w");
	
	//Check if the file exists or is readable
	if (dataFileQ9 == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return(0);
	}
	if (dataFileMaxQ9 == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return(0);
	}
	if (dataFileMinQ9 == NULL){
		printf("Error File Cannot Be Read or Detected!\n");
		return(0);
	}
	
	//Create the headers for the file
	fprintf(dataFileQ9, "Century Temp\n");
	fprintf(dataFileMaxQ9, "Century TempMax\n");
	fprintf(dataFileMinQ9, "Century TempMin\n");
	
	//Determine the max and min average century temperature	
	for (int i = 0; i < MAX_ROWS; i++){
		if (years[i] >= 1850 && years[i] <= 2015){	
			totalTempsMax += maxLandTemps[i];	
			totalTempsMin += minLandTemps[i];
			if (years[i] == 1899 && months[i] == 12){	
				//Denominator has a +1 to include the subtracted year 
				//The denominator is multiplied by 12 to convert into months
				centuryMaxAverages[0] = totalTempsMax / (((1899-1850)+1)*12);
				centuryMinAverages[0] = totalTempsMin / (((1899-1850)+1)*12);
				totalTempsMax = 0;	
				totalTempsMin = 0;
			}
			else if (years[i] == 1999 && months[i] == 12){	
				centuryMaxAverages[1] = totalTempsMax / (((1999-1900)+1)*12);
				centuryMinAverages[1] = totalTempsMin / (((1999-1900)+1)*12);
				totalTempsMax = 0;	
				totalTempsMin = 0;
			}
			else if (years[i] == 2015 && months[i] == 12){
				centuryMaxAverages[2] = totalTempsMax / (((2015-2000)+1)*12);
				centuryMinAverages[2] = totalTempsMin / (((2015-2000)+1)*12);
				totalTempsMax = 0;	
				totalTempsMin = 0;
			}
		}
	}
	
	//Write the data in the file
	fprintf(dataFileQ9, "19 %.2lf\n20 %.2lf\n21 %.2lf", centuryLandAverages[1], centuryLandAverages[2], centuryLandAverages[3]);
	fprintf(dataFileMaxQ9, "19 %.2lf\n20 %.2lf\n21 %.2lf", centuryMaxAverages[0], centuryMaxAverages[1], centuryMaxAverages[2]);
	fprintf(dataFileMinQ9, "19 %.2lf\n20 %.2lf\n21 %.2lf", centuryMinAverages[0], centuryMinAverages[1], centuryMinAverages[2]);
	
	//Close the data files
	fclose(dataFileQ9);
	fclose(dataFileMaxQ9);
	fclose(dataFileMinQ9);
	
	//Close the file
	fclose(globalTempsFile);
	
	return (0);
}

