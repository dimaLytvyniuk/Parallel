with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO;
with Ada.Synchronous_Task_Control;
use Ada.Integer_Text_IO;
use Ada.Synchronous_Task_Control;

package body Data is
   procedure F1(N: Integer) is
      task CreateData is
      end CreateData;

      task MultMatrixVector is
         entry inputMO(in_MO: in Integer_Matrix);
         entry inputS(in_S: in Integer_Vector);
      end MultMatrixVector;

      task MaxVector is
         entry inputMOS(in_MOS: in Integer_Vector);
      end MaxVector;

      task MultMatrix is
         entry inputMT(in_MT: in Integer_Matrix);
         entry inputMO(in_MO: in Integer_Matrix);
      end MultMatrix;

      task PlusMatrix is
         entry inputMTMO(in_MTMO: in Integer_Matrix);
         entry inputMP(in_MP: in Integer_Matrix);
      end PlusMatrix;

      task MinMatrix is
         entry inputMTMOMP(in_MTMOMP: in Integer_Matrix);
      end MinMatrix;

      task Result is
         entry inputMax(in_Max: in Integer);
         entry inputMin(in_Min: in Integer);
      end Result;

      task body CreateData is
         MO: Integer_Matrix(1..N, 1..N);
         MT: Integer_Matrix(1..N, 1..N);
         MP: Integer_Matrix(1..N, 1..N);
         S: Integer_Vector(1..N);
      begin
         for i in 1..N loop
            for j in 1..N loop
               MO(i, j) := 1;
               MP(i, j) := 1;
               MT(i, j) := 1;
            end loop;
            S(i) := 1;
         end loop;

         MultMatrixVector.inputMO(MO);
         MultMatrixVector.inputS(S);
         MultMatrix.inputMO(MO);
         MultMatrix.inputMT(MT);
         PlusMatrix.inputMP(MP);
      end CreateData;

      task body MultMatrixVector is
         MO: Integer_Matrix(1..N,1..N);
         S: Integer_Vector(1..N);
         MOS: Integer_Vector(1..N);
         sum: Integer;
      begin
         accept inputMO (in_MO : in Integer_Matrix) do
            MO := in_MO;
         end inputMO;
         accept inputS (in_S : in Integer_Vector) do
            S := in_S;
         end inputS;

         for i in 1..S'Length loop
            sum := 0;
            for j in 1..S'Length loop
               sum := sum + MO(i,j) * S(j);
            end loop;
            MOS(i) := sum;
         end loop;

         MaxVector.inputMOS(MOS);
      end MultMatrixVector;

      task body MaxVector is
         max: Integer;
         MOS: Integer_Vector(1..N);
      begin
         accept inputMOS (in_MOS : in Integer_Vector) do
            MOS := in_MOS;
         end inputMOS;

         max := MOS(1);
         for i in 2..MOS'Length loop
            if MOS(i) > max then
               max := MOS(i);
            end if;
         end loop;

         Result.inputMax(max);
      end MaxVector;

      task body MultMatrix is
         MT: Integer_Matrix(1..N, 1..N);
         MO: Integer_Matrix(1..N, 1..N);
         MTMO: Integer_Matrix(1..N, 1..N);
         sum: Integer;
      begin
         accept inputMO (in_MO : in Integer_Matrix) do
            MO := in_MO;
         end inputMO;
         accept inputMT (in_MT : in Integer_Matrix) do
            MT := in_MT;
         end inputMT;

         for i in 1..MO'Length loop
            for j in 1..MO'Length loop
               sum := 0;
               for r in 1..MO'Length loop
                  sum := sum + MT(i,r) * MO(r, j);
               end loop;
            MTMO(i, j) := sum;
            end loop;
         end loop;

         PlusMatrix.inputMTMO(MTMO);
      end MultMatrix;

      task body PlusMatrix is
         MTMO: Integer_Matrix(1..N, 1..N);
         MP: Integer_Matrix(1..N, 1..N);
         MTMOMP: Integer_Matrix(1..N, 1..N);
      begin
         for i in 1..2 loop
            select
               accept inputMP (in_MP : in Integer_Matrix) do
                  MP := in_MP;
               end inputMP;
            or
               accept inputMTMO (in_MTMO : in Integer_Matrix) do
                  MTMO := in_MTMO;
               end inputMTMO;
            end select;
         end loop;

         for i in 1..MP'Length loop
            for j in 1..MP'Length loop
               MTMOMP(i, j) := MTMO(i, j) + MP(i,j);
            end loop;
         end loop;

         MinMatrix.inputMTMOMP(MTMOMP);
      end PlusMatrix;

      task body MinMatrix is
         min: Integer;
         MTMOMP: Integer_Matrix(1..N, 1..N);
      begin
         accept inputMTMOMP (in_MTMOMP : in Integer_Matrix) do
            MTMOMP := in_MTMOMP;
         end inputMTMOMP;

         min := MTMOMP(1, 1);
         for i in 1..MTMOMP'Length loop
            for j in 1..MTMOMP'Length loop
               if min > MTMOMP(i, j) then
                  min := MTMOMP(i, j);
               end if;
            end loop;
         end loop;

         Result.inputMin(min);
      end MinMatrix;

      task body Result is
         min: Integer;
         max: Integer;
         result: Integer;
      begin
         for i in 1..2 loop
            select
               accept inputMin (in_Min : in Integer) do
                  min := in_Min;
               end inputMin;
            or
               accept inputMax (in_Max : in Integer) do
                  max := in_Max;
               end inputMax;
            end select;
         end loop;

         result := max + min;
         Put("MAX(MO*S) + MIN(MT*MO + MP) = ");
         Put(result);
      end Result;
   begin
      Put("");
   end F1;
end Data;
