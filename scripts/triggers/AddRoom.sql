USE `mydb`;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`RezervisanaSoba_BEFORE_INSERT`
BEFORE INSERT ON `RezervisanaSoba` FOR EACH ROW
BEGIN
	SET NEW.idSobe = ( 	select s.id 
						from Soba s
                        where not exists(select * from DodeljenaSoba ds where ds.idSobe = s.id)
                        and not exists(select * from Rezervacija r join RezervisanaSoba rs on r.id = rs.idRezervacije
							where rs.idSobe = s.id and (r.datumPocetka between (select datumPocetka from Rezervacija where id = NEW.idRezervacije) and 
																				(select datumZavrsetka from Rezervacija where id = NEW.idRezervacije) 
													or r.datumZavrsetka between (select datumPocetka from Rezervacija where id = NEW.idRezervacije) and 
																				(select datumZavrsetka from Rezervacija where id = NEW.idRezervacije) 
													)
										)
                                        and s.idTipaSobe = (select idTipaSobe from Rezervacija where id = NEW.idRezervacije)
						limit 1
					); 
END|
DELIMITER ;

