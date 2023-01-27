#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define MAX_ITEMS 100


// -----------------------------------function 
// -------------------system login
void displayMenu();
void takeinput(char ch[50]);
char generateUsername(char email[50], char username[50]);
void takepassword(char pwd[50]);
void login();
void signup();

// -----------------display
void display_exit();
void displayStock();
void addItem();
void removeItem();
void updateItem();
void areUSure();
void displayCrud();
void displayOverflow(int i);
void displayCrud();


// -------------------crud
void create(char *fileName);
void read(char *fileName);
void update(char *fileName);
void delete(char *fileName);

int compareByName(const void* a, const void* b);
int compareByPrice(const void* a, const void* b);
int compareByQuantity(const void *a, const void *b);

// -------------------struct
struct user
{
		char fullName[50];
		char email[50];
		char password[50];
		char username[50];
		char phone[50];
};

struct Goods {
    char name[50];
    int quantity;
    float price;
	char supplier[50];
};
struct Item {
    char name[30];
    int quantity;
    float price;
};

struct Item stock[MAX_ITEMS];
int itemCount = 0;

int main()
{
	main_Menu:
		FILE *fp;
		int opt, usrFound = 0;
		struct user user;
		char password2[50];
		displayMenu();
		scanf("%d", &opt);
		fgetc(stdin);

	switch (opt){
	case 1: //--------------------------------------------------------signup
		system("cls");
		signup();
		printf("\nEnter your full name:\t");
		takeinput(user.fullName);
		printf("Enter your email:\t");
		takeinput(user.email);
		printf("Enter your contact no:\t");
		takeinput(user.phone);
		printf("Enter your password:\t");
		takepassword(user.password);
		printf("\nConfirm your password:\t");
		takepassword(password2);

		if (!strcmp(user.password, password2))
		{
			generateUsername(user.email, user.username);
			fp = fopen("Users.dat", "a+");
			fwrite(&user, sizeof(struct user), 1, fp);
			if (fwrite != 0)
				printf("\n\nUser resgistration success, Your username is %s", user.username);
			else
				printf("\n\nSorry! Something went wrong :(");
			fclose(fp);
		}
		else
		{
			printf("\n\nPassword donot matched");
			Beep(750, 300);
		}
		Sleep(4000);
		system("cls");
		main();
		break;

	case 2: //----------------------------------------------------login
		login:
			char username[50], pword[50];
			struct user usr;
			system("cls");
			login();
			
			printf("\nEnter your username:\t");
			takeinput(username);
			printf("Enter your password:\t");
			takepassword(pword);

			fp = fopen("Users.dat", "r");
			while (fread(&usr, sizeof(struct user), 1, fp))
			{
				if (!strcmp(usr.username, username))
				{
					if (!strcmp(usr.password, pword))
					{
						//  --------------------------------------------------crud
						system("cls");
						char word1[] = "selamat datang di program stock of goods";
						char word2[] = "satu platform yang akan pernah Anda butuhkan untuk mengubah semua aktivitas Anda";
						int length1 = strlen(word1);
						int length2 = strlen(word2);

						for(int i = 0 ; i < length1; i++){
							printf("%c",word1[i]);
							fflush(stdout);
							Sleep(50);
						}
						system("cls");
						for(int i = 0; i < length2;i++){
							printf("%c",word2[i]);
							fflush(stdout);
							Sleep(50);
						}
						system("cls");
						printf("==========================================================================================================\n");
											printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
											printf("|          ");
											char WelcomeName[] = "welcome";
											int length  = strlen(WelcomeName);
											printf("\t\t\t\t\t");
											for(int i = 0; i < length; i++){
												printf("%c",WelcomeName[i]);
												fflush(stdout);
												Sleep(100);
											}
											printf("\033[1;31m %s\033[0m",usr.fullName);
											printf("                                        |\n");
											printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
						printf("==========================================================================================================\n");	
						int choice;
							while(1) {
							displayCrud();
							scanf("%d", &choice);
							switch(choice) {
								case 1:
									displayOverflow(choice);
									create(usr.username);
									system("cls");
									break;
								case 2:
									
									displayOverflow(choice);
									read(usr.username);
									break;
								case 3: 
									displayOverflow(choice);
									update(usr.username);
									break;
								case 4: 
									displayOverflow(choice);
									delete(usr.username);
									break;
								case 5: 
									system("cls");
									goto main_Menu;
								default: 
									printf("Invalid choice\n");
									Sleep(500);
									system("cls");
								}
						}
						
					}
					else
					{
						
						printf("\n\nInvalid Password!");
						Beep(800, 300);
						goto login;
						
					}
					usrFound = 1;
				}
			}
			if (!usrFound)
			{
				printf("\n\nUser is not registered!");
				int i = 0 ;
				Beep(800, 300);
				printf("\ntype 1 to back: ");
				scanf("%d",&i);
				if(i == 1){
					system("cls");
					goto main_Menu;
				}else{
					goto login;
				}
			}
			fclose(fp);
			break;

	case 3:
		system("cls");
		display_exit();
		return 0;
		break;
	default:
		char error[] ="error, select the option above";
		int length = strlen(error);
		for(int i = 0 ; i < length ; i++){
			printf("%c",error[i]);
			fflush(stdout);
			Sleep(100);
		}
		printf("\n");
		system("cls");
		main();
	}
	return 0;
}
void takeinput(char ch[50])
{
	fgets(ch, 50, stdin);
	ch[strlen(ch) - 1] = 0;
}

