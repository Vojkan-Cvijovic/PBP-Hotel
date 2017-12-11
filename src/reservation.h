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
void select_reservation(long long jmbg);
void make_reservation(int option);

#endif