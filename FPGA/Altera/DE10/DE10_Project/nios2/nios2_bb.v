
module nios2 (
	clk_clk,
	leds_external_connection_export,
	switches_external_connection_export,
	button_external_connection_export,
	hex_external_connection_export);	

	input		clk_clk;
	output	[9:0]	leds_external_connection_export;
	input	[9:0]	switches_external_connection_export;
	input	[3:0]	button_external_connection_export;
	output	[6:0]	hex_external_connection_export;
endmodule
