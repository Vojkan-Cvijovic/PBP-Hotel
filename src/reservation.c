#include "reservation.h"
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


void list_reservation(MYSQL *connection, int id, long long jmbg){
    MYSQL_RES *result;
    MYSQL_ROW *row;
    MYSQL_FIELD *field;

    char query[QUERY_SIZE];
    

    if(id == -1)
        sprintf(query, "SELECT r.id, o.ime, o.prezime, s.status, o.brojMobilnogTelefona \"broj mob.\", datumPocetka, datumZavrsetka, t.tipSobe from Rezervacija r join Klijent k on r.idKlijenta = k.jmbg join Osoba o on o.jmbg = k.jmbg join StatusRezervacije s on r.idStatusaRezervacije = s.id join TipSobe t on r.id = t.id where o.jmbg = \"%lli\";", jmbg);
    else
        sprintf(query, "SELECT r.id, o.ime, o.prezime, s.status, o.brojMobilnogTelefona \"broj mob.\", datumPocetka, datumZavrsetka, t.tipSobe from Rezervacija r join Klijent k on r.idKlijenta = k.jmbg join Osoba o on o.jmbg = k.jmbg join StatusRezervacije s on r.idStatusaRezervacije = s.id join TipSobe t on r.id = t.id where r.id = \"%d\" and o.jmbg = \"%lli\";", id, jmbg);
    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);

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


}

void make_reservation(int option){
    // option 0 : at reception
    // option 1 : client makes reservation over phone
    // option 2 : agent makes reservation over phone for client
    system("@cls||clear");

    long long agent_id = -1;
    char start_date[DATE_SIZE];
    char end_date[DATE_SIZE];
    int rooms_count = 0;
    MYSQL *connection;

    if(option == 2){
        printf("Enter agents id:\n");
        scanf("%ul", &agent_id);
        if(agent_id == -1)
            return;
    }

    long long client_id = add_person(option == 2?option-1:option);

    system("cal 1");
    printf("Start date: \n");
    scanf("%s", start_date);
    printf("End date: \n");
    scanf("%s", end_date);

    printf("Choose room type: \n");

    connection = mysql_init(NULL);
    if(mysql_real_connect(connection, "localhost", "root", "root", "mydb", 0, NULL, 0) == NULL)
        error_fatal("Connection error: %s\n", mysql_error(connection));
    
    list_rooms(connection, "2017/12/1", "2017/12/16");

    printf("Enter room type id:\n");
    int room_type_id;
    scanf("%d", &room_type_id);

    int reservation_id = add_reservation(connection, client_id ,option , agent_id, start_date, end_date, room_type_id);

    if(option == 0)
         confirm_reservation(connection, 2);

    mysql_close (connection);
    return ;

}

void confirm_reservation(MYSQL* connection, int reservation_id){ 
    char query[QUERY_SIZE];

    sprintf(query, "UPDATE Rezervacija SET idStatusaRezervacije = (select id from StatusRezervacije where status = \"potvrdjeno\") WHERE id = \"%d\"", reservation_id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    sprintf(query, "INSERT INTO RezervisanaSoba (idRezervacije) VALUES (\"%d\");", reservation_id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));
    
    printf("Reservation has been confirmed\n");
}
int add_reservation(MYSQL* connection, long long client_id, int option, long long agent_id, char* start_date, char* end_date, int room_type_id){
    MYSQL_RES *result;
    MYSQL_ROW *row;
    MYSQL_FIELD *field;
    
    char query[QUERY_SIZE];

    if(option == 1 || option == 0){
        sprintf(query, "INSERT INTO Rezervacija(idKlijenta, idTipaSobe, datumPocetka, datumZavrsetka) values(\"%lli\", \"%d\", \"%s\", \"%s\");", client_id, room_type_id, start_date, end_date);
    }else{
        sprintf(query, "INSERT INTO Rezervacija(idKlijenta, idAgenta, idTipaSobe, datumPocetka, datumZavrsetka) values(\"%lli\", \"%lli\", \"%d\", \"%s\", \"%s\");", client_id, agent_id, room_type_id, start_date, end_date);
    }
    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    if(mysql_query(connection, LAST_INSERTED_ID) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);

    row = mysql_fetch_row (result);
    int reservation_id = row[0];

    mysql_free_result(result);

    return reservation_id;

}

