with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

package Data is
   type Integer_Vector is array (Positive range <>) of Integer;
   type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

   await: Suspension_Object;
   function F1 (A,B : Integer_Vector; MA,ME : Integer_Matrix) return Integer_Vector;
   function F2 (MF,MK,ML : Integer_Matrix) return Integer_Matrix;
   function F3 (MP,MR : Integer_Matrix; S : Integer_Vector) return Integer_Vector;
   procedure InitializeSemaphore;
   procedure Print_Matrix(MR: Integer_Matrix);
   procedure Print_Vector(M: Integer_Vector);
end Data;
