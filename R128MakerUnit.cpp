//---------------------------------------------------------------------------

#include "Generic.h"
#pragma hdrstop

// Next one (for oversampling) below hdrstop because code in headers.

#include "samplerate.h"
#include "R128MakerUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

//---------------------------------------------------------------------------

// ID for the menu item.

static const int CSettingsMenuID = 0;

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// Attach an instance of the storage class.

	FStorage = TStorage::Instance();

	// Add a settings menu to the system menu.

	AddSettings(Handle);

	// This program allows for dropped files.

	DragAcceptFiles(Handle, true);

	// Restore form position and size.

	Left = FStorage->GetValue("Left", 40);
	Top = FStorage->GetValue("Top", 40);
	Width = FStorage->GetValue("Width", 400);
	Height = FStorage->GetValue("Height", 350);

	// Load and report user settings.

	LoadSettings();
	SetPriority(FPriority);
	ReportSettings();
}

//---------------------------------------------------------------------------

void TForm1::AddSettings(HWND Window)
{
	HMENU SystemMenu = GetSystemMenu(Window, false);

	if(!SystemMenu)
	{
		return;
	}

	static char MenuString[] = "Settings...";

	MENUITEMINFO MenuItemInfo;

	MenuItemInfo.cbSize        = sizeof(MENUITEMINFO);
	MenuItemInfo.fMask         = MIIM_ID | MIIM_TYPE;
	MenuItemInfo.fType         = MFT_STRING;
	MenuItemInfo.fState        = MFS_DEFAULT;
	MenuItemInfo.wID           = CSettingsMenuID;
	MenuItemInfo.hSubMenu      = 0;
	MenuItemInfo.hbmpChecked   = 0;
	MenuItemInfo.hbmpUnchecked = 0;
	MenuItemInfo.dwItemData    = 0;
	MenuItemInfo.dwTypeData    = reinterpret_cast <LPTSTR> (MenuString);
	MenuItemInfo.cch           = lstrlen(MenuString);
	MenuItemInfo.hbmpItem      = 0;

	int MenuItems = GetMenuItemCount(SystemMenu);

	InsertMenuItem
	(
		SystemMenu,
		MenuItems,
		true,
		&MenuItemInfo
	);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	// Save form position and size for next run.

	FStorage->PutValue("Left", Left);
	FStorage->PutValue("Top", Top);
	FStorage->PutValue("Width", Width);
	FStorage->PutValue("Height", Height);
}

//---------------------------------------------------------------------------

// Gain Filename dB decibels.
// Throws exception on error.
// A backup of the original file is made.

void TForm1::Gain(const AnsiString Filename, const float dB)
{
	// Calculate gain factor.

	float GainFactor = pow(10.0, dB / 20.0);

	// Make a backup of the inputfile.

	AnsiString BackupFilename = Filename + "_backup.wav";

	if(!MoveFile(Filename.c_str(), BackupFilename.c_str()))
	{
		throw Exception("Error renaming file (backup already exists?).");
	}

	// Attempt to open the input file.

	SF_INFO FileInfo;
	memset(&FileInfo, 0, sizeof(FileInfo));

	SNDFILE* InputFile = sf_open(BackupFilename.c_str(), SFM_READ, &FileInfo);

	if(!InputFile)
	{
		throw Exception("Error opening " + BackupFilename);
	}

	// Attempt to open the output file.

	SF_INFO FileInfo2;
	memset(&FileInfo2, 0, sizeof(FileInfo2));

	FileInfo2.samplerate = FileInfo.samplerate;
	FileInfo2.channels = FileInfo.channels;
	FileInfo2.format = FileInfo.format;

	SNDFILE* OutputFile = sf_open(Filename.c_str(), SFM_WRITE, &FileInfo2);

	if(!OutputFile)
	{
		sf_close(InputFile);

		throw Exception("Error creating " + Filename);
	}

	const int Channels = FileInfo.channels;
	const int Samplerate = FileInfo.samplerate;

	// 1 second buffer. Buffersize maybe should be different.

	const int BufferSize = FBufferSize * Channels * Samplerate;

	float* Buffer = new float[BufferSize];

	sf_count_t FramesRead;

	do
	{
		FramesRead = sf_readf_float(InputFile, Buffer, Samplerate * FBufferSize);

		// Apply gain.

		const int SampleCount = Channels * FramesRead;

		for(int Idx = 0; Idx < SampleCount; ++Idx)
		{
        	Buffer[Idx] *= GainFactor;
        }

		// Save.

		sf_writef_float(OutputFile, Buffer, FramesRead);
	} while(FramesRead);

	delete [] Buffer;

	// Close output file.

	sf_close(OutputFile);

	// Close input file.

	sf_close(InputFile);
}

