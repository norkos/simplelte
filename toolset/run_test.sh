export TESTS_ENVIRONMENT="valgrind --quiet --trace-children=yes --error-exitcode=1 --leak-check=yes"
protoc -I CP_Util/messages --python_out=test/acceptance_test CP_Util/messages/messages.proto
for i in `find build -executable -type f -name "test*"`; do $TESTS_ENVIRONMENT ./$i; done && py.test test
