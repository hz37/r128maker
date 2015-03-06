//---------------------------------------------------------------------------

#include "Generic.h"
#pragma hdrstop

//---------------------------------------------------------------------------

#include "SettingsUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------

TSettingsForm *SettingsForm;

//---------------------------------------------------------------------------

__fastcall TSettingsForm::TSettingsForm(TComponent* Owner) :
	TForm(Owner),
	FStorage(TStorage::Instance())
{
	LoadSettings();
}

//---------------------------------------------------------------------------

void TSettingsForm::LoadSettings()
{
	RefLevelUpDown->Position = FStorage->GetValue
	(
		CDefaultRefLevelKey, CDefaultRefLevel
	);

	DeviationMaskEdit->Text = AnsiString().sprintf
	(
		"%.3f",
		FStorage->GetValue(CDefaultAllowedDeviationKey, CDefaultAllowedDeviation)
	);

	TruePeakUpDown->Position = FStorage->GetValue
	(
		CDefaultTruePeakLevelKey, CDefaultTruePeakLevel
	);

	BufferSizeUpDown->Position = FStorage->GetValue
	(
		CDefaultBufferSizeKey, CDefaultBufferSize
	);

	OversampleCheckBox->Checked = FStorage->GetValue
	(
		CDefaultOversampleKey, CDefaultOversample
	);

	MethodComboBox->ItemIndex = FStorage->GetValue
	(
		CDefaultOversampleMethodKey, CDefaultOversampleMethod
	);

	SkipOversamplingCheckBox->Checked = FStorage->GetValue
	(
		CDefaultSkipOversamplingKey, CDefaultSkipOversampling
	);

	SkipPeakUpDown->Position = FStorage->GetValue
	(
		CDefaultSkipOversamplingPeakKey, CDefaultSkipOversamplingPeak
	);

	DoNotCheckAgainCheckBox->Checked = FStorage->GetValue
	(
		CDefaultDoNotCheckAgainKey, CDefaultDoNotCheckAgain
	);

	PriorityComboBox->ItemIndex = FStorage->GetValue
	(
    	CDefaultPriorityKey, CDefaultPriority
	);

	UpdateControlsEnabled();
}

//---------------------------------------------------------------------------

void __fastcall TSettingsForm::OKBitBtnClick(TObject *Sender)
{
	SaveSettings();
}

//---------------------------------------------------------------------------

void __fastcall TSettingsForm::OversampleCheckBoxClick(TObject *Sender)
{
	UpdateControlsEnabled();
}

//---------------------------------------------------------------------------

void TSettingsForm::SaveSettings()
{
	FStorage->PutValue(CDefaultRefLevelKey, RefLevelUpDown->Position);

	try
	{
		double AllowedDeviation = DeviationMaskEdit->Text.ToDouble();
		FStorage->PutValue(CDefaultAllowedDeviationKey, AllowedDeviation);
	}
	catch(...)
	{
		FStorage->PutValue(CDefaultAllowedDeviationKey, CDefaultAllowedDeviation);
	}

	FStorage->PutValue(CDefaultTruePeakLevelKey, TruePeakUpDown->Position);

	FStorage->PutValue(CDefaultBufferSizeKey, BufferSizeUpDown->Position);

	FStorage->PutValue
	(
		CDefaultOversampleKey, OversampleCheckBox->Checked ? 1 : 0
	);

	FStorage->PutValue(CDefaultOversampleMethodKey, MethodComboBox->ItemIndex);

	FStorage->PutValue
	(
		CDefaultSkipOversamplingKey,
		SkipOversamplingCheckBox->Checked ? 1 : 0
	);

	FStorage->PutValue
	(
		CDefaultSkipOversamplingPeakKey,
		SkipPeakUpDown->Position
	);

	FStorage->PutValue
	(
		CDefaultDoNotCheckAgainKey,
		DoNotCheckAgainCheckBox->Checked ? 1 : 0
	);

	FStorage->PutValue
	(
		CDefaultPriorityKey,
		PriorityComboBox->ItemIndex
	);
}

//---------------------------------------------------------------------------

void __fastcall TSettingsForm::SkipOversamplingCheckBoxClick(TObject *Sender)
{
	UpdateControlsEnabled();
}

//---------------------------------------------------------------------------

// Determine which controls should be enabled based on other choices.

void TSettingsForm::UpdateControlsEnabled()
{
	// Are we oversampling?

	bool Oversampling = OversampleCheckBox->Checked;

	// Are we skipping oversampling based on peaks?

	bool SkipOversampling = SkipOversamplingCheckBox->Checked;

	MethodComboBox->Enabled = Oversampling;
	SkipOversamplingCheckBox->Enabled = Oversampling;
	SkipPeakEdit->Enabled = Oversampling && SkipOversampling;
	SkipPeakUpDown->Enabled = Oversampling && SkipOversampling;

	// This last one is just for cosmetic reasons.

	AfterGainLabel->Enabled = Oversampling;
}

//---------------------------------------------------------------------------