//---------------------------------------------------------------------------

// Fetch persistent settings.

void TForm1::LoadSettings()
{
	FRefLevel = FStorage->GetValue
	(
		CDefaultRefLevelKey, CDefaultRefLevel
	);

	FAllowedDeviation = FStorage->GetValue
	(
		CDefaultAllowedDeviationKey, CDefaultAllowedDeviation
	);

	FTruePeakLevel = FStorage->GetValue
	(
		CDefaultTruePeakLevelKey, CDefaultTruePeakLevel
	);

	FBufferSize = FStorage->GetValue
	(
		CDefaultBufferSizeKey, CDefaultBufferSize
	);

	FOversample = FStorage->GetValue
	(
		CDefaultOversampleKey, CDefaultOversample
	);

	FOversampleMethod = FStorage->GetValue
	(
		CDefaultOversampleMethodKey, CDefaultOversampleMethod
	);

	FDoNotCheckAgain = FStorage->GetValue
	(
		CDefaultDoNotCheckAgainKey, CDefaultDoNotCheckAgain
	);

	FSkipOversample = FStorage->GetValue
	(
		CDefaultSkipOversamplingKey, CDefaultSkipOversampling
	);

	FSkipPeak = FStorage->GetValue
	(
		CDefaultSkipOversamplingPeakKey, CDefaultSkipOversamplingPeak
	);

	FPriority = FStorage->GetValue
	(
		CDefaultPriorityKey, CDefaultPriority
	);
}

//---------------------------------------------------------------------------

// Doubleclick will reveal who made this.

void __fastcall TForm1::OutputMemoDblClick(TObject *Sender)
{
	OutputMemo->Color = clWhite;
	OutputMemo->Clear();
	OutputMemo->Lines->Add("Programming by Hens Zimmerman");
	OutputMemo->Lines->Add("");
	OutputMemo->Lines->Add
	(
		"LIBSNDFILE and SECRET RABBIT CODE by Erik de Castro Lopo"
	);

	char Version[128] ;
	sf_command(0, SFC_GET_LIB_VERSION, Version, sizeof(Version));

	OutputMemo->Lines->Add
	(
		AnsiString().sprintf("LIBSNDFILE version: %s", Version)
	);
}

//---------------------------------------------------------------------------

