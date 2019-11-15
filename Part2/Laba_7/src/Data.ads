with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

package Data is
   type Integer_Vector is array (Positive range <>) of Integer;
   type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

   procedure F1(N: Integer);
end Data;
