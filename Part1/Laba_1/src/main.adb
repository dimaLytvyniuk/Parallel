with Ada.Text_IO; use Ada.Text_IO;
with Data; use Data;
with Ada.Integer_Text_IO;           use Ada.Integer_Text_IO;

procedure Main is
   task T1 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task1");
      pragma Priority(0);
      pragma CPU(0);
   end T1;

   task body T1 is
      N : Integer := 50;
      B : Integer_Vector(1 .. N);
      C : Integer_Vector(1 .. N);
      MA : Integer_Matrix(1..N, 1..N);
      ME : Integer_Matrix(1..N, 1..N);
      MD : Integer_Matrix(1..N, 1..N);
   begin
      for i in 1..N loop
         for j in 1..N loop
            MA(i, j) := 1;
            ME(i, j) := 1;
         end loop;
         B(i) := 1;
         C(i) := 1;
      end loop;

      Put_Line("Task1 started");
      -- MD = (B*C)*(MA*ME);
      MD := F1(B, C, MA, ME);
      printer.Seize;
      printer.Print_Matrix(MD);
      printer.Release;
      Put_Line("Task1 finished");
   end T1;

   task T2 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task2");
      pragma Priority(4);
      pragma CPU(0);
   end T2;
   task body T2 is
      N : Integer := 70;
      MH : Integer_Matrix(1..N, 1..N);
      MK : Integer_Matrix(1..N, 1..N);
      MF : Integer_Matrix(1..N, 1..N);
      MG : Integer_Matrix(1..N, 1..N);
   begin
      Put_Line("Task2 started");

      for i in 1..N loop
         for j in 1..N loop
            MK(i, j) := 1;
            MF(i, j) := 1;
            MH(i, j) := 1;
         end loop;
      end loop;

      -- MG = TRANS(MK) *(MH*MF);
      MG := F2(MK, MH, MF);

      delay 0.1;
      printer.Seize;
      printer.Print_Matrix(MG);
      printer.Release;
      Put_Line("Task2 finished");
   end T2;

   task T3 is
      pragma Storage_Size (10_000_000);
      pragma Task_Name ("Task3");
      pragma Priority(1);
      pragma CPU(0);
   end T3;
   task body T3 is
      N : Integer := 100;
      T : Integer_Vector(1 .. N);
      O : Integer_Vector(1 .. N);
      MP : Integer_Matrix(1..N, 1..N);
      MR : Integer_Matrix(1..N, 1..N);
   begin
      Put_Line("Task3 started");

      for i in 1..N loop
         for j in 1..N loop
            MP(i, j) := 1;
            MR(i, j) := 1;
         end loop;
         T(i) := 1;
      end loop;

      -- O = MAX(MP*MR) * T;
      O := F3(MP, MR, T);

      delay 0.2;
      printer.Seize;
      printer.Print_Vector(O);
      printer.Release;
      Put_Line("Task3 finished");
   end T3;


begin
   Put_Line("Laba_1 paralel:");
end Main;
