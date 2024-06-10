#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#pragma warning(disable:4996)

void logo();
void previousTable(int, int, int, int, int, int, int, int, int, int, int, float, float, float);
void inputCurrentData(int*, int*, int*, int*, int, int,int);
void calculateTotal(int, int, int, int, int, int, int, int, int*, int*, int*, int*, int*);
void calculatePercentage(int, int, int, int, int, int, float*, float*, float*);
void calculateDifference(int,int,int,int, int, float, float, int, int, float, float, int*, int*, float*, float*);
void summaryReport(int, int, int, int, int, int, int, int, float, float, float);
void comparativeReport(int, int, int, int, int, float, float, int, int, float, float, int, int, float, float);
char viewing();


void main()
{
	//memory constants previous day 9
	const int PREVIOUS_NEW_CASES = 9;
	const int PREVIOUS_TOTAL_CASES = 100;
	const int PREVIOUS_TOTAL_DEATHS = 2;
	const int PREVIOUS_TOTAL_RECOVERED = 10;
	const int PREVIOUS_UNDER_TREATMENT = 88;

	// array for calculate day of highest and lowest new cases
	int day[2] = { 9 ,9 };

	//variable current day(input)
	int currentLocalCases, currentImportedCases, currentDeaths, currentRecovered;

	//variable for calculate total and percentage(process)
	int newCases, totalCases, totalDeaths = 0, totalRecovered = 0, underTreatment = 0;
	float percentagePreviousTreatment, percentagePreviousDeath, percentagePreviousRecovered, percentageTotalDeaths , percentageTotalRecovered , percentageUnderTreatment;

	//variable for calculate difference(process)
	float compareDeathRate , compareRecoveredRate;
	int compareNewCases , compareTotalcases;

	//variable for output
	char choice, yesNo;
	int currentDay = 10, totalDay = 0, highest = PREVIOUS_NEW_CASES, lowest = PREVIOUS_NEW_CASES;
	int oldNewCases = 0, oldTotalCases = 0;


	//logo
	logo();

	//LOOPING
	do {
		if (currentDay != 10)
		{
			oldTotalCases = totalCases;
			oldNewCases = newCases;

			percentagePreviousDeath = totalDeaths / (float)totalCases * 100;
			percentagePreviousRecovered = totalRecovered / (float)totalCases * 100;
			percentagePreviousTreatment = underTreatment / (float)totalCases * 100;
		}
		else
		{
			percentagePreviousRecovered = PREVIOUS_TOTAL_RECOVERED / (float)PREVIOUS_TOTAL_CASES * 100;
			percentagePreviousDeath = PREVIOUS_TOTAL_DEATHS / (float)PREVIOUS_TOTAL_CASES * 100;
			percentagePreviousTreatment = PREVIOUS_UNDER_TREATMENT / (float)PREVIOUS_TOTAL_CASES * 100;
		}


		//previous day's data
		previousTable(currentDay, PREVIOUS_NEW_CASES, PREVIOUS_TOTAL_CASES, PREVIOUS_TOTAL_DEATHS, PREVIOUS_TOTAL_RECOVERED, PREVIOUS_UNDER_TREATMENT, oldNewCases, oldTotalCases, totalDeaths, totalRecovered, underTreatment, percentagePreviousDeath, percentagePreviousRecovered, percentagePreviousTreatment);

		//input
		inputCurrentData(&currentLocalCases, &currentImportedCases, &currentDeaths, &currentRecovered, PREVIOUS_NEW_CASES, currentDay, oldNewCases);

		//process calculation
		calculateTotal(currentDay, PREVIOUS_TOTAL_CASES, PREVIOUS_TOTAL_DEATHS, PREVIOUS_TOTAL_RECOVERED, currentLocalCases, currentImportedCases, currentDeaths, currentRecovered, &newCases, &totalCases, &totalDeaths, &totalRecovered, &underTreatment);
		calculatePercentage(currentDay, newCases, totalCases, totalDeaths, totalRecovered, underTreatment, &percentageTotalDeaths, &percentageTotalRecovered, &percentageUnderTreatment);
		calculateDifference(currentDay, oldNewCases, oldTotalCases, PREVIOUS_TOTAL_CASES, PREVIOUS_NEW_CASES, percentagePreviousRecovered, percentagePreviousDeath, newCases, totalCases, percentageTotalDeaths, percentageTotalRecovered, &compareNewCases, &compareTotalcases, &compareDeathRate, &compareRecoveredRate);

		//output
		do {
			rewind(stdin);
			choice = viewing();
			if (choice == '1')
				summaryReport(currentDay, currentLocalCases, currentImportedCases, newCases, totalCases, totalDeaths, totalRecovered, underTreatment, percentageTotalDeaths, percentageTotalRecovered, percentageUnderTreatment);
			else if (choice == '2')
				comparativeReport(currentDay, oldTotalCases, oldNewCases, PREVIOUS_TOTAL_CASES, PREVIOUS_NEW_CASES, percentagePreviousRecovered, percentagePreviousDeath, newCases, totalCases, percentageTotalDeaths, percentageTotalRecovered, compareNewCases, compareTotalcases, compareDeathRate, compareRecoveredRate);
			else
			{
				printf("\033[0;31m");
				printf("<ERROR> Please enter a valid number.\n\n");
				printf("\033[0m");
			}
		} while (!(choice == '1' || choice == '2'));

		printf("\033[0m");
		printf("\n  -------------------------------- ");
		printf("\033[1;31m");
		printf(" End of Day %d Reporting", currentDay);
		printf("\033[0m");
		printf("  -----------------------------------------\n\n");

		//find highest & lowest cases and that day
		if (newCases > highest)
		{
			highest = newCases;
			day[0] = currentDay;
		}
		if(newCases < lowest)
		{
			lowest = newCases;
			day[1] = currentDay;
		}


		++currentDay;
		totalDay++;

		//used to avoid user key in wrong message of input data after first looping
		currentLocalCases = -1, currentImportedCases = -1, currentDeaths = -1, currentRecovered = -1;

		//ask user want continue or not
		do {
			printf("\033[1;33m");
			printf("Continue to next day ('Y' or 'y' = yes , 'N' or 'n' = no)? >  ");
			rewind(stdin);
			yesNo = getchar();

			if (!(yesNo == 'Y' || yesNo == 'y' || yesNo == 'N' || yesNo == 'n'))
			{
				printf("\033[0;31m");
				printf("<ERROR> Please enter a valid letter.\n\n");
			}
			printf("\033[0m");
		} while (!(yesNo == 'Y' || yesNo == 'y' || yesNo == 'N' || yesNo == 'n'));

	} while (yesNo == 'Y' || yesNo == 'y');

	// Ending message
	printf("\033[0;33m");
	printf("\n     TOTAL Days recorded        = %d %s (Day 10 to Day %d)\n", totalDay, (totalDay == 1 ? "day" : "days"), currentDay - 1);
	printf("\033[1;33m");
	printf("     HIGHTEST number of cases   = %d, occurring on Day %d\n", highest, day[0]);
	printf("\033[0;33m");
	printf("     LOWEST number of cases     = %d, occurring on Day %d\n", lowest, day[1]);
	printf("\033[1;36m");
	printf("\n     Bye and Thank You!!\n");
	printf("\033[0m");

	//MY name
	printf("\n\t\t\t\tPrepared by : %c%c%c %c%c %c%c%c (DIA GROUP 15)\n", 76, 105, 109, 69, 114, 72, 97, 111);
	printf("\t\t\t\t\t\t %c%c%c\n\n", 3, 3, 3);

	system("pause");
}


