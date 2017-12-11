#ifndef __RESERVATION__ 
#define __RESERVATION__ 1
#include "registration.h"
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DATE_SIZE 20


void list_reservation(MYSQL *connection,int id, long long jmbg);
void select_reservation(MYSQL *connection, long long jmbg);
void make_reservation(MYSQL* connection, int option);
void make_new_reservation(MYSQL* connection);
void select_existing_reservation(MYSQL* connection);
int add_reservation(MYSQL* connection, long long client_id, int option, long long agent_id, char* start_date, char* end_date, int room_type_id);

#endif