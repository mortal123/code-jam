:loop
gen.exe
code.exe
cmp.exe
fc output.txt output2.txt
if %errorlevel%==0 goto loop
pause