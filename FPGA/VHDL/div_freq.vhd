----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : div_freq.vhd
-- Auteur                   : W. Beauperin
-- Derniere mise a jour     : 20/03/18
----------------------------------------------------------------------------------------------------------


---- CODE ----

library ieee;
use ieee.std_logic_1164.all;

-- Vue externe du circuit

entity div_freq is
	port (clk,rst: in std_logic;
			clk100k: out std_logic);
end div_freq;

-- Fonctionnement du circuit 

architecture beh of div_freq is
	signal s_cpt: natural range 0 to 249;
	signal s_clk100k: std_logic;
	
-- Creation de signaux pour les lire et ecrire

	begin
		P1 : process(clk,rst)
			
			begin
				if (rst = '0') then  -- si rst = 0 tout est  0
					s_cpt <= 0;					
					s_clk100k <= '0';
										
				elsif rising_edge (clk) then -- sinon on regarde les front montant
					if s_cpt = 249 then -- si on est au max on repart a 0 et on change de base
						s_cpt <= 0;
						s_clk100k <= not(s_clk100k);
					else s_cpt <= s_cpt+1; -- sinon on avance point par point
					end if;
				end if;
				end process P1;
				clk100k <= s_clk100k; -- on annnonce avant la fin qui est clk100k
end beh;