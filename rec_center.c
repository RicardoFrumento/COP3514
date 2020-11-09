#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CLASS_LEN 100 //Defining the size of the buffers used
#define NAME_LEN 30
#define EMAIL_LEN 50

struct request{ //Defining the structure of the linked list used to store the information necessary to check and/or store the request
	char class[CLASS_LEN+1];
	char first[NAME_LEN+1];
	char last[NAME_LEN+1];
	char email[EMAIL_LEN+1];;

	struct request *next;
};

struct request *load(); //Prototypes of the function used on the program
void save(struct request *list);
struct request *append(struct request *list);
struct request *delete(struct request *list);
void printList(struct request *list);
void clearList(struct request *list);
int read_line(char str[], int n);

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main(void)
{
  char code;

  struct request *wait_list = load();
  printf("Operation Code: d for removing from the list, a for appending to the list,"
	  ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n')   /* skips to end of line */
      ;
    switch (code) {
      case 'd': wait_list = delete(wait_list);
                break;
      case 'a': wait_list = append(wait_list);
                break;
      case 'p': printList(wait_list);
                break;
      case 'q': save(wait_list);
		clearList(wait_list);
		return 0;
      default:  printf("Illegal code\n");
    }
    printf("\n");
  }
}

/**********************************************************
 * load: read file "waiting_list.txt" and store the data  *
 *       in a linked list and returns the linked list     *
 **********************************************************/

struct request *load(){
	struct request * list= NULL;
	struct request *prev, *new_node;
	char f_name[NAME_LEN+1];
	char l_name[NAME_LEN+1];
	char e_address[EMAIL_LEN+1];
	char class_name[CLASS_LEN+1];

	FILE *pFile;

        pFile = fopen("waiting_list.txt", "r");

	if(pFile == NULL)
	{
		printf("Error opening the file\n");
		return NULL;
	}

        while(!feof(pFile)&&!ferror(pFile))
	{
	       if(fscanf(pFile, "%s%s%s%s", e_address, class_name, f_name, l_name)== 4)
		{

 			 new_node = malloc(sizeof(struct request));
 			 if (new_node == NULL) {
    				printf("Database is full; loding error.\n");
    				return NULL;
 			 }

			strcpy(new_node->email, e_address);
			strcpy(new_node->class, class_name);
			strcpy(new_node->first, f_name);
			strcpy(new_node->last, l_name);
			new_node->next = NULL;

			if(list == NULL)
				list = new_node;
			else
				prev->next = new_node;
			prev = new_node;

        	}
	}
	return list;
}

/**********************************************************
 * save: write to file "waiting_list.txt" with the data   *
 *       in the linked list passed in as parameter        *
 **********************************************************/


void save(struct request *list)
{

	struct request * p;

	FILE *pFile;

        pFile = fopen("waiting_list.txt", "w");

	if(pFile == NULL)
	{
		printf("Error opening the file\n");
		return;
	}
	for (p =list; p != NULL; p = p->next)
    		fprintf(pFile, "%-s %s %s %s\n", p->email, p->class, p->first,p->last);

	fclose(pFile);


}

/**********************************************************
 * delete: Asks for the information of a request and      *
 *         if found, deletes it. If the request does not  *
 *         exists, prints an error message                *
 **********************************************************/

struct request *delete(struct request *list){
    char email[EMAIL_LEN+1];
    char class[CLASS_LEN+1];
    char fName[NAME_LEN+1];
    char lName[NAME_LEN+1];

    struct request *info1, *info2;

    printf("Enter email: ");
    read_line(email,EMAIL_LEN+1);
    printf("Enter class: ");
    read_line(class,CLASS_LEN+1);
    printf("Enter first name: ");
    read_line(fName,NAME_LEN+1);
    printf("Enter last name: ");
    read_line(lName, NAME_LEN+1);

    for(info2 = list, info1 = NULL; info2 != NULL; info1 = info2, info2 = info2->next){ //Runs through the list until found a NULL pointer
        if(strcmp(info2->email,email)==0 && strcmp(info2->first,fName)==0 && strcmp(info2->last,lName)==0 && strcmp(info2->class,class)==0) //Checks is the request exists
            break;
    }
    if(info2 == NULL){
        printf("There is no request\n"); //Error message if the request does not exists
        return list;
    }
    if(info1 == NULL){
        list = list->next;
    }
    else{
        info1->next = info2->next;
    }
    free(info2);
    return list;


}

/**********************************************************
 * append: Asks for the information of a request and if   *
 *         it does not exists add it to the end of the    *
 *         of the linked list
 **********************************************************/

struct request *append(struct request *list){

    char email[EMAIL_LEN+1];
    char class[CLASS_LEN+1];
    char fName[NAME_LEN+1];
    char lName[NAME_LEN+1];

    struct request *info1, *info2, *newRequest;

    printf("Enter email: ");
    read_line(email,EMAIL_LEN+1);
    printf("Enter class: ");
    read_line(class,CLASS_LEN+1);
    printf("Enter first name: ");
    read_line(fName,NAME_LEN+1);
    printf("Enter last name: ");
    read_line(lName, NAME_LEN+1);

    for(info2 = list, info1 = NULL; info2 != NULL; info1 = info2, info2 = info2->next){ //Runs through the liked list
        if(strcmp(info2->email,email)==0 && strcmp(info2->first,fName)==0 && strcmp(info2->last,lName)==0 && strcmp(info2->class,class)==0) //Checks if the request exists
            break;
    }
    if(info2 == NULL){
        newRequest = malloc(sizeof(struct request)); //Allocating memory for the new node

        if(newRequest == NULL){
            printf("Operation did not work\n");
            return list;
        }

        strcpy(newRequest->email,email);
        strcpy(newRequest->class,class);
        strcpy(newRequest->first,fName);
        strcpy(newRequest->last,lName);
        info1->next=newRequest;
        info2 = newRequest;
        return list;
    }
    else{
        printf("There is already a request\n"); //Error message if the request already exists
        return list;
    }
}


/**********************************************************
 * printList: print the data  in the linked list passed   *
 * in as parameter                                        *
 **********************************************************/


void printList(struct request *list){

  struct request *p;

  for (p =list; p != NULL; p = p->next)
    printf("%-50s%-15s%-15s%15s\n", p->email, p->first,p->last,
           p->class);

}

/**********************************************************
 * clearList: Frees the memory used to store the store the*
 *            linked list with the information about the  *
 *            requests                                    *
 **********************************************************/

void clearList(struct request *list)
{

    struct request *clearMemory;
    while(list!=NULL){
        clearMemory = list;
        list = list->next;
        if(clearMemory != NULL){
            free(clearMemory);
        }
    }

}

/**********************************************************
 * read_line: Reads one line of user input                *
 **********************************************************/

int read_line(char str[], int n)
{
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  str[i++] = ch;
  while ((ch = getchar()) != '\n') {
    if (i < n)
      str[i++] = ch;

   }
   str[i] = '\0';
   return i;
}
