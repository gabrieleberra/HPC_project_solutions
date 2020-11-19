function [A] = symmetry(A)
	if issymmetric(A) ~= 1 
		A = (A + A.')/2;
	end
end


