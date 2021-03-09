---------------------------------
-- fichier IP_PWM
------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity IP_PWM is
  port( clk, reset_n, CS_n : in std_logic;
    read_n,write_n : in std_logic;
	 address : in std_logic_vector(1 downto 0);
	 writedata : in std_logic_vector(31 downto 0);
	 readdata : out std_logic_vector(31 downto 0);
    pwm : out std_logic);
end IP_PWM;


architecture beh of IP_PWM is


component bloc_pwm is
  port( clk, rst, ena : in std_logic;
    reg_p, reg_th : in std_logic_vector(31 downto 0);
    pwm : out std_logic);
end component;

signal ena_wr_P, ena_wr_TH, ena_wr_control, ena_read : std_logic;
signal s_reg_P, s_reg_TH, s_reg_control : std_logic_vector(31 downto 0);

begin
------------------------------------------------------------------------------------------------------------------------------
--Circuits combinatoires de décodage des adresses lors d'une demande d'écriture du NIOSII

-- reg_P registre d'offset 0 dans le périphérique IP_pwm => le registre est à l'adresse 0 dans le périhérique
ena_wr_P <= '1' when ((CS_n='0') and (write_n='0') and (address="00")) else '0';

-- reg_TH registre d'offset 1 dans le périphérique IP_pwm => le registre est à l'adresse 1 dans le périhérique 
ena_wr_TH <= '1' when ((CS_n='0') and (write_n='0') and (address="01")) else '0';

-- reg_control registre d'offset 2 dans le périphérique IP_pwm => le registre est à l'adresse 2 dans le périhérique 
ena_wr_control <= '1' when ((CS_n='0') and (write_n='0') and (address="10")) else '0';

-----------------------------------------------------------------------------------------------------------------------------
--Circuits séquentiels de mémorisation des écritures faites par le Nios dans les registres de l'IP_pwm

PP: process(clk,reset_n)
begin
if (reset_n='0') then s_reg_P <= (others=>'0');
elsif rising_edge(clk) then
	if (ena_wr_P='1') then s_reg_P <= writedata;
	end if;
end if;
end process PP;



PTH: process(clk,reset_n)
begin
if (reset_n='0') then s_reg_TH <= (others=>'0');
elsif rising_edge(clk) then
	if (ena_wr_TH='1') then s_reg_TH <= writedata;
	end if;
end if;
end process PTH;


PC: process(clk,reset_n)
begin
if (reset_n='0') then s_reg_control <= (others=>'0');
elsif rising_edge(clk) then
	if (ena_wr_control='1') then s_reg_control <= writedata;
	end if;
end if;
end process PC;



---------------------------------------------------------------------------------
-- cablage du composant bloc_pwm dans l'IP_pwm

BPWM : bloc_pwm 
	port map(clk => clk,
			rst=> reset_n,
			ena=> s_reg_control(0),
			reg_TH => s_reg_TH,
			reg_P => s_reg_P,
			pwm=> pwm);
		
---------------------------------------------------------------------------------------------------------------------		
--Circuit combinatoire de décodage d'adresses lors d'une demande de lecture du NIOSII
		
ena_read <= '1' when ((CS_n='0')	and (read_n='0')) else '0';

-- mise à jour de la sortie readdata en fonction de la demande de lecture
with ena_read&address select
readdata <= s_reg_P when "100",
				s_reg_TH when "101",
				s_reg_control when others;
				
				
end beh;
