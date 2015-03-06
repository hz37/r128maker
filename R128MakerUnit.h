//---------------------------------------------------------------------------

#ifndef R128MakerUnitH
#define R128MakerUnitH

//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Storage.h"
#include "sndfile.h"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *OutputMemo;
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall OutputMemoDblClick(TObject *Sender);
	
private:	// User declarations
	TStorage* FStorage;

	// Flag to color interface according to success.

	bool FAllIsFine;

	float FRefLevel;
	float FAllowedDeviation;
	float FTruePeakLevel;
	int FBufferSize;
	bool FOversample;
	int FOversampleMethod;
	bool FDoNotCheckAgain;
	bool FSkipOversample;
	float FSkipPeak;
	int FPriority;

	void AddSettings(HWND Window);
	void Gain(const AnsiString Filename, const float dB);
	void LoadSettings();
	void Process(const AnsiString Filename);
	void ReportSettings();
	void SetPriority(const int Priority);
	AnsiString SndFileError(SNDFILE*);
	void Stats
	(
		const AnsiString Filename,
		float& LUFS,
		float& Peak,
		int& Channels,
		int& Samplerate,
		const bool Oversample
	);
	void __fastcall WmDropFiles(TWMDropFiles& Message);
	void __fastcall WMSysCommand(TMessage& Message);

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

		// Message map to intercept Windows messages.

	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WmDropFiles)
		MESSAGE_HANDLER(WM_SYSCOMMAND, TMessage, WMSysCommand)
	END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
