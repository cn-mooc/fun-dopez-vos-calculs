all: test_g test_sa test_sl
test_g:bogues.cpp
	g++ -g -O0 -o $@ $<
test_sa:bogues.cpp
	g++ -g -fsanitize=address -O0 -o $@ $<
test_sl:bogues.cpp
	g++ -g  -fsanitize=leak -O0 -o $@ $<
