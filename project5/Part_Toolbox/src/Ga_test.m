
close all;
clear all;
clc;



adj_ch = csvread('CH-4468-adj.csv',1);
coor_ch = csvread('CH-4468-pts.csv',1);
A = sparse(max(max(adj_ch)), max(max(adj_ch)));
for i = 1:size(adj_ch,1)
	A(adj_ch(i,1), adj_ch(i,2)) = 1;
end
A = (A + A.')/2;






%{
% INERTIAL BISECTION
% compute x mean and y mean
bar_x = sum(coor_ch(:,1))/size(A,1);
bar_y = sum(coor_ch(:,2))/size(A,1);

% compute S
S_xx = sum((coor_ch(:,1) - bar_x).^2);
S_yy = sum((coor_ch(:,2) - bar_y).^2);
S_xy = dot((coor_ch(:,1) - bar_x),(coor_ch(:,2) - bar_y));

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

[V1,V2] = partition(coor_ch, v_ortNorm)
%}



% SPECTRAL BISECTION
%{
D = sparse(size(A,1),size(A,1));
for i = 1:size(A,1)
	D(i,i) = sum(A(i,:));
end
L = D - A;


[eigVec,eigVal] = eigs(L,2,'smallestabs');

v2 = eigVec(:,2);
thres = 0;
V1 = zeros;
V2 = zeros;

counterV1 = 1;
counterV2 = 1;
for i = 1:length(eigVec)
	if v2(i) < thres
		V1(counterV1,1) = i;
		counterV1 = counterV1 + 1; 
	else
		V2(counterV2,1) = i;
		counterV2 = counterV2 + 1;
	end
end

[part1,part2] = V1,V2




%roba fatta da Olly
n = size(A,1);
map = zeros(n,1);
map(1:round((n/2))) = 0; 
map((round((n/2))+1):n) = 1;
[part1,part2] = other(map);
%}