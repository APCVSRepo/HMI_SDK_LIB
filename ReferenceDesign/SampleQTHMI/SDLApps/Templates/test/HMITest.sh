#!/bin/bash

export LD_LIBRARY_PATH=.
./HMI_TEST

LOG_F=cov_log.log

if [ ! -f "${LOG_F}" ];then
	touch ${LOG_F}
else
	rm -f ${LOG_F}
	touch ${LOG_F}
fi

echo "Extraction coverage rate ..."
lcov -c -o test.info -d ../../ > ${LOG_F}
lcov --extract test.info '*/SDLApps/Templates/*' -o result.info > ${LOG_F}

echo "Generate html ..."
genhtml result.info -o ../../TestResult > ${LOG_F}
echo "Summary coverage rate:"
cat ${LOG_F} | grep -F "lines......"
cat ${LOG_F} | grep -F "functions.."