void TForm1::Process(const AnsiString Filename)
{
	if(ExtractFileExt(Filename).LowerCase() != ".wav")
	{
		OutputMemo->Lines->Add("Skipping " + Filename + " => not a *.wav file");
		return;
	}

	OutputMemo->Lines->Add(" ");
	OutputMemo->Lines->Add("Processing " + Filename);

	AnsiString PeakMeasurement = FOversample ? "True peak" : "Max peak";
	AnsiString PeakQualifier = FOversample ? "dBTP" : "dBFS";

	try
	{
		// Find current LUFS, peak and true peak of Filename.

		float LUFS = 0.0;
		float TruePeak = 0.0;
		int Channels;
		int Samplerate;

		Stats
		(
			Filename,
			LUFS,
			TruePeak,
			Channels,
			Samplerate,
			FOversample && !FSkipOversample);

		OutputMemo->Lines->Add
		(
			AnsiString().sprintf
			(
				"%d channel%s, %d Hz samplerate",
				Channels,
				Channels > 1 ? "s" : "",
				Samplerate
			)
		);

		OutputMemo->Lines->Add
		(
			AnsiString().sprintf
			(
				"Integrated loudness: %f LUFS, %s: %f %s",
				LUFS,
				PeakMeasurement,
				TruePeak,
				PeakQualifier
			)
		);

		float Difference = FRefLevel - LUFS;

		// We may now have to perform oversampling after all.

		if(	FOversample && FSkipOversample &&
			((TruePeak + Difference) > FSkipPeak))
		{
			OutputMemo->Lines->Add("Checking again with oversampling.");

			Stats(Filename, LUFS, TruePeak, Channels, Samplerate, true);

			OutputMemo->Lines->Add
			(
				AnsiString().sprintf
				(
					"Integrated loudness: %f LUFS, %s: %f %s",
					LUFS,
					PeakMeasurement,
					TruePeak,
					PeakQualifier
				)
			);
		}

		if(fabs(Difference) > FAllowedDeviation)
		{
			if(TruePeak + Difference > FTruePeakLevel)
			{
				OutputMemo->Lines->Add
				(
					"Skipping => Correcting this will result in clipping distortion (you've mixed too soft)!"
				);

				FAllIsFine = false;
			}
			else
			{
				OutputMemo->Lines->Add
				(
					AnsiString().sprintf("Applying %f dB gain.", Difference)
				);

				Gain(Filename, Difference);

				if(!FDoNotCheckAgain)
				{
					LUFS = 0.0;
					TruePeak = 0.0;

					Stats
					(
						Filename,
						LUFS,
						TruePeak,
						Channels,
						Samplerate,
						FOversample && !FSkipOversample
					);

					OutputMemo->Lines->Add
					(
						AnsiString().sprintf
						(
							"Integrated loudness: %f LUFS, %s: %f %s",
							LUFS,
							PeakMeasurement,
							TruePeak,
							PeakQualifier
						)
					);
				}
			}
		}
		else
		{
			// LUFS within range. But true peak too?

			if(TruePeak > FTruePeakLevel)
			{
				OutputMemo->Lines->Add
				(
					AnsiString().sprintf
					(
						"True peak level (%f dBTP) higher than allowed (%f dBTP)!",
						TruePeak,
						FTruePeakLevel
					)
				);
				
				FAllIsFine = false;
			}
		}
	}
	catch(Exception& E)
	{
		OutputMemo->Lines->Add(E.Message);
		
		FAllIsFine = false;
	}
}

//---------------------------------------------------------------------------

// Report the current state of affairs.

void TForm1::ReportSettings()
{
	OutputMemo->Clear();
	
	OutputMemo->Lines->Add("Current settings:");
	OutputMemo->Lines->Add
	(
		AnsiString().sprintf("Integrated loudness level: %f LUFS", FRefLevel)
	);
	OutputMemo->Lines->Add
	(
		AnsiString().sprintf("Allowed deviation (+/-): %f LU", FAllowedDeviation)
	);
	OutputMemo->Lines->Add
	(
		AnsiString().sprintf("Max true peak level: %f dBTP", FTruePeakLevel)
	);
	OutputMemo->Lines->Add
	(
		AnsiString().sprintf("Buffer size: %d seconds", FBufferSize)
	);

	if(FOversample)
	{
		AnsiString Method;
		
		switch(FOversampleMethod)
		{
			case 0:
				Method = "best";
				break;
			case 1:
				Method = "medium";
				break;
			case 2:
				Method = "fastest";
				break;
		}

		OutputMemo->Lines->Add
		(
			AnsiString().sprintf("Oversampling - %s sinc interpolator", Method)
		);
	}
	else
	{
		OutputMemo->Lines->Add("No oversampling (linear interpolation)");
	}

	AnsiString WindowsPriority;

	switch(FPriority)
	{
		case 0:
			WindowsPriority = "ABOVE_NORMAL_PRIORITY_CLASS";
			break;
		case 1:
			WindowsPriority = "BELOW_NORMAL_PRIORITY_CLASS";
			break;
		case 2:
			WindowsPriority = "HIGH_PRIORITY_CLASS";
			break;
		case 3:
			WindowsPriority = "IDLE_PRIORITY_CLASS";
			break;
		case 4:
			WindowsPriority = "NORMAL_PRIORITY_CLASS";
			break;
		case 5:
			WindowsPriority = "REALTIME_PRIORITY_CLASS";
			break;
	}

	OutputMemo->Lines->Add("Running " + WindowsPriority);

	OutputMemo->Lines->Add(" ");
	OutputMemo->Lines->Add("Drop a *.wav (or a whole bunch) here...");
}

