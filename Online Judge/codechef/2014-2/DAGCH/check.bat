@echo off
:again
code.exe < input.txt > output.txt
DAGCH.exe < input.txt > answer.txt
fc output.txt  answer.txt || pause
goto again
gen.exe