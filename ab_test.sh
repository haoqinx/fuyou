#!/bin/bash
rm ./fuyou/base/log/fuyou.log
ab -c 1000 -n 10000 -k http://localhost:6666/hello