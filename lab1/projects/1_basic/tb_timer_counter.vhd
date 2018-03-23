--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:05:49 03/06/2018
-- Design Name:   
-- Module Name:   D:/RA60-2015/lab1/projects/1_basic/tb_timer_counter.vhd
-- Project Name:  lab1_basic
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: timer_counter
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY tb_timer_counter IS
END tb_timer_counter;
 
ARCHITECTURE behavior OF tb_timer_counter IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT timer_counter
    PORT(
         clk_i : IN  std_logic;
         rst_i : IN  std_logic;
         one_sec_i : IN  std_logic;
         cnt_en_i : IN  std_logic;
         cnt_rst_i : IN  std_logic;
         led_o : OUT  std_logic_vector(7 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal clk_i : std_logic := '0';
   signal rst_i : std_logic := '0';
   signal one_sec_i : std_logic := '0';
   signal cnt_en_i : std_logic := '0';
   signal cnt_rst_i : std_logic := '0';

 	--Outputs
   signal led_o : std_logic_vector(7 downto 0);

   -- Clock period definitions
   constant clk_i_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: timer_counter PORT MAP (
          clk_i => clk_i,
          rst_i => rst_i,
          one_sec_i => one_sec_i,
          cnt_en_i => cnt_en_i,
          cnt_rst_i => cnt_rst_i,
          led_o => led_o
        );

   -- Clock process definitions
   clk_i_process :process
   begin
		clk_i <= '0';
		wait for clk_i_period/2;
		clk_i <= '1';
		wait for clk_i_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
		rst_i <= '0';
      wait for 100 ns;
		
		rst_i <= '1';
		wait for clk_i_period;
		
		cnt_rst_i <= '0';
		wait for clk_i_period;
		
		cnt_en_i <= '1';
		wait for clk_i_period;
		
		one_sec_i <= '1';
		

      -- insert stimulus here 

      wait;
   end process;

END;
