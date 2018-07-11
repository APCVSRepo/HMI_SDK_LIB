export LD_LIBRARY_PATH=.
./HMI_TEST
lcov -c -o test.info -d ../../
lcov --extract test.info '*/SDLApps/Templates/*' -o result.info
genhtml result.info -o ./TestResult
mv TestResult ../../


