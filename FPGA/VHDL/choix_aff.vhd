----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : choix_aff.vhd
-- Auteur                   : A.LLORENTE
-- Derniere mise a jour     : 21/03/18
----------------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity choix_aff is
  port(
    bp_reg: in std_logic;
    SW : in std_logic_vector(1 downto 0);
    SALB,SALH, BPM : in std_logic_vector(11 downto 0);
    moy_DC : in std_logic_vector(11 downto 0);
    aff : out std_logic_vector(11 downto 0));
end;
architecture beh of choix_aff is
  signal s_SEL: std_logic_vector(2 downto 0);
  begin
    s_SEL <= SW & bp_reg; -- Concaténation de SW avec bpReg (selecteur 3 bits)
    with s_SEL select -- Multiplexeur
    aff <=
    SALB when "000",
    SALB when "001",
    SALH when "010",
    SALH when "011",
    moy_DC when "100",
    BPM when "101",
    moy_DC when "110",
    BPM when "111",
    BPM when others;
end beh;


