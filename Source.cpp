#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include <sys/stat.h>

#define OUTPUT_SYSTEM "database.csv"
#define OUTPUT_DISPLAY "databaseLabel.csv"

#define GREEN 32
#define L_GREEN 92
#define RED 91
#define YELLOW 93
#define BLUE 34
#define MAGENTA 35
#define CYAN 96



typedef struct userNode {
	char userName[20];
	char password[7];
	struct userNode* NEXT;
}userT;

typedef struct userLoaded {
	char userName[20];
	char password[7];
}userLoadedT;

typedef struct node {
	int regNo;
	char name[40];
	char country[40];
	int yearFounded;
	char email[50];
	char contactName[30];
	float lastOrder;
	int numbEmployees;
	float avgAnnualOrder;

	int isVatRegistered;
	int averageTurnover;
	int staffEmployed;
	int areaOfSales;

	struct node* NEXT;
}companyT;

//labels
char vatLabel[2][10] = { "Yes","No" };
char turnOverLabel[3][30] = { "Less than 1M EURO","Less than 10M EURO","Over 10M EURO" };
char staffLabel[3][20] = { "Less than 10","Less than 100","Over 100" };
char areaSalesLabel[3][20] = { "ICT","Medical Devices","Other Area" };
userLoaded loginLoaded[3];
companyT* foundCompany;
char uName[20];

//login functions
void loginRegister(userT** userHead);
void outputloginRegister(userT* userHead);
int loginListLength(userT* userHead);
int login();
void loadLoginFile();

//client functions
struct node* createNode(int regNumber);
void menu();
void displayAllDatabase(companyT* head);
int searchCompany(companyT* head, int search);
int listLength(companyT* head);
void deleteCompany(companyT** head, int regDel);
void addCompany(companyT** head, int regNumber);
void outputClientFILES(companyT* head);
void loadClientFile(companyT** head);
void generateStatistics(companyT** head);
void SortLinkedList(companyT* head);
void swap(companyT* a, companyT* b);



void loadLoginFile() {

	FILE* readFile = fopen("login.txt", "r");
	for (int i = 0; i < 10; i++) {
		fscanf(readFile, "%s %s\n", loginLoaded[i].userName, loginLoaded[i].password);
		//printf("%s %s", loginLoaded[i].userName, loginLoaded[i].password);
	}

}

void loginRegister(userT** userHead) {

	//create new node
	userT* newUserNode = (userT*)malloc(sizeof(userT));


	printf("\n*************** NEW LOGIN REGISTER ********************\n");
	printf("\tNew Username: ");
	scanf("%19s", newUserNode->userName);
	printf("\tNew Password: ");
	scanf("%6s", newUserNode->password);
	printf("\n*******************************************************\n");

	newUserNode->NEXT = NULL;

	//if head is null, the list is empty
	if (*userHead == NULL) {
		*userHead = newUserNode;
	}//if not null, find the last node and add the node
	else {
		userT* lastNode = *userHead;
		//last node's next address will be null
		while (lastNode->NEXT != NULL) {
			lastNode = lastNode->NEXT;
		}
		//add the nide at the end of the list
		lastNode->NEXT = newUserNode;
	}
}

void outputloginRegister(userT* userHead) {
	userT* temp;
	temp = userHead;
	FILE* fp;
	int counter = 0;

	fp = fopen("login.txt", "w+");

	while (temp != NULL) {


		if (fp != NULL) {

			fprintf(fp, "%s %s\n", temp->userName, temp->password);
		}

		temp = temp->NEXT;
	}
	//close the file
	if (fp != NULL) {
		fclose(fp);
	}
}

int loginListLength(userT* userHead) {

	userT* temp = userHead;
	int count = 0;

	while (temp != NULL)
	{
		count = count + 1;
		temp = temp->NEXT;
	}

	return count;
}

int login() {

	char pwd[7], ch;
	int i, j;

	printf("\n\tPlease enter your credentials:\n");
	printf("\tUsername: ");
	scanf("%19s", uName);


	printf("\tPassword: ");
	printf("\033[%dm", CYAN);
	for (j = 0; j < 6; j++) {
		ch = getch();
		if (ch == 6) break;
		pwd[j] = ch;
		ch = '*';
		printf("%c", ch);

	}
	pwd[j] = '\0';

	for (i = 0; i < 3; i++) {

		if (strcmp(loginLoaded[i].userName, uName) && strcmp(loginLoaded[i].password, pwd) == 0) {
			return 0;
		}
	}
	return 1;

}

