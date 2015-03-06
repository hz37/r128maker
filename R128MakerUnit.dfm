object Form1: TForm1
  Left = 0
  Top = 0
  Caption = ' R128 maker'
  ClientHeight = 317
  ClientWidth = 643
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object OutputMemo: TMemo
    Left = 0
    Top = 0
    Width = 643
    Height = 317
    Align = alClient
    BevelKind = bkFlat
    BevelOuter = bvSpace
    Color = clScrollBar
    Font.Charset = OEM_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Terminal'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    OnDblClick = OutputMemoDblClick
  end
end
