//---------------------------------------------------------------------------

#ifndef SettingsUnitH
#define SettingsUnitH

//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>

#include "Storage.h"

//---------------------------------------------------------------------------

class TSettingsForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *OversampleCheckBox;
	TComboBox *MethodComboBox;
	TBitBtn *OKBitBtn;
	TEdit *RefLevelEdit;
	TMaskEdit *DeviationMaskEdit;
	TEdit *TruePeakEdit;
	TEdit *BufferSizeEdit;
	TUpDown *RefLevelUpDown;
	TUpDown *TruePeakUpDown;
	TUpDown *BufferSizeUpDown;
	TCheckBox *SkipOversamplingCheckBox;
	TEdit *SkipPeakEdit;
	TUpDown *SkipPeakUpDown;
	TCheckBox *DoNotCheckAgainCheckBox;
	TLabel *AfterGainLabel;
	TComboBox *PriorityComboBox;
	void __fastcall OKBitBtnClick(TObject *Sender);
	void __fastcall OversampleCheckBoxClick(TObject *Sender);
	void __fastcall SkipOversamplingCheckBoxClick(TObject *Sender);
	
private:	// User declarations
	TStorage* FStorage;

	void LoadSettings();
	void UpdateControlsEnabled();
	void SaveSettings();

public:		// User declarations
	__fastcall TSettingsForm(TComponent* Owner);
};

//---------------------------------------------------------------------------

extern PACKAGE TSettingsForm *SettingsForm;

//---------------------------------------------------------------------------

#endif

//---------------------------------------------------------------------------

