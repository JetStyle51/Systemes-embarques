----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : acq_echantillons.vhd
-- Auteur                   : W. Beauperin
-- Derniere mise a jour     : 21/03/18
----------------------------------------------------------------------------------------------------------


---- CODE ----

library ieee;
use ieee.std_logic_1164.all;

-- Vue externe du circuit

entity acq_echantillons is
	port (clk,dout_adc,ena2ms,modop,rst: in std_logic;
			clk_adc,cs_adc,din_adc,echAC_pret,echDC_pret: out std_logic;
			echantillon: out std_logic_vector (11 downto 0));
end acq_echantillons;

-- Fonctionnement du circuit

architecture beh of acq_echantillons is
  signal s_regdec: std_logic_vector (11 downto 0);
	signal s_cpt: natural range 0 to 127;
	signal s_clkadc: std_logic;
	signal s_cs_adc: std_logic;
	signal s_din_adc: std_logic;
	signal s_echAC_pret: std_logic;
	signal s_echDC_pret: std_logic;
	signal s_echantillon: std_logic_vector (11 downto 0);
	
-- Creation de signaux pour les lire et ecrire

	begin
		P1 : process(clk,rst)
			
			begin
				if (rst = '0') then  -- si rst = 0 tout est  0
					s_cpt <= 0;					
					s_clkadc <= '0';
					s_cs_adc <= '1';
					s_din_adc <= '0';
					s_echAC_pret <= '0';
					s_echDC_pret <= '0';
					s_echantillon <= "000000000000";
				
				elsif rising_edge (clk) then -- sinon on regarde les fronts montants
										
				  if (modop = '0') then -- si modop = 0 tout est  0
				    s_cpt <= 0;					
					  s_clkadc <= '0';
					  s_cs_adc <= '1';
					  s_din_adc <= '0';
					  s_echAC_pret <= '0';
					  s_echDC_pret <= '0';
					  s_echantillon <= "000000000000";
				
				  elsif (ena2ms = '1') then -- sinon on remet tout à 0 pour lancer un cycle quand ena2ms = 1
					  s_cpt <= 0;
					 	s_clkadc <= '0';
			      s_cs_adc <= '1';
				    s_din_adc <= '0';
				    s_echAC_pret <= '0';
				    s_echDC_pret <= '0';
				    s_echantillon <= "000000000000";

				  else -- dans les autres cas on est dans le cycle
					  s_cpt <= s_cpt + 1;	    -- on rajoute 1 au compteur (etat)
				                            -- en fonction de l etat on adapte les signaux de sortie
				    if s_cpt = 0 then       -- etat 1
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 2 then       -- etat 2
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 3 then       -- etat 3
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 4 then       -- etat 4
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 5 then       -- etat 5
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 6 then       -- etat 6
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 7 then       -- etat 7
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 8 then       -- etat 8
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					  
					  elsif s_cpt = 9 then       -- etat 9
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 10 then       -- etat 10
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 11 then       -- etat 11
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 12 then       -- etat 12
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 13 then       -- etat 13
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 14 then       -- etat 14
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 15 then       -- etat 15
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(11) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 16 then       -- etat 16
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 17 then       -- etat 17
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(10) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 18 then       -- etat 18
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 19 then       -- etat 19
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(9) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 20 then       -- etat 20
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 21 then       -- etat 21
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(8) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 22 then       -- etat 22
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 23 then       -- etat 23
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(7) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 24 then       -- etat 24
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					  
					  elsif s_cpt = 25 then       -- etat 25
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(6) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 26 then       -- etat 26
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 27 then       -- etat 27
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(5) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 28 then       -- etat 28
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 29 then       -- etat 29
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(4) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 30 then       -- etat 30
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 31 then       -- etat 31
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(3) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 32 then       -- etat 32
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 33 then       -- etat 33
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(2) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 34 then       -- etat 34
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
					    
					  elsif s_cpt = 35 then       -- etat 35
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(1) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 36 then       -- etat 36
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 37 then       -- etat 37
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(0) <= dout_adc;
				      s_echantillon <= "000000000000";
				      
				    elsif s_cpt = 38 then       -- etat 38
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= s_regdec(11) & s_regdec(10) & s_regdec(9) & s_regdec(8) & s_regdec(7) & s_regdec(6) & s_regdec(5) & s_regdec(4) & s_regdec(3) & s_regdec(2) & s_regdec(1) & s_regdec(0);
					    
					  elsif s_cpt = 39 then       -- etat 39
				      s_clkadc <= '1';
					    s_cs_adc <= '1';
					    s_din_adc <= '0';
			        s_echAC_pret <= '1';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 40 then       -- etat 40
				      s_clkadc <= '0';
					    s_cs_adc <= '1';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					  
					  elsif s_cpt = 41 then       -- etat 41
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 42 then       -- etat 42
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 43 then       -- etat 43
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 44 then       -- etat 44
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 45 then       -- etat 45
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 46 then       -- etat 46
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 47 then       -- etat 47
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 48 then       -- etat 48
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 49 then       -- etat 49
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 50 then       -- etat 50
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '1';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 51 then       -- etat 51
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 52 then       -- etat 52
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 53 then       -- etat 53
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 54 then       -- etat 54
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 55 then       -- etat 55
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(11) <= dout_adc;
				      
				    elsif s_cpt = 56 then       -- etat 56
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					  
					  elsif s_cpt = 57 then       -- etat 57
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(10) <= dout_adc;
				      
				    elsif s_cpt = 58 then       -- etat 58
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
					  elsif s_cpt = 59 then       -- etat 59
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(9) <= dout_adc;
				      
				    elsif s_cpt = 60 then       -- etat 60
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 61 then       -- etat 61
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(8) <= dout_adc;
				      
				    elsif s_cpt = 62 then       -- etat 62
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 63 then       -- etat 63
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(7) <= dout_adc;
				      
				    elsif s_cpt = 64 then       -- etat 64
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      
				    elsif s_cpt = 65 then       -- etat 65
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(6) <= dout_adc;
				      
				    elsif s_cpt = 66 then       -- etat 66
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 67 then       -- etat 67
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(5) <= dout_adc;
				      
				    elsif s_cpt = 68 then       -- etat 68
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 69 then       -- etat 69
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(4) <= dout_adc;
				      
				    elsif s_cpt = 70 then       -- etat 70
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 71 then       -- etat 71
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(3) <= dout_adc;
				      
				    elsif s_cpt = 72 then       -- etat 72
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					  
					  elsif s_cpt = 73 then       -- etat 73
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(2) <= dout_adc;
				      
				    elsif s_cpt = 74 then       -- etat 74
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
					    
					  elsif s_cpt = 75 then       -- etat 75
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(1) <= dout_adc;
				      
				    elsif s_cpt = 76 then       -- etat 76
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      
				    elsif s_cpt = 77 then       -- etat 77
				      s_clkadc <= '1';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_regdec(0) <= dout_adc;
				      
				    elsif s_cpt = 78 then       -- etat 78
				      s_clkadc <= '0';
					    s_cs_adc <= '0';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_echantillon <= s_regdec(11) & s_regdec(10) & s_regdec(9) & s_regdec(8) & s_regdec(7) & s_regdec(6) & s_regdec(5) & s_regdec(4) & s_regdec(3) & s_regdec(2) & s_regdec(1) & s_regdec(0);
					    
					  elsif s_cpt = 79 then       -- etat 79
				      s_clkadc <= '0';
					    s_cs_adc <= '1';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '1';
				      
				    else                    -- etat de 80 jusqu au pulse
				      s_clkadc <= '0';
					    s_cs_adc <= '1';
					    s_din_adc <= '0';
			        s_echAC_pret <= '0';
				      s_echDC_pret <= '0';
				      s_cpt <= 100; -- on fixe le compteur pour eviter qu il s envole
					  
					  end if;
					end if;
				end if;
			  end process P1;
			  clk_adc <= s_clkadc; -- on annnonce avant la fin les valeurs des elements de sortie
			  cs_adc <= s_cs_adc;
			  din_adc <= s_din_adc;
			  echAC_pret <= s_echAC_pret;
			  echDC_pret <= s_echDC_pret;
			  echantillon <= s_echantillon;
				
end beh;