char generateUsername(char email[50], char username[50])
{
	for (int i = 0; i < strlen(email); i++)
	{
		if (email[i] == '@')
			break;
		else
			username[i] = email[i];
	}
}

void takepassword(char pwd[50])
{
	int i;
	char ch;
	while (1)
	{
		ch = getch();
		if (ch == ENTER || ch == TAB)
		{
			pwd[i] = '\0';
			break;
		}
		else if (ch == BCKSPC)
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}

void displayMenu()
{

	printf("==========================================================================================================\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("|                                             system login                                               |\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("==========================================================================================================\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("|\t\t\t\t\tPlease choose your operation\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t1.Signup\t\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t2.Login\t\t\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t3.Exit\t\t\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("==========================================================================================================\n");
	printf("\n\t\t\t\t\tYour choice:\t");
}

void displayCrud(){
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("|\t\t\t\t\tPlease choose your operation\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t1.create item\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t2.display item\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t3.update item\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t4.delete item\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t5.exit\t\t\t\t\t\t\t |");
	printf("\n|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("==========================================================================================================\n");
	printf("\n\t\t\t\t\tYour choice:\t");
}

void login(){
	printf("==========================================================================================================\n");	
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("|                                             login                                                      |\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
	printf("==========================================================================================================\n");
}

void signup(){
		printf("==========================================================================================================\n");
		printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
		printf("|                                 Hello! signup to get started                                           |\n");
		printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
		printf("==========================================================================================================\n");
}
void display_name(){
		printf("==========================================================================================================\n");
		printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");

		printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t |\n");
		printf("==========================================================================================================\n");
}
void display_exit(){
		printf("==========================================================================================================\n");
		printf("|                   &&&&&& &&  &&     &    &&&  && &&  &&   &&  &&  &&&   &&  &&                         |\n");
		printf("|                     &&   &&  &&    &&&   &&&& && && &&     &&&&  && &&  &&  &&                         |\n");
		printf("|                     &&   &&&&&&   &&&&&  && &&&& &&&&       &&  &&   && &&  &&                         |\n");
		printf("|                     &&   &&  &&  &&   && &&  &&& && &&      &&   &&&&&  &&&&&&                         |\n");
		printf("|                                                                                                        |\n");
		printf("|                                            made by :                                                   |\n");
		printf("|                                    pancamaulana 1203220102                                             |\n");
		printf("|                                  arrenga nabakata 11203220108                                          |\n");
		printf("|                                    syahrul aziz 1203220084                                             |\n");
		printf("==========================================================================================================\n");
		Sleep(10000);
}


// ====================================crud function
// create read delete 
void create(char *fileName) {
    struct Goods g;
	 printf("Enter supplier: ");
    scanf("%s", g.supplier);
    printf("Enter name: ");
    scanf("%s", g.name);
    printf("Enter quantity: ");
    scanf("%d", &g.quantity);
    printf("Enter price: ");
    scanf("%f", &g.price);
    FILE *fp;
    fp = fopen(fileName, "a");
    fwrite(&g, sizeof(g), 1, fp);
    fclose(fp);
    printf("Record added successfully\n");
	Sleep(1000);
}
// function display
void read(char *fileName){
struct Goods g[100]; 
FILE *fp;
int i = 0;
int opt;
menu:
printf("\t\t\t\t  =========================================\n");
printf("\t\t\t\t  |----------------display----------------|\n");
printf("\t\t\t\t  |1.display by alphabetical order of name|\n");
printf("\t\t\t\t  |2.display by price                     |\n");
printf("\t\t\t\t  |3.display by quantity                  |\n");
printf("\t\t\t\t  =========================================\n");
printf("\t\t\t\t  your choice: ");
scanf("%d", &opt);

fp = fopen(fileName, "r");
while(fread(&g[i], sizeof(g[i]), 1, fp)) {
i++;
}
fclose(fp);


if(opt == 1){
	qsort(g, i, sizeof(struct Goods), compareByName); // sorting by name

}else if(opt == 2){
	qsort(g, i, sizeof(struct Goods), compareByPrice); // sorting by price
} else if(opt == 3){
	qsort(g, i, sizeof(struct Goods), compareByQuantity); // sorting by quantity
}else{
	printf("Invalid choice\n");
	Beep(750, 300);
	system("cls");
	goto menu;
}
// display the goods in the sorted order
printf("\n\t\t|----|-------------------|-------------------|-------------------|-------------------|\n");
printf("\t\t| No |supplier\t\t |Name\t\t     |Quantity\t\t |Price\t\t     |\n");
printf("\t\t|----|-------------------|-------------------|-------------------|-------------------|\n");
for(int j = 0; j < i; j++){
    printf("\t\t| %d  |%s\t\t |%s\t\t     |%d\t\t         |%.2f\t\t     |\n", j+1, g[j].supplier, g[j].name, g[j].quantity, g[j].price);
    printf("\t\t|----|-------------------|-------------------|-------------------|-------------------|\n");
}
printf("==========================================================================================================\n");

}

// --------------------------------------------sorting 
int compareByName(const void* a, const void* b){
struct Goods *ia = (struct Goods *)a;
struct Goods *ib = (struct Goods *)b;
return strcmp(ia->name, ib->name);
}


int compareByPrice(const void* a, const void* b){
struct Goods *ia = (struct Goods *)a;
struct Goods *ib = (struct Goods *)b;
if(ia->price < ib->price) return -1;
else if(ia->price > ib->price) return 1;
else return 0;
}

int compareByQuantity(const void *a, const void *b) {
    struct Goods *goods1 = (struct Goods *)a;
    struct Goods *goods2 = (struct Goods *)b;
    return (goods1->quantity - goods2->quantity);
}

void update(char *fileName) {
    struct Goods g;
    char name[50];
    int quantity;
    float price;
	char supplier[50];
    FILE *fp;
    fp = fopen(fileName, "r+");
    printf("Enter name of goods to update: ");
    scanf("%s", name);
    printf("Enter new quantity: ");
    scanf("%d", &quantity);
    printf("Enter new price: ");
    scanf("%f", &price);
    while(fread(&g, sizeof(g), 1, fp)) {
        if(strcmp(g.name, name) == 0) {
            g.quantity = quantity;
            g.price = price;
            fseek(fp, -sizeof(g), SEEK_CUR);
            fwrite(&g, sizeof(g), 1, fp);
            printf("Record updated successfully\n");
            break;
        }
    }
    fclose(fp);
}

void delete(char *fileName) {
struct Goods g;
char name[50];
int found = 0;
FILE *fp, *temp;
fp = fopen(fileName, "r");
temp = fopen("temp.txt", "w");
printf("Enter name of goods to delete: ");
scanf("%s", name);
while(fread(&g, sizeof(g), 1, fp)) {
		if(strcmp(g.name, name) != 0) {
		fwrite(&g, sizeof(g), 1, temp);
		}
		else {
		found = 1;
		}
		}
		if(found == 0) {
		printf("Error: Goods with name %s does not exist\n", name);
		Beep(750, 300);
		Sleep(1000);
		system("cls");
		}
		else {
		printf("Record deleted successfully\n");
		Sleep(500);
		system("cls");
		}
	fclose(fp);
	fclose(temp);
	remove(fileName);
	rename("temp.txt", fileName);
}
void areUSure() {
    char input;
    printf("Are you sure? (y/n) ");
    scanf("%c", &input);
    while (input != 'y' && input != 'n') {
        printf("Invalid input. Please enter 'y' or 'n': ");
        scanf(" %c", &input);
    }
    if (input == 'y') {
        main();
    }
}

void displayOverflow(int i){
	system("cls");
	switch(i){
		case 1:
			printf("\t\t             x--------------0--------------0--------------0               \n");
			break;
		case 2: 
			printf("\t\t             0--------------x--------------0--------------0               \n");
			break;
		case 3: 
			printf("\t\t             0--------------0--------------x--------------0               \n");
			break;
		case 4:
			printf("\t\t             0--------------0--------------0--------------x               \n");
			break;
	}
	      	printf("\t\t             create item   display item    update item   delete item     \n");
}
