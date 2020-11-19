% Visualize information from the eigenspectrum of the graph Laplacian
%
% D.P & O.S for HPC in USI Lugano

close all;
clear all;
clc;

% add necessary paths
addpaths_GP;

% Graphical output at bisection level
picture = 0;

% Cases under consideration
% load airfoil1.mat;
% load 3elt.mat;
% load barth4.mat;
% load mesh3e1.mat;
% load crack.mat;


cases = {
	'airfoil1.mat';
    '3elt.mat';
    'barth4.mat';
    'mesh3e1.mat';
    'crack.mat';
    };

for c = 1:length(cases)
	load(cases{c}) 
	% Initialize the Cases
	W      = Problem.A;
	coords = Problem.aux.coord;

	% Steps
	% 1. Construct the graph Laplacian of the graph in question.
	D = sparse(size(W,1),size(W,1));
	for i = 1:size(W,1)
		D(i,i) = sum(W(i,:));
	end
	L = D - W;

	% 2. Compute eigenvectors associated with the smallest eigenvalues.
	[eigVec,eigVal] = eigs(L,2,'smallestabs');

	% 3. Perform spectral bisection.
	[V1,V2] = bisection_spectral(W, coords, picture);

	zeros_init = zeros(size(coords,1),1);
	coords_xyz = [coords zeros_init];
	% 4. Visualize:
	%   i. a)   The first and second eigenvectors.
		figure();
		plot(eigVec(:,1))
		hold on 
		plot(eigVec(:,2))
	%   ii.  The second eigenvector projected on the coordinate system space of graphs.
		
		figure();
		gplotpartEx6(W,coords_xyz,V1);
		hold on
		scatter3(coords(:,1),coords(:,2), eigVec(:,2), [], eigVec(:,2));
		colormap('jet')
		colorbar
		title(cases{c})
		axis([min(coords(:,1)) max(coords(:,1)) min(coords(:,2)) max(coords(:,2)) min(eigVec(:,2)) max(eigVec(:,2))]);

	%   iii. The spectral bi-partitioning results using the spectral coordinates of each graph.
		[eigVec_bi,eigVal_bi] = eigs(L,3,'smallestabs');
		
		new_coords = [eigVec_bi(:,2) eigVec_bi(:,3)];
		figure;
		gplotpart(W,new_coords,V1)

		figure;
		gplotpart(W,coords,V1)		

end







