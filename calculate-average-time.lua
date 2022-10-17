#!/usr/bin/env lua

local data_file <close> = io.open('deneme.txt')
local lines = {}
local products = {}
local exponent = 1.0
for line in data_file:lines() do
   table.insert(lines, tonumber(line)/1000.0)
end

local lines_num = #lines - 1

for i=0,(lines_num // 100) - 1 do
   table.insert(products, 1.0)
   for j=0,99 do
      products[i+1] = products[i+1] * lines[i*100 + j+1]
   end
   products[i+1] = products[i+1] ^ (1.0/100.0)
end

local product = 1.0

for i=0,(lines_num // 100) - 1 do
   product = product * products[i+1]
end

print(product ^ (1/(lines_num // 100)))
