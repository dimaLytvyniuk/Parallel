with Ada.Text_IO; use Ada.Text_IO;
with Data; use Data;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

procedure Main is
   task T1 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task1");
      pragma Priority(4);
      pragma CPU(0);
   end T1;

   task body T1 is
      N : Integer := 10;
      C : Integer_Vector(1 .. N);
      A : Integer_Vector(1 .. N);
      B : Integer_Vector(1 .. N);
      MA : Integer_Matrix(1..N, 1..N);
      ME : Integer_Matrix(1..N, 1..N);
   begin
      Suspend_Until_True(await);
      Set_False(await);
      Put_Line("Task1 started");
      Set_True(await);
      for i in 1..N loop
         for j in 1..N loop
            MA(i, j) := 1;
            ME(i, j) := 1;
         end loop;
         A(i) := 1;
         B(i) := 1;
      end loop;

      -- C = SORT(A) *(MA*ME) + SORT(B)
      C := F1(A, B, MA, ME);

      Suspend_Until_True(await);
      Set_False(await);
      Put_Line("Task1 result:");
      Print_Vector(C);
      Put_Line("Task1 finished");
      Set_True(await);

   end T1;

   task T2 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task2");
      pragma Priority(7);
      pragma CPU(0);
   end T2;
   task body T2 is
      N : Integer := 10;
      MG : Integer_Matrix(1..N, 1..N);
      MF : Integer_Matrix(1..N, 1..N);
      MK : Integer_Matrix(1..N, 1..N);
      ML : Integer_Matrix(1..N, 1..N);
   begin
      Suspend_Until_True(await);
      Set_False(await);
      Put_Line("Task2 started");
      Set_True(await);
      for i in 1..N loop
         for j in 1..N loop
            MK(i, j) := 1;
            MF(i, j) := 1;
            ML(i, j) := 1;
         end loop;
      end loop;

      -- MG = SORT(MF) *MK + ML
      MG := F2(MF, MK, ML);

      Suspend_Until_True(await);
      Set_False(await);
      Put_Line("Task2 result:");
      Print_Matrix(MG);
      Put_Line("Task2 finished");
      Set_True(await);
   end T2;

   task T3 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task3");
      pragma Priority(5);
      pragma CPU(0);
   end T3;
   task body T3 is
      N : Integer := 10;
      O : Integer_Vector(1 .. N);
      S : Integer_Vector(1 .. N);
      MP : Integer_Matrix(1..N, 1..N);
      MR : Integer_Matrix(1..N, 1..N);
   begin
      Suspend_Until_True(await);
      Set_False(await);
      Put_Line("Task3 started");
      Set_True(await);

      for i in 1..N loop
         for j in 1..N loop
            MP(i, j) := 1;
            MR(i, j) := 1;
         end loop;
         S(i) := 1;
      end loop;

      -- O = (SORT(MP*MR)*S)
      O := F3(MP, MR, S);

      Suspend_Until_True(await);
      Set_False(await);
      Print_Vector(O);
      Put_Line("Task3 finished");
      Set_True(await);
   end T3;


begin
   Put_Line("Laba_1 paralel:");
   InitializeSemaphore;
end Main;
