#!/usr/bin/env fish
make clean
make
for i in (seq $argv[1])
   ./bin/main >> deneme.txt
end
./calculate-average-time.lua
