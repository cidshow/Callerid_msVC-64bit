# include <stdio.h>
 
#include <string>
#include <stdafx.h>
 
#include <tchar.h>
#include <windows.h> 
#include <conio.h> 
#include <iostream>
#include <fstream>

 

 using namespace std;

typedef void(__cdecl *_CallerID)(LPWSTR   DeviceSerial, LPWSTR   Line, LPWSTR   PhoneNumber, LPWSTR   DateTime, LPWSTR   Other );
typedef void(__cdecl *_Signal)(LPWSTR   DeviceModel, LPWSTR   DeviceSerial, int Signal1, int Signal2, int Signal3, int Signal4 );
typedef void(__cdecl *_SetEvents)(_CallerID CallerIDEvent, _Signal SignalEvent);

_CallerID CallerID1;
_Signal Signal1;
_SetEvents SetEvents1;


void CallerIDEvent(LPWSTR   DeviceSerial, LPWSTR   Line, LPWSTR   PhoneNumber, LPWSTR   DateTime, LPWSTR   Other)
{
	static int counter = 0;


	counter++;
	wcout << "    CallerID: " << PhoneNumber << "   DateTime: " << DateTime << "   Counter: " << (int)counter << endl;
 

}

void SignalEvent(LPWSTR   DeviceModel, LPWSTR   DeviceSerial, int Signal1, int Signal2, int Signal3, int Signal4)
{
	static int connected = 0;
 
//	wcout << "    DeviceModel: " << DeviceModel << "   DeviceSerial: " << DeviceSerial << endl;
 


	if (  (DeviceModel == NULL || DeviceModel[0] == 0))
	  {

		if (connected == 1){
			wcout << "    Device disconnected\n" << endl;
			 
		}

		connected = 0;
 
	}
	else {

		if (connected == 0){
			wcout << "    Device Connected:  Model: " << DeviceModel << "  Serial: " << DeviceSerial << "\n" << endl;
			connected = 1;
		}

	}
 
	

 
 
}
 
int main(int argc, char** argv) {

	HINSTANCE hinstLib;
	
	BOOL  fRunTimeLinkSuccess = FALSE;

	wcout << "\n\n    ***************** CIDSHOW Caller ID *****************\n\n";
 




	hinstLib = LoadLibrary(TEXT("cid.dll"));
	//	hinstLib = LoadLibrary(TEXT("..\\..\\..\\cid.dll"));

	if (hinstLib != NULL)
	{
		SetEvents1 = (_SetEvents)GetProcAddress(hinstLib, "SetEvents");

		if (SetEvents1 != NULL)

		{
			CallerID1 = (_CallerID)  CallerIDEvent;
			Signal1 = (_Signal) SignalEvent;

			 SetEvents1(CallerID1, Signal1);
		 

			 fstream file("softtest.txt");

			 if (file.good())
			 {
				 std::cout << "\n\n    Softtest enabled." << endl;
			 }


			fRunTimeLinkSuccess = TRUE;
			wcout << "    Ready for test call..\n\n" ;


		}

		//  fFreeResult = FreeLibrary(hinstLib);
	}


	if (fRunTimeLinkSuccess == FALSE)
	{

 
		wcout << "\n\n    DLL error" ;
		wcout << "\n\n    Press any key to exit...";
	}



//	wcout << "\n\n    Press any key to exit..." ;

 

	_getch();
 
	//	fFreeResult = FreeLibrary(hinstLib); //?
 
 
	return 0;
}