
@SET VSINSTALLDIR=D:\Program Files (x86)\Microsoft Visual Studio 11.0
@SET VCINSTALLDIR=D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC
@SET FrameworkDir=C:\WINDOWS\Microsoft.NET\Framework
@rem @SET FrameworkVersion=v2.0.50727
@rem @SET Framework35Version=v3.5
@if "%VSINSTALLDIR%"=="" goto error_no_VSINSTALLDIR
@if "%VCINSTALLDIR%"=="" goto error_no_VCINSTALLDIR

@echo Setting environment for using Microsoft Visual Studio 2008 x86 tools.

@call :GetWindowsSdkDir

@if not "%WindowsSdkDir%" == "" (
	set "PATH=%WindowsSdkDir%bin;%PATH%"
	set "INCLUDE=%WindowsSdkDir%include;%INCLUDE%"
	set "LIB=%WindowsSdkDir%lib;%LIB%"
)


@rem
@rem Root of Visual Studio IDE installed files.
@rem
@set DevEnvDir=D:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE
@set PATH=D:\Program Files\CMake\bin;%PATH%
@set PATH=D:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE;D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\BIN;D:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools;C:\WINDOWS\Microsoft.NET\Framework\v3.5;C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\VCPackages;%PATH%
@set INCLUDE=D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\ATLMFC\INCLUDE;D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\INCLUDE;%INCLUDE%
@set LIB=D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\ATLMFC\LIB;D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\LIB;%LIB%
@set LIBPATH=C:\WINDOWS\Microsoft.NET\Framework\v3.5;C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\ATLMFC\LIB;D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\LIB;%LIBPATH%

@goto end

:GetWindowsSdkDir
@call :GetWindowsSdkDirHelper HKLM > nul 2>&1
@if errorlevel 1 call :GetWindowsSdkDirHelper HKCU > nul 2>&1
@if errorlevel 1 set WindowsSdkDir=%VCINSTALLDIR%\PlatformSDK\
@exit /B 0

:GetWindowsSdkDirHelper
@for /F "tokens=1,2*" %%i in ('reg query "%1\SOFTWARE\Microsoft\Microsoft SDKs\Windows" /v "CurrentInstallFolder"') DO (
	if "%%i"=="CurrentInstallFolder" (
		SET "WindowsSdkDir=%%k"
	)
)
@if "%WindowsSdkDir%"=="" exit /B 1
@exit /B 0

:error_no_VSINSTALLDIR
@echo ERROR: VSINSTALLDIR variable is not set. 
@goto end

:error_no_VCINSTALLDIR
@echo ERROR: VCINSTALLDIR variable is not set. 
@goto end

:end


cmake -G "NMake Makefiles" .
nmake