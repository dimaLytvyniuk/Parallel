with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;


-- F1: C = SORT(A) *(MA*ME) + SORT(B)

package body Data is
   function F1 (A,B : Integer_Vector; MA,ME : Integer_Matrix) return Integer_Vector is
      result : Integer_Vector(1..A'Length);
      MAME : Integer_Matrix(1..MA'Length, 1..MA'Length);
      AMAME : Integer_Vector(1..A'Length);
      AS : Integer_Vector(1..A'Length);
      BS : Integer_Vector(1..A'Length);

   task T1 is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("Task1");
     pragma Priority(4);
     pragma CPU(0);
   end T1;

   task body T1 is
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;

   begin
      Put_Line("Sort(A) started");

      for i in 1..A'Length loop
         AS(i) := A(i);
      end loop;
      lengthL := AS'Length - 1;

      for i in 1..lengthL loop
         lengthS := lengthL - i;
         for j in 1..lengthS loop
            if AS(j) > AS(j + 1) then
               tmp := AS(j);
               AS(j) := AS(j + 1);
               AS(j + 1) := tmp;
            end if;
            end loop;
      end loop;
      Set_True(awaitSortA);
      Put_Line("Sort(A) finished");
   end T1;

   task T2 is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("Task2");
     pragma Priority(4);
     pragma CPU(0);
   end T2;

   task body T2 is
      sum: Integer;
   begin
      Put_Line("MA*ME started");

      for i in 1..MA'Length loop
         for j in 1..MA'Length loop
            sum := 0;
            for r in 1..MA'Length loop
              sum := sum + MA(i,r) * ME(r, j);
            end loop;
            MAME(i, j) := sum;
         end loop;
      end loop;

      Set_True(awaitMAME);
      Put_Line("MA*ME finished");
   end T2;

   task T3 is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("Task3");
     pragma Priority(4);
     pragma CPU(0);
   end T3;

   task body T3 is
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;

   begin
      Put_Line("Sort(B) started");

      for i in 1..B'Length loop
         BS(i) := B(i);
      end loop;
      lengthL := BS'Length - 1;

      for i in 1..lengthL loop
         lengthS := lengthL - i;
         for j in 1..lengthS loop
            if BS(j) > BS(j + 1) then
               tmp := BS(j);
               BS(j) := BS(j + 1);
               BS(j + 1) := tmp;
            end if;
         end loop;
      end loop;
      Set_True(awaitSortB);
      Put_Line("Sort(B) finished");
   end T3;

   task T4 is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("Task3");
     pragma Priority(4);
     pragma CPU(0);
   end T4;

   task body T4 is
      sum: Integer;

   begin
      Put_Line("Sort(A) * (MA * ME) started");
      Suspend_Until_True(awaitSortA);
      Suspend_Until_True(awaitMAME);

      for i in 1..AS'Length loop
         sum := 0;
         for j in 1..AS'Length loop
              sum := sum + MAME(i, j) * AS(j);
            end loop;
            AMAME(i) := sum;
      end loop;

      Set_True(awaitSortAMAME);
      Put_Line("Sort(A) * (MA * ME) finished");
   end T4;

   begin
      Suspend_Until_True(awaitSortB);
      Suspend_Until_True(awaitSortAMAME);
      -- result = AMF + B;
      for i in 1..A'Length loop
         result(i) := AMAME(i) + BS(i);
      end loop;

      return result;
   end F1;

   procedure Print_Matrix(MR: Integer_Matrix) is
   begin
      for i in 1..MR'Length loop
         for j in 1..MR'Length loop
            Put(MR(i,i));
         end loop;
         New_Line(1);
      end loop;
   end Print_Matrix;

   procedure Print_Vector(M: Integer_Vector) is
   begin
      for i in 1..M'Length loop
         Put(M(i));
      end loop;
      New_Line(1);
   end Print_Vector;
end Data;
