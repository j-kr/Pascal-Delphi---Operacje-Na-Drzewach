#include <iostream>

using namespace std;



type
  TDana = integer; // deklaracja jakiejœ danej
  Drzewo = ^TDrzewo; // typ wskazuj¹cy na drzewko bo przecie¿ musimy pamiêtac jego potomków...
  TDrzewo = record   // drzewko
    etykieta: TDana;  // to jest nasza dana, mo¿e byæ ich oczywiœcie wiêcej
    lewy, prawy: Drzewo;  // potomkowie
  end;

var
  i, a, n: integer;
  dana: TDana;
  drzewko: Drzewo;

// procedura wstawiania
procedure Wstaw(var W : Drzewo; Co : TDana);
begin
  if W = nil then
  begin
    new(W);
    if W = nil then
      exit;
    W^.lewy:=nil;
    W^.prawy:=nil;
    W^.etykieta:=Co;
  end
  else
  if W^.etykieta > Co then
    Wstaw(W^.lewy,Co)
  else
  if W^.etykieta < Co then
    Wstaw(W^.prawy,Co);
end;

// procedura usuwania
procedure Usun(var W : Drzewo; Co : TDana);
var
  T,X,Y,Z: Drzewo; {X?rodzic, Y-usuwany, Z-dziecko}
begin
  X:=nil;
  Y:=W;
  while Y<>nil do
  begin
  if Y^.etykieta = Co then
    break
  else
  begin
    X:=Y;
    if Y^.etykieta > Co then
      Y:=Y^.lewy
    else
      Y:=Y^.prawy;
  end;
  end;
  if Y<>nil then
    if (Y^.lewy= nil) or (Y^.prawy=nil) then
    begin
      if (Y^.lewy = nil) and (Y^.prawy = nil) then
        Z:=nil
      else
        if (Y^.lewy =nil) then
          Z:=Y^.prawy
        else
          Z:=Y^.lewy;
      if X=nil then
        W:=Z
      else
        if Y=X^.lewy then
          X^.lewy:=Z
        else
          X^.prawy:=Z;
      dispose(Y);
    end
    else
    begin
      Z:=Y^.prawy;
      if Z^.lewy=nil then
        Y^.prawy:= Z^.prawy
      else
      begin
        repeat
          T:=Z;
          Z:=Z^.lewy;
        until
          Z^.lewy=NIL;
        T^.lewy:=Z^.prawy;
      end;
      Y^.etykieta:= Z^.etykieta;
      dispose(Z);
    end;
end;


//  procedura wyœwietlania. tutaj u¿y³em metody Inorder (lewe dziecko, dana, prawe dziecko).
//  ale s¹ jeszcze dwie: Postorder (lewe dziecko, prawe dziecko, dana) i
//  Preorder (dana, lewe dziecko i prawe dziecko).

procedure drukuj(W : Drzewo);
begin
  if W <> nil then
  begin
    drukuj(W^.Lewy);
    Writeln(W^.Etykieta);
    drukuj(W^.Prawy);
  end;
end;

// procedura szukania - zwyk³e przejœcie przed drzewo
procedure szukaj(W : Drzewo; dana: tdana);
begin
  if W <> nil then
  begin
    szukaj(W^.Lewy, dana);
    if W^.etykieta = dana then
    begin
      Writeln('znaleziona: ', W^.etykieta);
      Exit;
    end;
    szukaj(W^.Prawy, dana);
  end;
end;

// program g³ówny - wywo³anie tego co napisa³em wy¿ej...
begin
  Writeln('Podaj liczbe wartosci');
  Readln(a);
  Writeln('Podaj ', a, ' liczb');
  for i:= 1 to a do
  begin
    Readln(n);
    Wstaw(drzewko, n);
  end;
  writeln;
  Writeln('zawartosc drzewa:');
  drukuj(drzewko);
  Writeln;
  Writeln('podaj szukana wartosc:');
  Readln(a);
  szukaj(Drzewko, a);
  Writeln;
  Writeln('podaj wartosc do usuniecia');
  readln(a);
  usun(drzewko, a);
  writeln;
  drukuj(Drzewko);
  Readln;
end.
