USE `mydb`;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Assign_Room_To_Staff`
BEFORE INSERT ON `DodeljenaSoba` FOR EACH ROW
BEGIN
	SET NEW.idSobe = ( 	select s.id 
						from Soba s
                        where not exists(select * from DodeljenaSoba ds where ds.idSobe = s.id)
                        and not exists(select * from Rezervacija r join RezervisanaSoba rs on r.id = rs.idRezervacije
							where rs.idSobe = s.id and r.datumZavrsetka >= curdate()
                                        )
						and s.idTipaSobe = 1
						limit 1
					); 
END|
DELIMITER ;