void previousTable(int currentDay, int PREVIOUS_NEW_CASES, int PREVIOUS_TOTAL_CASES, int PREVIOUS_TOTAL_DEATHS, int PREVIOUS_TOTAL_RECOVERED, int PREVIOUS_UNDER_TREATMENT, int oldNewCases, int oldTotalCases, int totalDeaths, int totalRecovered, int underTreatment, float percentagePreviousDeath, float percentagePreviousRecovered, float percentagePreviousTreatment)
{
		printf("\033[1;32m");
		printf("\n     Yesterday's Totals - (Day %d):\n", currentDay - 1);
		printf("+---------------------------------------------------------------------------+\n");
		printf("|        Yesterday's   | Total      || Total      | Total      | Under      |\n");
		printf("|        Cases         | Cases      || Deaths     | Recovered  | Treatment  |\n");
		printf("|----------------------+------------++------------+------------+------------|\n");
		if (currentDay == 10)
			printf("|    %12d      |%11d ||%12d|%12d|%12d|\n", PREVIOUS_NEW_CASES, PREVIOUS_TOTAL_CASES, PREVIOUS_TOTAL_DEATHS, PREVIOUS_TOTAL_RECOVERED, PREVIOUS_UNDER_TREATMENT);
		else
			printf("|    %12d      |%11d ||%12d|%12d|%12d|\n", oldNewCases, oldTotalCases, totalDeaths, totalRecovered, underTreatment);
		printf("+---------------------------------------------------------------------------|\n");		
		printf("                                    ||%11.1f%%|%11.1f%%|%11.1f%%|\n", percentagePreviousDeath, percentagePreviousRecovered, percentagePreviousTreatment);
		printf("                                    ++--------------------------------------+\n\n\n");
		printf("\033[0m");
		
}