struct node* createNode(int regNumber) {

	struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node));
	int areaInput;
	bool emailValid = false;

	newNode->regNo = regNumber;
	printf("Please enter the Client Name >>  ");
	scanf("%s", newNode->name);
	printf("Please enter the Client Country >>  ");
	scanf("%s", newNode->country);
	printf("Please enter Year the Client was founded >>  ");
	scanf("%d", &newNode->yearFounded);
	//email must contai @ and .com
	do {
		printf("Please enter a valid E-mail address for the client >>  ");
		scanf("%s", newNode->email);
		char* comIndex = strstr(newNode->email, ".com");
		char* atIndex = strstr(newNode->email, "@");

		if (comIndex != NULL && atIndex != NULL) {
			emailValid = true;

		}
		else {
			printf("Email NOT valid! \n");
		}

	} while (emailValid == false);

	printf("Please enter Client contact name >>  ");
	scanf("%s", newNode->contactName);
	printf("Please enter Client last order >>  ");
	scanf("%f", &newNode->lastOrder);
	printf("Please enter the number of employees in the Client's Company >>  ");
	scanf("%d", &newNode->numbEmployees);
	printf("Please enter the Client's company last Order >>  ");
	scanf("%f", &newNode->avgAnnualOrder);

	int vatTemp;

	do {
		printf("Is the company VAT registered? (1-Yes / 2-No) >>  ");
		scanf("%d", &vatTemp);
		newNode->isVatRegistered = vatTemp;

	} while (vatTemp < 1 || vatTemp > 2);

	int turnTemp;

	do {
		printf("What are the company turnover? (1- Less than 1M / 2- Less than 10M / 3- Over 10M) >>  ");
		scanf("%d", &turnTemp);
		newNode->averageTurnover = turnTemp;

	} while (turnTemp < 1 || turnTemp > 3);

	int staffTemp;
	do {
		printf("How many staff are employed in the Company? (1- Less than 10 / 2- Less than 100 / 3- Over 100) >>  ");
		scanf("%d", &staffTemp);
		newNode->staffEmployed = staffTemp;

	} while (staffTemp < 1 || staffTemp > 3);

	int areaTemp;
	do {
		printf("Which area of Sales is the company? (1- ICT / 2- Medical Devices / 3- Other Area) >>  ");
		scanf("%d", &areaTemp);
		newNode->areaOfSales = areaTemp;

	} while (areaTemp < 1 || areaTemp > 3);

	return newNode;

}

void menu() {

	printf("\033[%dm", YELLOW);
	printf("\n\nMain menu:\n");
	printf("1- Add a client\n");
	printf("2- Display all the clients\n");
	printf("3- Search for a company\n");
	printf("4- Update client details\n");
	printf("5- Delete a client\n");
	printf("6- Generate statistics\n");
	printf("7- Print all client details to a file\n");
	printf("8- List all in order of their last average turnover\n");
	printf("-1 - Quit\n");
	printf("Type your choice >>  ");
	printf("\033[0m");

}

void displayAllDatabase(companyT* head) {
	companyT* temp;
	temp = head;

	while (temp != NULL) {
		printf("Company Registration Number: %d\n", temp->regNo);
		printf("Company Name: %s\n", temp->name);
		printf("Company Country: %s\n", temp->country);
		printf("Company Year founded: %d\n", temp->yearFounded);
		printf("Company E-mail address: %s\n", temp->email);
		printf("Company Contact name: %s\n", temp->contactName);
		printf("Company Last order: %f\n", temp->lastOrder);
		printf("Company Number of Employees: %d\n", temp->numbEmployees);
		printf("Company Average Annual Order: %f\n", temp->avgAnnualOrder);
		printf("Is the company VAT registered: %s\n", vatLabel[temp->isVatRegistered - 1]);
		printf("The company average turnover is: %s\n", turnOverLabel[temp->averageTurnover - 1]);
		printf("Number of staff employed in the company is: %s\n", staffLabel[temp->staffEmployed - 1]);
		printf("Company area of sales is: %s\n", areaSalesLabel[temp->areaOfSales - 1]);

		printf("\n*****************************************************************\n");

		temp = temp->NEXT;
	}

}

