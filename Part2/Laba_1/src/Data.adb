with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;


-- F1: C = SORT(A) *(MA*ME) + SORT(B)
-- F2: MG = SORT(MF) *MK + ML
-- F3: O = (SORT(MP*MR)*S)

package body Data is
   function F1 (A,B : Integer_Vector; MA,ME : Integer_Matrix) return Integer_Vector is
      result : Integer_Vector(1..A'Length);
      MF : Integer_Matrix(1..MA'Length, 1..MA'Length);
      AMF : Integer_Vector(1..A'Length);
      AS : Integer_Vector(1..A'Length);
      BS : Integer_Vector(1..A'Length);
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;
      sum: Integer;
   begin
      for i in 1..A'Length loop
         AS(i) := A(i);
         BS(i) := B(i);
      end loop;
      -- AS = SORT(AS);
      lengthL := B'Length - 1;
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

      -- B = SORT(B);
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

      -- MF = MA * ME;
      for i in 1..MA'Length loop
         for j in 1..MA'Length loop
            sum := 0;
            for r in 1..MA'Length loop
              sum := sum + MA(i,r) * ME(r, j);
            end loop;
            MF(i, j) := sum;
         end loop;
      end loop;

      -- AMF = AS * MF;
      for i in 1..A'Length loop
         sum := 0;
         for j in 1..A'Length loop
              sum := sum + MF(i, j) * AS(j);
            end loop;
            AMF(i) := sum;
      end loop;

      -- result = AMF + B;
      for i in 1..A'Length loop
         result(i) := AMF(i) + BS(i);
      end loop;

      return result;
   end F1;

   function F2 (MF,MK,ML : Integer_Matrix) return Integer_Matrix is
      MFMK : Integer_Matrix(1..MK'Length, 1..MK'Length);
      MFS : Integer_Matrix(1..MK'Length, 1..MK'Length);
      result : Integer_Matrix(1..MK'Length, 1..MK'Length);
      sum : Integer;
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;
   begin

      -- MF = SORT(MF);
      for i in 1..MF'Length loop
         for j in 1..MF'Length loop
            MFS(i, j) := MF(i, j);
         end loop;
      end loop;

      lengthL := MF'Length - 1;
      for i in 1..MF'Length loop
         for l in 1..lengthL loop
            lengthS := lengthL - l;
            for j in 1..lengthS loop
               if MFS(i, j) < MFS(i, j + 1) then
                  tmp := MFS(i, j);
                  MFS(i, j) := MFS(i, j + 1);
                  MFS(i, j + 1) := tmp;
               end if;
            end loop;
         end loop;
      end loop;

      -- MFMK = SORT(MF) * MK;
      for i in 1..MF'Length loop
         for j in 1..MF'Length loop
            sum := 0;
            for r in 1..MF'Length loop
              sum := sum + MK(i,r) * MFS(r, j);
            end loop;
            MFMK(i, j) := sum;
         end loop;
      end loop;

      -- result = MFMK + ML;
      for i in 1..ML'Length loop
         for j in 1..ML'Length loop
            result(i, j) := MFMK(i, j) + ML(i, j);
         end loop;
      end loop;


      return result;
   end F2;

   function F3 (MP,MR : Integer_Matrix; S : Integer_Vector) return Integer_Vector is
      MPMR : Integer_Matrix(1..MP'Length, 1..MP'Length);
      result : Integer_Vector(1..S'Length);
      sum : Integer;
      lengthL: Integer;
      lengthS: Integer;
      tmp: Integer;
   begin
      -- MPMR = MP * MR;
      for i in 1..MP'Length loop
         for j in 1..MP'Length loop
            sum := 0;
            for r in 1..MP'Length loop
              sum := sum + MP(i,r) * MR(r, j);
            end loop;
            MPMR(i, j) := sum;
         end loop;
      end loop;

      -- MPMR = SORT(MPMR);
      lengthL := MPMR'Length - 1;
      for i in 1..MPMR'Length loop
         for l in 1..lengthL loop
            lengthS := lengthL - l;
            for j in 1..lengthS loop
               if MPMR(i, j) < MPMR(i, j + 1) then
                  tmp := MPMR(i, j);
                  MPMR(i, j) := MPMR(i, j + 1);
                  MPMR(i, j + 1) := tmp;
               end if;
            end loop;
         end loop;
      end loop;

      --result = MPMR * S
      for i in 1..MPMR'Length loop
         sum := 0;
         for j in 1..MPMR'Length loop
              sum := sum + MPMR(i, j) * S(j);
            end loop;
            result(i) := sum;
      end loop;

      return result;
   end F3;

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

   procedure InitializeSemaphore is
   begin
      Set_True(await);
   end InitializeSemaphore;
end Data;
