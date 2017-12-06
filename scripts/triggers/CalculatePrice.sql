USE `mydb`;

DELIMITER |

CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Calculate_price`
BEFORE INSERT ON `Placanje` FOR EACH ROW
BEGIN
	SET new.suma = (select datediff(r.datumZavrsetka, r.datumPocetka)
    from Rezervacija r
    where r.id = NEW.idRezervacije) *
    (select cenaNocenja
    from Rezervacija r join TipSobe ts on r.idTipaSobe = ts.id
    where r.id = NEW.idRezervacije);
    IF ((select count(*)
		from Rezervacija r
        where r.idKlijenta = (	select idKlijenta
								from Rezervacija r1
                                where r1.id = NEW.idRezervacije)) = 1) THEN
		SET NEW.suma = NEW.suma *0.9;
    END IF;
END|

DELIMITER ;