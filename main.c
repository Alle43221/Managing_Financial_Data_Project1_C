#include <stdio.h>
#include "time.h"
#include "string.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

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

/// VALIDATION FUNCTIONS: ----------------------------------------------

int validate_date_format(char s[]){
    /**
     * param: char[]
     * return: integer (0/1)
     * description: checks if the string provided respects the imposed "DD/MM/YYYY" format
     */
     char copy[250];
    strcpy(copy, s);
    if(strlen(s)!=10){
        return 0;
    }
    char *p;
    p=strtok(s, "/");
    if(strlen(p)!=2){
        return 0;
    }
    if(!isdigit(*p) || !isdigit(*(p+1))) {
        return 0;
    }
    p= strtok(NULL, "/");
    if(strlen(p)!=2){
        return 0;
    }
    if(!isdigit(*p) || !isdigit(*(p+1))) {
        return 0;
    }
    p= strtok(NULL, "/");
    if(strlen(p)!=4){
        return 0;
    }
    if(!isdigit(*p) || !isdigit(*(p+1)) || !isdigit(*(p+2))|| !isdigit(*(p+3))) {
        return 0;
    }
    strcpy(s, copy);
    return 1;
}

int validate_date(char s[]){
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to a valid date
    * preconditions: the string respects the format "DD/MM/YYYY"
    */
    char copy[11];
    strcpy(copy, s);
    char *p=strtok(s, "/");
    int day= atoi(p);
    p=strtok(NULL, "/");
    int month= atoi(p);
    p=strtok(NULL, "/");
    int year= atoi(p);

    if(day<=0 || month<=0 || year<=0)
        return 0;
    if(year<1900)
        return 0;
    if(month>12)
        return 0;
    if(month==4 || month==6 || month==9 || month==11){
        if(day>30)
            return 0;
    }
    else if(month==2){
        if(year%16!=0 && year%4==0){
            if(day>29)
                return 0;
        }
        else
        if(day>28)
            return 0;
    }
    else{
        if(day>31)
            return 0;
    }
    strcpy(s, copy);
    return 1;
}

int validate_amount(char s[]){
    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to a valid amount
    */
    int len=strlen(s);
    for(int i=0; i< len; i++){
        if(isdigit(s[i])==0 && s[i]!='.')
            return 0;
    }
    double amount=atof(s);
    if(amount<=0)
        return 0;
    if(amount>1000000)
        return 0;
    amount*=100.0;
    amount-=(int) amount;
    if(amount>0)
        return 0;
    return 1;
}

int validate_description(char s[]){
    /**
   * param: char[]
   * return: integer (0/1)
   * description: checks if the string provided corresponds to a valid, not null description
   */
   if(strlen(s)==0)
       return 0;
    for(int i=0; i< strlen(s); i++){
        if(s[i]=='~')
            return 0;
    }
    return 1;
}

