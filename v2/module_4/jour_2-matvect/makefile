perf: perf1 perf2 perf3 dperf23 perf4 perf5 perf6 perf7
perf1: t1
	@(time ./$< ) >& perf$<.txt
perf2: t2
	@(time ./$<) >& perf$<.txt
	@valgrind --tool=callgrind --callgrind-out-file=callgrind.out.$< ./$<
	@valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out.$< ./$<
	@cg_annotate cachegrind.out.$< > $<.anotate
perf3: t3
	@(time ./$<) >& perf$<.txt
	@valgrind --tool=callgrind --callgrind-out-file=callgrind.out.$< ./$<
	@valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out.$< ./$<
	@cg_annotate cachegrind.out.$< > $<.anotate
perf4: t4
	@(time ./$<) >& perf$<.txt
	@valgrind --tool=callgrind --callgrind-out-file=callgrind.out.$< ./$<
	@valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out.$< ./$<
	@cg_annotate cachegrind.out.$< > $<.anotate
perf5: t5
	@mpiexec -np 8 valgrind --tool=callgrind ./$<
	@mpiexec -np 8 valgrind --tool=massif --time-unit=ms ./$<
	@mpiexec -np 8 --oversubscribe ./$<
perf6: t5m
	@export OPENMP_NUM_THREAD=1;export SCOREP_ENABLE_TRACING=false; export SCOREP_ENABLE_PROFILING=true;rm -rf scorep_run; scalasca -analyze -e scorep_run mpiexec -np 8 --oversubscribe ./$<
	@mpiexec -np 8 --oversubscribe ./t5
	@scalasca -examine scorep_run
	@~/software/tau-2.31/x86_64/bin/paraprof scorep_run/profile.cubex
perf6t: t5mt
	@export OPENMP_NUM_THREAD=1;export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;rm -rf scorep_run_trace; scalasca -analyze -e scorep_run_trace mpiexec -np 8 --oversubscribe ./$<
	@mpiexec -np 8 --oversubscribe ./t5
	@scalasca -examine scorep_run_trace
perf7: t6m
	@export OPENMP_NUM_THREAD=1;export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;rm -rf scorep_run_unbalanced; scalasca -analyze -e scorep_run_unbalanced mpiexec -np 8 --oversubscribe ./$<
	@scalasca -examine scorep_run_unbalanced 
	@~/software/tau-2.31/x86_64/bin/paraprof scorep_run_unbalanced/trace.cubex
dperf23:cachegrind.out.t2 cachegrind.out.t3
	@cg_diff cachegrind.out.t2 cachegrind.out.t3 > cachegrind.out.t23
	@cg_annotate cachegrind.out.t23 > t23.anotate
debug: t0 t00 t000
	@valgrind --tool=memcheck --leak-check=full --track-origins=yes ./t0 -p >& t0.txt
	@./t000 -p >& t000.txt
	@./t00 -p >& t00.txt
	@gdb t0
t000:prod_mm0.cpp
	@ g++ -O0 -fsanitize=leak  -g $< -o $@
t00:prod_mm0.cpp
	@ g++ -O0 -fsanitize=address  -g $< -o $@
t0:prod_mm0.cpp
	@ g++ -O0 -g $< -o $@
t1:prod_mm1.cpp
	@ g++ -O0 -g $< -o $@
t2:prod_mm1.cpp
	@ g++ -O3 -g $< -o $@
t3:prod_mm2.cpp
	@ g++ -O3 -g $< -o $@
t4:prod_mm3.cpp
	@ g++ -O3 -g -lopenblas $< -o $@
t5:prod_mm4.cpp
	@mpicxx -O3 -g $< -lopenblas -lscalapack -o $@
t5m:prod_mm4.cpp
	@export SCOREP_ENABLE_TRACING=false; export SCOREP_ENABLE_PROFILING=true;scorep --user mpicxx -O3 -g $<  -lopenblas -lscalapack -o $@
t5mt:prod_mm4.cpp
	@export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;scorep --user mpicxx -O3 -g $<  -lopenblas -lscalapack -o $@
t6m:prod_mm5.cpp
	@export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;scorep --user mpicxx -O3 -g $<  -lopenblas -lscalapack -o $@
clean:
	@rm -rf t0 t00 t000 t1 t2 t3 t4 t5 t5m t5mt t6m callgrind.out.* cachegrind.out.t* scorep_run* t*.anotate perf*.txt output_main*.txt massif.out.*
