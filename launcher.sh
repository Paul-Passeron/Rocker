set -xe
clear;
./format.sh
make;
./main examples/token.rkr -t;