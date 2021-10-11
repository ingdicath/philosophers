echo "--- NO ARGUMENTS ---"
./philo
echo ""
echo "--- INVALID ARGUMENTS ---"
./philo a a a a
echo ""
echo "--- ONE ARGUMENT ---"
./philo 10
echo ""
echo "--- TWO ARGUMENTS ---"
./philo 10 10
echo ""
echo "--- THREE ARGUMENTS ---"
./philo 10 10 10
echo ""
echo "--- SIX ARGUMENTS ---"
./philo 10 10 10 10 10 10
echo ""
echo "--- NEGATIVE ARGUMENTS 1 ---"
./philo -1 10 10 10
echo ""
echo "--- NEGATIVE ARGUMENTS 2 ---"
./philo 10 -1 10 10
echo ""
echo "--- NEGATIVE ARGUMENTS 3 ---"
./philo 10 10 -1 10
echo ""
echo "--- NEGATIVE ARGUMENTS 4 ---"
./philo 10 10 10 -1
echo ""
echo "--- NEGATIVE ARGUMENTS 5 ---"
./philo 10 10 10 10 -1
echo ""
echo "--- UINT_MAX ARGUMENT 1---"
./philo 4294967296 10 10 10 10
echo ""
echo "--- UINT_MAX ARGUMENT 2---"
./philo 10 4294967296 10 10 10
echo ""
echo "--- UINT_MAX ARGUMENT TIMES TO EAT---"
./philo 10 10 10 10 4294967296
echo ""
echo "--- INT_MAX ARGUMENT ---"
./philo 2147483648 10 10 10
echo ""
echo "--- INT_MAX ARGUMENT ---"
./philo 2147483648 10 10 10
echo ""
echo "--- INT_MIN ARGUMENT ---"
./philo -2147483649 10 10 10
echo ""
echo "--- LONG_MIN ARGUMENT ---"
./philo -9223372036854775809 10 10 10
echo ""
echo "--- LONG_MAX ARGUMENT ---"
./philo 9223372036854775808 10 10 10
echo ""
echo "--- ULONG_MAX ARGUMENT ---"
./philo 18446744073709551616 10 10 10
echo ""
echo "--- ZERO PHILOSOPHERS ---"
./philo 0 120 60 60
echo ""
echo "--- ONE PHILOSOPHERS ---"
./philo 1 120 60 60
echo ""
echo "--- TWO PHILOSOPHERS ---"
./philo 2 120 60 60
echo ""
echo "--- THREE PHILOSOPHERS ---"
./philo 3 120 60 60