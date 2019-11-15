with Ada.Text_IO; use Ada.Text_IO;
with Data; use Data;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

procedure Main is
   N : Integer := 10;
   C : Integer_Vector(1 .. N);
   A : Integer_Vector(1 .. N);
   B : Integer_Vector(1 .. N);
   MA : Integer_Matrix(1..N, 1..N);
   ME : Integer_Matrix(1..N, 1..N);

begin
   Put_Line("Laba_1 paralel:");
   for i in 1..N loop
      for j in 1..N loop
         MA(i, j) := 1;
         ME(i, j) := 1;
      end loop;
      A(i) := 1;
      B(i) := 1;
   end loop;
   C := F1(A, B, MA, ME);
   Print_Vector(C);
end Main;
