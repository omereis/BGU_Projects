object dlgContent: TdlgContent
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Dataset Content'
  ClientHeight = 426
  ClientWidth = 784
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 8
    Top = 8
    Width = 38
    Height = 13
    Caption = 'Dataset'
  end
  object Label4: TLabel
    Left = 135
    Top = 8
    Width = 53
    Height = 13
    Caption = 'Description'
  end
  object bitbtnOK: TBitBtn
    Left = 107
    Top = 393
    Width = 75
    Height = 25
    TabOrder = 0
    Visible = False
    Kind = bkOK
  end
  object bitbtnCancel: TBitBtn
    Left = 188
    Top = 395
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkCancel
  end
  object lboxObjects: TListBox
    Left = 0
    Top = 103
    Width = 129
    Height = 273
    ItemHeight = 13
    MultiSelect = True
    Sorted = True
    TabOrder = 2
  end
  object btnObjects: TButton
    Left = 16
    Top = 72
    Width = 97
    Height = 25
    Caption = 'Show Objects'
    TabOrder = 3
    OnClick = btnObjectsClick
  end
  object edtName: TEdit
    Left = 8
    Top = 27
    Width = 121
    Height = 21
    ReadOnly = True
    TabOrder = 4
    Text = 'edtName'
  end
  object edtDesc: TEdit
    Left = 135
    Top = 27
    Width = 306
    Height = 21
    ReadOnly = True
    TabOrder = 5
    Text = 'edtDesc'
  end
  object btnShowRoutes: TButton
    Left = 135
    Top = 72
    Width = 99
    Height = 25
    Caption = 'Show Routes'
    TabOrder = 6
    OnClick = btnShowRoutesClick
  end
  object gridRoutePoints: TStringGrid
    Left = 135
    Top = 103
    Width = 208
    Height = 273
    ColCount = 2
    DefaultColWidth = 110
    DefaultRowHeight = 21
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
    TabOrder = 7
    ColWidths = (
      116
      60)
  end
  object panelCount: TPanel
    Left = 247
    Top = 72
    Width = 105
    Height = 25
    TabOrder = 8
  end
  object gridPoints: TStringGrid
    Left = 349
    Top = 103
    Width = 379
    Height = 273
    ColCount = 4
    DefaultColWidth = 85
    DefaultRowHeight = 21
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
    TabOrder = 9
    ColWidths = (
      85
      69
      63
      135)
  end
  object brnShowPoints: TButton
    Left = 415
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Show Points'
    TabOrder = 10
    OnClick = brnShowPointsClick
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = OnIdle
    Left = 552
    Top = 64
  end
end
