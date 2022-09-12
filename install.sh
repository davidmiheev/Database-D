echo "Compiling [clang++ main.cpp -o database-d]... "
clang++ main.cpp -o database-d
echo "\033[FCompiling... [clang++ main.cpp -o database-d]... done"
echo "Generating test dataset [python3 test.py 10000]..."
python3 test.py 10000
echo "\033[FGenerating test dataset [python3 test.py 10000]... done"
