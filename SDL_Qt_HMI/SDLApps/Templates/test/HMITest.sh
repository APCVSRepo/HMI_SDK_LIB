export LD_LIBRARY_PATH=.
./HMI_TEST
lcov -c -o test.info -d CMakeFiles/HMI_TEST.dir
genhtml test.info -o ./TestResult


