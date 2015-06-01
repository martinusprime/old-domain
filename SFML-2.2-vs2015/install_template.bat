@echo off
set location="%USERPROFILE%\Documents\Visual Studio 2015\Templates\ProjectTemplates\Visual C++ Project"
echo Installing template to %location% ...
xcopy "SFML-TEMPLATE.zip" %location%
pause