object Form1: TForm1
  Left = 198
  Top = 120
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Animation Tool Ver. 3.00 ( 2009. 3. 26 )'
  ClientHeight = 718
  ClientWidth = 1012
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 205
    Top = 0
    Width = 402
    Height = 403
  end
  object Bevel2: TBevel
    Left = 608
    Top = 0
    Width = 402
    Height = 403
  end
  object Bevel4: TBevel
    Left = 0
    Top = 408
    Width = 801
    Height = 289
  end
  object Bevel5: TBevel
    Left = 801
    Top = 408
    Width = 209
    Height = 289
  end
  object Edit_screen: TImage
    Left = 609
    Top = 1
    Width = 400
    Height = 400
    Stretch = True
  end
  object Source_screen: TImage
    Left = 206
    Top = 1
    Width = 400
    Height = 400
    ParentShowHint = False
    ShowHint = False
    Stretch = True
  end
  object Bevel3: TBevel
    Left = 0
    Top = 0
    Width = 205
    Height = 403
  end
  object BackImage: TImage
    Left = 414
    Top = 1
    Width = 400
    Height = 400
    ParentShowHint = False
    ShowHint = False
    Stretch = True
    Visible = False
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 699
    Width = 1012
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 193
    Height = 241
    Caption = 'SOURCE AN3 files'
    TabOrder = 1
    object AN_ListBox: TListBox
      Left = 8
      Top = 98
      Width = 177
      Height = 111
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      ItemHeight = 13
      Items.Strings = (
        'Layer 1 ( no image )'
        'Layer 2 ( no image )'
        'Layer 3 ( no image )'
        'Layer 4 ( no image )'
        'Layer 5 ( no image )'
        'Layer 6 ( no image )'
        'Layer 7 ( no image )'
        'Layer 8 ( no image )')
      TabOrder = 0
      OnClick = AN_ListBoxClick
    end
    object AllSourceSelect: TCheckBox
      Left = 8
      Top = 57
      Width = 121
      Height = 17
      Caption = 'Select All Layer'
      TabOrder = 1
      OnClick = AllSourceSelectClick
    end
    object Load_AN_button: TButton
      Left = 16
      Top = 216
      Width = 75
      Height = 17
      Caption = 'Load Image'
      TabOrder = 2
      OnClick = Load_AN_buttonClick
    end
    object Del_AN_button: TButton
      Left = 96
      Top = 216
      Width = 75
      Height = 17
      Caption = 'Delete Image'
      TabOrder = 3
      OnClick = Del_AN_buttonClick
    end
    object AN_ViewCheck: TCheckBox
      Left = 8
      Top = 78
      Width = 153
      Height = 17
      Caption = 'Layer Show/Hide'
      TabOrder = 4
      OnClick = AN_ViewCheckClick
    end
    object AN_Select: TLabeledEdit
      Left = 8
      Top = 32
      Width = 177
      Height = 21
      AutoSize = False
      EditLabel.Width = 115
      EditLabel.Height = 12
      EditLabel.Caption = 'Now Selected Layer'
      EditLabel.Font.Charset = ANSI_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -12
      EditLabel.Font.Name = #44404#47548
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      LabelPosition = lpAbove
      LabelSpacing = 3
      MaxLength = 49
      ReadOnly = True
      TabOrder = 5
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 256
    Width = 193
    Height = 137
    Caption = 'SOURCE Frame Edit'
    TabOrder = 2
    object Label2: TLabel
      Left = 9
      Top = 23
      Width = 56
      Height = 12
      Caption = 'Animation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 8
      Top = 52
      Width = 25
      Height = 12
      Caption = 'ACT'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 80
      Width = 19
      Height = 12
      Caption = 'DIR'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 3
      Top = 110
      Width = 36
      Height = 12
      Caption = 'Frame'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Play_AN_button: TButton
      Left = 80
      Top = 17
      Width = 49
      Height = 25
      Caption = '> Start'
      TabOrder = 0
      OnClick = Play_AN_buttonClick
    end
    object Stop_AN_button: TButton
      Left = 136
      Top = 17
      Width = 49
      Height = 25
      Caption = '|| Stop'
      TabOrder = 1
      OnClick = Stop_AN_buttonClick
    end
    object Before_AN_action: TButton
      Left = 80
      Top = 46
      Width = 49
      Height = 25
      Caption = '<<'
      TabOrder = 2
      OnClick = Before_AN_actionClick
    end
    object Next_AN_action: TButton
      Left = 136
      Top = 46
      Width = 49
      Height = 25
      Caption = '>>'
      TabOrder = 3
      OnClick = Next_AN_actionClick
    end
    object Before_AN_direction: TButton
      Left = 80
      Top = 75
      Width = 49
      Height = 25
      Caption = '<<'
      TabOrder = 4
      OnClick = Before_AN_directionClick
    end
    object Next_AN_direction: TButton
      Left = 136
      Top = 75
      Width = 49
      Height = 25
      Caption = '>>'
      TabOrder = 5
      OnClick = Next_AN_directionClick
    end
    object Before_AN_frame: TButton
      Left = 80
      Top = 104
      Width = 49
      Height = 25
      Caption = '<<'
      TabOrder = 6
      OnClick = Before_AN_frameClick
    end
    object Next_AN_frame: TButton
      Left = 136
      Top = 104
      Width = 49
      Height = 25
      Caption = '>>'
      TabOrder = 7
      OnClick = Next_AN_frameClick
    end
    object SourceAnimation: TEdit
      Left = 40
      Top = 48
      Width = 33
      Height = 21
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      ReadOnly = True
      TabOrder = 8
      Text = '0'
    end
    object SourceDirection: TEdit
      Left = 40
      Top = 76
      Width = 33
      Height = 21
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      ReadOnly = True
      TabOrder = 9
      Text = '0'
    end
    object SourceFrame: TEdit
      Left = 40
      Top = 104
      Width = 33
      Height = 21
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      ReadOnly = True
      TabOrder = 10
      Text = '0'
    end
  end
  object GroupBox3: TGroupBox
    Left = 112
    Top = 416
    Width = 209
    Height = 113
    Caption = 'SOURCE to EDIT'
    TabOrder = 3
    object Label6: TLabel
      Left = 17
      Top = 16
      Width = 121
      Height = 12
      Caption = 'SOURCE image copy'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Label7: TLabel
      Left = 7
      Top = 63
      Width = 180
      Height = 12
      Caption = 'Now SOURCE ACT image copy'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Copy_frame: TButton
      Left = 152
      Top = 34
      Width = 49
      Height = 25
      Caption = '1 Frame'
      TabOrder = 0
      OnClick = Copy_frameClick
    end
    object Append_frame: TButton
      Left = 64
      Top = 34
      Width = 81
      Height = 25
      Caption = 'Append(Add)'
      TabOrder = 1
      OnClick = Append_frameClick
    end
    object Copy_all_frame_selected: TButton
      Left = 8
      Top = 81
      Width = 97
      Height = 25
      Caption = 'Selected Layer'
      TabOrder = 2
      OnClick = Copy_all_frame_selectedClick
    end
    object Copy_all_frame_all: TButton
      Left = 112
      Top = 81
      Width = 89
      Height = 25
      Caption = 'All Layer'
      TabOrder = 3
      OnClick = Copy_all_frame_allClick
    end
    object AllCopyButton: TButton
      Left = 8
      Top = 34
      Width = 49
      Height = 25
      Cursor = crHandPoint
      Caption = 'Copy All'
      TabOrder = 4
      OnClick = AllCopyButtonClick
    end
  end
  object GroupBox4: TGroupBox
    Left = 328
    Top = 416
    Width = 465
    Height = 273
    Caption = 'EDIT TOOLS'
    TabOrder = 4
    object Label16: TLabel
      Left = 312
      Top = 232
      Width = 68
      Height = 12
      Caption = 'Blend Value'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object GroupBox5: TGroupBox
      Left = 264
      Top = 16
      Width = 193
      Height = 150
      Caption = 'Frame Controller'
      TabOrder = 0
      object Label8: TLabel
        Left = 9
        Top = 18
        Width = 56
        Height = 12
        Caption = 'Animation'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 8
        Top = 38
        Width = 25
        Height = 12
        Caption = 'ACT'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Label10: TLabel
        Left = 8
        Top = 61
        Width = 19
        Height = 12
        Caption = 'DIR'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 3
        Top = 85
        Width = 36
        Height = 12
        Caption = 'Frame'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 6
        Top = 112
        Width = 29
        Height = 12
        Caption = 'Time'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Play_Edit_button: TButton
        Left = 80
        Top = 13
        Width = 49
        Height = 21
        Caption = '> Start'
        TabOrder = 0
        OnClick = Play_Edit_buttonClick
      end
      object Stop_Edit_button: TButton
        Left = 136
        Top = 13
        Width = 49
        Height = 21
        Caption = '|| Stop'
        TabOrder = 1
        OnClick = Stop_Edit_buttonClick
      end
      object EditNextAnimation: TButton
        Left = 136
        Top = 35
        Width = 49
        Height = 21
        Caption = '>>'
        TabOrder = 2
        OnClick = EditNextAnimationClick
      end
      object EditBeforeAnimation: TButton
        Left = 80
        Top = 35
        Width = 49
        Height = 21
        Caption = '<<'
        TabOrder = 3
        OnClick = EditBeforeAnimationClick
      end
      object Before_Edit_direction: TButton
        Left = 80
        Top = 57
        Width = 49
        Height = 21
        Caption = '<<'
        TabOrder = 4
        OnClick = Before_Edit_directionClick
      end
      object Next_Edit_direction: TButton
        Left = 136
        Top = 57
        Width = 49
        Height = 21
        Caption = '>>'
        TabOrder = 5
        OnClick = Next_Edit_directionClick
      end
      object Next_Edit_frame: TButton
        Left = 136
        Top = 79
        Width = 49
        Height = 21
        Caption = '>>'
        TabOrder = 6
        OnClick = Next_Edit_frameClick
      end
      object Before_Edit_frame: TButton
        Left = 80
        Top = 79
        Width = 49
        Height = 21
        Caption = '<<'
        TabOrder = 7
        OnClick = Before_Edit_frameClick
      end
      object EditAnimation: TEdit
        Left = 42
        Top = 34
        Width = 33
        Height = 21
        ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
        ReadOnly = True
        TabOrder = 8
        Text = '0'
      end
      object EditDirection: TEdit
        Left = 42
        Top = 57
        Width = 33
        Height = 21
        ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
        ReadOnly = True
        TabOrder = 9
        Text = '0'
      end
      object EditFrame: TEdit
        Left = 42
        Top = 79
        Width = 33
        Height = 21
        ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
        ReadOnly = True
        TabOrder = 10
        Text = '0'
      end
      object TrackBar1: TTrackBar
        Left = 42
        Top = 100
        Width = 145
        Height = 25
        Max = 10000
        Orientation = trHorizontal
        Frequency = 1
        Position = 0
        SelEnd = 0
        SelStart = 0
        TabOrder = 11
        ThumbLength = 15
        TickMarks = tmBottomRight
        TickStyle = tsAuto
        OnChange = TrackBar1Change
      end
      object Edit1: TEdit
        Left = 120
        Top = 124
        Width = 57
        Height = 21
        ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
        TabOrder = 12
        Text = '0'
        OnChange = Edit1Change
      end
      object Button2: TButton
        Left = 8
        Top = 125
        Width = 49
        Height = 21
        Caption = 'All Ani'
        TabOrder = 13
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 61
        Top = 125
        Width = 49
        Height = 21
        Caption = 'Now Ani'
        TabOrder = 14
        OnClick = Button3Click
      end
    end
    object GroupBox6: TGroupBox
      Left = 8
      Top = 16
      Width = 121
      Height = 49
      Caption = 'Now Frame Edit'
      TabOrder = 1
      object CopyEditFrame: TButton
        Left = 8
        Top = 16
        Width = 49
        Height = 25
        Caption = 'Copy'
        TabOrder = 0
        OnClick = CopyEditFrameClick
      end
      object DeleteEditFrame: TButton
        Left = 64
        Top = 16
        Width = 49
        Height = 25
        Caption = 'Delete'
        TabOrder = 1
        OnClick = DeleteEditFrameClick
      end
    end
    object GroupBox7: TGroupBox
      Left = 136
      Top = 16
      Width = 121
      Height = 49
      Caption = 'ACTION Edit'
      TabOrder = 2
      object InsDelAnimationButton: TButton
        Left = 8
        Top = 16
        Width = 105
        Height = 25
        Caption = 'Insert/Delete Func'
        TabOrder = 0
        OnClick = InsDelAnimationButtonClick
      end
    end
    object OutputType: TRadioGroup
      Left = 144
      Top = 168
      Width = 161
      Height = 97
      Caption = 'Now Frame Output Style'
      Columns = 2
      ItemIndex = 1
      Items.Strings = (
        'No Draw'
        'Normal'
        'Half Blend'
        'Lightning'
        'Smoke'
        'Screen'
        'Different'
        'Alpha Blend')
      TabOrder = 3
      OnClick = OutputTypeClick
    end
    object GroupBox8: TGroupBox
      Left = 144
      Top = 72
      Width = 113
      Height = 94
      Caption = 'Now Frame Position'
      TabOrder = 4
      object Label13: TLabel
        Left = 3
        Top = 20
        Width = 49
        Height = 11
        Caption = 'X ( L, R )'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Label14: TLabel
        Left = 3
        Top = 44
        Width = 51
        Height = 11
        Caption = 'Y ( U, D )'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Label15: TLabel
        Left = 3
        Top = 68
        Width = 49
        Height = 11
        Caption = 'Z ( F, B )'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
      end
      object Frame_X: TCSpinEdit
        Left = 61
        Top = 16
        Width = 49
        Height = 22
        TabOrder = 0
        OnChange = Frame_XChange
      end
      object Frame_Y: TCSpinEdit
        Left = 61
        Top = 40
        Width = 49
        Height = 22
        TabOrder = 1
        OnChange = Frame_YChange
      end
      object Frame_Z: TCSpinEdit
        Left = 61
        Top = 64
        Width = 49
        Height = 22
        TabOrder = 2
        OnChange = Frame_ZChange
      end
    end
    object GroupBox11: TGroupBox
      Left = 8
      Top = 72
      Width = 129
      Height = 193
      Caption = 'Now Frame Sound Edit'
      TabOrder = 5
      object SoundTreeView: TTreeView
        Left = 8
        Top = 48
        Width = 113
        Height = 137
        HideSelection = False
        Indent = 19
        ReadOnly = True
        TabOrder = 0
        OnDblClick = SoundTreeViewDblClick
      end
      object InsertSound: TButton
        Left = 3
        Top = 16
        Width = 41
        Height = 25
        Caption = 'Insert'
        TabOrder = 1
        OnClick = InsertSoundClick
      end
      object DeleteSound: TButton
        Left = 44
        Top = 16
        Width = 41
        Height = 25
        Caption = 'Delete'
        TabOrder = 2
        OnClick = DeleteSoundClick
      end
      object AllSoundDelete: TButton
        Left = 85
        Top = 16
        Width = 41
        Height = 25
        Caption = 'Initial'
        TabOrder = 3
        OnClick = AllSoundDeleteClick
      end
    end
    object BlendValue: TCSpinEdit
      Left = 312
      Top = 248
      Width = 65
      Height = 22
      EditorEnabled = False
      Enabled = False
      MaxValue = 31
      TabOrder = 6
      Value = 31
      OnChange = BlendValueChange
    end
    object GroupBox15: TGroupBox
      Left = 312
      Top = 168
      Width = 145
      Height = 57
      Caption = 'Direction Link'
      TabOrder = 7
      object DirectionLinkGap: TEdit
        Left = 8
        Top = 32
        Width = 33
        Height = 21
        Enabled = False
        ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
        ReadOnly = True
        TabOrder = 0
        Text = '0'
      end
      object DirectionLinkCheck: TCheckBox
        Left = 24
        Top = 16
        Width = 97
        Height = 17
        Caption = 'Now Dir Link'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #44404#47548
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = DirectionLinkCheckClick
      end
      object DirectionLinkBefore: TButton
        Left = 48
        Top = 32
        Width = 41
        Height = 17
        Caption = '<<'
        Enabled = False
        TabOrder = 2
        OnClick = DirectionLinkBeforeClick
      end
      object DirectionLinkNext: TButton
        Left = 96
        Top = 32
        Width = 41
        Height = 17
        Caption = '>>'
        Enabled = False
        TabOrder = 3
        OnClick = DirectionLinkNextClick
      end
    end
    object Button1: TButton
      Left = 384
      Top = 232
      Width = 73
      Height = 33
      Caption = 'Layer Color'
      TabOrder = 8
      OnClick = Button1Click
    end
  end
  object GroupBox9: TGroupBox
    Left = 808
    Top = 416
    Width = 193
    Height = 193
    Caption = 'Select Edit Layer / Sorting Layer'
    TabOrder = 5
    object Label12: TLabel
      Left = 16
      Top = 16
      Width = 115
      Height = 12
      Caption = 'Now Selected Layer'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      ParentFont = False
    end
    object Edit_ListBox: TListBox
      Left = 8
      Top = 74
      Width = 121
      Height = 111
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      ItemHeight = 13
      Items.Strings = (
        'Layer 1 ( no image )'
        'Layer 2 ( no image )'
        'Layer 3 ( no image )'
        'Layer 4 ( no image )'
        'Layer 5 ( no image )'
        'Layer 6 ( no image )'
        'Layer 7 ( no image )'
        'Layer 8 ( no image )')
      TabOrder = 0
      OnClick = Edit_ListBoxClick
    end
    object AllEditSelect: TCheckBox
      Left = 24
      Top = 57
      Width = 121
      Height = 17
      Caption = 'Select All Layer'
      TabOrder = 1
      OnClick = AllEditSelectClick
    end
    object Edit_Select: TEdit
      Left = 8
      Top = 32
      Width = 177
      Height = 21
      Enabled = False
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      TabOrder = 2
    end
    object SortUp: TButton
      Left = 131
      Top = 72
      Width = 57
      Height = 57
      Caption = 'Up'
      TabOrder = 3
      OnClick = SortUpClick
    end
    object SortDown: TButton
      Left = 131
      Top = 128
      Width = 57
      Height = 57
      Caption = 'Down'
      TabOrder = 4
      OnClick = SortDownClick
    end
  end
  object GroupBox10: TGroupBox
    Left = 808
    Top = 616
    Width = 193
    Height = 73
    Caption = 'Layer Sorting Data Copy'
    TabOrder = 6
    object Copy_AnimationSort: TButton
      Left = 8
      Top = 16
      Width = 177
      Height = 25
      Caption = 'To All Direction Now Action'
      TabOrder = 0
      OnClick = Copy_AnimationSortClick
    end
    object Copy_DirectionSort: TButton
      Left = 9
      Top = 44
      Width = 81
      Height = 25
      Caption = 'To Now DIR'
      TabOrder = 1
      OnClick = Copy_DirectionSortClick
    end
    object Copy_AllAnimationSort: TButton
      Left = 104
      Top = 44
      Width = 81
      Height = 25
      Caption = 'To All ACT'
      TabOrder = 2
      OnClick = Copy_AllAnimationSortClick
    end
  end
  object GroupBox12: TGroupBox
    Left = 112
    Top = 536
    Width = 209
    Height = 97
    Cursor = crHandPoint
    Caption = 'Final Data Read/Write'
    Color = clBtnFace
    Ctl3D = False
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 7
    object EditFileSave: TButton
      Left = 8
      Top = 56
      Width = 193
      Height = 25
      Cursor = crHandPoint
      Caption = 'Final Data(*.ina) File Saving'
      TabOrder = 0
      OnClick = EditFileSaveClick
    end
    object LoadAnimationInfo: TButton
      Left = 8
      Top = 24
      Width = 193
      Height = 25
      Cursor = crHandPoint
      Caption = '*.ina File Loading'
      TabOrder = 1
      OnClick = LoadAnimationInfoClick
    end
  end
  object GroupBox13: TGroupBox
    Left = 112
    Top = 640
    Width = 209
    Height = 49
    Caption = 'Background Skin'
    TabOrder = 8
    object Button26: TButton
      Left = 8
      Top = 16
      Width = 97
      Height = 25
      Caption = 'Color Change'
      TabOrder = 0
      OnClick = Button26Click
    end
    object BackLoading: TButton
      Left = 112
      Top = 16
      Width = 89
      Height = 25
      Caption = 'Back Image'
      TabOrder = 1
      OnClick = BackLoadingClick
    end
  end
  object GroupBox14: TGroupBox
    Left = 8
    Top = 416
    Width = 97
    Height = 273
    TabOrder = 9
    object Memo1: TMemo
      Left = 8
      Top = 48
      Width = 81
      Height = 217
      TabStop = False
      Alignment = taCenter
      Enabled = False
      ImeName = #54620#44397#50612' '#51077#47141' '#49884#49828#53596' (IME 2000)'
      Lines.Strings = (
        'Animation Tool'
        'version 2.00'
        '(8'#50900' 25'#51068')'
        'Created by'
        'head77x')
      TabOrder = 0
    end
    object FramePerSecond: TRadioGroup
      Left = 8
      Top = 8
      Width = 81
      Height = 33
      Caption = 'Refresh Rate'
      ItemIndex = 0
      Items.Strings = (
        '30 fps')
      TabOrder = 1
    end
  end
  object MainMenu1: TMainMenu
    Top = 672
    object N1: TMenuItem
      Caption = 'File'
      object New1: TMenuItem
        Caption = 'New'
        OnClick = New1Click
      end
      object Close1: TMenuItem
        Caption = 'Close'
        OnClick = Close1Click
      end
    end
    object N2: TMenuItem
      Caption = 'Tool'
      object N3: TMenuItem
        Caption = 'Full Screen'
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = 'Original Screen'
        OnClick = N4Click
      end
    end
  end
  object OpenAN3: TOpenDialog
    DefaultExt = '*.AN3'
    FileName = '*.AN3'
    Filter = 'Source Image File|*.AN3'
    InitialDir = '.\AN_files'
    Options = [ofReadOnly, ofNoChangeDir, ofEnableSizing]
    Title = 'Source Image( *.AN3 files ) Loading'
    Left = 216
    Top = 8
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Options = [cdFullOpen]
    Left = 216
    Top = 48
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Options = [ofNoChangeDir, ofEnableSizing]
    Title = 'Background Skin Image Loading'
    Left = 216
    Top = 88
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.ina'
    FileName = 'noname.ina'
    Filter = 'Animation Info File|*.ina'
    InitialDir = 'result'
    Options = [ofNoChangeDir, ofEnableSizing]
    Title = 'Final Data File Saving'
    Left = 216
    Top = 128
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.ina'
    FileName = '*.ina'
    Filter = 'Animation Info File|*.ina'
    InitialDir = '.\result'
    Options = [ofReadOnly, ofNoChangeDir, ofEnableSizing]
    Title = 'Final Data( *.ina file ) Loading'
    Left = 216
    Top = 168
  end
end
