#include <stdio.h>
#include "registration.h"
#include "reservation.h"
MYSQL* connection;
static void error_fatal(char *format, ...){
    va_list arguments;
    
    va_start(arguments, format);
    vfprintf(stderr, format, arguments);
    va_end(arguments);

}

int main(){
    
    connection = mysql_init(NULL);
    if(mysql_real_connect(connection, "localhost", "root", "root", "mydb", 0, NULL, 0) == NULL)
        error_fatal("Connection error: %s\n", mysql_error(connection));
    
    printf("Welcome!\n");
    while(1){
        int menu_option = -1;
        printf("Menu:\n");
        printf("1) Make reservation\n");
        printf("2) Select existing reservation\n");
        printf("3) Register agent\n");
        printf("4) Assign staff a room\n");
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
                break;
            case 4:
                assign_room(connection);
                break;
        }
    }
    
    mysql_close(connection);
}