int searchCompany(companyT* head, int search) {
	int found = 0;
	companyT* temp = head;

	foundCompany = (companyT*)malloc(sizeof(companyT));

	while (temp != NULL) {

		if (temp->regNo == search) {

			foundCompany = temp;

			found = 1;

		}

		temp = temp->NEXT;
	}

	return found;
}

int listLength(companyT* head) {
	int count = 0;
	companyT* temp = head;

	while (temp != NULL) {//to make sure you get the end of the list value NOT temp->NEXT != NULL
		count = count + 1;
		temp = temp->NEXT;

	}
	return count;

}

void addCompany(companyT** head, int regNumber) {
	//create new node
	companyT* newNode = (companyT*)malloc(sizeof(companyT));
	newNode = createNode(regNumber);
	newNode->NEXT = NULL;

	//if head is null, the list is empty
	if (*head == NULL) {
		*head = newNode;
	}//if not null, find the last node and add the node
	else {
		companyT* lastNode = *head;
		//last node's next address will be null
		while (lastNode->NEXT != NULL) {
			lastNode = lastNode->NEXT;
		}
		//add the nide at the end of the list
		lastNode->NEXT = newNode;
	}


}

void deleteCompany(companyT** head, int regDel) {
	companyT* temp;
	//if found on the head node
	//move head node to the next and free the head
	if ((*head)->regNo == regDel) {
		temp = *head; //backup to free memory
		*head = (*head)->NEXT;
		free(temp);
	}
	else {
		companyT* current = *head;
		while (current->NEXT != NULL) {
			//if yes delete the current->next node
			if (current->NEXT->regNo == regDel) {
				temp = current->NEXT;
				//disconect node from list
				current->NEXT = current->NEXT->NEXT;
				free(temp);
				break;

			}
			//if not, move the current node and proceed
			else {
				current = current->NEXT;
			}
		}
	}


}

//print 2 files. 1 for information purpose with labes
//the second for the software to read
void outputClientFILES(companyT* head) {

	companyT* temp1 = head;
	companyT* temp2 = head;
	FILE* fpLabels;
	FILE* fpSystem;
	fpLabels = fopen(OUTPUT_DISPLAY, "w+");
	fpSystem = fopen(OUTPUT_SYSTEM, "w+");

	//labels
	fprintf(fpLabels, "Company Registration Number, Company Name, Company Country, Year founded, E-mail address, Contact name, Last order, Number of Employees, Average Annual Order ,VAT Registered, Average turnover, Number of staff, Area of Sales\n");

	while (temp1 != NULL) {


		if (fpLabels != NULL) {

			fprintf(fpLabels, "%d, %s, %s, %d, %s, %s, %f, %d, %f, %s, %s, %s, %s\n",
				temp1->regNo, temp1->name,
				temp1->country, temp1->yearFounded, temp1->email, temp1->contactName, temp1->lastOrder,
				temp1->numbEmployees, temp1->avgAnnualOrder,
				vatLabel[temp1->isVatRegistered - 1],
				turnOverLabel[temp1->averageTurnover - 1],
				staffLabel[temp1->staffEmployed - 1],
				areaSalesLabel[temp1->areaOfSales - 1]);

		}

		temp1 = temp1->NEXT;
	}

	//without labels
	while (temp2 != NULL) {
		if (fpSystem != NULL) {
			fprintf(fpSystem, "%d, %s, %s, %d, %s, %s, %f, %d, %f, %d, %d, %d, %d\n",
				temp2->regNo, temp2->name,
				temp2->country, temp2->yearFounded, temp2->email, temp2->contactName, temp2->lastOrder,
				temp2->numbEmployees, temp2->avgAnnualOrder,
				temp2->isVatRegistered,
				temp2->averageTurnover,
				temp2->staffEmployed,
				temp2->areaOfSales);
		}

		temp2 = temp2->NEXT;
	}


	//close the labels file
	if (fpLabels != NULL) {
		fclose(fpLabels);
	}
	//close the system file
	if (fpSystem != NULL) {
		fclose(fpSystem);
	}
}

