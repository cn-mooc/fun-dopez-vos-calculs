all: t bis
bis:
	export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;scorep --user mpicxx -O3 -g jacobi_mpi-bis.cpp -o jacobi_mpi-bis
	export OPENMP_NUM_THREAD=1;export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;export SCOREP_TOTAL_MEMORY=64000K;rm -rf scorep_run_bis;scalasca -analyze -e scorep_run_bis mpiexec --oversubscribe -np 8 ./jacobi_mpi-bis -n 512 -maxiter 1000
	scalasca -examine scorep_run_bis
t:
	export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;scorep --user mpicxx -O3 -g jacobi_mpi.cpp -o jacobi_mpi
	export OPENMP_NUM_THREAD=1;export SCOREP_ENABLE_TRACING=true; export SCOREP_ENABLE_PROFILING=false;export SCOREP_TOTAL_MEMORY=64000K;rm -rf scorep_run;scalasca -analyze -e scorep_run mpiexec --oversubscribe -np 8 ./jacobi_mpi -n 512 -maxiter 1000
	scalasca -examine scorep_run
jacobi_mpi-bis_tau:jacobi_mpi-bis.cpp
	tau_cxx.sh -tau_options=-optCompInst -tau_makefile=~/software/tau-2.31/x86_64/lib/Makefile.tau-ompt-mpi-pdt-openmp jacobi_mpi-bis.cpp -I/usr/include/openmpi-x86_64 -L/usr/lib64/openmpi/lib -o jacobi_mpi-bis_tau
bistau: tau_run_bis/tau.slog2
	cd tau_run_bis/; ~/software/tau-2.31/x86_64/bin/jumpshot tau.slog2
tau_run_bis/tau.slog2: tau_run_bis/tau.trc 
	cd tau_run_bis/;~/software/tau-2.31/x86_64/bin/tau2slog2 tau.trc tau.edf -o tau.slog2
tau_run_bis/tau.trc: jacobi_mpi-bis_tau
	export OPENMP_NUM_THREAD=1;export TAU_VERBOSE=1;export  TAU_TRACE=1;export  TRACEDIR=./tau_run_bis; rm -rf ./tau_run_bis;mkdir tau_run_bis; mpiexec --oversubscribe -np 8 ./jacobi_mpi-bis_tau -n 512 -maxiter 1000
	cd tau_run_bis/; ~/software/tau-2.31/x86_64/bin/tau_treemerge.pl
jacobi_mpi_tau:jacobi_mpi.cpp
	~/software/tau-2.31/x86_64/bin/tau_cxx.sh -tau_makefile=~/software/tau-2.31/x86_64/lib/Makefile.tau-ompt-mpi-pdt-openmp jacobi_mpi.cpp -I/usr/include/openmpi-x86_64 -L/usr/lib64/openmpi/lib -o jacobi_mpi_tau
tau: tau_run/tau.slog2
	cd tau_run/; ~/software/tau-2.31/x86_64/bin/jumpshot tau.slog2
tau_run/tau.slog2: tau_run/tau.trc 
	cd tau_run/;~/software/tau-2.31/x86_64/bin/tau2slog2 tau.trc tau.edf -o tau.slog2
tau_run/tau.trc: jacobi_mpi_tau
	export OPENMP_NUM_THREAD=1;export TAU_VERBOSE=1;export  TAU_TRACE=1;export  TRACEDIR=./tau_run; rm -rf ./tau_run;mkdir tau_run; mpiexec --oversubscribe -np 32 ./jacobi_mpi_tau -n 2048 -maxiter 1000
	cd tau_run/; ~/software/tau-2.31/x86_64/bin/tau_treemerge.pl


