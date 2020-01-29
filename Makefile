build:
	g++ -Wall -pedantic -std=c++11 main.cpp -o sorer

test:
	g++ -g -Wall -pedantic -std=c++11 test.cpp -o sorer_test
	./sorer_test
	make run_all

run:
	./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0

run_all:
	./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0
	./sorer -f "data.sor" -from 0 -len 100 -print_col_type 2
	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 0
	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 1
	./sorer -f "data.sor" -from 0 -len 100 -is_missing_idx 2 2
	./sorer -f "data.sor" -from 0 -len 100 -print_col_idx 2 0
	./sorer -f "data.sor" -from 5 -len 100 -print_col_idx 1 0

valgrind:
	valgrind --leak-check=yes ./sorer -f "data.sor" -from 0 -len 100 -print_col_type 0

clean:
	-rm sorer
	-rm -rf sorer.dSYM
	-rm sorer_test
	-rm -rf sorer_test.dSYM