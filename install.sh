echo "Compiling... [clang++ main.cpp -o database-d] "
clang++ main.cpp -o database-d
echo "Generating test dataset (test.txt)... [python3 test.py 5000]"
python3 test.py 5000
