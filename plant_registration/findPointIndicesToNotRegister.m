function [ idx ] = findPointIndicesToNotRegister( ...
                           X,Y,max_registrable_dist )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    



idx = find( neighborDistances > max_registrable_dist );

end
