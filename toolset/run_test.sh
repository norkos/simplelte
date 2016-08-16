export TESTS_ENVIRONMENT="valgrind --quiet --trace-children=yes --error-exitcode=1 --leak-check=yes"
for i in `find build -executable -type f -name "test*"`; do $TESTS_ENVIRONMENT ./$i; done && ./toolset/run_acceptance_tests.sh
