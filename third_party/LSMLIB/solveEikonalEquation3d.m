%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% solveEikonalEquation3d() solves the Eikonal equation 
%
%   |grad(phi)| = 1/speed(x,y,z)
%
% in three-dimensions using the Fast Marching Method.
% 
% Usage: phi = solveEikonalEquation3d(boundary_data, speed, dX, ...
%                                     mask, spatial_discretization_order)
%
% Arguments:
% - boundary_data:                 data array containing boundary data and
%                                    domain information.  The value at grid 
%                                    points adjacent to the boundary of the 
%                                    domain should be set to the desired 
%                                    positive values; the value at all other 
%                                    grid points should be negative.
% - speed:                         speed function in Eikonal equation
% - dX:                            array containing the grid spacing
%                                    in each coordinate direction
% - mask:                          mask for domain of problem;
%                                    grid points outside of the domain
%                                    of the problem should be set to a
%                                    negative value
%                                    (default = [])
% - spatial_discretization_order:  order of discretization for 
%                                    spatial derivatives
%                                    (default = 2)
%
% Return value:
% - phi:                           solution to Eikonal equation
%
% NOTES:
% - It is the user's responsibility to set the boundary data for phi.
%   Grid points where the value of phi are to be solved for MUST be
%   set to a negative value.
%
% - All data arrays are assumed to be in the order generated by the
%   MATLAB meshgrid() function.  That is, data corresponding to the
%   point (x_i,y_j,z_k) is stored at index (j,i,k).
%
% - It is NOT necessary to mask out regions where the speed is zero.
%   Grid points where the speed is zero are automatically treated as
%   being outside of the domain.
%
% - boundary_data, speed, and mask MUST have the same grid dimensions.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Copyrights: (c) 2005 The Trustees of Princeton University and Board of
%                 Regents of the University of Texas.  All rights reserved.
%             (c) 2009 Kevin T. Chu.  All rights reserved.
% Revision:   $Revision: 149 $
% Modified:   $Date: 2009-01-18 00:31:09 -0800 (Sun, 18 Jan 2009) $
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

