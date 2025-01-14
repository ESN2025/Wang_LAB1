library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity lab1_top is
    port (
        clk_50M  : in  std_logic;
        reset_n  : in  std_logic;
        button_in: in  std_logic;
        switch_in: in  std_logic_vector(3 downto 0);  
        led_out  : out std_logic_vector(7 downto 0)
    );
end entity lab1_top;

architecture rtl of lab1_top is

    component lab1 is
        port (
            clk_clk                               : in  std_logic                    := 'X';
            reset_reset_n                         : in  std_logic                    := 'X';
            pio_button_external_connection_export : in  std_logic                    := 'X';
            pio_leds_external_connection_export   : out std_logic_vector(7 downto 0);
            switch_external_connection_export     : in  std_logic_vector(3 downto 0) := (others => 'X')
        );
    end component;

begin

    u0 : component lab1
        port map (
            clk_clk                               => clk_50M,
            reset_reset_n                         => reset_n,
            pio_button_external_connection_export => button_in,
            pio_leds_external_connection_export   => led_out,
            switch_external_connection_export     => switch_in
        );

end architecture rtl;
