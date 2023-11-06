#include <stdio.h>
#include "time.h"


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
    printf("Your current account balance is: %g", balance);
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

int main(){
    char menu_choice[1];
    struct transaction v[50];
    int records=0;
    write_menu();
    while(menu_choice[0]!='0'){
        scanf("%1s", menu_choice);
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
            //financial report
        }
        else{
            printf("Invalid option.");
        }
    }
    return 0;
}
