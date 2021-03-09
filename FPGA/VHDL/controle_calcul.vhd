----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : controle_calcul.vhd
-- Auteur                   : A.LLORENTE
-- Derniere mise a jour     : 22/03/18
----------------------------------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity controle_calcul is
  port(
    clk,rst,dout_adc,bp_reg: in std_logic;
    sw: in std_logic_vector(1 downto 0);
    clk_adc,cs_adc,din_adc,led_al : out std_logic;
    affc,affd,affu: out std_logic_vector(6 downto 0));
end controle_calcul;

architecture beh of controle_calcul is

component div_freq is
	port (clk,rst: in std_logic;
			clk100k: out std_logic);
end component;

component pulse2ms is
  port(
    rst,clk: in std_logic;
    ena2ms: out std_logic);
end component;

component acq_echantillons is
	port (clk,dout_adc,ena2ms,modop,rst: in std_logic;
			clk_adc,cs_adc,din_adc,echAC_pret,echDC_pret: out std_logic;
			echantillon: out std_logic_vector (11 downto 0));
end component;

component trait_AC is
  port(
    rst,clk,echAC_pret, modop: in std_logic;
    echAC: in std_logic_vector(11 downto 0);
    debord_cpt: out std_logic;
    cptperiode_moy: out std_logic_vector(9 downto 0));
end component;

component rom1BPM IS
	PORT
	(
		address		: IN STD_LOGIC_VECTOR (9 DOWNTO 0);
		clock		: IN STD_LOGIC  := '1';
		q		: OUT STD_LOGIC_VECTOR (9 DOWNTO 0)
	);
END component;

component trait_DC is
  port (
	 clk,rst,echDC_pret  : in  std_logic;
	 echDC               : in std_logic_vector(11 downto 0);
	 DC_moy              : out std_logic_vector(11 downto 0));
end component;

component choix_aff is
  port(
    bp_reg: in std_logic;
    SW : in std_logic_vector(1 downto 0);
    SALB,SALH, BPM : in std_logic_vector(11 downto 0);
    moy_DC : in std_logic_vector(11 downto 0);
    aff : out std_logic_vector(11 downto 0));
end component;

component trans_hexa_7seg is
  port(
    code_e: in std_logic_vector(3 downto 0);
    code_s: out std_logic_vector(6 downto 0));
end component;

---------- DECLARATION DES SIGNAUX
signal s_clk100k,s_ena2ms,s_echAC_pret,s_echDC_pret,s_modop : std_logic;
signal s_echantillon,s_aff,s_DC_moy : std_logic_vector(11 downto 0);
signal s_cptperiode_moy,s_q,s_SALB,s_SALH : std_logic_vector(9 downto 0);
------------ DEBUT ---------------
begin
  ---- DECLARATION DES CONSTANTES POUR LE MOMENT A REGLER DANS LE SYSTEME 2
  s_modop <= '1';
  s_SALB <= "0000011110";
  s_SALH <= "0011111111";
  -- DIVISEUR DE FREQUENCE
  DIV : div_freq
  port map(
    clk => clk,
    rst => rst,
    clk100k =>  s_clk100k);
  -- PULSE
  PULSE : pulse2ms
    port map(
      rst => rst,
      clk => s_clk100k,
      ena2ms => s_ena2ms);
  -- ACQUISITION ECHANTILLON
  ECHANTILLONNAGE : acq_echantillons
  port map(
      rst => rst,
      clk => s_clk100k,
      ena2ms => s_ena2ms,
      modop => s_modop,
      dout_adc => dout_adc,
      clk_adc => clk_adc,
      cs_adc => cs_adc,
      din_adc => din_adc,
      echAC_pret => s_echAC_pret,
      echDC_pret => s_echDC_pret,
      echantillon => s_echantillon);
  
  -- TRAIT AC
  TRAITEMENT_AC : trait_AC
  port map(
    clk => s_clk100k,
    echAC_pret => s_echAC_pret,
    modop => s_modop,
    rst => rst,
    echAC => s_echantillon,
    debord_cpt => led_al,
    cptperiode_moy => s_cptperiode_moy);
    
  -- ROM
  ROM : rom1BPM
  port map(
    address => s_cptperiode_moy, clock => s_clk100k, q=> s_q);
    
  -- TRAIT DC
  TRAITEMENT_DC : trait_DC
  
  port map(
    clk => s_clk100k,
    rst => rst,
    echDC_pret => s_echDC_pret,
    echDC => s_echantillon,
    DC_moy => s_DC_moy);

-- choix affichages

  choix_affichage : choix_aff
  port map(
      bp_reg => bp_reg,
      SW => sw,
      SALB => s_SALB,
      SALH => s_SALH,
      BPM=> s_q,
      moy_DC => s_DC_moy,
      aff => s_aff);
      
-- TRANSCODEUR 1 centaines

  trans1 : trans_hexa_7seg
  port map(
      code_e => s_aff(11 downto 7),
      code_s => affc);
  
-- TRANSCODEUR 2 Dizaines

  trans2 : trans_hexa_7seg
  port map(
      code_e => s_aff(7 downto 3),
      code_s => affd);
      
-- TRANSCODEUR 3 unites

  trans3 : trans_hexa_7seg
  port map(
      code_e => s_aff(3 downto 0),
      code_s => affu);
  
end;
------------ FIN ---------------
