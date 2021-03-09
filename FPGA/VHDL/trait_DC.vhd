----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : trait_DC.vhd
-- Auteur                   : W. Beauperin
-- Derniere mise a jour     : 21/03/18
----------------------------------------------------------------------------------------------------------


---- CODE ----

library ieee;
use ieee.std_logic_1164.all;
use ieee.NUMERIC_STD.all;
use IEEE.STD_LOGIC_UNSIGNED.all;

-- Vue externe du circuit

entity trait_DC is
  port (
	 clk,rst,echDC_pret  : in  std_logic;
	 echDC               : in std_logic_vector(11 downto 0);
	 DC_moy              : out std_logic_vector(11 downto 0));
end trait_DC;

-- Fonctionnement du circuit

architecture beh of trait_DC is

  -- Declaration des signaux
  
	signal s_ech1    : std_logic_vector(11 downto 0);
	signal s_ech2    : std_logic_vector(11 downto 0);
	signal s_ech3    : std_logic_vector(11 downto 0);
	signal s_ech4    : std_logic_vector(11 downto 0);
	signal s_ech5    : std_logic_vector(11 downto 0);
	signal s_ech6    : std_logic_vector(11 downto 0);
	signal s_ech7    : std_logic_vector(11 downto 0);
	signal s_ech8    : std_logic_vector(11 downto 0);
	signal s_ech_add : std_logic_vector(14 downto 0);
	begin

-- Sous-bloc 1 : Registre à decalage

		P1 : process(clk, rst)
		begin
			if rst = '0' then -- si rst = 0 tout est à 0 
				s_ech1 <= "000000000000";
				s_ech2 <= "000000000000";
				s_ech3 <= "000000000000";
				s_ech4 <= "000000000000";
				s_ech5 <= "000000000000";
				s_ech6 <= "000000000000";
				s_ech7 <= "000000000000";
				s_ech8 <= "000000000000";
				
			elsif rising_edge(clk) then -- sinon on regarde les fronts montants
				if(echDC_pret = '1') then -- si le signal est prêt on l ajoute
				  s_ech8 <= s_ech7;
					s_ech7 <= s_ech6;
					s_ech6 <= s_ech5;
					s_ech5 <= s_ech4;
					s_ech4 <= s_ech3;
					s_ech3 <= s_ech2;
					s_ech2 <= s_ech1;
					s_ech1 <= echDC;
					                        -- sinon rien ne se passe
				end if;
			end if;
		end process P1;
		
	-- Sous-bloc 2 : Additionneur
	
		s_ech_add <= ("000" & s_ech1) + ("000" & s_ech2) + ("000" & s_ech3) + ("000" & s_ech4) + ("000" & s_ech5) + ("000" & s_ech6) + ("000" & s_ech7) + ("000" & s_ech8);
		
	-- Sous-bloc 3 : Registre
	
		P2 : process(clk,rst)
		begin
			if rst = '0' then -- si rst = 0 tout est à 0
				DC_moy <= "000000000000";	
			elsif rising_edge(clk) then -- sinon on regarde les fronts montants
				DC_moy <= s_ech_add (14 downto 3); -- on divise par 8
			end if;
		end process P2;
end beh;