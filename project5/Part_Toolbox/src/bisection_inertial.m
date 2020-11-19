function [part1,part2] = bisection_inertial(A,xy,picture)
% INERTPART : Inertial partition of a graph.
%
% p = inertpart(A,xy) returns a list of the vertices on one side of a partition
%     obtained by bisection with a line or plane normal to a moment of inertia
%     of the vertices, considered as points in Euclidean space.
%     Input A is the adjacency matrix of the mesh (used only for the picture!);
%     each row of xy is the coordinates of a point in d-space.
%
% inertpart(A,xy,1) also draws a picture.
%
% See also PARTITION

%{
disp(' ');
disp(' HPC 2020 @ USI Lugano:   ');
disp(' Implement inertial bisection');
disp(' ');
%}

% compute x mean and y mean
bar_x = sum(xy(:,1))/size(A,1);
bar_y = sum(xy(:,2))/size(A,1);

% compute S
S_xx = sum((xy(:,1) - bar_x).^2);
S_yy = sum((xy(:,2) - bar_y).^2);
S_xy = dot((xy(:,1) - bar_x),(xy(:,2) - bar_y));

% compute M
M = [S_xx S_xy; S_xy S_yy];

% compute eigenvector
[eigVec, eigVal] = eig(M);

% partitioning plane
v_small = eigVec(:,1);

% create orthogonal vector
v_ortogonal(1,1) = -eigVec(2,1);
v_ortogonal(2,1) = eigVec(1,1);

% normalizing orthogonal vector
v_ortNorm = v_ortogonal./norm(v_ortogonal,2);

[part1,part2] = partition(xy, v_ortNorm);

if picture == 1
    gplotpart(A,xy,part1);
    title('Inertial bisection');
end

%{
% <<<< Dummy implementation to generate a partitioning
n   = size(A,1);
map = zeros(n,1);
map(1:round((n/2)))     = 0; 
map((round((n/2))+1):n) = 1;


[part1,part2] = other(map);

if picture == 1
    gplotpart(A,xy,part1);
    title('Inertial bisection (dummy) using the Fiedler Eigenvector');
end

% Dummy implementation to generate a partitioning >>>>

%}
end