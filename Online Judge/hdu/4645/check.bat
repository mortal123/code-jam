:loop
make
force
code
fc output.txt output2.txt
if %errorlevel%==0 goto loop
pause