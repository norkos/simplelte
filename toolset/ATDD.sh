ulimit -c unlimited
protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/*.proto
cd build && ninja hwserver && cd .. && py.test $1
