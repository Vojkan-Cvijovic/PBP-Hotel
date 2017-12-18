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

#define BACK_OPTION -2
#define ALL_OPTION -1
#define FULL_REGISTRATION_TYPE 0
#define PARTIAL_REGISTRATION_TYPE 1
#define AGENT_REGISTRATION_TYPE 2



#define LAST_INSERTED_ID "SELECT LAST_INSERT_ID();"

void list_clients();
void register_agent(MYSQL* connection);
long long add_person(MYSQL* connection, int type);
int add_company();
void make_reservation();
int isAvaliablePersonsId(long long id);
void checkIfPersonExists();
void assign_room(MYSQL* connection);

#endif
