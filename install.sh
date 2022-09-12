echo "Compiling [g++ main.cpp -o database-d]... "
g++ main.cpp -o database-d
echo "\033[FCompiling [g++ main.cpp -o database-d]... done \033[01;32m✔\033[0m"
echo "Generating test dataset [python3 test.py 10000]..."
python3 test.py 10000
echo "\033[FGenerating test dataset [python3 test.py 10000]... done \033[01;32m✔\033[0m"
