library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity multiplier is
port(
  clk : in std_logic;
  a, b : in std_logic_vector(15 downto 0);
  p : out std_logic_vector(31 downto 0));
end multiplieur;

architecture beh of multiplier is
begin

PP: process(clk)
begin
if clk'event and clk = '1' then
  p <= a * b;
end if;
end process PP;

end multiplier;