int validate_type(char s[]){

    /**
    * param: char[]
    * return: integer (0/1)
    * description: checks if the string provided corresponds to a valid type
    */

    if(strlen(s)!=1)
        return 0;
    if(s[0]!='0' && s[0]!='1')
        return 0;

    return 1;
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

void calculate_income_expenses(struct transaction v[], int records, double *income, double *expenses, struct tm start_date, struct tm end_date){
    /**
    * param: array of transaction objects, integer, *double, *double, tm object, tm object
    * return: none
    * description: calculates the sum of income and, respectively, expenses between two given dates
    */
    *income=0, *expenses=0;
    for (int i=0; i<records; i++){
        if(check_date_in_interval(start_date, end_date, v[i].date)){
            if(v[i].type==0)
                *income+=v[i].amount;
            else *expenses+=v[i].amount;
        }
    }
}

void generate_financial_report(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: generates a financial report consisting of a summary of income and expenses between two given dates
     * exception: No transactions found for given dates
     */
    char s[250];
    struct tm start_date, end_date;
    gets(s);
    printf("Write the start date in format DD/MM/YYYY:");
    gets(s);
    int ok=0;
    while(ok==0){
        if(validate_date_format(s)==1){
            if(validate_date(s)==1)
                ok=1;
            else {
                printf("Invalid format!");
                gets(s);
            }
        }
        else
        {
            printf("Invalid format!");
            gets(s);
        }
    }
    strftime(s,10,"%d/%m/%Y", &start_date);
    ok=0;
    printf("Write the end date in format DD/MM/YYYY:");
    gets(s);
    while(ok==0){
        if(validate_date_format(s))
            if(validate_date(s))
                ok=1;
            else {
                printf("Invalid format!");
                gets(s);
            }
        else
        {
            printf("Invalid format!");
            gets(s);
        }
    }
    strftime(s,10,"%d/%m/%Y", &end_date);

    //separate summing of rest of function
    double income, expenses;
    calculate_income_expenses(v, records, &income, &expenses, start_date, end_date);
    if(income==0 && expenses==0)
        printf("No transactions found between given dates");
    else{
        printf("Income: %g\n", income);
        printf("Expenses: %g\n", expenses);
    }
}

void add(struct transaction v[], int *records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: appends a new transaction to the array passed as argument
     */
    struct transaction aux;
    char s[250];
    gets(s);
    printf("Type amount:\n");
    gets(s);
    int ok=0;
    while(ok==0){
        if(validate_amount(s))
            ok=1;
        else {
            printf("Invalid input!\n");
            gets(s);
        }
    }
    aux.amount= atof(s);

    printf("Type description:\n");
    ok=0;
    gets(s);
    while(ok==0){
        if(validate_description(s))
            ok=1;
        else {
            printf("Description can not contain the character \"~\" and must not be null!\n");
            gets(s);
        }
    }
    strcpy(aux.description, s);

    printf("Income or expense? [0/1]");
    gets(s);
    ok=0;
    while(ok==0){
        if(validate_type(s))
            ok=1;
        else{
            printf("Invalid input!\n");
            gets(s);
        }
    }
    aux.type=atoi(s);

    time_t t = time(NULL);
    aux.date = *localtime(&t);
    v[*records]=aux;
    *records=*records+1;
    printf("Added transaction:\n");
    print_one_transaction(v[*records-1]);
}

/// TESTING FUNCTIONS: ------------------------------------------------

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

void calculate_income_expenses_tester(){
    struct transaction array[1];
    struct tm date1; date1.tm_mday=20; date1.tm_mon=9; date1.tm_year=2023;
    double income=0, expenses=0;
    calculate_income_expenses(array, 0, &income, &expenses, date1, date1);
    assert(income==0 && expenses== 0);

    struct transaction array1[2], aux1, aux2;
    aux1.amount=100.25; aux2.amount=120.36;
    aux1.type=0; aux2.type=0;
    aux1.date=date1; aux2.date=date1;
    array1[1]=aux1;array1[0]=aux2;
    calculate_income_expenses(array1, 2, &income, &expenses, date1, date1);
    assert(income==220.61 && expenses==0);

    array1[0].type=1;
    calculate_income_expenses(array1, 2, &income, &expenses, date1, date1);
    assert(income==100.25 && expenses==120.36);

    array1[1].type=1;
    calculate_income_expenses(array1, 2, &income, &expenses, date1, date1);
    assert(income==0 && expenses==220.61);
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

void validate_date_format_tester(){
    char s[15]="1/12/2023";
    assert(validate_date_format(s)==0);
    strcpy(s, "12/1/2023");
    assert(validate_date_format(s)==0);
    strcpy(s, "12/12/23");
    assert(validate_date_format(s)==0);
    strcpy(s, "01/12/2023");
    assert(validate_date_format(s)==1);
    strcpy(s, "12/01/2023");
    assert(validate_date_format(s)==1);
    strcpy(s, "//");
    assert(validate_date_format(s)==0);
    strcpy(s, "aa/aa/aaaa");
    assert(validate_date_format(s)==0);
    strcpy(s, "abracadabra");
    assert(validate_date_format(s)==0);
    strcpy(s, "23/14/2000");
    assert(validate_date_format(s)==1);
    strcpy(s, "-3/14/2000");
    assert(validate_date_format(s)==0);
}

void validate_date_tester(){
    char s[11]="12/12/2023";
    assert(validate_date(s)==1);
    strcpy(s, "11/13/2023");
    assert(validate_date(s)==0);
    strcpy(s, "11/12/1800");
    assert(validate_date(s)==0);
    strcpy(s, "33/12/2023");
    assert(validate_date(s)==0);
    strcpy(s, "31/04/2023");
    assert(validate_date(s)==0);
    strcpy(s, "00/04/2023");
    assert(validate_date(s)==0);
    strcpy(s, "29/02/2016");
    assert(validate_date(s)==0);
    strcpy(s, "28/02/2016");
    assert(validate_date(s)==1);
    strcpy(s, "29/02/2020");
    assert(validate_date(s)==1);
}

void validate_amount_tester(){
    assert(validate_amount("120"));
    assert(validate_amount("120.59"));
    assert(validate_amount("120,59")==0);
    assert(validate_amount("120."));
    assert(validate_amount("portocala")==0);
    assert(validate_amount("12a")==0);
    assert(validate_amount("0")==0);
    assert(validate_amount("-12")==0);
    assert(validate_amount("10000000")==0);
    assert(validate_amount("100.658")==0);
}

void validate_description_tester(){
    char s[15]="bursa";
    assert(validate_description(s));
    strcpy(s, "bursa~");
    assert(validate_description(s)==0);
    strcpy(s, "");
    assert(validate_description(s)==0);
}

void validate_type_tester(){
    char s[15]="0";
    assert(validate_type(s));
    s[0]='1';
    assert(validate_type(s));
    strcpy(s, "01");
    assert(validate_type(s)==0);
    strcpy(s, "income");
    assert(validate_type(s)==0);
}

void global_tester(){
    check_date_in_interval_tester();
    calculate_account_balance_tester();
    validate_date_format_tester();
    validate_date_tester();
    calculate_income_expenses_tester();
    validate_amount_tester();
    validate_description_tester();
    validate_type_tester();
}

/// --------------------------------------------------------------------

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
            printf("Invalid option!\n");
        }
    }
    return 0;
}
