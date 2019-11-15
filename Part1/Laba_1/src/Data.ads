package Data is
   type Integer_Vector is array (Positive range <>) of Integer;
   type Integer_Matrix is array (Positive range <>, Positive range <>) of Integer;

   protected type OutputData is
      entry Seize;
      procedure Release;
      procedure Print_Vector(v:Integer_Vector);
      procedure Print_Matrix(m:Integer_Matrix);
   private
      Owned : Boolean := False;
   end OutputData;

   printer: OutputData;

   function F1 (B,C : Integer_Vector; MA,ME : Integer_Matrix) return Integer_Matrix;
   function F2 (MK,MH,MF : Integer_Matrix) return Integer_Matrix;
   function F3 (MP,MR : Integer_Matrix; T : Integer_Vector) return Integer_Vector;
   procedure Print_Matrix(MR: Integer_Matrix);
   procedure Print_Vector(M: Integer_Vector);
end Data;