//---------------------------------------------------------------------------

// Set process priority. Must translate Priority to Windows number.

void TForm1::SetPriority(const int Priority)
{
	DWORD WindowsPriority;

	switch(Priority)
	{
		case 0:
			WindowsPriority = ABOVE_NORMAL_PRIORITY_CLASS;
			break;
		case 1:
			WindowsPriority = BELOW_NORMAL_PRIORITY_CLASS;
			break;
		case 2:
			WindowsPriority = HIGH_PRIORITY_CLASS;
			break;
		case 3:
			WindowsPriority = IDLE_PRIORITY_CLASS;
			break;
		case 4:
			WindowsPriority = NORMAL_PRIORITY_CLASS;
			break;
		case 5:
			WindowsPriority = REALTIME_PRIORITY_CLASS;
			break;
	}

	if(!SetPriorityClass(GetCurrentProcess(), WindowsPriority))
	{
		OutputMemo->Lines->Add("Error switching priority.");
	}
}

//---------------------------------------------------------------------------

// Return error message that describes what has occurred in SndFile.

AnsiString TForm1::SndFileError(SNDFILE* SndFile)
{
	AnsiString ReturnValue = "Unknown error";

	switch(sf_error(SndFile))
	{
		case SF_ERR_NO_ERROR:
			ReturnValue = "SF_ERR_NO_ERROR";
			break;
		case SF_ERR_UNRECOGNISED_FORMAT:
			ReturnValue = "SF_ERR_UNRECOGNISED_FORMAT";
			break;
		case SF_ERR_SYSTEM:
			ReturnValue = "SF_ERR_SYSTEM (file not found?)";
			break;
		case SF_ERR_MALFORMED_FILE:
			ReturnValue = "SF_ERR_MALFORMED_FILE";
			break;
		case SF_ERR_UNSUPPORTED_ENCODING:
			ReturnValue = "SF_ERR_UNSUPPORTED_ENCODING";
			break;
		}

	return ReturnValue;
}

//---------------------------------------------------------------------------

// Return R128 EBU LUFS, peak (dBFS) or true peak (dBTP) of Filename.
// Throws an exception if this fails.

