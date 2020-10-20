----------------------------------------------------------------------------------------------------------
-- projet                   : Projet
----------------------------------------------------------------------------------------------------------
-- Fichier                  : trait_AC.vhd
-- Auteur                   : A.LLORENTE
-- Derniere mise a jour     : 21/03/18
----------------------------------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


------------- VUE EXTERNE DU CIRCUIT -------------
entity trait_AC is
  port(
    rst,clk,echAC_pret, modop: in std_logic;
    echAC: in std_logic_vector(11 downto 0);
    debord_cpt: out std_logic;
    cptperiode_moy: out std_logic_vector(9 downto 0));
end;
-------------- ARCHITECTURE ---------------------
architecture beh of trait_AC is
  type etat is (erreur,att_depseuilH, att_depseuilB, att_periode_seuilH, att_periode_seuilB, mem_etat_CPT, etat_CPT); ----- Déclaration des etats de la FSM
  signal EP : etat;
  signal s_echAC : integer range 0 to 4095; ---- SIGNAL IMAGE DE LA VALEUR DE L'ECHANTILLON
  signal s_cpt : natural range 0 to 1023;---- SIGNAL IMAGE DU COMPTEUR
  constant seuilH : integer := 2148; ---- CONSTANTE DE DEPASSEMENT
  constant seuilB : integer := 1948;---- CONSTANTE DE DEPASSEMENT
  signal ena_mem_reg : std_logic;---- SIGNAL ACTIVATION DES BASCULES D (AVEC ENABLE)
  signal ena_mem_moy : std_logic;---- SIGNAL ACTIVATION DES BASCULES D (AVEC ENABLE)
  signal s_debord_cpt: std_logic;---- SIGNAL DE DEBORDEMENT
  ------------- DECLARATION DES REGISTRES A MEMOIRES
  signal cpt_MEM1 : natural range 0 to 1023;
  signal cpt_MEM2 : natural range 0 to 1023;
  signal cpt_MEM3 : natural range 0 to 1023;
  signal cpt_MEM4 : natural range 0 to 1023;
  signal cpt_MEM5 : natural range 0 to 1023;
  signal cpt_MEM6 : natural range 0 to 1023;
  signal cpt_MEM7 : natural range 0 to 1023;
  signal cpt_MEM8 : natural range 0 to 1023;
  -------- SIGNAUX POUR CALCULER LA SOMME PUIS LA MOYENNE
  signal s_somme : natural range 0 to 8191;
  signal s_somme_bin : std_logic_vector(12 downto 0);
  signal s_cpt_periodmoy : std_logic_vector(9 downto  0);
  begin
    --------- PARTIE COMBINATOIRE
    s_echAC <= to_integer(unsigned(echAC)) ; -- Convertion du signal binaire en un nombre
    s_somme <= (cpt_MEM8)+(cpt_MEM7)+(cpt_MEM6)+(cpt_MEM5)+(cpt_MEM4)+(cpt_MEM3)+(cpt_MEM2)+(cpt_MEM1); --- SOMME DES REGISTRES
    s_somme_bin <= std_logic_vector(to_unsigned(s_somme,13)); ---- CONVERTION DE LA VALEUR DE LA SOMME EN BINAIRE 13 BITS
    s_cpt_periodmoy <=  s_somme_bin(12 downto 3); --REGISTRE A DECALLAGE A GAUCHE SUR 3 BITS VALEUR DE SORTIE SUR 10 BITS
    debord_cpt <= s_debord_cpt;
    -------- PROCESS SEQUENTIEL
