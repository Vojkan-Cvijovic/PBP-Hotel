#include <stdio.h>
#include "registration.h"
#include "reservation.h"

static void error_fatal(char *format, ...){
    va_list arguments;
    
    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);

    exit(EXIT_FAILURE);
}

int main(){
    MYSQL* connection;
    connection = mysql_init(NULL);
    if(mysql_real_connect(connection, "localhost", "root", "root", "mydb", 0, NULL, 0) == NULL)
        error_fatal("Connection error: %s\n", mysql_error(connection));
    
    int menu_option = -1;
    printf("Welcome!\n");
    while(1){
        printf("Menu:\n");
            printf("1) Make reservation\n");
            printf("2) Select existing reservation\n");
            printf("3) Register agent\n");
            scanf("%d", &menu_option);

            switch(menu_option){
                case 1:
                    make_new_reservation(connection);
                    break;
                case 2:
                    select_existing_reservation(connection);
                    break;
                case 3:
                    register_agent(connection);
            }
    }
    mysql_close(connection);
}