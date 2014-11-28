:loop
make
cmp
code
fc output.txt a.out
if %errorlevel%==0 goto loop
pause