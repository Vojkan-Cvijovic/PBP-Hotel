#!/bin/sh

USER="root"
PASS="-proot"
DATABASE_NAME="mydb"

echo "Welcome to onbording for hotel management system database\n"

# Create database structure
echo "Creating database $DATABASE_NAME"
mysql -u $USER $PASS < ./createDatabase.sql
echo "Database $DATABASE_NAME created\n"

#create triggers
echo "Creating triggers"
mysql -u $USER $PASS $DATABASE_NAME < ./triggers/MatchDefaultStatusWithReservation.sql
mysql -u $USER $PASS $DATABASE_NAME < ./triggers/CalculatePrice.sql
echo "Triggers are created\n"

#import data
echo "Importing data from data folder"
mysql -u $USER $PASS $DATABASE_NAME < ./data/tipSobe.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/soba.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/osoblje.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/dodeljenaSoba.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/odeljenje.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/pozicija.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/pripada.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/osoba.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/klijent.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/firma.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/agent.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/statusRezervacije.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/rezervacija.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/rezervisanaSoba.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/tipPlacanja.sql
mysql -u $USER $PASS $DATABASE_NAME < ./data/placanje.sql
echo "All data is imported\n"

echo "Success!"

