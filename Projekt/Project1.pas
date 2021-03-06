program Project1;

uses
  SysUtils;

type
  drzewo=^wezel;
  wezel=record
      liczba:byte;
      lewy,prawy:drzewo;
    end;

var
  w:drzewo;
  opcja,co:byte;

procedure dodaj(var w:drzewo; co:byte);
  begin
    if(w=nil) then
      begin
        new(w);
        w^.liczba:=co;
        w^.lewy:=nil;
        w^.prawy:=nil;
      end
    else
      if(w^.liczba>co) then dodaj(w^.lewy,co)
      else if(w^.liczba<co) then dodaj(w^.prawy,co);
  end;

procedure usun(var w:drzewo; co:byte);
  var
    t,x,y,z:drzewo; // x-rodzic, y-usuwany, z-dziecko
  begin
    x:=nil;
    y:=w;
    while(y<>nil) do
      begin
        if(y^.liczba=co) then break
        else
          begin
            x:=y;
            if(y^.liczba>co) then y:=y^.lewy
            else y:=y^.prawy;
          end;
      end;
    if(y<>nil) then // znaleziono
      if(y^.lewy=nil) or (y^.prawy=nil) then
        begin // jest 0 lub 1 dziecko - szukamy z
          if(y^.lewy=nil) and (y^.prawy=nil) then z:=nil
          else if(y^.lewy=nil) then z:=y^.prawy
            else z:=y^.lewy;
          if(x=nil) then w:=z // usuwamy korzen
          else if(y=x^.lewy) then x^.lewy:=z
            else x^.prawy:=z;
          dispose(y);
        end
      else  // jest dwoje dzieci
        begin
          z:=y^.prawy;
          if(z^.lewy=nil) then y^.prawy:=z^.prawy
          else
            begin // znajdz minimum z poddrzewa
              repeat
                t:=z;
                z:=z^.lewy;
              until(z^.lewy=nil);
              t^.lewy:=z^.prawy;
            end;
          y^.liczba:=z^.liczba;
          dispose(z);
        end;
  end;

procedure inorder(w:drzewo);
  begin
    if(w<>nil) then
      begin
        inorder(w^.lewy);
        writeln(w^.liczba);
        inorder(w^.prawy);
      end;
  end;

procedure postorder(w:drzewo);
  begin
    if(w<>nil) then
      begin
        postorder(w^.lewy);
        postorder(w^.prawy);
        writeln(w^.liczba);
      end;
  end;

procedure preorder(w:drzewo);
  begin
    if(w<>nil) then
      begin
        writeln(w^.liczba);
        preorder(w^.lewy);
        preorder(w^.prawy);
      end;
  end;

begin
  repeat
    writeln('1) Dodaj');
    writeln('2) Wyswietl INORDER');
    writeln('3) Wyswietl POSTORDER');
    writeln('4) Wyswietl PREORDER');
    writeln('5) Usun');
    writeln('0) Zakoncz');
    write('Wybieram: ');
    readln(opcja);
    case opcja of
      1: begin

          write('Dodaj <0-255>: ');
          readln(co);

          dodaj(w,co);
         end;
      2: inorder(w);
      3: postorder(w);
      4: preorder(w);
      5: begin

          write('Usun <0-255>: ');
          readln(co);

          usun(w,co);
         end;
      else write('Bledna opcja!');
    end;
    writeln;

  until(opcja=0);
end.