void call_off_reservation(MYSQL* connection, int reservation_id){
    char query[QUERY_SIZE];
    
    sprintf(query, "UPDATE Rezervacija SET idStatusaRezervacije = (select id from StatusRezervacije where status = \"otkazano\") WHERE id = \"%d\"", reservation_id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    sprintf(query, "DELETE FROM RezervisanaSoba where idRezervacije=\"%d\";", reservation_id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));
    
    sprintf(query, "DELETE FROM Placanje where idRezervacije=\"%d\";", reservation_id);
    
    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));
    
    printf("Reservation with id %d is no longer active\n", reservation_id);
}
void list_payments(MYSQL* connection){
    char query[QUERY_SIZE];
    MYSQL_RES *result;
    MYSQL_ROW *row;
    MYSQL_FIELD *field;

    sprintf(query, "SELECT id, tipPlacanja FROM TipPlacanja");

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));
    
    result = mysql_use_result(connection);

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

}
void make_payment(MYSQL* connection, int reservation_id){

    int payment_id;
    printf("Select payment method\n");
    list_payments(connection);
    scanf("%d", &payment_id);

    char query[QUERY_SIZE];
    sprintf(query, "INSERT INTO Placanje(idRezervacije, idTipaPlacanja) VALUES(\"%d\",\"%d\");", reservation_id, payment_id);

    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));
    printf("Payment has been made!\n");
}

void select_reservation(long long jmbg){
    system("@cls||clear");
    MYSQL *connection;

    connection = mysql_init(NULL);
    
    if(mysql_real_connect(connection, "localhost", "root", "root", "mydb", 0, NULL, 0) == NULL)
            error_fatal("Connection error: %s\n", mysql_error(connection));

    int id =1;
    char option;

    while(1){
        system("@cls||clear");
        printf("Select id of reservation:\n");
        list_reservation(connection, id, jmbg);
        printf("Enter id\n");
        scanf("%d", &id);
        system("@cls||clear");
        printf("You have selected: \n");
        list_reservation(connection, id, jmbg);

        printf("Press y/Y to confirm selection\n");
        scanf("%c", &option);
        while( option == '\n' || option == ' ')
            scanf("%c", &option);

        if(option == 'y' || option == 'Y'){

            printf("Select one of the options:\n");
                printf("1) Confirm reservation\n");
                printf("2) Call off reservation\n");
                printf("3) Go to payments\n");
            int option = 0;
            scanf("%d", &option);
            printf("%d\n",option);
            if( option == 1)
                confirm_reservation(connection, id);
            else if(option == 2)
                call_off_reservation(connection, id);
            else{
                make_payment(connection, id);
            }
            break;
        }
    }
    
    mysql_close(connection);


}

void list_rooms(MYSQL *connection, char* start_date, char* end_date){
    MYSQL_RES *result;
    MYSQL_ROW *row;
    
    char query[2*QUERY_SIZE];
    
    sprintf(query, "select distinct t.id, t.tipSobe, t.cenaNocenja from TipSobe t join Soba s on t.id = s.idTipaSobe where not exists (select * from RezervisanaSoba rs join Rezervacija r on r.id = rs.idRezervacije where rs.idSobe = s.id and (r.datumPocetka between \'%s\' and \'%s\' or r.datumZavrsetka between \'%s\' and \'%s\')) and not exists ( select * from DodeljenaSoba ds where ds.idSobe = s.id);", start_date, end_date, start_date, end_date);


    if(mysql_query(connection, query) != 0)
        error_fatal("Query error %s\n", mysql_error(connection));

    result = mysql_use_result(connection);
    int num = mysql_num_fields (result);
    int j;

    for(j = 0; j< num; j++)
        printf("%8s\t", (mysql_fetch_field(result))[0].name);
    printf("\n");

    int i;
    while ((row = mysql_fetch_row (result)) != 0){
        for (i = 0; i < num; i++)
            printf ("%8s\t", row[i]);
        printf ("\n");
      }

    mysql_free_result(result);
}



