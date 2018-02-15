object dlgContact: TdlgContact
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Contact'
  ClientHeight = 155
  ClientWidth = 354
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label8: TLabel
    Left = 31
    Top = 12
    Width = 27
    Height = 13
    Caption = 'Name'
  end
  object Label9: TLabel
    Left = 32
    Top = 36
    Width = 30
    Height = 13
    Caption = 'phone'
  end
  object Label10: TLabel
    Left = 34
    Top = 63
    Width = 24
    Height = 13
    Caption = 'email'
  end
  object Label1: TLabel
    Left = 8
    Top = 89
    Width = 50
    Height = 13
    Caption = 'Comments'
  end
  object edtName: TEdit
    Left = 64
    Top = 8
    Width = 161
    Height = 21
    TabOrder = 0
    Text = 'edtName'
  end
  object edtPhone: TEdit
    Left = 64
    Top = 32
    Width = 161
    Height = 21
    TabOrder = 1
    Text = 'edtPhone'
  end
  object edtEmail: TEdit
    Left = 64
    Top = 59
    Width = 161
    Height = 21
    TabOrder = 2
    Text = 'edtEmail'
  end
  object edtComments: TEdit
    Left = 64
    Top = 85
    Width = 161
    Height = 21
    TabOrder = 3
    Text = 'edtComments'
  end
  object bitbtnOK: TBitBtn
    Left = 96
    Top = 122
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkOK
  end
  object bitbtnCancel: TBitBtn
    Left = 181
    Top = 122
    Width = 75
    Height = 25
    TabOrder = 5
    Kind = bkCancel
  end
  object panelID: TPanel
    Left = 256
    Top = 8
    Width = 73
    Height = 33
    TabOrder = 6
  end
end
