with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

package Data is
   type Integer_Vector is array (Positive range <>) of Integer;
   type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

   awaitSortA: Suspension_Object;
   awaitSortB: Suspension_Object;
   awaitMAME: Suspension_Object;
   awaitSortAMAME: Suspension_Object;

   function F1 (A,B : Integer_Vector; MA,ME : Integer_Matrix) return Integer_Vector;
   procedure Print_Matrix(MR: Integer_Matrix);
   procedure Print_Vector(M: Integer_Vector);
end Data;
