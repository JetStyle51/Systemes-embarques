----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : pulse_2ms.vhd
-- Auteur                   : A.LLORENTE
-- Derniere mise a jour     : 21/03/18
----------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity pulse2ms is
  port(
    rst,clk: in std_logic;
    ena2ms: out std_logic);
end;
architecture beh of pulse2ms is
  signal s_cpt: natural range 0 to 200; -- Compteur 2 ms
  signal s_clk: std_logic;
  begin
    PULSE_2MS: process(clk,rst)
    begin
      if (rst='0') then 
        s_cpt <= 0;
        s_clk <= '0';
    elsif rising_edge(clk) then
      if s_cpt = 199 then    -- FRONT MONTANT HORLOGE DEBUT DU PULSE
                  s_clk <= not s_clk;
                  s_cpt <= s_cpt+1;
      elsif s_cpt = 200 then -- FRONT MONTANT HORLOGE FIN DU PULSE
                  s_clk <= not s_clk;
                  s_cpt <= 0;
      else s_cpt <= s_cpt+1;
  end if;
end if;
end process PULSE_2MS;
ena2ms<=s_clk;
end beh;

