#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "registration.h"

#define QUERY_SIZE 1256
#define BUFFER_SIZE 80

static void error_fatal(char *format, ...){
    va_list arguments;
    
    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);

    exit(EXIT_FAILURE);
}
void clrscr(){
    system("@cls||clear");
}

void list_clients(){

    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW *row;
    MYSQL_FIELD *field;

    char query[QUERY_SIZE];
    
    connection = mysql_init(NULL);

    if(mysql_real_connect(connection, "localhost", "root",
         "root", "mydb", 0, NULL, 0) == NULL)
         error_fatal("Connection error: %s\n", mysql_error(connection));

    sprintf(query, "SELECT o.jmbg, ime, prezime FROM Osoba o join Klijent k on k.jmbg = o.jmbg");

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);

    printf("%s\n", (mysql_fetch_field(result))[0].name);

    int num = mysql_num_fields (result);
    int i;
    while ((row = mysql_fetch_row (result)) != 0){
        for (i = 0; i < num; i++)
      printf ("%s\t", row[i]);
        printf ("\n");
      }

    mysql_free_result(result);
    mysql_close(connection);

}

long long add_person(int type){
    // type 1: creates client full infomation
    // type 2: creates client limited info
    // type 3: creates agent and company

    long long jmbg;
    int companyId;
    char first_name[FIRST_NAME_SIZE];
    char last_name[LAST_NAME_SIZE];
    char address[ADDRESS_SIZE];
    char city[CITY_NAME_SIZE];
    unsigned int zip_code;
    char country[COUNTRY_NAME_SIZE];
    char mobile[MOBILE_PHONE_SIZE];
    char email[EMAIL_SIZE];
    char gendure[GENURE_SIZE];
    char phone_number[PHONE_NUMBER_SIZE];
    char persional_number[PERSIONAL_NUMBER_SIZE];
    char passport_number[PASSPORT_NUMBER];
    char option;

    clrscr();
    printf("Page for adding new client\n");

    printf("Click y/Y to begin with registration, any other key for quit\n");
    scanf("%c", &option);
    while( option == '\n' || option == ' ')
        scanf("%c", &option);

    if(option == 'y' || option == 'Y'){

        printf("Enter new clients unique master citizen number\n");
        scanf("%lli", &jmbg);

        printf("Enter first name:\n");
        scanf("%s", first_name);
        printf("Enter last name:\n");
        scanf("%s", last_name);
        printf("Enter city:\n");
        scanf("%s", city);
        printf("Enter mobile number:\n");
        scanf("%s", mobile);

        printf("Select type:\n1. Client\n2. Agent\nInsert 1 or 2\n");
        int type;

        while(1){
            scanf("%d", &type);
            if(type == 1 || type == 2)
                break;
            if(type == -1)
                return;
        }
        
        if(type == 0){
            printf("Enter personal number:\n");
            scanf("%s", persional_number);
    
            printf("Enter passport number:\n");
            scanf("%s", passport_number);
        }else if(type == 2){
            list_company();
            printf("Choose id of company from above\n");
            scanf("%d", &companyId);
            if(companyId < 0){
                companyId = add_company();
            }
            
        }

        printf("\nYou have entered:\n");
        printf("Unique master citizen number: %lli\n", jmbg);
        printf("First name: %s\n", first_name);
        printf("Last name: %s\n", last_name);
        printf("City: %s\n", city);
        printf("Mobile: %s\n", mobile);
        if(type == 1){
            printf("Personal number: %s\n", persional_number);
            printf("Passport number: %s\n", passport_number);
        }else{
            printf("Company id: %d\n", companyId);
        }

        printf("Click y/Y for confirm, any other key for quit\n");
        scanf("%c", &option);
        while( option == '\n' || option == ' ')
            scanf("%c", &option);

        if(option == 'y' || option == 'Y'){
            printf("Add in db\n");

            MYSQL *connection;

            char query[QUERY_SIZE];
            
            connection = mysql_init(NULL);

            if(mysql_real_connect(connection, "localhost", "root",
                    "root", "mydb", 0, NULL, 0) == NULL)
                    error_fatal("Connection error: %s\n", mysql_error(connection));

            sprintf(query, "INSERT INTO Osoba values (\"%lli\", \"%s\", \"%s\", \"%s\", \"%s\");", jmbg, first_name, last_name, city, mobile);

            if(mysql_query(connection, query) != 0)
                error_fatal("Query error %s\n", mysql_error(connection));

            if(type == 0)
                sprintf(query, "INSERT INTO Klijent(jmbg ,brojLicneKarte, brojPasosa) values (\"%lli\", \"%s\", \"%s\");", jmbg, persional_number, passport_number);
            else if(type == 2)
                sprintf(query, "INSERT INTO Agent values (\"%lli\", \"%d\");", jmbg, companyId);
            else{
                sprintf(query, "INSERT INTO Klijent(jmbg) values (\"%lli\");", jmbg);
            }

            if(mysql_query(connection, query) != 0)
                error_fatal("Query error %s\n", mysql_error(connection));
            
            printf("Finish with entry\n");

            mysql_close (connection);
            return jmbg;
        }
    }  
    printf("exit\n");
    return -1;
    
}
void list_company(){
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW *row;
    MYSQL_FIELD *field;

    char query[QUERY_SIZE];
    
    connection = mysql_init(NULL);

    if(mysql_real_connect(connection, "localhost", "root",
         "root", "mydb", 0, NULL, 0) == NULL)
         error_fatal("Connection error: %s\n", mysql_error(connection));

    sprintf(query, "SELECT idFirme, naziv from Firma");

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);

    printf("%s\n", (mysql_fetch_field(result))[0].name);

    int num = mysql_num_fields (result);
    int i;
    while ((row = mysql_fetch_row (result)) != 0){
        for (i = 0; i < num; i++)
      printf ("%s\t", row[i]);
        printf ("\n");
      }

    mysql_free_result(result);
    mysql_close(connection);
}

