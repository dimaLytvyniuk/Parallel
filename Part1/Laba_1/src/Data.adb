with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;           use Ada.Integer_Text_IO;


-- F1: MD = (B*C)*(MA*ME);
-- F2: MG = MAX(MH) * (MK*ML);
-- F3: O = MAX(MP*MR) * T;

package body Data is

     protected body OutputData is
      entry Seize when not Owned is
      begin
         Owned := True;
      end Seize;

      procedure Print_Matrix(m: Integer_Matrix) is
      begin
         for i in 1..m'Length loop
            for j in 1..m'Length loop
               Put(m(i,i));
            end loop;
            New_Line(1);
         end loop;
      end Print_Matrix;

      procedure Print_Vector(v: Integer_Vector) is
      begin
         for i in 1..v'Length loop
            Put(v(i));
         end loop;
         New_Line(1);
      end Print_Vector;

      procedure Release is
      begin
         Owned := False;
      end Release;
   end OutputData;


   function F1 (B,C : Integer_Vector; MA,ME : Integer_Matrix) return Integer_Matrix is
      result : Integer_Matrix(1..MA'Length, 1..MA'Length);
      D : Integer_Matrix(1..MA'Length, 1..MA'Length);
      MF : Integer_Matrix(1..MA'Length, 1..MA'Length);
      sum : Integer;
   begin
      -- D = B * C;
      for i in 1..B'Length loop
         for j in 1..C'Length loop
            D(i, j) := B(i) * C(j);
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

      -- result = D * MF;
      for i in 1..D'Length loop
         for j in 1..D'Length loop
            sum := 0;
            for r in 1..D'Length loop
              sum := sum + D(i,r) * MF(r, j);
            end loop;
            result(i, j) := sum;
         end loop;
      end loop;

      return result;
   end F1;

   function F2 (MK,MH,MF : Integer_Matrix) return Integer_Matrix is
      MT : Integer_Matrix(1..MK'Length, 1..MK'Length);
      MM : Integer_Matrix(1..MK'Length, 1..MK'Length);
      result : Integer_Matrix(1..MK'Length, 1..MK'Length);
      sum : Integer;
   begin
      -- MT = TRANS(MT);
      for i in 1..MT'Length loop
         for j in 1..MT'Length loop
            MT(i,j) := MK(j,i);
         end loop;
      end loop;

      -- MM = MH * MF;
      for i in 1..MH'Length loop
         for j in 1..MH'Length loop
            sum := 0;
            for r in 1..MH'Length loop
              sum := sum + MH(i,r) * MF(r, j);
            end loop;
            MM(i, j) := sum;
         end loop;
      end loop;

      -- result = MT * MM;
      for i in 1..MT'Length loop
         for j in 1..MT'Length loop
            sum := 0;
            for r in 1..MT'Length loop
              sum := sum + MT(i,r) * MM(r, j);
            end loop;
            result(i, j) := sum;
         end loop;
      end loop;


      return result;
   end F2;

   function F3 (MP,MR : Integer_Matrix; T : Integer_Vector) return Integer_Vector is
      MM : Integer_Matrix(1..MP'Length, 1..MP'Length);
      result : Integer_Vector(1..T'Length);
      sum : Integer;
      max : Integer;
   begin
      -- MM = MP * MR;
      for i in 1..MP'Length loop
         for j in 1..MP'Length loop
            sum := 0;
            for r in 1..MP'Length loop
              sum := sum + MP(i,r) * MR(r, j);
            end loop;
            MM(i, j) := sum;
         end loop;
      end loop;

      max := MM(1,1);
      -- max = MAX(MM);
      for i in 1..MM'Length loop
         for j in 1..MM'Length loop
            if MM(i, j) > max then
               max := MM(i,j);
            end if;
         end loop;
      end loop;

      -- result = max * T;
      for i in T'Range loop
         result(i) := T(i) * max;
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

end Data;
