USE `mydb`;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Default_Reservation_Status`
BEFORE INSERT ON `Rezervacija` FOR EACH ROW
BEGIN
	SET NEW.idStatusaRezervacije = ( select id
									from StatusRezervacije
                                    where status = "odobreno");
END|
DELIMITER ;

