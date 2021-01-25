NUM?=1
numbers=10 11 12 13 14 15 16 17 18 19 20 61 62
tests=TestIOs

n7=1 3 4 5 6 7 noway
n9=
n10=

run:
	for number in $(numbers); \
	do \
		./lab1 ./TestIOs/in$$number.txt > $(tests)/out.txt ; \
		diff $(tests)/out$$number.txt $(tests)/out.txt || (echo "diff failed on test $$number \n") ; \
	done
	rm $(tests)/out.txt

compile:
	g++ -Wall -Werror -std=c++17 -g classes/*.cpp main.cpp -o lab$(NUM)

test:
	./lab1 test_in.txt > test_out.txt
	diff test_out.txt solution_out.txt

big_test:
	for case in $(n7); \
	do \
		./lab1 ./Lab1PassOffCases/1-70/input$$case.txt > Lab1PassOffCases/out.txt; \
		diff ./Lab1PassOffCases/1-70/answer$$case.txt ./Lab1PassOffCases/out.txt || (echo "diff failed on test case $$case \n") ; \
	done
	# rm Lab1PassOffCases/out.txt

		for case in $(n9); \
	do \
		./lab1 ./Lab1PassOffCases/1-90/input$$case.txt > Lab1PassOffCases/out.txt; \
		diff ./Lab1PassOffCases/1-90/answer$$case.txt ./Lab1PassOffCases/out.txt || (echo "diff failed on test case $$case \n") ; \
	done
	# rm Lab1PassOffCases/out.txt

		for case in $(n10); \
	do \
		./lab1 ./Lab1PassOffCases/1-100/input$$case.txt > Lab1PassOffCases/out.txt; \
		diff ./Lab1PassOffCases/1-100/answer$$case.txt ./Lab1PassOffCases/out.txt || (echo "diff failed on test case $$case \n") ; \
	done
	rm Lab1PassOffCases/out.txt