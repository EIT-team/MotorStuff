function [ valout ] = map_ard( x, in_min, in_max, out_min, out_max )
%MAP_ARD Summary of this function goes here
%   Detailed explanation goes here

valout = ( x - in_min) * (out_max - out_min) / (in_max - in_min) +out_min;

valout = int16(valout);
end

