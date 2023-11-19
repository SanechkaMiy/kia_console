#!/bin/bash
cd /home/alexander/Projects/starplatinum/apps/KIANK/build/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/alexander/.conan/data/boost/1.72.0/_/_/package/dc0a56269363b447d36ad64fac747c023d3cb08a/lib/
export LD_LIBRARY_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/alexander/.conan/data/glog/0.4.0/_/_/package/021f4686d5235a37bfebfeec187fbd19f1dc533d/lib/
export LD_LIBRARY_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/alexander/.conan/data/gflags/2.2.2/_/_/package/6dd0089565b78ff65df78f32f3433147677c5078/lib/
export LD_LIBRARY_PATH
./KIANK
