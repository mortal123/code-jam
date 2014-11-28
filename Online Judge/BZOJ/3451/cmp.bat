@echo off
:again
gen
code
check
fc output.txt  answer.txt || pause
goto again
gen.exe