object dlgImportGeoLife: TdlgImportGeoLife
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Import GeoLife Dataset'
  ClientHeight = 558
  ClientWidth = 785
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 368
    Top = 208
    Width = 37
    Height = 13
    Caption = 'Objects'
  end
  object Label2: TLabel
    Left = 536
    Top = 208
    Width = 34
    Height = 13
    Caption = 'Routes'
  end
  object bitbtnOK: TBitBtn
    Left = 110
    Top = 522
    Width = 75
    Height = 25
    TabOrder = 0
    Kind = bkOK
  end
  object bitbtnCancel: TBitBtn
    Left = 191
    Top = 522
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkCancel
  end
  object DriveComboBox1: TDriveComboBox
    Left = 30
    Top = 8
    Width = 145
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 2
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 181
    Top = 8
    Width = 145
    Height = 97
    FileList = FileListBox1
    ItemHeight = 16
    TabOrder = 3
    OnChange = DirectoryListBox1Change
  end
  object bitbtnSelDir: TBitBtn
    Left = 8
    Top = 118
    Width = 129
    Height = 25
    Caption = 'Root Directory...'
    TabOrder = 4
  end
  object edtRootDir: TEdit
    Left = 8
    Top = 149
    Width = 577
    Height = 21
    TabOrder = 5
    Text = 'edtRootDir'
  end
  object bitbtnFind: TBitBtn
    Left = 16
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Find'
    TabOrder = 6
    OnClick = bitbtnFindClick
  end
  object FileListBox1: TFileListBox
    Left = 344
    Top = 8
    Width = 145
    Height = 97
    ItemHeight = 13
    TabOrder = 7
  end
  object lboxFiles: TListBox
    Left = 1
    Top = 227
    Width = 337
    Height = 273
    ItemHeight = 13
    TabOrder = 8
    OnDblClick = lboxFilesDblClick
  end
  object Panel1: TPanel
    Left = 288
    Top = 506
    Width = 185
    Height = 26
    TabOrder = 9
  end
  object btnInsObjs: TButton
    Left = 110
    Top = 177
    Width = 107
    Height = 25
    Caption = 'Insert Objects'
    TabOrder = 10
    OnClick = btnInsObjsClick
  end
  object lboxObjs: TListBox
    Left = 344
    Top = 227
    Width = 98
    Height = 273
    ItemHeight = 13
    TabOrder = 11
  end
  object lboxRoutes: TListBox
    Left = 448
    Top = 227
    Width = 185
    Height = 273
    ItemHeight = 13
    TabOrder = 12
  end
  object btnLoadObjects: TButton
    Left = 344
    Top = 176
    Width = 98
    Height = 25
    Caption = 'Load Objects...'
    TabOrder = 13
    OnClick = btnLoadObjectsClick
  end
  object btnShowRoutes: TButton
    Left = 510
    Top = 176
    Width = 83
    Height = 25
    Caption = 'Show Routes'
    TabOrder = 14
    OnClick = btnShowRoutesClick
  end
  object Panel2: TPanel
    Left = 360
    Top = 111
    Width = 113
    Height = 25
    Caption = 'Panel2'
    TabOrder = 15
    OnClick = Panel2Click
  end
  object Panel3: TPanel
    Left = 496
    Top = 506
    Width = 113
    Height = 25
    Caption = 'Panel3'
    TabOrder = 16
  end
  object Panel6: TPanel
    Left = 520
    Top = 64
    Width = 185
    Height = 33
    Caption = 'Panel6'
    TabOrder = 17
  end
  object Panel7: TPanel
    Left = 520
    Top = 103
    Width = 185
    Height = 33
    Caption = 'Panel7'
    TabOrder = 18
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = OnIdle
    Left = 512
    Top = 16
  end
  object timerUpdateGui: TTimer
    Enabled = False
    OnTimer = timerUpdateGuiTimer
    Left = 552
    Top = 16
  end
end