int add_company(){
    char option;
    char name[COMPANY_NAME];
    int companyId = -1;

    clrscr();
    printf("Page for adding new company\n");

    printf("Click y/Y to begin with company registration, any other key for quit\n");
    scanf("%c", &option);
    while( option == '\n' || option == ' ')
        scanf("%c", &option);

    if(option == 'y' || option == 'Y'){
        printf("Enter name\n");
        scanf("%c", &option);

        fgets(name, sizeof name, stdin);
        name[strlen(name) - 1] = 0;

        printf("Company name is : %s\n", name);

        printf("Click y/Y for confirm, any other key for quit\n");
        scanf("%c", &option);
        while( option == '\n' || option == ' ')
            scanf("%c", &option);

        if(option == 'y' || option == 'Y'){
            printf("Add in db\n");

            MYSQL *connection;
            MYSQL_RES *result;
            MYSQL_ROW *row;

            char query[QUERY_SIZE];
            
            connection = mysql_init(NULL);

            if(mysql_real_connect(connection, "localhost", "root",
                    "root", "mydb", 0, NULL, 0) == NULL)
                    error_fatal("Connection error: %s\n", mysql_error(connection));

            sprintf(query, "INSERT INTO Firma(naziv) values (\"%s\");", name);

            if(mysql_query(connection, query) != 0)
                error_fatal("Query error %s\n", mysql_error(connection));
            
            if(mysql_query(connection, LAST_INSERTED_ID) !=0)
                error_fatal("Query error %s\n", mysql_error(connection));
            
            result = mysql_use_result(connection);
            
            row = mysql_fetch_row (result);
            companyId = row[0];

            printf("Finish with entry\n");
            mysql_free_result(result);

            mysql_close (connection);
            
        }

    }

    return companyId;
}




