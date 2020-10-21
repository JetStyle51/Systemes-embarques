	component nios2 is
		port (
			clk_clk                             : in  std_logic                    := 'X';             -- clk
			leds_external_connection_export     : out std_logic_vector(9 downto 0);                    -- export
			switches_external_connection_export : in  std_logic_vector(9 downto 0) := (others => 'X'); -- export
			button_external_connection_export   : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			hex_external_connection_export      : out std_logic_vector(6 downto 0)                     -- export
		);
	end component nios2;

	u0 : component nios2
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			leds_external_connection_export     => CONNECTED_TO_leds_external_connection_export,     --     leds_external_connection.export
			switches_external_connection_export => CONNECTED_TO_switches_external_connection_export, -- switches_external_connection.export
			button_external_connection_export   => CONNECTED_TO_button_external_connection_export,   --   button_external_connection.export
			hex_external_connection_export      => CONNECTED_TO_hex_external_connection_export       --      hex_external_connection.export
		);

