#include <stdio.h>
#include "time.h"
#include "string.h"
#include <stdlib.h>
#include <assert.h>

 struct transaction{
    double amount;
    struct tm date;
    char description[200];
    int type;
};

/// PRINT FUNCTIONS: -------------------------------------------------

void write_menu(){
    /**
     * param: none
     * return: none
     * description: prints in the console a list of available options for the user
     */
    printf("MENU:\n");
    printf("1. Add transaction\n");
    printf("2. View transactions\n");
    printf("3. Calculate account balance\n");
    printf("4. Generate financial report\n");
    printf("5. Save transactions to file\n");
    printf("6. Load transactions from file\n");
}

void print_one_transaction(struct transaction v){
    /**
     * param: array of transaction objects
     * return: none
     * description: prints in the console one transaction, passed as the argument
     * preconditions: validity of transaction information
     */
    char c;
    if(v.type==0){
        c='+';
    }else c='-';
    char buffer[32];
    strftime(buffer, 32, "%d/%m/%Y %H:%M:%S", &v.date);
    printf("Date: %s\n", buffer);
    printf("Amount: %c%1.2lf\n", c,v.amount);
    printf("Description: %s\n", v.description);
}

void print_transactions(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: prints in the console the history of transactions, found in the first argument
     * exception: empty array raises the "No available transaction" error message
     * preconditions: validity of transaction information
     */
     if(records==0){
         printf("No available transactions\n");
     }
     else{
         printf("-  -  -  -  -  -  -  -  -  -  -\n");
         for(int i=0; i<records; i++){
             print_one_transaction(v[i]);
             printf("-  -  -  -  -  -  -  -  -  -  -\n");
         }
     }
}

/// FUNCTIONS FOR FILE MANIPULATION: ----------------------------------

void add_from_file(char s[], struct transaction v[], int *records){
    /**
     * param: char[], array of transaction objects, integer
     * return: none
     * description: appends a new transaction from the given string to the array passed as argument
     * preconditions: validity of transaction information
     */
    struct transaction aux;
    char *p=strtok(s, "~");
    aux.amount=atof(p);
    p=strtok(NULL, "~");
    strcpy(aux.description, p);
    p=strtok(NULL, "~");
    aux.type=atoi(p);
    p=strtok(NULL, "~");
    aux.date.tm_mday=atoi(p);
    p=strtok(NULL, "~");
    aux.date.tm_mon=atoi(p)-1;
    p=strtok(NULL, "~");
    aux.date.tm_year=atoi(p)-1900;
    p=strtok(NULL, "~");
    aux.date.tm_hour=atoi(p);
    p=strtok(NULL, "~");
    aux.date.tm_min=atoi(p);
    p=strtok(NULL, "~");
    aux.date.tm_sec=atoi(p);

    v[*records]=aux;
    (*records)++;
}

void save_transactions_to_file(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: prints in file "history.txt" a list of all transactions
     * preconditions: validity of transaction information
     * exception: empty array raises "No transactions available"
     */
    FILE *fp;
    fp = fopen("history.txt", "w");
    for(int i=0; i<records; i++) {
        fprintf(fp, "%g~", v[i].amount);
        fprintf(fp, "%s~", v[i].description);
        fprintf(fp, "%d~", v[i].type);
        char buffer[26];
        strftime(buffer, 26, "%d~%m~%Y~%H~%M~%S", &v[i].date);
        fprintf(fp, "%s\n", buffer);
    }
    fclose(fp);
    if(records==0)
        printf("No transactions available\n");
    else printf("Transactions saved to file\n");
}

void load_transactions_from_file(struct transaction v[], int *records){
    /**
    * param: array of transaction objects, integer
    * return: none
    * description: saves in the array passed as an argument the transactions from file "history.txt"
    * exception: empty file raises "No available back-up"
    * preconditions: validity of transaction information
    */
    FILE *fp;
    fp = fopen("history.txt", "r");

    *records=0;
    char myString[1000];
    int iterations=0;
    while(fgets(myString, 1000, fp)) {
        iterations++;
        add_from_file(myString, v, records);
    }

    fclose(fp);
    if(iterations==0){
        printf("No available back-up\n");
    }
    else
        printf("Transactions loaded from file\n");
}

/// BASIC ACCOUNTING FEATURES: -----------------------------------------

int check_date_in_interval(struct tm start_date, struct tm end_date, struct tm item){
    /**
     * param: tm datetime object, tm datetime object, tm datetime object
     * return: integer (0/1)
     * description: checks if argument item is between two given dates
     * preconditions: validity of transaction information
     */
    struct tm new_date=item;
    start_date.tm_year-=1900;
    end_date.tm_year-=1900;
    new_date.tm_year-=1900;
    int s_date=mktime(&start_date);
    int e_date=mktime(&end_date);
    int item_date=mktime(&new_date);
    long long int dif1=item_date-s_date;
    long long int dif2=e_date-item_date;
    if(dif1>=0 && dif2>=0)
        return 1;
    return 0;
}