void inputCurrentData(int* h, int* i, int* j, int* k, int PREVIOUS_NEW_CASES, int currentDay,int oldNewCases)
{
	// *h=currentLocalCases , *i=currentImportedCases , *j=currentDeaths , *k=currentRecovered

	printf("\033[0;33m");
	printf(" Day %d\n", currentDay);
	printf("---------\n");
	printf("\033[1;33m");
	printf("Key in Today's data:\n");
	do {
		rewind(stdin);
		printf("        No. of new local cases    : ");
		scanf("%d", &*h);

		if (*h < 0 )
		{
		    printf("\033[0;31m");
		    printf("        <ERROR> Please enter a valid number.\n\n");
			printf("\033[1;33m");
		}
	} while (*h < 0);

	do {
		rewind(stdin);
		printf("        No. of new imported cases : ");
		scanf("%d", &*i);

		if (*i < 0)
		{
			printf("\033[0;31m");
			printf("        <ERROR> Please enter a valid number.\n\n");
			printf("\033[1;33m");
		}
	} while (*i < 0 );

	if (currentDay == 10)
	{
		printf("Total no. of new cases = %d", *h + *i);
		if ((*h + *i) > PREVIOUS_NEW_CASES || (*h + *i) < PREVIOUS_NEW_CASES)
			printf("     ( %s by %d from yesterday. )\n", (*h + *i) > PREVIOUS_NEW_CASES ? "Increased" : "Decreased", abs((*h + *i) - PREVIOUS_NEW_CASES));
		else
			printf("     ( No change from yesterday. )\n");
	}
	else
	{
		printf("Total no. of new cases = %d", *h + *i);
		if (*h + *i > oldNewCases || *h + *i < oldNewCases)
			printf("     ( %s by %d from yesterday. )\n", *h + *i > oldNewCases ? "Increased" : "Decreased", abs(*h + *i - oldNewCases));
		else
			printf("     ( No change from yesterday. )\n");
	}

	do {
		rewind(stdin);
		printf("No. of deaths          = ");
		scanf("%d", &*j);

		if (*j < 0 )
		{
			printf("\033[0;31m");
			printf("<ERROR> Please enter a valid number.\n\n");
			printf("\033[1;33m");
		}
	} while (*j < 0 );

	do {
		rewind(stdin);
		printf("No. recovered          = ");
		scanf("%d", &*k);

		if (*k < 0 )
		{
			printf("\033[0;31m");
			printf("<ERROR> Please enter a valid number.\n\n");
			printf("\033[1;33m");
		}
	} while (*k < 0 );

	printf("\033[0m");
	printf("\n\n");	
}


