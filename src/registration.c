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
void checkIfPersonExists(){
    printf("Enter persons id\n");
    long long personsId;
    scanf("%d\n", &personsId);
    if(!isAvaliablePersonsId(personsId))
        printf("Persons with id %lli does not exists\n", personsId);
}
int isAvaliablePersonsId(long long personsId){
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW *row;
    char query[QUERY_SIZE];

    connection = mysql_init(NULL);

    if(mysql_real_connect(connection, "localhost", "root", "root", "mydb", 0, NULL, 0) == NULL)
        error_fatal("Connection error: %s\n", mysql_error(connection));

    sprintf(query, "SELECT jmbg FROM Osoba WHERE jmbg = \"%lli\";", personsId);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));
    
    result = mysql_use_result(connection);

    row = mysql_fetch_row(result);

    if( row == NULL){
        mysql_free_result(result);
        return 1;
    }

    int num = mysql_num_fields (result);
    int j;
    for(j = 0; j< num; j++)
        printf("%10s\t", (mysql_fetch_field(result))[0].name);
    printf("\n");

    int i;
    while ((row = mysql_fetch_row (result)) != 0){
        for (i = 0; i < num; i++)
      printf ("%10s\t", row[i]);
        printf ("\n");
      }

    mysql_free_result(result);
    return 0;

}

long long add_person(MYSQL* connection, int type){
    // type 0: creates client full infomation
    // type 1: creates client limited info
    // type 2: creates agent and company

    long long jmbg;
    int companyId;
    char first_name[FIRST_NAME_SIZE];
    char last_name[LAST_NAME_SIZE];
    char city[CITY_NAME_SIZE];
    char country[COUNTRY_NAME_SIZE];
    char mobile[MOBILE_PHONE_SIZE];
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

        if(!isAvaliablePersonsId(jmbg)){
            printf("There is all ready one person with id %lli\n", jmbg);
            return jmbg;
        }

        printf("Enter first name:\n");
        scanf("%s", first_name);
        printf("Enter last name:\n");
        scanf("%s", last_name);
        printf("Enter city:\n");
        scanf("%s", city);
        printf("Enter mobile number:\n");
        scanf("%s", mobile);
        if(type == FULL_REGISTRATION_TYPE){
            printf("Enter personal number:\n");
            scanf("%s", persional_number);
    
            printf("Enter passport number:\n");
            scanf("%s", passport_number);
        }else if(type == AGENT_REGISTRATION_TYPE){
            list_company(connection);
            printf("Choose id of company from above\n");
            printf("Enter -1 for new company, %d for exit\n" , BACK_OPTION);
            scanf("%d", &companyId);
            if(companyId == BACK_OPTION)
                return;
            if(companyId == -1){
                companyId = add_company(connection);
            }
        }

        printf("\nYou have entered:\n");
        printf("Unique master citizen number: %lli\n", jmbg);
        printf("First name: %s\n", first_name);
        printf("Last name: %s\n", last_name);
        printf("City: %s\n", city);
        printf("Mobile: %s\n", mobile);
        if(type == FULL_REGISTRATION_TYPE){
            printf("Personal number: %s\n", persional_number);
            printf("Passport number: %s\n", passport_number);
        }else if(type == AGENT_REGISTRATION_TYPE){
            printf("Company id: %d\n", companyId);
        }

        printf("Click y/Y for confirm, any other key for quit\n");
        scanf("%c", &option);
        while( option == '\n' || option == ' ')
            scanf("%c", &option);

        if(option == 'y' || option == 'Y'){
            char query[QUERY_SIZE];
            
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
            return jmbg;
        }
    }  

    return -1;
    
}
void list_company(MYSQL* connection){
    MYSQL_RES *result;
    MYSQL_ROW *row;
    MYSQL_FIELD *field;

    char query[QUERY_SIZE];
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
}

int add_company(MYSQL* connection){
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
            MYSQL_RES *result;
            MYSQL_ROW *row;

            char query[QUERY_SIZE];
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
        }

    }

    return companyId;
}

void register_agent(MYSQL* connection){

    add_person(connection, AGENT_REGISTRATION_TYPE);

}
void assign_room_to(MYSQL* connection, int id){
    MYSQL_RES *result;
    MYSQL_ROW *row;

    char query[QUERY_SIZE];
    sprintf(query, "INSERT INTO DodeljenaSoba(idOsoblja) values (%d);", id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    sprintf(query, "SELECT idSobe FROM DodeljenaSoba WHERE idOsoblja = %d", id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);
    int roomId = -1;
    
    row = mysql_fetch_row (result);
    roomId = atoi(row[0]);
    mysql_free_result(result);
    printf("Room %d is assigned\n", roomId);
}
void list_all_staff(MYSQL* connection){
    MYSQL_RES *result;
    MYSQL_ROW *row;

    char query[QUERY_SIZE];
    sprintf(query, "select id, ime, prezime from Osoblje where id not in (select idOsoblja from DodeljenaSoba);");

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);

    int num = mysql_num_fields (result);
    int i;
    printf("All staff without assigned room\n");
    while ((row = mysql_fetch_row (result)) != 0){
        for (i = 0; i < num; i++)
      printf ("%s\t", row[i]);
        printf ("\n");
      } 

    mysql_free_result(result);
}

void assign_room(MYSQL* connection){
    list_all_staff(connection);
    printf("Select id:\n<0 to go back\n");
    int staffId;
    scanf("%d", &staffId);
    if(staffId < 0)
        return;
    assign_room_to(connection, staffId);
}


