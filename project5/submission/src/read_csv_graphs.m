% Script to load .csv lists of adjacency matrices and the corresponding 
% coordinates. 
% The resulting graphs should be visualized and saved in a .csv file.
% D.P & O.S for HPC in USI Lugano
close all;
clear all;
clc;

addpaths_GP;

% Steps
% 1. Load the .csv files

adj_ch = csvread('CH-4468-adj.csv',1);
coor_ch = csvread('CH-4468-pts.csv',1);

adj_cl = csvread('CL-13042-adj.csv',1);
coor_cl = csvread('CL-13042-pts.csv',1);

adj_gb = csvread('GB-5946-adj.csv',1);
coor_gb = csvread('GB-5946-pts.csv',1);

adj_gr = csvread('GR-3117-adj.csv',1);
coor_gr = csvread('GR-3117-pts.csv',1);

adj_no = csvread('NO-9935-adj.csv',1);
coor_no = csvread('NO-9935-pts.csv',1);

adj_ru = csvread('RU-40527-adj.csv',1);
coor_ru = csvread('RU-40527-pts.csv',1);

adj_vn = csvread('VN-4031-adj.csv',1);
coor_vn = csvread('VN-4031-pts.csv',1);


% 2. Construct the adjacency matrix (NxN). There are multiple ways
%    to do so.

% Initialize sparse matrix
W_ch = sparse(max(max(adj_ch)), max(max(adj_ch)));
W_cl = sparse(max(max(adj_cl)), max(max(adj_cl)));
W_gb = sparse(max(max(adj_gb)), max(max(adj_gb)));
W_gr = sparse(max(max(adj_gr)), max(max(adj_gr)));
W_no = sparse(max(max(adj_no)), max(max(adj_no)));
W_ru = sparse(max(max(adj_ru)), max(max(adj_ru)));
W_vn = sparse(max(max(adj_vn)), max(max(adj_vn)));


% Fill sparse matrix  with 1 if nodes are connected
for i = 1:size(adj_ch,1)
	W_ch(adj_ch(i,1), adj_ch(i,2)) = 1;
end
for i = 1:size(adj_cl,1)
	W_cl(adj_cl(i,1), adj_cl(i,2)) = 1;
end
for i = 1:size(adj_gb,1)
	W_gb(adj_gb(i,1), adj_gb(i,2)) = 1;
end
for i = 1:size(adj_gr,1)
	W_gr(adj_gr(i,1), adj_gr(i,2)) = 1;
end
for i = 1:size(adj_no,1)
	W_no(adj_no(i,1), adj_no(i,2)) = 1;
end
for i = 1:size(adj_ru,1)
	W_ru(adj_ru(i,1), adj_ru(i,2)) = 1;
end
for i = 1:size(adj_vn,1)
	W_vn(adj_vn(i,1), adj_vn(i,2)) = 1;
end



% Make the adjecency matrix symmetric
W_ch = symmetry(W_ch);
W_gb = symmetry(W_gb);
W_gr = symmetry(W_gr);
W_no = symmetry(W_no);
W_ru = symmetry(W_ru);
W_vn = symmetry(W_vn);

%help accumarray
%help sparse
% 3. Visualize the resulting graphs

%figure()
%gplotg(W_ch,coor_ch)

%figure()
%gplotg(W_cl,coor_cl)

%figure()
%gplotg(W_gb,coor_gb)

%figure()
%gplotg(W_gr,coor_gr)

%figure()
%gplotg(W_ru,coor_ru)

figure();
gplotg(W_no,coor_no); % Norway graph
title('Norway','Fontsize', 18)

figure();
gplotg(W_vn,coor_vn); % Vietnam graph
title('Vietnam','Fontsize', 18)



% 4. Save the resulting graphs
save('datasets/Countries/mat/Norway_graph','W_no','coor_no');
save('datasets/Countries/mat/Vietnam_graph','W_vn','coor_vn');


% Example of the desired graph format for CH

%load Swiss_graph.mat

%whos

%figure;
%gplotg(W,coords);
