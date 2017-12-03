DELIMITER |

CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`Calculate_price`
BEFORE INSERT ON `Placanje` FOR EACH ROW
BEGIN
	SET new.suma = (select datediff(r.datumZavrsetka, r.datumPocetka)
    from Rezervacija r
    where r.id = NEW.idRezervacije) * 
    (select distinct cenaNocenja
    from TipSobe t join Soba s on t.id = s.idTipaSobe);
    IF (select count(*) 
		from Rezervacija r join Klijent k on r.idKlijenta = k.id
		where r.id = NEW.idRezervacije) = 1 THEN
        
        SET new.suma = new.suma *0.9;
	END IF;
END|