void TForm1::Stats
(
	const AnsiString Filename,
	float& LUFS,
	float& Peak,
	int& Channels,
	int& Samplerate,
	const bool Oversample
)
{
	// Attempt to open the input file.

	SF_INFO FileInfo;
	memset(&FileInfo, 0, sizeof(FileInfo));

	SNDFILE* InputFile = sf_open(Filename.c_str(), SFM_READ, &FileInfo);

	if(!InputFile)
	{
		throw Exception("Error opening " + Filename);
	}

	Channels = FileInfo.channels;
	Samplerate = FileInfo.samplerate;

	// Initialize EBU R128 lib.

	ebur128_state* EBUR128State = ebur128_init
	(
		Channels,
		Samplerate,
		EBUR128_MODE_I // == gated.
	);

    // FBufferSize == seconds (from user settings).

	const int BufferSize = Samplerate * FBufferSize;

	float* Buffer = new float[BufferSize * Channels];
	float* SrcBuffer = new float[BufferSize * Channels * COversampleRatio];

	sf_count_t FramesRead;

	// Reset max amplitude.

	float MaxAmplitude = 0.0;

	// SRC oversampling.

	SRC_DATA SrcData;
	SRC_STATE* SrcState;

	SrcData.end_of_input = 0;

	int Error = 0;

	// Initialize the sample rate converter.

	if(Oversample)
	{
		SrcState = src_new(FOversampleMethod, Channels, &Error);

		if(!SrcState)
		{
			throw Exception
			(
				AnsiString().sprintf
				(
					"Error: src_new() failed: %s", src_strerror(Error)
				)
			);
		}

		SrcData.data_in = Buffer;
		SrcData.src_ratio = COversampleRatio;
		SrcData.data_out = SrcBuffer;
		SrcData.output_frames = BufferSize * COversampleRatio / Channels;

		OutputMemo->Lines->Add
		(
			AnsiString().sprintf
			(
				"Oversampling frequency: %d Hz", Samplerate * COversampleRatio
			)
		);
	}

	// Start looping through this file.

	do
	{
		FramesRead = sf_readf_float(InputFile, Buffer, BufferSize);

		if(Oversample)
		{
			SrcData.input_frames = FramesRead;

			Error = src_process(SrcState, &SrcData);
		}

		ebur128_add_frames_float
		(
			EBUR128State,
			Buffer,
			static_cast <size_t> (FramesRead)
		);

		const int Count = FramesRead * Channels;

		for(int Idx = 0; Idx < Count; ++Idx)
		{
			MaxAmplitude = std::max
			(
				MaxAmplitude,
				Oversample ? SrcBuffer[Idx] : Buffer[Idx]
			);
		}
	} while(FramesRead);

	// Update input vars.

	LUFS = ebur128_loudness_global(EBUR128State);

	// Guard against sing errors.

	Peak = MaxAmplitude ? 20.0 * log10(MaxAmplitude) : 0.0;

	delete [] SrcBuffer;
	delete [] Buffer;

	// Close input file.

	sf_close(InputFile);

	// Done with the EBU state.

	ebur128_destroy(&EBUR128State);

	// Done with SRC.

	if(Oversample)
	{
		src_delete(SrcState) ;
	}
}

//---------------------------------------------------------------------------

// Low level Windows event when one or more files are dropped onto our form.

void __fastcall TForm1::WmDropFiles(TWMDropFiles& Message)
{
	Screen->Cursor = crHourGlass;

	HDROP DropHandle = reinterpret_cast <HDROP> (Message.Drop);

	const int FileCount = DragQueryFile
	(
		reinterpret_cast <HDROP> (Message.Drop),
		0xFFFFFFFF,
		0,
		0
	);

	// Reset flag.

	FAllIsFine = true;

	// Process files.

	for(int Idx = 0; Idx < FileCount; ++Idx)
	{
		char Buffer[MAX_PATH];

		DragQueryFile(DropHandle, Idx, Buffer, sizeof(Buffer));
		Process(Buffer);
	}

	DragFinish(DropHandle);

	OutputMemo->Color = FAllIsFine ? clGreen : clRed;

	Screen->Cursor = crDefault;

	if(FileCount > 1)
	{
		OutputMemo->Lines->Add("");
		
		OutputMemo->Lines->Add
		(
			AnsiString().sprintf("Done processing %d files.", FileCount)
		);
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::WMSysCommand(TMessage& Message)
{

	if((Message.WParam & 0xfff0) == CSettingsMenuID)
	{
		// Ah! Someone clicked our menu item.

		std::auto_ptr <TSettingsForm> SettingsForm(new TSettingsForm(0));

		SettingsForm->ShowModal();

		// Reload and report user settings.

		LoadSettings();
		SetPriority(FPriority);
		ReportSettings();
	}

	TForm::Dispatch(&Message);
}

//---------------------------------------------------------------------------

