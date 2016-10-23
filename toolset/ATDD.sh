protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/*.proto
cd build && make hwserver && cd .. && py.test $1