void loadClientFile(companyT** head) {

	FILE* fptr = fopen(OUTPUT_SYSTEM, "r");

	char buffer[256];
	companyT* temp = NULL;

	if (fptr != NULL) {
		while (fgets(buffer, 256, fptr)) {

			companyT* node = (companyT*)malloc(sizeof(companyT));

			sscanf(buffer, "%d,%[^,], %[^,], %d, %[^,], %[^,], %f, %d, %f, %d, %d, %d, %d",
				&(node->regNo), node->name,
				node->country, &(node->yearFounded), node->email, node->contactName, &(node->lastOrder),
				&(node->numbEmployees), &(node->avgAnnualOrder), &(node->isVatRegistered), &(node->averageTurnover), &(node->staffEmployed), &(node->areaOfSales));

			node->NEXT = NULL;


			if (temp == NULL) { // First item
				*head = node;
			}
			else {
				temp->NEXT = node;
			}
			temp = node;


		}
		//displayAllDatabase(*head);
	}


}

void generateStatistics(companyT** head, int listSize) {
	int statOption;
	int filterOption1 = 0;
	int filterOption2 = 0;

	do {
		printf("\tYou have chosen the option 6 to generate statistics, please select if you want it completed by:\n");
		printf("\t1- Area of Company Sales\n");
		printf("\t2- Number of Employees\n");
		printf("\tPlease type your choice >>  ");
		scanf("%d", &statOption);

	} while (statOption < 1 || statOption>2);


	double areTurnoverCounter[3][3] = { 0 };
	double employeeTurnoverCounter[3][3] = { 0 };
	double counter[6] = { 0 };
	int totalArea[3] = { 0 };
	int totalEmp[3] = { 0 };


	for (companyT* node = *head; node != NULL; node = node->NEXT) {

		if (statOption == 1) {

			if (node->areaOfSales == 1) {//ICT [0][]

				if (node->averageTurnover == 1) { //less than 1 million
					areTurnoverCounter[0][0] += 1;
					totalArea[0] += 1;
				}
				else if (node->averageTurnover == 2) { //less than 10 million
					areTurnoverCounter[0][1] += 1;
					totalArea[0] += 1;
				}
				else if (node->averageTurnover == 3) { //more than 10 million
					areTurnoverCounter[0][2] += 1;
					totalArea[0] += 1;
				}
			}
			else if (node->areaOfSales == 2) {//medical device
				if (node->averageTurnover == 1) { //less than 1 million
					areTurnoverCounter[1][0] += 1;
					totalArea[1] += 1;
				}
				else if (node->averageTurnover == 2) { //less than 10 million
					areTurnoverCounter[1][1] += 1;
					totalArea[1] += 1;
				}
				else if (node->averageTurnover == 3) { //more than 10 million
					areTurnoverCounter[1][2] += 1;
					totalArea[1] += 1;
				}
			}
			else if (node->areaOfSales == 3) {//others
				if (node->averageTurnover == 1) { //less than 1 million
					areTurnoverCounter[2][0] += 1;
					totalArea[2] += 1;
				}
				else if (node->averageTurnover == 2) { //less than 10 million
					areTurnoverCounter[2][1] += 1;
					totalArea[2] += 1;
				}
				else if (node->averageTurnover == 3) { //more than 10 million
					areTurnoverCounter[2][2] += 1;
					totalArea[2] += 1;
				}
			}

		}
		else {

			if (node->numbEmployees <= 10) {//less than 10

				if (node->averageTurnover == 1) { //less than 1 million
					employeeTurnoverCounter[0][0] += 1;
					totalEmp[0] += 1;
				}
				else if (node->averageTurnover == 2) { //less than 10 million
					employeeTurnoverCounter[0][1] += 1;
					totalEmp[0] += 1;
				}
				else if (node->averageTurnover == 3) { //more than 10 million
					employeeTurnoverCounter[0][2] += 1;
					totalEmp[0] += 1;
				}


			}
			if (node->numbEmployees > 10 && node->numbEmployees <= 100) {//less than 100
				if (node->averageTurnover == 1) { //less than 1 million
					employeeTurnoverCounter[1][0] += 1;
					totalEmp[1] += 1;
				}
				else if (node->averageTurnover == 2) { //less than 10 million
					employeeTurnoverCounter[1][1] += 1;
					totalEmp[1] += 1;
				}
				else if (node->averageTurnover == 3) { //more than 10 million
					employeeTurnoverCounter[1][2] += 1;
					totalEmp[1] += 1;
				}
			}
			if (node->numbEmployees > 100) {//more than 100
				if (node->averageTurnover == 1) { //less than 1 million
					employeeTurnoverCounter[2][0] += 1;
					totalEmp[2] += 1;
				}
				else if (node->averageTurnover == 2) { //less than 10 million
					employeeTurnoverCounter[2][1] += 1;
					totalEmp[2] += 1;
				}
				else if (node->averageTurnover == 3) { //more than 10 million
					employeeTurnoverCounter[2][2] += 1;
					totalEmp[2] += 1;
				}
			}
		}

	}
	if (statOption == 1) {
		do {
			printf("\n\tNext selection is:\n");
			printf("\t1- ICT\n");
			printf("\t2- Medical Devices\n");
			printf("\t3- Other Area\n");
			printf("\tPlease type your choice >>  ");
			scanf("%d", &filterOption1);
		} while (filterOption1 < 1 || filterOption1 > 3);

		if (filterOption1 == 1) {

			printf("\033[%dm", CYAN);
			printf("\n\t***************************************************\n");
			printf("\n\t*      Statistics for Companies in ICT Area      *\n");
			printf("\n\t***************************************************\n");
			printf("\t\tLess than 1 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][0] / totalArea[0]) * 100);
			printf("\t\tLess than 10 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][1] / totalArea[0]) * 100);
			printf("\t\tOver 10 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][2] / totalArea[0]) * 100);
			printf("\033[%m");

		}
		else if (filterOption1 == 2) {
			printf("\033[%dm", CYAN);
			printf("\n\t*****************************************************\n");
			printf("\n\t*  Statistics for Companies in Medical Devices Area *\n");
			printf("\n\t*****************************************************\n");
			printf("\t\tLess than 1 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][0] / totalArea[1]) * 100);
			printf("\t\tLess than 10 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][1] / totalArea[1]) * 100);
			printf("\t\tOver 10 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][2] / totalArea[1]) * 100);
			printf("\033[%m");

		}
		else if (filterOption1 == 3) {
			printf("\033[%dm", CYAN);
			printf("\n\t***************************************************\n");
			printf("\n\t*      Statistics for Companies in Other Areas    *\n");
			printf("\n\t***************************************************\n");
			printf("\t\tLess than 1 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][0] / totalArea[2]) * 100);
			printf("\t\tLess than 10 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][1] / totalArea[2]) * 100);
			printf("\t\tOver 10 Million: %.1lf%%\n", (areTurnoverCounter[filterOption1 - 1][2] / totalArea[2]) * 100);
			printf("\033[%m");
		}
	}
	else {
		do {

			printf("\tNext selection is:\n");
			printf("\t1- Less than 10\n");
			printf("\t2- Less than 100\n");
			printf("\t3- More then 100\n");
			printf("\tPlease type your choice >>  ");
			scanf("%d", &filterOption2);

		} while (filterOption2 < 1 || filterOption2 > 3);

		if (filterOption2 == 1) {

			printf("\033[%dm", CYAN);
			printf("\n\t*********************************************************\n");
			printf("\n\t*    Statistics for Companies with Less than 10 Staff   *\n");
			printf("\n\t*********************************************************\n");
			printf("\t\tLess than 1 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][0] / totalEmp[0]) * 100);
			printf("\t\tLess than 10 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][1] / totalEmp[0]) * 100);
			printf("\t\tOver 10 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][2] / totalEmp[0]) * 100);
			printf("\033[%m");

		}
		else if (filterOption2 == 2) {
			printf("\033[%dm", CYAN);
			printf("\n\t*********************************************************\n");
			printf("\n\t*   Statistics for Companies with Less than 100 Staff   *\n");
			printf("\n\t*********************************************************\n");
			printf("\t\tLess than 1 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][0] / totalEmp[1]) * 100);
			printf("\t\tLess than 10 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][1] / totalEmp[1]) * 100);
			printf("\t\tOver 10 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][2] / totalEmp[1]) * 100);
			printf("\033[%m");
		}
		else if (filterOption2 == 3) {
			printf("\033[%dm", CYAN);
			printf("\n\t*********************************************************\n");
			printf("\n\t*   Statistics for Companies with More than 100 Staff    *\n");
			printf("\n\t*********************************************************\n");
			printf("\t\tLess than 1 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][0] / totalEmp[2]) * 100);
			printf("\t\tLess than 10 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][1] / totalEmp[2]) * 100);
			printf("\t\tOver 10 Million: %.1lf%%\n", (employeeTurnoverCounter[filterOption2 - 1][2] / totalEmp[2]) * 100);
			printf("\033[%m");
		}
	}

}

void SortLinkedList(companyT* head)
{
	/* Bubble sort the given linked list */
	int swapped, i;
	companyT* ptr1;
	companyT* lptr = NULL;

	/* Checking for empty list */
	if (head == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = head;

		while (ptr1->NEXT != lptr)
		{
			if (ptr1->avgAnnualOrder > ptr1->NEXT->avgAnnualOrder)
			{
				swap(ptr1, ptr1->NEXT);
				swapped = 1;
			}
			ptr1 = ptr1->NEXT;
		}
		lptr = ptr1;
	} while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(companyT* a, companyT* b)
{
	int temp = a->avgAnnualOrder;
	a->avgAnnualOrder = b->avgAnnualOrder;
	b->avgAnnualOrder = temp;
}


void main() {
	companyT* headPtr = NULL;
	userT* userHeadPtr = NULL;
	companyT* temp;
	int loginMenuChoice;
	int choice;
	int loginSuccess;


	int regSearch;
	int found;
	int proposedRegNumber;
	int regToDelete;
	int result;
	char c;
	printf("\033[%dm", L_GREEN);
	printf("\n****************************************************************************************************************\n");
	printf("*                                             XYZ MEDICAL SUPPLIER LTD                                         *\n");
	printf("****************************************************************************************************************\n");

	do {
		printf("\tLogin Menu:\n");
		printf("\t1 - Login\n");
		printf("\t2 - Register New Login\n");
		printf("\t-1 - Quit\n");
		printf("\tPlease enter you choice >>  ");
		
		scanf("\t%d", &loginMenuChoice);

	} while (loginMenuChoice<1||loginMenuChoice>2);
	printf("\033[0m");

	loadLoginFile();


	while (loginMenuChoice != -1) {


		if (loginMenuChoice == 1) {

			while ((loginSuccess = login()) != 0) {
				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n*                Invalid credentials! Please try again!                 *\n");
				printf("\n************************************************************************\n");
				printf("\033[0m");

			}
			system("cls");
			printf("\033[%dm", L_GREEN);
			printf("\n****************************************************************************************************************\n");
			printf("*                                             XYZ MEDICAL SUPPLIER LTD                                         *\n");
			printf("*                                               Welcome back %s                                           *\n", uName);

			printf("****************************************************************************************************************\n");
			printf("\n\t\t\t\tYou're now logged into XYZ MEDICAL SUPPLIER LTD System!\n");
			printf("\033[0m");
			break;



		}
		else if (loginMenuChoice == 2) {
			loginRegister(&userHeadPtr);
			printf("Login created successfully!\n");
			outputloginRegister(userHeadPtr);
			printf("Login details saved to login.txt!\n");
			
		}
		system("cls");
		printf("\033[%dm", L_GREEN);
		printf("\n****************************************************************************************************************\n");
		printf("*                                             XYZ MEDICAL SUPPLIER LTD                                         *\n");
		printf("****************************************************************************************************************\n");
		
		do {
			loadLoginFile();
			printf("\tLogin Menu:\n");
			printf("\t1 - Login\n");
			printf("\t2 - Register New Login\n");
			printf("\t-1 - Quit\n");
			printf("\tPlease enter you choice >>  ");

			scanf("\t%d", &loginMenuChoice);

		} while (loginMenuChoice < 1 || loginMenuChoice>2);
		printf("\033[0m");
	}
	//load database
	loadClientFile(&headPtr);

	printf("\033[0m");
	printf("\n****************************************************************************************************************\n");
	printf("*                                                Database loaded...                                             *\n");
	printf("****************************************************************************************************************\n");
	printf("\033[0m");
	menu();
	scanf("%d", &choice);

	while (choice != -1) {

		if (choice == 1) {

			printf("Please enter the proposed Company Registration Number to check availability >>  ");
			scanf("%d", &proposedRegNumber);

			result = searchCompany(headPtr, proposedRegNumber);

			while (result == 1) {
				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n* The Company Registration Number already exist in the Database!       *\n");
				printf("\n************************************************************************\n");
				printf("\033[0m");

				printf("Please enter the Company Registration Number:\n");
				scanf("%d", &proposedRegNumber);

				result = searchCompany(headPtr, proposedRegNumber);

			}
			printf("The company Registration Number %d is available!\n\n", proposedRegNumber);

			addCompany(&headPtr, proposedRegNumber);

		}
		else if (choice == 2) {

			result = listLength(headPtr);

			if (result == 0) {
				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n*\t\t\t The Database is empty *\n");
				printf("\n************************************************************************\n");
				printf("\033[0m");
			}
			else {
				displayAllDatabase(headPtr);
			}
		}
		else if (choice == 3) {
			printf("\nPlease enter the Company Registration Number you are looking for >>  ");
			scanf("%d", &regSearch);
			found = searchCompany(headPtr, regSearch);

			if (found == 0) {
				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n\t\t Company registration number %d wasn't found!\n", regSearch);
				printf("\n************************************************************************\n");
				printf("\033[0m");
			}
			else {
				printf("\nThe Company Registration number %d was found\n", regSearch);

				printf("\n\tCompany Registration Number: %d\n", foundCompany->regNo);
				printf("\tCompany Name: %s\n", foundCompany->name);
				printf("\tCompany Country: %s\n", foundCompany->country);
				printf("\tCompany Year founded: %d\n", foundCompany->yearFounded);
				printf("\tCompany E-mail address: %s\n", foundCompany->email);
				printf("\tCompany Contact name: %s\n", foundCompany->contactName);
				printf("\tCompany Last order: %f\n", foundCompany->lastOrder);
				printf("\tCompany Number of Employees: %d\n", foundCompany->numbEmployees);
				printf("\tCompany Average Annual Order: %f\n", foundCompany->avgAnnualOrder);
				printf("\tIs the company VAT registered: %s\n", vatLabel[foundCompany->isVatRegistered - 1]);
				printf("\tThe company average turnover is %s\n", turnOverLabel[foundCompany->averageTurnover - 1]);
				printf("\tNumber of staff employed in the company is %s\n", staffLabel[foundCompany->staffEmployed - 1]);
				printf("\tCompany area of sales is %s\n", areaSalesLabel[foundCompany->areaOfSales - 1]);


			}
		}
		else if (choice == 4) {
			printf("\nPlease enter the Company Registration Number for update >>  ");
			scanf("%d", &regSearch);
			found = searchCompany(headPtr, regSearch);
			bool emailValid = false;

			if (found == 0) {
				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n\t\t Company registration number %d wasn't found!\n", regSearch);
				printf("\n************************************************************************\n");
				printf("\033[0m");
			}
			else {
				printf("\n\tThe Company Registration number %d was found\n", regSearch);

				printf("\tPlease enter the Client Name >>  ");
				scanf("%s", foundCompany->name);
				printf("\tPlease enter the Client Country >>  ");
				scanf("%s", foundCompany->country);
				printf("\tPlease enter Year the Client was founded >>  ");
				scanf("%d", &foundCompany->yearFounded);
				//email must contai @ and .com
				do {
					printf("\tPlease enter a valid E-mail address for the client >>  ");
					scanf("%s", foundCompany->email);
					char* comIndex = strstr(foundCompany->email, ".com");
					char* atIndex = strstr(foundCompany->email, "@");

					if (comIndex != NULL && atIndex != NULL) {
						emailValid = true;

					}
					else {
						printf("\033[%dm", RED);
						printf("\n******************************** ALERT! ********************************\n");
						printf("\n                           Email NOT valid!                             \n", regSearch);
						printf("\n************************************************************************\n");
						printf("\033[0m");
					}

				} while (emailValid == false);

				printf("\tPlease enter New Client contact name >>  ");
				scanf("%s", foundCompany->contactName);
				printf("\tPlease enter New Client last order >>  ");
				scanf("%f", &foundCompany->lastOrder);
				printf("\tPlease enter the New number of employees in the Client's Company >>  ");
				scanf("%d", &foundCompany->numbEmployees);
				printf("\tPlease enter the Client's company New last Order >>  ");
				scanf("%f", &foundCompany->avgAnnualOrder);

				int vatTemp;

				do {
					printf("\tIs the company VAT registered? (1-Yes / 2-No) >>  ");
					scanf("%d", &vatTemp);
					foundCompany->isVatRegistered = vatTemp;

				} while (vatTemp < 1 || vatTemp > 2);

				int turnTemp;

				do {
					printf("\tWhat is the company New turnover? (1- Less than 1M / 2- Less than 10M / 3- Over 10M) >>  ");
					scanf("%d", &turnTemp);
					foundCompany->averageTurnover = turnTemp;

				} while (turnTemp < 1 || turnTemp > 3);

				int staffTemp;
				do {
					printf("\tHow many staff are employed in the Company? (1- Less than 10 / 2- Less than 100 / 3- Over 100) >>  ");
					scanf("%d", &staffTemp);
					foundCompany->staffEmployed = staffTemp;

				} while (staffTemp < 1 || staffTemp > 3);

				int areaTemp;
				do {
					printf("\tWhich area of Sales is the company? (1- ICT / 2- Medical Devices / 3- Other Area) >>  ");
					scanf("%d", &areaTemp);
					foundCompany->areaOfSales = areaTemp;

				} while (areaTemp < 1 || areaTemp > 3);

				
			}

		}
		else if (choice == 5) {

			printf("\nPlease enter the Company registration Number you want to delete >>  ");
			scanf("%d", &regToDelete);
			result = searchCompany(headPtr, regToDelete);


			if (result == 0) {
				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n\t\t Company registration number %d wasn't found!\n", regToDelete);
				printf("\n************************************************************************\n");
				printf("\033[0m");
			}
			else {
				printf("\tDetails of company you want to delete\n");
				printf("\tCompany Registration Number: %d\n", foundCompany->regNo);
				printf("\tCompany Name: %s\n", foundCompany->name);
				printf("\tCompany Country: %s\n", foundCompany->country);
				printf("\tCompany Year founded: %d\n", foundCompany->yearFounded);
				printf("\tCompany E-mail address: %s\n", foundCompany->email);
				printf("\tCompany Contact name: %s\n", foundCompany->contactName);
				printf("\tCompany Last order: %f\n", foundCompany->lastOrder);
				printf("\tCompany Number of Employees: %d\n", foundCompany->numbEmployees);
				printf("\tCompany Average Annual Order: %f\n", foundCompany->avgAnnualOrder);
				printf("\tIs the company VAT registered: %s\n", vatLabel[foundCompany->isVatRegistered - 1]);
				printf("\tThe company average turnover is %s\n", turnOverLabel[foundCompany->averageTurnover - 1]);
				printf("\tNumber of staff employed in the company is %s\n", staffLabel[foundCompany->staffEmployed - 1]);
				printf("\tCompany area of sales is %s\n", areaSalesLabel[foundCompany->areaOfSales - 1]);

				printf("\n\tAre you sure you want do delete? (y/n) >>  ");
				scanf("%s", &c);

				printf("\033[%dm", RED);
				printf("\n******************************** ALERT! ********************************\n");
				printf("\n\t\t Company registration number %d DELETE from the databse!           *\n", regToDelete);
				printf("\n************************************************************************\n");
				printf("\033[0m");


				if (c == 'y' || c == 'Y') {
					deleteCompany(&headPtr, regToDelete);
				}
				else {
					printf("No problem!\n");

				}
			}

		}
		else if (choice == 6) {
			int listS = listLength(headPtr);
			generateStatistics(&headPtr, listS);

		}
		else if (choice == 7) {
			outputClientFILES(headPtr);
			printf("\033[%dm", L_GREEN);
			printf("\n******************************** ALERT! ********************************\n");
			printf("\n*                     File printed successfully!                       *\n");
			printf("\n************************************************************************\n");
			printf("\033[0m");

		}
		else if (choice == 8) {
			SortLinkedList(headPtr);
			displayAllDatabase(headPtr);


		}

		menu();
		scanf("%d", &choice);
	}

	outputClientFILES(headPtr);
	printf("\033[%dm", L_GREEN);
	printf("\n******************************** ALERT! ********************************\n");
	printf("\n*                     File printed successfully!                       *\n");
	printf("\n************************************************************************\n");
	printf("\033[0m");

}