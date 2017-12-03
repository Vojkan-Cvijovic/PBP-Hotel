DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Rezervacija_BEFORE_INSERT`
BEFORE INSERT ON `Rezervacija` FOR EACH ROW
BEGIN
	SET NEW.idStatusaRezervacije = ( select id
									from StatusRezervacije
                                    where naziv = "odobreno");
END|