void calculateTotal(int currentDay,int PREVIOUS_TOTAL_CASES, int PREVIOUS_TOTAL_DEATHS, int PREVIOUS_TOTAL_RECOVERED, int currentLocalCases, int currentImportedCases, int currentDeaths, int currentRecovered, int* a, int* b, int* c, int* d, int* e)
{
	// *a=newCases , *b=totalCases , *c=totalDeaths , *d=totalRecovered , *e=underTreatment
	switch (currentDay)
	{
	case 10:
		*a = currentLocalCases + currentImportedCases;
		*b = PREVIOUS_TOTAL_CASES + *a;
		*c = PREVIOUS_TOTAL_DEATHS + currentDeaths;
		*d = PREVIOUS_TOTAL_RECOVERED + currentRecovered;
		*e = *b - *c - *d;
		break;

	default:

		*a = currentLocalCases + currentImportedCases;
		*b += *a;
		*c += currentDeaths;
		*d += currentRecovered;
		*e = *b - *c - *d;
	}

}


void calculatePercentage(int currentDay,int newCases, int totalCases, int totalDeaths, int totalRecovered, int underTreatment, float* x, float* y, float* z)
{
	// *x=percentageTotalDeaths , *y=percentageTotalRecovered , *z=percentageUnderTreatment
	
	*x = totalDeaths / (float)totalCases * 100;
	*y = totalRecovered / (float)totalCases * 100;
	*z = underTreatment / (float)totalCases * 100;
	
}


void calculateDifference(int currentDay,int oldNewCases,int oldTotalCases,int PREVIOUS_TOTAL_CASES, int PREVIOUS_NEW_CASES, float percentagePreviousRecovered, float percentagePreviousDeath, int newCases, int totalCases, float percentageTotalDeaths, float percentageTotalRecovered, int* o, int* p, float* q, float* r)
{
	
	//*o= compareNewCases , *p=compareTotalcases , *q=compareDeathRate , *r=compareRecoveredRate
	if (currentDay == 10)
	{
		*o = newCases - PREVIOUS_NEW_CASES;
		*p = totalCases - PREVIOUS_TOTAL_CASES;
	}
	else
	{
		*o = newCases - oldNewCases;
		*p = totalCases - oldTotalCases;
	}

	//  used to avoid percentage value automatically round up for get the true percentage
	if ((((int)(percentageTotalDeaths * 100)) % 10) > 4)
		percentageTotalDeaths += (float)0.1;

	percentageTotalDeaths = ((float)((int)(percentageTotalDeaths * 10)))  / 10;

	if ((((int)(percentagePreviousDeath * 100)) % 10) > 4)
		percentagePreviousDeath += (float)0.1;

	percentagePreviousDeath = ((float)((int)(percentagePreviousDeath * 10))) / 10;

	if ((((int)(percentageTotalRecovered * 100)) % 10) > 4)
		percentageTotalRecovered += (float)0.1;

	percentageTotalRecovered = ((float)((int)(percentageTotalRecovered * 10))) / 10;

	if ((((int)(percentagePreviousRecovered * 100)) % 10) > 4)
		percentagePreviousRecovered += (float)0.1;

	percentagePreviousRecovered = ((float)((int)(percentagePreviousRecovered * 10))) / 10;
	//end

	*q = percentageTotalDeaths - percentagePreviousDeath;
	*r = percentageTotalRecovered - percentagePreviousRecovered;


}

