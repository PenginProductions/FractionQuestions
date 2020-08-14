This C++ project was created using Microsoft Visual Studio Community Edition. This program was a case study finished for a c++ course but never polished.
 2 files are contained:

	FractionQuestions.cpp => contains Class structure for 2 classes (Fraction and MathProblem)
			            also contains main method.

	FractionQuestions.exe => used to run program.
__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
To Run:

	1) Launch FractionQuestions.exe
__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
Tips:

When prompted for your answer be sure to follow the instructions. Entering an entire mixed number when only asked for the whole number portion will endless loop at the moment.

There are still some errors that need to be solved in this program:
	-When finished the program tells you how many questions out of 5 you got correct, but if you get an answer wrong it will ask you the same question until you enter the answer correctly.

	-When dividing fractions the program has trouble accepting # 0/1 as a whole number.

	-If  incorrect information is entered when prompted the program fails. (no exception handling)