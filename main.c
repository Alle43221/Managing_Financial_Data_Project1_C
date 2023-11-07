#include <stdio.h>
#include "time.h"
#include "regex.h"
#include "string.h"
#include <stdlib.h>

typedef struct transaction{
    float amount;
    struct tm date;
    char description[200];
    enum available_types{income, expense} type;
};

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
     */
    char c;
    if(v.type==0){
        c='+';
    }else c='-';
    printf("Date: %s", asctime(&v.date));
    printf("Amount: %c%g\n", c,v.amount);
    printf("Description: %s\n", v.description);
}

void print_transactions(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: prints in the console the history of transactions, found in the first argument
     * exception: empty array raises the "No available transaction" error message
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

void add(struct transaction v[], int *records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: appends a new transaction to the array passed as argument
     */
    struct transaction aux;
    printf("Type amount:\n");
    scanf("%f", &aux.amount);
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

void calculate_account_balance(struct transaction v[], int records){
    /**
     * param: array of transaction objects, integer
     * return: none
     * description: prints in the console the current account balance
     */
    float balance=0;
    for(int i=0; i<records; i++){
        if(v[i].type==0)
            balance+=v[i].amount;
        else balance-=v[i].amount;
    }
    printf("Your current account balance is: %g\n", balance);
}

/*
int validate_date(char s[]){
    int day=0, month=0, year=0;
    regex_t rx;
    int value;
    //value = re_compile_pattern(&rx, "([0-9]+(/[0-9]+)+)", 0);
    //value = re_compile_pattern (&rx, "Hello World", 0);
    //value = re_match(&rx, "Hello World again", 0, NULL, 0);
    if (value == 0)
    {
        printf("Pattern matched\n");
        return 1;
    }
    else if (value == REG_NOMATCH)
    {
        printf("Pattern not found\n");
        return 0;
    }
    else
    {
        printf("Some error occured\n");
        return 0;
    }
}
 */

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

    new_date->tm_year=year-1900;
    new_date->tm_mon=month-1;
    new_date->tm_mday=day;

    //check valid date manually

    new_date->tm_hour = 0;
    new_date->tm_min = 0;
    new_date->tm_sec = 1;
    new_date->tm_isdst = -1;

    int result = mktime(new_date);
    if( result == -1 ) {
        printf("Invalid date\n");
        return 0;
    } else {
        return 1;
    }
}

int check_date_in_interval(struct tm start_date, struct tm end_date, struct tm item){
    /**
     * param: tm datetime object, tm datetime object, tm datetime object
     * return: integer (0/1)
     * description: checks if argument item is between two given dates
     */
    struct tm new_date=item;
    new_date.tm_hour = 0;
    new_date.tm_min = 0;
    new_date.tm_sec = 1;
    new_date.tm_isdst = -1;
    int s_date=mktime(&start_date);
    int e_date=mktime(&end_date);
    int item_date=mktime(&new_date);
    long long int dif1=item_date-s_date;
    long long int dif2=e_date-item_date;
    if(dif1>=0 && dif2>=0)
        return 1;
    return 0;
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
    strftime(e,80,"%d/%m/%Y", &end_date);
    printf("Generating report for transactions between %s and %s:\n", s, e);

    float income=0, expenses=0;
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
/**
 *  // declaring a variable to create a regex
    regex_t rx;

    // to store the return value after regex creation
    int value;

    // calling regcompn() function to create regex
    value = regcomp(&rx, "[:word:]", 0);

    // checking if the compilation was successful
    if (value == 0)
    {
        printf("Process successful");
    }
    else
    {
        printf("Process failed");
    }
 * @return
 */

void save_transactions_to_file(struct transaction v[], int records){
    FILE *fp;
    fp = fopen("history.txt", "w");
    for(int i=0; i<records; i++) {
        fprintf(fp, "%g ", v[i].amount);
        fprintf(fp, "%s ", v[i].description);
        fprintf(fp, "%d ", v[i].type);
        char buffer[26];
        strftime(buffer, 26, "%d/%m/%Y/%H:%M:%S", &v[i].date);
        fprintf(fp, "%s", buffer);
    }
    fclose(fp);
    printf("Transactions saved to file");
}

void load_transactions_from_file(struct transaction v[], int *records){
    FILE *fp;
    fp = fopen("history.txt", "w");

    fclose(fp);
    printf("Transactions loaded from file");
}

int main(){
    char menu_choice[100];
    struct transaction v[50];
    int records=0;
    write_menu();
    while(menu_choice[0]!='0'){
        gets(menu_choice);
        if(menu_choice[0]=='1'){
            add(v, &records);
        }
        else if(menu_choice[0]=='2'){
            print_transactions(v, records);
        }
        else if(menu_choice[0]=='3'){
            calculate_account_balance(v, records);
        }
        else if(menu_choice[0]=='4'){
            generate_financial_report(v, records);
        }
        else if(menu_choice[0]=='5'){
            save_transactions_to_file(v, records);
        }
        else if(menu_choice[0]=='5'){
            load_transactions_from_file(v, &records);
        }
        else{
            printf("Invalid option.");
        }
    }
    return 0;
}
