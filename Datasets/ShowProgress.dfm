object frmShowProgress: TfrmShowProgress
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Show Progress'
  ClientHeight = 185
  ClientWidth = 426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel4: TPanel
    Left = 0
    Top = 96
    Width = 426
    Height = 89
    Align = alBottom
    TabOrder = 0
    object gauge1: TCGauge
      Left = 1
      Top = 47
      Width = 424
      Height = 41
      Align = alBottom
      Color = 0
      ForeColor = 16711680
      ParentColor = False
      ExplicitLeft = 29
      ExplicitTop = 72
      ExplicitWidth = 100
    end
    object panelCaption: TPanel
      Left = 1
      Top = 1
      Width = 424
      Height = 33
      Align = alTop
      TabOrder = 0
    end
  end
  object btnStop: TButton
    Left = 144
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Stop'
    TabOrder = 1
  end
end
