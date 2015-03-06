//---------------------------------------------------------------------------

// Persistent values are stored in the registry via this class.
// Implemented as singleton class so all instances refer to the same object.
// H.Zimmerman, 17 november 2012.

//---------------------------------------------------------------------------

#ifndef StorageH
#define StorageH

//---------------------------------------------------------------------------

#include <Vcl.h>

//---------------------------------------------------------------------------

class TStorage
{
private:
protected:
	TStorage();
	TStorage(const TStorage& Rhs);
	TStorage& operator = (const TStorage&);
public:
	static TStorage* Instance();
	~TStorage();

	int GetValue(const AnsiString Key, const int DefaultValue);
	double GetValue(const AnsiString Key, const double DefaultValue);
	void PutValue(const AnsiString Key, const int Value);
	void PutValue(const AnsiString Key, const double Value);
};

//---------------------------------------------------------------------------

#endif

//---------------------------------------------------------------------------

