object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Settings'
  ClientHeight = 317
  ClientWidth = 346
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 162
    Height = 13
    Caption = 'Integrated reference level (LUFS)'
  end
  object Label2: TLabel
    Left = 8
    Top = 35
    Width = 107
    Height = 13
    Caption = 'Allowed deviation (LU)'
  end
  object Label3: TLabel
    Left = 8
    Top = 62
    Width = 108
    Height = 13
    Caption = 'True peak level (dBTP)'
  end
  object Label4: TLabel
    Left = 8
    Top = 89
    Width = 101
    Height = 13
    Caption = 'Buffer size (seconds)'
  end
  object AfterGainLabel: TLabel
    Left = 27
    Top = 203
    Width = 112
    Height = 13
    Caption = '(after gain adjustment)'
  end
  object OversampleCheckBox: TCheckBox
    Left = 8
    Top = 120
    Width = 97
    Height = 17
    Caption = '4x oversample'
    TabOrder = 0
    OnClick = OversampleCheckBoxClick
  end
  object MethodComboBox: TComboBox
    Left = 8
    Top = 150
    Width = 329
    Height = 21
    AutoComplete = False
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
    Items.Strings = (
      'Best Sinc Interpolator'
      'Medium Sinc Interpolator'
      'Fastest Sinc Interpolator')
  end
  object OKBitBtn: TBitBtn
    Left = 8
    Top = 280
    Width = 328
    Height = 25
    TabOrder = 2
    OnClick = OKBitBtnClick
    Kind = bkOK
  end
  object RefLevelEdit: TEdit
    Left = 239
    Top = 5
    Width = 81
    Height = 21
    TabOrder = 3
    Text = '0'
  end
  object DeviationMaskEdit: TMaskEdit
    Left = 240
    Top = 32
    Width = 80
    Height = 21
    EditMask = '!0.000;1;_'
    MaxLength = 5
    TabOrder = 4
    Text = ' .   '
  end
  object TruePeakEdit: TEdit
    Left = 239
    Top = 59
    Width = 81
    Height = 21
    TabOrder = 5
    Text = '0'
  end
  object BufferSizeEdit: TEdit
    Left = 239
    Top = 86
    Width = 81
    Height = 21
    TabOrder = 6
    Text = '1'
  end
  object RefLevelUpDown: TUpDown
    Left = 320
    Top = 5
    Width = 16
    Height = 21
    Associate = RefLevelEdit
    Min = -99
    Max = 0
    TabOrder = 7
  end
  object TruePeakUpDown: TUpDown
    Left = 320
    Top = 59
    Width = 16
    Height = 21
    Associate = TruePeakEdit
    Min = -99
    Max = 0
    TabOrder = 8
  end
  object BufferSizeUpDown: TUpDown
    Left = 320
    Top = 86
    Width = 16
    Height = 21
    Associate = BufferSizeEdit
    Min = 1
    Max = 999
    Position = 1
    TabOrder = 9
  end
  object SkipOversamplingCheckBox: TCheckBox
    Left = 8
    Top = 188
    Width = 225
    Height = 17
    Caption = 'Skip oversampling if linear peak <= (dBFS)'
    TabOrder = 10
    OnClick = SkipOversamplingCheckBoxClick
  end
  object SkipPeakEdit: TEdit
    Left = 239
    Top = 186
    Width = 82
    Height = 21
    ReadOnly = True
    TabOrder = 11
    Text = '-1'
  end
  object SkipPeakUpDown: TUpDown
    Left = 321
    Top = 186
    Width = 16
    Height = 21
    Associate = SkipPeakEdit
    Min = -99
    Max = -1
    Position = -1
    TabOrder = 12
  end
  object DoNotCheckAgainCheckBox: TCheckBox
    Left = 8
    Top = 222
    Width = 289
    Height = 17
    Caption = 'Do not check again after gain adjustment'
    TabOrder = 13
  end
  object PriorityComboBox: TComboBox
    Left = 8
    Top = 245
    Width = 328
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 14
    Items.Strings = (
      'Above normal priority'
      'Below normal priority'
      'High priority'
      'Idle priority'
      'Normal priority'
      'Realtime priority')
  end
end
