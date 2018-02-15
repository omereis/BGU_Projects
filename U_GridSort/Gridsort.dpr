program Gridsort;

uses
  Forms,
  U_Gridsort in 'U_Gridsort.pas' {Form1};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
