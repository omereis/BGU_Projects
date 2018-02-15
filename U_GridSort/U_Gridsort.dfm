object Form1: TForm1
  Left = 192
  Top = 104
  Width = 536
  Height = 480
  Caption = 'StringGrid Sort Demo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 112
    Top = 32
    Width = 162
    Height = 20
    Caption = 'Select a column to sort'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid1: TStringGrid
    Left = 56
    Top = 72
    Width = 337
    Height = 257
    RowCount = 10
    ScrollBars = ssNone
    TabOrder = 0
    OnMouseUp = StringGrid1MouseUp
  end
end
