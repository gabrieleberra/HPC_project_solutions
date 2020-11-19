function [cut_recursive,cut_kway] = Bench_metis(picture)
% Compare recursive bisection and direct k-way partitioning,
% as implemented in the Metis 5.0.2 library.

%  Add necessary paths
addpaths_GP;

% Graphs in question
% load usroads;
% load luxembourg_osm;

% Steps
% 1. Initialize the cases
% US adjacency and coordinates
us_road = load('usroads.mat');
A_us = us_road.Problem.A;
coord_us = us_road.Problem.aux.coord;

% Luxembourg adjacency and coordinates
lux_road = load('luxembourg_osm.mat');
A_lux = lux_road.Problem.A;
coord_lux = lux_road.Problem.aux.coord;

% Greece adjacency and coordinates
adj_gr = csvread('GR-3117-adj.csv',1);
coor_gr = csvread('GR-3117-pts.csv',1);

% Swizerland adjacency and coordinates
adj_ch = csvread('CH-4468-adj.csv',1);
coor_ch = csvread('CH-4468-pts.csv',1);

% Vietnam adjacency and coordinates
adj_vn = csvread('VN-4031-adj.csv',1);
coor_vn = csvread('VN-4031-pts.csv',1);

% Norway adjacency and coordinates
adj_no = csvread('NO-9935-adj.csv',1);
coor_no = csvread('NO-9935-pts.csv',1);

% Russia adjacency and coordinates
adj_ru = csvread('RU-40527-adj.csv',1);
coor_ru = csvread('RU-40527-pts.csv',1);


% Initialize sparse matrix
W_ch = sparse(max(max(adj_ch)), max(max(adj_ch)));
W_gr = sparse(max(max(adj_gr)), max(max(adj_gr)));
W_no = sparse(max(max(adj_no)), max(max(adj_no)));
W_ru = sparse(max(max(adj_ru)), max(max(adj_ru)));
W_vn = sparse(max(max(adj_vn)), max(max(adj_vn)));

% Fill sparse matrix  with 1 if nodes are connected
for i = 1:size(adj_ch,1)
	W_ch(adj_ch(i,1), adj_ch(i,2)) = 1;
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
W_gr = symmetry(W_gr);
W_no = symmetry(W_no);
W_ru = symmetry(W_ru);
W_vn = symmetry(W_vn);

% 2. Call metismex to
% a) Recursively and kwaypartition the graphs in 16 and 32 subsets.

% LUXEMBOURG  recursive and kway
[map_lux_rec_16, cut_lux_rec_16] = metismex('PartGraphRecursive',A_lux,16);
[map_lux_rec_32, cut_lux_rec_32] = metismex('PartGraphRecursive',A_lux,32);

[map_lux_kway_16, cut_lux_kway_16] = metismex('PartGraphKway',A_lux,16);
[map_lux_kway_32, cut_lux_kway_32] = metismex('PartGraphKway',A_lux,32);

% US recursive and kway
[map_us_rec_16, cut_us_rec_16] = metismex('PartGraphRecursive',A_us,16);
[map_us_rec_32, cut_us_rec_32] = metismex('PartGraphRecursive',A_us,32);

[map_us_kway_16, cut_us_kway_16] = metismex('PartGraphKway',A_us,16);
[map_us_kway_32, cut_us_kway_32] = metismex('PartGraphKway',A_us,32);

% GREECE recursive and kway
[map_gr_rec_16, cut_gr_rec_16] = metismex('PartGraphRecursive',W_gr,16);
[map_gr_rec_32, cut_gr_rec_32] = metismex('PartGraphRecursive',W_gr,32);

[map_gr_kway_16, cut_gr_kway_16] = metismex('PartGraphKway',W_gr,16);
[map_gr_kway_32, cut_gr_kway_32] = metismex('PartGraphKway',W_gr,32);

% SWITZERLAND recursive and kway
[map_ch_rec_16, cut_ch_rec_16] = metismex('PartGraphRecursive',W_ch,16);
[map_ch_rec_32, cut_ch_rec_32] = metismex('PartGraphRecursive',W_ch,32);

[map_ch_kway_16, cut_ch_kway_16] = metismex('PartGraphKway',W_ch,16);
[map_ch_kway_32, cut_ch_kway_32] = metismex('PartGraphKway',W_ch,32);

% VIETNAM recursive and kway
[map_vn_rec_16, cut_vn_rec_16] = metismex('PartGraphRecursive',W_vn,16);
[map_vn_rec_32, cut_vn_rec_32] = metismex('PartGraphRecursive',W_vn,32);

[map_vn_kway_16, cut_vn_kway_16] = metismex('PartGraphKway',W_vn,16);
[map_vn_kway_32, cut_vn_kway_32] = metismex('PartGraphKway',W_vn,32);

% NORWAY recursive and kway
[map_no_rec_16, cut_no_rec_16] = metismex('PartGraphRecursive',W_no,16);
[map_no_rec_32, cut_no_rec_32] = metismex('PartGraphRecursive',W_no,32);

[map_no_kway_16, cut_no_kway_16] = metismex('PartGraphKway',W_no,16);
[map_no_kway_32, cut_no_kway_32] = metismex('PartGraphKway',W_no,32);

% RUSSIA recursive and kway
[map_ru_rec_16, cut_ru_rec_16] = metismex('PartGraphRecursive',W_ru,16);
[map_ru_rec_32, cut_ru_rec_32] = metismex('PartGraphRecursive',W_ru,32);

[map_ru_kway_16, cut_ru_kway_16] = metismex('PartGraphKway',W_ru,16);
[map_ru_kway_32, cut_ru_kway_32] = metismex('PartGraphKway',W_ru,32);



recursive_cut_16 = [cut_lux_rec_16, cut_us_rec_16, cut_gr_rec_16, cut_ch_rec_16, cut_vn_rec_16, cut_no_rec_16, cut_ru_rec_16];
recursive_cut_32 = [cut_lux_rec_32, cut_us_rec_32, cut_gr_rec_32, cut_ch_rec_32, cut_vn_rec_32, cut_no_rec_32, cut_ru_rec_32];
kway_cut_16 = [cut_lux_kway_16, cut_us_rec_16, cut_gr_kway_16, cut_ch_kway_16, cut_vn_kway_16, cut_no_kway_16, cut_ru_kway_16];
kway_cut_32 = [cut_lux_kway_32, cut_us_rec_32, cut_gr_kway_32, cut_ch_kway_32, cut_vn_kway_32, cut_no_kway_32, cut_ru_kway_32];

cut_recursive = [recursive_cut_16; recursive_cut_32];
cut_kway = [kway_cut_16; kway_cut_32];


% 3. Visualize the results for 32 partitions.
figure;
gplotmap(A_us,coord_us,map_us_rec_32)
title('Metis Recursive US')

figure;
gplotmap(A_us,coord_us,map_us_kway_32)
title('Metis Kway US')

figure;
gplotmap(A_lux,coord_lux,map_lux_rec_32)
title('Metis Recursive Luxembourg')

figure;
gplotmap(A_lux,coord_lux,map_lux_kway_32)
title('Metis Kway Luxembourg')

figure;
gplotmap(W_ru,coor_ru,map_ru_rec_32)
title('Metis Recursive Russia')

figure;
gplotmap(W_ru,coor_ru,map_ru_kway_32)
title('Metis Kway Russia')


end