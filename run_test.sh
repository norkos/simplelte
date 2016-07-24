protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/messages.proto
./toolset/python_virtualenv/bin/py.test test
