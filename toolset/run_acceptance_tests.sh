protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/*.proto
py.test test
