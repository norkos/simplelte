export VALGRIND="valgrind --quiet --trace-children=yes --error-exitcode=1 --leak-check=yes --suppressions=misc/valgrind-python.supp"
ulimit -c unlimited
protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/*.proto
cd build && make hwserver && cd .. && $VALGRIND py.test $1
