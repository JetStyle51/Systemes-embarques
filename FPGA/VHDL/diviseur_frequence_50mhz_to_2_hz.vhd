library ieee;
use ieee.std_logic_1164.all;

entity div_freq_2Hz is
  port(
    rst,clk: in std_logic;
    clk_s: out std_logic);
end;
architecture beh of div_freq_2Hz is
  signal s_cpt: natural range 0 to 12499999;
  signal s_clk: std_logic;
  begin
    DIV: process(clk,rst)
    begin
      if (rst='0') then 
        s_cpt <= 0;
        s_clk <= '0';
    elsif rising_edge(clk) then
      if s_cpt = 12499999 then s_cpt <= 0;
                            s_clk <= not s_clk;
      else s_cpt <= s_cpt+1;
  end if;
end if;
end process DIV;
clk_s<=s_clk;
end beh;