void summaryReport(int currentDay, int currentLocalCases, int currentImportedCases, int newCases, int totalCases, int totalDeaths, int totalRecovered, int underTreatment, float percentageTotalDeaths, float percentageTotalRecovered, float percentageUnderTreatment)
{
	printf("\033[1;34m");
	printf("\nDAY %d                        DAILY SUMMARY REPORT\n", currentDay);
	printf("+-------------------------------------------------------------------------+\n");
	printf("|        Today's     | Total     || Total      | Total       | Under      |\n");
	printf("|        Cases       | Cases     || Deaths     | Recovered   | Treatment  |\n");
	printf("|--------------------+-----------++------------+-------------+------------|\n");
	printf("| Local %13d|%11s||%12s|%13s|%12s|\n", currentLocalCases, "", "", "", "");
	printf("| Imported %10d|%11s||%12s|%13s|%12s|\n", currentImportedCases, "", "", "", "");
	printf("|%20d|%11d||%12d|%13d|%12d|\n", newCases, totalCases, totalDeaths, totalRecovered, underTreatment);
	printf("+-------------------------------------------------------------------------|\n");
	printf("                                 ||%11.1f%%|%12.1f%%|%11.1f%%|\n", percentageTotalDeaths, percentageTotalRecovered, percentageUnderTreatment);
	printf("                                 ++---------------------------------------+\n");
	printf("\033[0m");

}


void comparativeReport(int currentDay, int oldTotalCases, int oldNewCases, int PREVIOUS_TOTAL_CASES, int PREVIOUS_NEW_CASES, float percentagePreviousRecovered, float percentagePreviousDeath, int newCases, int totalCases, float percentageTotalDeaths, float percentageTotalRecovered, int compareNewCases, int compareTotalcases, float compareDeathRate, float compareRecoveredRate)
{
	

		printf("\033[1;35m");
		printf("\n                  DAILY COMPARATIVE REPORT\n");
		printf("                    +----------------------------------------------------------------+\n");
		printf("                    |   YESTERDAY       |      TODAY        ||    DIFFERENCE         |\n");
		printf("                    |    Day %-9d  |     Day %-9d ||                       |\n", currentDay - 1, currentDay);
		printf("+-------------------+-------------------+-------------------++-----------------------|\n");
		if (currentDay == 10)
		    printf("| New Cases         |%15d    |%15d    || %7s %-10d ]  |\n", PREVIOUS_NEW_CASES, newCases, (newCases > PREVIOUS_NEW_CASES ? "[ +" : newCases == PREVIOUS_NEW_CASES ? "[  " : "[ -"), abs(compareNewCases));
		else
			printf("| New Cases         |%15d    |%15d    || %7s %-10d ]  |\n", oldNewCases, newCases, (newCases > oldNewCases ? "[ +" : newCases == oldNewCases ? "[  " : "[ -"), abs(compareNewCases));
		printf("|-------------------+-------------------+-------------------++-----------------------|\n");
		if (currentDay == 10)
		    printf("| Total Cases       |%15d    |%15d    || %7s %-10d ]  |\n", PREVIOUS_TOTAL_CASES, totalCases, (totalCases > PREVIOUS_TOTAL_CASES ? "[ +" : "[  "), compareTotalcases);
		else
			printf("| Total Cases       |%15d    |%15d    || %7s %-10d ]  |\n", oldTotalCases, totalCases, (totalCases > oldTotalCases ? "[ +" : "[  "), compareTotalcases);
		printf("|-------------------+-------------------+-------------------++-----------------------|\n");
		printf("| Death Rate        |%14.1f%%    |%14.1f%%    || %7s%5.1f%%      ]  |\n", percentagePreviousDeath, percentageTotalDeaths, (percentageTotalDeaths > percentagePreviousDeath ? "[ +" : percentageTotalDeaths == percentagePreviousDeath ? "[  " : "[ -"), fabs(compareDeathRate));
		printf("|-------------------+-------------------+-------------------++-----------------------|\n");
		printf("| Recovery Rate     |%14.1f%%    |%14.1f%%    || %7s%5.1f%%      ]  |\n", percentagePreviousRecovered, percentageTotalRecovered, (percentageTotalRecovered > percentagePreviousRecovered ? "[ +" : percentageTotalRecovered == percentagePreviousRecovered ? "[  " : "[ -"), fabs(compareRecoveredRate));
		printf("+------------------------------------------------------------------------------------+\n");
		printf("\033[0m");

	
}