int check_date_in_interval_tester(){
    struct tm date1; date1.tm_mday=20; date1.tm_mon=9; date1.tm_year=2023;
    struct tm date2; date2.tm_mday=21; date2.tm_mon=9; date2.tm_year=2023;
    struct tm date3; date3.tm_mday=23; date3.tm_mon=9; date3.tm_year=2023;
    assert(check_date_in_interval(date1, date1, date1)==1);
    assert(check_date_in_interval(date1, date1, date2)==0);
    assert(check_date_in_interval(date1, date2, date2)==1);
    assert(check_date_in_interval(date1, date2, date1)==1);
    assert(check_date_in_interval(date2, date1, date2)==0);
    assert(check_date_in_interval(date1, date3, date2)==1);
}

double calculate_account_balance(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: calculates the current account balance
     * preconditions: validity of transaction data
     */
    double balance=0;
    for(int i=0; i<records; i++){
        if(v[i].type==0)
            balance+=v[i].amount;
        else balance-=v[i].amount;
    }
    return balance;
}

void calculate_account_balance_tester(){
    struct transaction array[1];
    assert(calculate_account_balance(array, 0)==0);
    struct transaction array1[2], aux1, aux2;
    aux1.amount=100; aux2.amount=120;
    array1[1]=aux1;array1[0]=aux2;
    assert(calculate_account_balance(array1, 2)==220);
    aux1.amount=100.25; aux2.amount=120.36;
    array1[1]=aux1;array1[0]=aux2;
    assert(calculate_account_balance(array1, 2)==220.61);
    aux1.amount=-100.25; aux2.amount=120.36;
    array1[1]=aux1;array1[0]=aux2;
    assert(calculate_account_balance(array1, 2)==20.11);
    aux1.amount=100.25; aux2.amount=-120.36;
    array1[1]=aux1;array1[0]=aux2;
    assert(calculate_account_balance(array1, 2)==-20.11);
}

void print_account_balance(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: prints in the console the current account balance
     * exception: empty array raises "No available transactions"
     * preconditions: validity of transaction data
     */
    double balance= calculate_account_balance(v, records);
    if(records==0){
        printf("No available transactions\n");
    }
    else printf("Your current account balance is: %g\n", balance);
}

/// --------------------------------------------------------------------

void global_tester(){
    check_date_in_interval_tester();
    calculate_account_balance_tester();
}

void add(struct transaction v[], int *records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: appends a new transaction to the array passed as argument
     */
    struct transaction aux;
    printf("Type amount:\n");
    scanf("%lf", &aux.amount);
    printf("Type description:\n");
    scanf("%200s", aux.description);
    printf("Income or expense? [0/1]");
    scanf("%d", &aux.type);
    time_t t = time(NULL);
    aux.date = *localtime(&t);
    v[*records]=aux;
    *records=*records+1;
    printf("Added transaction:\n");
    print_one_transaction(v[*records-1]);
}

int validate_date(char s[], struct tm *new_date){
    /**
     * param: char[], *tm datetime object
     * return: integer (0/1)
     * description: checks if the date provided as an argument meets the ISO C standard and stores
     *  the data for a time since the Epoch object
     * exception: the result can not be represented -> "Invalid date"
     */
    int day, month, year;
    char *p=strtok(s, "/");
    day=atoi(p);
    p=strtok(NULL, "/");
    month=atoi(p);
    p=strtok(NULL, "/");
    year=atoi(p);

    return 1;

}

void generate_financial_report(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: generates a financial report consisting of a summary of income and expenses between two given dates
     * exception: no transactions found for given dates
     */
    char s[250], e[250];
    struct tm start_date, end_date;
    printf("Write the start date in format DD/MM/YYYY:");
    gets(s);
    while(validate_date(s, &start_date)==0){
        gets(s);
    }

    printf("Write the end date in format DD/MM/YYYY:");
    gets(s);
    while(validate_date(s, &end_date)==0){
        gets(s);
    }

    strftime(s,80,"%d/%m/%Y", &start_date);
    printf("%s\n", s);
    strftime(e,80,"%d/%m/%Y", &end_date);

    double income=0, expenses=0;
    for (int i=0; i<records; i++){
        if(check_date_in_interval(start_date, end_date, v[i].date)){
            if(v[i].type==0)
                income+=v[i].amount;
            else expenses+=v[i].amount;
        }
    }
    if(income==0 && expenses==0)
        printf("No transactions found between given dates");
    else{
        printf("Income: %g\n", income);
        printf("Expenses: %g\n", expenses);
    }
}

int main(){
    global_tester();
    char menu_choice[100];
    struct transaction v[50];
    int records=0;
    write_menu();
    while(menu_choice[0]!='0'){
        scanf("%s", menu_choice);
        if(strcmp(menu_choice,"1")==0){
            add(v, &records);
        }
        else if(strcmp(menu_choice,"2")==0){
            print_transactions(v, records);
        }
        else if(strcmp(menu_choice,"3")==0){
            print_account_balance(v, records);
        }
        else if(strcmp(menu_choice,"4")==0){
            generate_financial_report(v, records);
        }
        else if(strcmp(menu_choice,"5")==0){
            save_transactions_to_file(v, records);
        }
        else if(strcmp(menu_choice,"6")==0){
            load_transactions_from_file(v, &records);
        }
        else{
            printf("Invalid option.");
        }
    }
    return 0;
}
