USE `mydb`;

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Dusica", "Velickovic", "Kralja Milana 7", "Beograd", 11000, "Srbija", "0657733252", "zenski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Milica", "Lazic", "Beogradska 10", "Beograd", 11000, "Srbija", "0648825360", "zenski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Jovana", "Todorov", "Kosovska 19", "Beograd", 11000, "Srbija", "0644569743", "zenski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Dusan", "Petrovic", "Kneza Milosa 180", "Beograd", 11000, "Srbija", "0641689436", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Dejan", "Joksimovic", "Balkanska 50", "Beograd", 11000, "Srbija", "0658794399", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Stefan", "Petrovic", "Ljermontova 4", "Beograd", 11000, "Srbija", "0601238631", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Jelena", "Zivkovic", "Ilije Garasarnina 13", "Beograd", 11000, "Srbija", "0641239476", "zenski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Jelena", "Lazic", "Cvijiceva 76", "Beograd", 11000, "Srbija", "0601976484", "zenski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Marko", "Nikolic", "Takovska 19", "Beograd", 11000, "Srbija", "0671946898", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Momir", "Nikolic", "Topolska 18", "Beograd", 11000, "Srbija", "0658894699", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Mladen", "Sentic", "Ruzveltova 56", "Beograd", 11000, "Srbija", "0658899463", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Lazar", "Bogdanovic", "Dalmatinska 14", "Beograd", 11000, "Srbija", "0658479366", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Jovan", "Zoric", "Ustanicka 19", "Beograd", 11000, "Srbija", "0659134666", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Boban", "Petrovic", "Ustanicka 170", "Beograd", 11000, "Srbija", "0601359466", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol) 
values ("Stevan", "Cvetkovic", "Zdravka Celara 16", "Beograd", 11000, "Srbija", "0651113346", "muski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol)
values ("Jelena", "Biorcanin", "Ustanicka 16", "Novi Sad", 21000, "Srbija", "0657352654", "zenski");

insert into Osoblje (ime, prezime, adresa, grad, postanskiKod, drzava, brojTelefona, pol)
values ("Sanja", "Jokic", "Ustanicka 12", "Novi Sad", 21000, "Srbija", "0657352654", "zenski");

delete from Osoblje where ime = "Sanja" and prezime = "Jokic";