PSEQ: process(clk,rst) 
    begin
      ------------- INITIALISATION ---------------
      if rst = '0' then 
              EP<= att_depseuilH;
              cpt_MEM8<= 430;
              cpt_MEM7<= 430;
              cpt_MEM6<= 430;  
              cpt_MEM5<= 430;
              cpt_MEM4<= 430;
              cpt_MEM3<= 430;
              cpt_MEM2<= 430;
              cpt_MEM1 <= 430;
              cptperiode_moy <= "0110101110";
              s_debord_cpt <= '0';
    ----------- SUR FRONT D'HORLOGE -------------------
      elsif rising_edge(clk) then --Sinon sur le front d'horloge on change d'état
        
            if ena_mem_reg ='1' then ----------- SI BASCULE ENA ACTIVE ON FAIT PASSER LES VALEURS D'UNE BASCULE A UNE AUTRE
                cpt_MEM8<= cpt_MEM7;
                cpt_MEM7<= cpt_MEM6;
                cpt_MEM6<= cpt_MEM5;  
                cpt_MEM5<= cpt_MEM4;
                cpt_MEM4<= cpt_MEM3;
                cpt_MEM3<= cpt_MEM2;
                cpt_MEM2<= cpt_MEM1;
                cpt_MEM1 <= s_cpt;
            end if;
            
            if ena_mem_moy='1' then ----------- SI BASCULE ENA ACTIVE ON CALCULE LA MOYENNE
                cptperiode_moy <= s_cpt_periodmoy;
            end if;
            
            case EP is ----------- FSM ---------------
              when erreur =>
                s_debord_cpt <= '1';
                EP <= att_depseuilH;
              
              when att_depseuilH =>
                s_debord_cpt <= '1';
                if s_echAC > seuilH then 
                    EP <= att_depseuilB;
                else EP <= att_depseuilH;
                end if;
              
              when att_depseuilB =>
                s_debord_cpt <= '1';
                s_cpt <= 0;
                if s_echAC < seuilB then
                  EP <= att_periode_seuilH;
                else EP <= att_depseuilB;
                end if;
              
              when att_periode_seuilH =>
                s_debord_cpt <= '0';
                if echAC_pret = '1' then-- Incrémentation du compteur
                    s_cpt <= s_cpt +1 ;
                end if;
                if s_cpt>1000 then
                  EP <= erreur;
                elsif s_echAC > seuilH then
                 EP <= att_periode_seuilB;
                else EP <= att_periode_seuilH;
                end if;
              
              when att_periode_seuilB =>
                s_debord_cpt <= '0';
                if echAC_pret = '1' then-- Incrémentation du compteur
                    s_cpt <= s_cpt +1 ;
                end if;
                if s_cpt>1000 then
                  EP <= erreur;
                elsif s_echAC < seuilB then
                  EP <= mem_etat_CPT;
                else EP <= att_periode_seuilB;
                end if;
                
              when mem_etat_CPT =>
                s_debord_cpt <= '0';
                EP <= etat_CPT;
                
              when etat_CPT =>
                s_debord_cpt <= '0';
                s_cpt <= 0;
                EP <= att_periode_seuilH;
                
              when others => 
                EP <= att_depseuilH;
                
                
          end case;
        end if;
        
end process PSEQ;

PCOMB : process (EP) --------- PROCESS COMBINATOIRE AVEC CHANGEMENT ETAT ENA
    begin
  
case EP is
    when erreur =>
     ena_mem_reg <= '0';
     ena_mem_moy <= '0';
      
   when att_depseuilH =>
     ena_mem_reg <= '0';
     ena_mem_moy <= '0';

   when att_depseuilB =>
     ena_mem_reg <= '0';
     ena_mem_moy <= '0';

  when att_periode_seuilH =>
    ena_mem_reg <= '0';
     ena_mem_moy <= '0';
     

  when att_periode_seuilB =>
     ena_mem_reg <= '0';
     ena_mem_moy <= '0';
     
  when mem_etat_CPT =>
    ena_mem_reg <= '1';
    ena_mem_moy <= '0';
    
  when etat_CPT =>
    ena_mem_reg <= '0';
    ena_mem_moy <= '1';
   	      
  when others =>
     ena_mem_reg <= '0';
     ena_mem_moy <= '0';

  end case;
  end process PCOMB;
end beh;