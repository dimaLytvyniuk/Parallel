with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;


-- F1: C = SORT(A) *(MA*ME) + SORT(B)

package body Data is
   protected body monitor is
      entry Wait_Sort when not sorted is
      begin
         sorted := True;
      end Wait_Sort;

      entry Wait_Mult when not multed is
      begin
         multed := True;
      end;

      entry Wait_MultVector when not multedVector is
      begin
         multedVector := True;
      end;

      procedure Release_Sort is
      begin
         sorted := False;
      end;

      procedure Release_Mult is
      begin
         multed := False;
      end;

      procedure Release_MultVector is
      begin
         multedVector := False;
      end;
   end monitor;

   procedure F1(R: Integer_Vector; S: out Integer_Vector; MO, MP: Integer_Matrix) is
   MOMP: Integer_Matrix(1..R'Length, 1..R'Length);
   SMOMPR: Integer_Vector(1..R'Length);

   begin
      Sort(MOMP, R'Length);
      monitor.Wait_Sort;
      MultMatrix(MO, MP, MOMP, R'Length);
      monitor.Wait_Mult;
      SMOMPR := MultMatrixVector(MOMP, R);
      MinusVectors(SMOMPR, S);
   end F1;

 procedure MultMatrix(MO, MP: Integer_Matrix; MOMP:out Integer_Matrix; n: Integer) is
  awaitFirstMult: Suspension_Object;
  awaitSecondMult: Suspension_Object;

   task FirstHalf is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("FirstHalfMult");
     pragma Priority(4);
     pragma CPU(0);
   end FirstHalf;

   task body FirstHalf is
   sum: Integer;
   k: Integer;
   k1: Integer;
begin
   k := n / 2;
      for i in 1..k loop
         for j in 1..k loop
            sum := 0;
            for r in 1..MO'Length loop
              sum := sum + MO(i,r) * MP(r, j);
            end loop;
            MOMP(i, j) := sum;
         end loop;
      end loop;

   Set_True(awaitFirstMult);
   Suspend_Until_True(awaitSecondMult);

   k1 := k + 1;
   for i in 1..k loop
         for j in k..MO'Length loop
            sum := 0;
            for r in 1..MO'Length loop
              sum := sum + MO(i,r) * MP(r, j);
            end loop;
            MOMP(i, j) := sum;
         end loop;
   end loop;
   Set_True(awaitSecondMult);
   end FirstHalf;

   task SecondHalf is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("SecondHalfMult");
     pragma Priority(4);
     pragma CPU(0);
   end SecondHalf;

   task body SecondHalf is
      sum: Integer;
      k: Integer;
      k1: Integer;
   begin
      k := n / 2;
      k1 := n / 2 + 1;
      for i in k1..MO'Length loop
         for j in k1..MO'Length loop
            sum := 0;
            for r in 1..MO'Length loop
              sum := sum + MO(i,r) * MP(r, j);
            end loop;
            MOMP(i, j) := sum;
         end loop;
      end loop;

   Set_True(awaitSecondMult);
   Suspend_Until_True(awaitFirstMult);

   for i in k1..MO'Length loop
         for j in 1..k loop
            sum := 0;
            for r in 1..MO'Length loop
              sum := sum + MO(i,r) * MP(r, j);
            end loop;
            MOMP(i, j) := sum;
         end loop;
      end loop;

      Suspend_Until_True(awaitSecondMult);
      monitor.Release_Mult;
   end SecondHalf;
begin
Put("");
end MultMatrix;

 procedure Sort(MOMP:out Integer_Matrix; n: Integer) is
   awaitStartSort: Suspension_Object;
   task FirstHalf is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("FirstHalf");
     pragma Priority(4);
     pragma CPU(0);
   end FirstHalf;

   task body FirstHalf is
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;
      finish: Integer;
   begin

      lengthL := MOMP'Length - 1;
      finish := n / 2;
      for k in 1..finish loop
         for i in 1..lengthL loop
            lengthS := lengthL - i;
            for j in 1..lengthS loop
               if MOMP(k, j) > MOMP(k, j + 1) then
               tmp := MOMP(k, j);
               MOMP(k, j) := MOMP(k, j + 1);
               MOMP(k, j + 1) := tmp;
               end if;
            end loop;
         end loop;
      end loop;

      Set_True(awaitStartSort);
   end FirstHalf;

   task SecondHalf is
     pragma Storage_Size (10_000_000);
     pragma Task_Name ("SecondHalf");
     pragma Priority(4);
     pragma CPU(0);
   end SecondHalf;

   task body SecondHalf is
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;
      start: Integer;
   begin

      lengthL := MOMP'Length - 1;
      start := n / 2 + 1;
      for k in start..n loop
         for i in 1..lengthL loop
            lengthS := lengthL - i;
            for j in 1..lengthS loop
               if MOMP(k, j) > MOMP(k, j + 1) then
               tmp := MOMP(k, j);
               MOMP(k, j) := MOMP(k, j + 1);
               MOMP(k, j + 1) := tmp;
               end if;
            end loop;
         end loop;
      end loop;

      Suspend_Until_True(awaitStartSort);
      monitor.Release_Sort;
   end SecondHalf;
begin
Put("");
end Sort;
   function MultMatrixVector (MOMP: Integer_Matrix; R : Integer_Vector) return Integer_Vector is
      sum: Integer;
      T: Integer_Vector(1..MOMP'Length);
   begin
      for i in 1..MOMP'Length loop
         sum := 0;
         for j in 1..MOMP'Length loop
            sum := sum + MOMP(i,j) * R(j);
         end loop;
         T(i) := sum;
      end loop;
      return T;
   end MultMatrixVector;

   procedure MinusVectors(SMOMPR:Integer_Vector; S: out Integer_Vector) is
   begin
      for i in 1..S'Length loop
         S(i) := SMOMPR(i) + S(i);
      end loop;
   end MinusVectors;
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
