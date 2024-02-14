set -xe
clear;
make;
./main examples/token.rkr -t;
./format.sh