protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/messages.proto
for i in `find build -executable -type f -name "test*"`; do ./$i; done && py.test test
