protoc -I messages --python_out=test/acceptance_test messages/messages.proto
./toolset/python_virtualenv/bin/py.test test
