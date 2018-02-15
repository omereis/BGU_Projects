unit U_Gridsort;

{Sample program to sort rows of a stringgrid based on any selected column}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, StdCtrls;

type
  TForm1 = class(TForm)
    StringGrid1: TStringGrid;
    Label1: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure StringGrid1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure SortGrid(Grid : TStringGrid; SortCol:integer);
  end;

  var
  Form1: TForm1;

implementation

{$R *.DFM}

{************** SortGrid *************}
procedure Tform1.Sortgrid(Grid : TStringGrid; SortCol:integer);
{A simple exchange sort of grid rows}
var
   i,j : integer;
   temp:tstringlist;
begin
  temp:=tstringlist.create;
  with Grid do
  for i := FixedRows to RowCount - 2 do  {because last row has no next row}
  for j:= i+1 to rowcount-1 do {from next row to end}
  if AnsiCompareText(Cells[SortCol, i], Cells[SortCol,j]) > 0
  then
  begin
    temp.assign(rows[j]);
    rows[j].assign(rows[i]);
    rows[i].assign(temp);
  end;
  temp.free;
end;


procedure TForm1.FormCreate(Sender: TObject);
var
  i,j:integer;
  totwidth:integer;
begin
  with stringgrid1 do
  begin
    {assign some random numbers}
    for j := 1 to rowcount-1 do
    for i:= 1 to colcount-1 do
    cells[i,j]:=format('%3d',[random(1000)]);
    {Add row labels}
    for i:= 1 to rowcount-1 do cells[0,i]:='Row '+ format('%2d',[i]);
    {Add column labels and change column widths}
    totwidth:=0;
    for i:= 0 to colcount-1 do
    begin
      cells[i,0]:='Column '+ inttostr(i+1);
      {vary column widths for testing}
      colwidths[i]:=defaultcolwidth+random(48);
      inc(totwidth,colwidths[i]);
    end;
    {adjust grid width so that all column are visible}
    width:=totwidth+(colcount+3)*gridlinewidth;
  end;
end;


{************ StringgridMouseUp **************}
procedure TForm1.StringGrid1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  c,j:integer;
  rect:trect;
begin
  with stringgrid1 do
  if y<rowheights[0] then   {make sure row 0 was clicked}
  begin
    for j:= 0 to colcount-1 do {determine which column was clicked}
    begin
      rect := cellrect(j,0);
      if (rect.Left < x) and (rect.Right> x) then
      begin
        c := j;
        break;
      end;
    end;
    sortgrid(stringgrid1,c);
  end;  
end;


end.
