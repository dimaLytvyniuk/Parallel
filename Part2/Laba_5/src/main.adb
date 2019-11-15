with Ada.Text_IO; use Ada.Text_IO;
with Data; use Data;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

procedure Main is
   N : Integer := 10;
   MO: Integer_Matrix(1..N, 1..N);
   MP: Integer_Matrix(1..N, 1..N);
   R: Integer_Vector(1 .. N);
   S: Integer_Vector(1..N);

begin
   for i in 1..N loop
      for j in 1..N loop
         MO(i, j) := 1;
         MP(i, j) := 1;
      end loop;
      R(i) := 1;
      S(i) := 1;
   end loop;
   F1(R, S, MO, MP);
   Print_Vector(S);
end Main;
