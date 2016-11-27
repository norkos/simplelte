screen -dmS my_session bash -c "valgrind --quiet --trace-children=yes --error-exitcode=1 --leak-check=yes --suppressions=misc/valgrind-python.supp build/CP_eNB/src/hwserver > build/memory.out 2>&1"
sleep 1
py.test test/acceptance_test/memory_leaks.py
sleep 1
cat build/memory.out
[ ! -s build/memory.out ] || exit 1


