with Ada.Synchronous_Task_Control;
use Ada.Synchronous_Task_Control;

package Data is
   type Integer_Vector is array (Positive range <>) of Integer;
   type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

   protected monitor is
      entry Wait_Sort;
      entry Wait_Mult;
      entry Wait_MultVector;
      procedure Release_Sort;
      procedure Release_Mult;
      procedure Release_MultVector;
   private
      sorted: Boolean:= True;
      multed: Boolean:= True;
      multedVector: Boolean:= True;
   end monitor;

   procedure F1(R: Integer_Vector; S: out Integer_Vector; MO, MP: Integer_Matrix);
   procedure MultMatrix(MO, MP: Integer_Matrix; MOMP:out Integer_Matrix; n: Integer);
   procedure Sort(MOMP:out Integer_Matrix; n: Integer);
   function MultMatrixVector (MOMP: Integer_Matrix; R : Integer_Vector) return Integer_Vector;
   procedure MinusVectors(SMOMPR:Integer_Vector; S: out Integer_Vector);
   procedure Print_Matrix(MR: Integer_Matrix);
   procedure Print_Vector(M: Integer_Vector);
end Data;