char viewing()
{
	char number;
	printf("\033[1;34m");
	printf(" 1 - Daily Summary Report");
	printf("\033[0m");
	printf("	      ");
	printf("\033[1;35m");
	printf("2 - Daily Comparative Report\n\n");
	printf("\033[0m");

	printf("\033[1;33m");
	printf("What type of Report would you like to view (Choose 1 or 2)?  >  ");
	scanf("%c", &number);
	printf("\033[0m");

	return number;
}



void logo()
{
	printf("\033[1;31m");
	printf("                              +________________________");
	printf("\033[1;33m");
	printf("______________________+\n");
	printf("                              |           ");
	printf("\033[1;31m");
	printf("	                             |\n");
	printf("\033[1;33m");
	printf("                              |");
	printf("\033[1;31m");
	printf("	      @@@ @@@@ @@@@  @@@@ @@  @    @@  ");
	printf("\033[1;31m");
	printf("	     |\n");
	printf("\033[1;33m");
	printf("                              |");
	printf("\033[1;31m");
	printf("	     @@   @  @ @  @  @  @ @ @ @   @  @ ");
	printf("\033[1;31m");
	printf("	     |\n");
	printf("\033[1;33m");
	printf("                              |");
	printf("\033[1;33m");
	printf("      @@   @  @ @@@@  @  @ @  @@  @@@@@@ ");
	printf("\033[1;31m");
	printf("     |\n");
	printf("\033[1;33m");
	printf("                              |");
	printf("\033[1;33m");
	printf("	      @@@ @@@@ @   @ @@@@ @   @ @      @ ");
	printf("\033[1;31m");
	printf("    |\n");
	printf("\033[1;33m");
	printf("                              |        ");
	printf("\033[1;31m");
	printf("	                                     |\n");
	printf("\033[1;33m");
	printf("                              |");
	printf("\033[1;33m");
	printf("	                 @@@   @@@@");
	printf("\033[1;31m");
	printf("   	             |\n");
	printf("\033[1;31m");
	printf("                              |");
	printf("\033[1;33m");
	printf("	                @@     @  @");
	printf("\033[1;33m");
	printf("	             |\n");
	printf("\033[1;31m");
	printf("                              |");
	printf("\033[1;31m");
	printf("	                @@ @@@ @  @");
	printf("\033[1;33m");
	printf("            	     |\n");
	printf("\033[1;31m");
	printf("                              |");
	printf("\033[1;31m");
	printf("	                 @@@ @ @@@@");
	printf("\033[1;33m");
	printf("	             |\n");
	printf("\033[1;31m");
	printf("                              |                     ");
	printf("\033[1;33m");
	printf("	                     |\n");
	printf("\033[1;31m");
	printf("                               \\                                  ");
	printf("\033[1;33m");
	printf("	    /\n");
	printf("\033[1;31m");
	printf("                                \\                                 ");
	printf("\033[1;33m");
	printf("	   /\n");
	printf("\033[1;31m");
	printf("                                 \\                                ");
	printf("\033[1;33m");
	printf("	  /\n");
	printf("\033[1;31m");
	printf("                                  \\");
	printf("\033[1;33m");
	printf("___________________");
	printf("\033[1;31m");
	printf("___________________");
	printf("\033[1;33m");
	printf("/\n\n");

	printf("\033[0m");
	printf("  ----------------------------------- ");
	printf("\033[1;31m");
	printf(" COVID-19 CASES TRACKING SYSTEM");
	printf("\033[0m");
	printf("  --------------------------------------\n\n");

}
