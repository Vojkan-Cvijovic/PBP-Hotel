#ifndef __REGISTRATION__ 
#define __REGISTRATION__ 1
#include <mysql/mysql.h>
#define FIRST_NAME_SIZE 45
#define LAST_NAME_SIZE 45
#define ADDRESS_SIZE 75
#define CITY_NAME_SIZE 45
#define COUNTRY_NAME_SIZE 75
#define MOBILE_PHONE_SIZE 45
#define EMAIL_SIZE 45
#define GENURE_SIZE 10
#define PHONE_NUMBER_SIZE 45
#define PERSIONAL_NUMBER_SIZE 45
#define PASSPORT_NUMBER 45
#define COMPANY_NAME 45

void list_clients();
void add_person();
void add_company();
void make_reservation();

#endif