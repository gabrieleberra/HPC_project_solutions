function [part1,part2] = bisection_spectral(A,xy,picture)
% bisection_spectral : Spectral partition of a graph.
%
% [part1,part2] = bisection_spectral(A) returns a partition of the n vertices
%                 of A into two lists part1 and part2 according to the
%                 spectral bisection algorithm of Simon et al:  
%                 Label the vertices with the components of the Fiedler vector
%                 (the second eigenvector of the Laplacian matrix) and partition
%                 them around the median value or 0.



%{
disp(' ');
disp(' HPC 2020 @ USI Lugano:   ');
disp(' Implement spectral bisection');
disp(' ');


answ = input('\n\n Which type of partition? \n Type "median" or "zero" for Median Value or Zero respectevely \n >>> ', 's');
if lower(string(answ)) == '"zero"' 
	answ = 'zero';
elseif lower(string(answ)) == "'zero'"
	answ = 'zero';
elseif lower(string(answ)) == '"median"' 
	answ = 'median';
elseif lower(string(answ)) == "'median'"
	answ = 'median';
end
%}

% Steps
% 1. Construct the Laplacian.
D = sparse(size(A,1),size(A,1));
for i = 1:size(A,1)
	D(i,i) = sum(A(i,:));
end
L = D - A;

% 2. Calculate its eigensdecomposition.
[eigVec,eigVal] = eigs(L,2,'smallestabs');

% 3. Label the vertices with the components of the Fiedler vector.
v2 = eigVec(:,2);
V1 = zeros;
V2 = zeros;

% 4. Partition them around 0.
counterV1 = 1;
counterV2 = 1;
thres = 0;

for i = 1:length(eigVec)
	if v2(i) < thres
		V1(counterV1,1) = i;
		counterV1 = counterV1 + 1; 
	else
		V2(counterV2,1) = i;
		counterV2 = counterV2 + 1;
	end
end

part1 = V1;
part2 = V2;




if picture == 1
    gplotpart(A,xy,V1);
    title('Spectral bisection using the Fiedler Eigenvector');
end





%{
if lower(string(answ)) == 'zero'
	thres = 0;
	for i = 1:length(eigVec)
		if v2(i) < thres
			V1(counterV1,1) = i;
			counterV1 = counterV1 + 1; 
		else
			V2(counterV2,1) = i;
			counterV2 = counterV2 + 1;
		end
	end
elseif lower(string(answ)) == 'median'
	thres = median(v2);
	for i = 1:length(eigVec)
		if v2(i) < thres
			V1(counterV1,1) = i;
			counterV1 = counterV1 + 1; 
		else
			V2(counterV2,1) = i;
			counterV2 = counterV2 + 1;
		end
	end
else 
	disp('Incorrect type of partition, please insert a correct one!')
end

%}




%{
% <<<< Dummy implementation to generate a partitioning
n = size(A,1);
map = zeros(n,1);
map(1:round((n/2))) = 0; 
map((round((n/2))+1):n) = 1;
[part1,part2] = other(map);

if picture == 1
    gplotpart(A,xy,part1);
    title('Spectral bisection (dummy) using the Fiedler Eigenvector');
end

% Dummy implementation to generate a partitioning >>>>
%}

end