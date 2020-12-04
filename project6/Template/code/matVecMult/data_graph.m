

procs = [1,4,8,12,16,32,64];

% strong scaling time with different number of processors 1, 2, 4, 8, 12(4008), 16, 32, 64(4032)
str_scal = [56.702305, 14.281268, 7.226491, 4.870897, 3.688307, 2.775795, 2.764656];
str_par_eff = str_scal(1)./(str_scal.*procs);





% weak scaling time with:
% p = 1 - n = 4000 - k = 100  sqrt(1) = 1 
% p = 4 - n = 8000 - k = 100  sqrt(4) = 2 
% p = 8 - n = 11312 - k = 100  sqrt(8) = 2.828 = 4000*sqrt(8)-mod(4000*sqrt(8),8)           |
% p = 12 - n = 13848 - k = 100  sqrt(12) = 3.464 = (4000*sqrt(12)-mod(4000*sqrt(12),12))    |    adjustment in order for p to be
% p = 16 - n = 16000 - k = 100  sqrt(16) = 4                                                |	a perfect divisor of n
% p = 32 - n = 22624 - k = 100  sqrt(32) = 5.656 = (4000*sqrt(32)-mod(4000*sqrt(32),32))    |
% p = 64 - n = 32000 - k = 100  sqrt(64) = 8 

weak_scal = [5.681354, 5.683748, 5.703939, 5.721666, 5.749904, 6.028132, 9.256683];
weak_par_eff = weak_scal./weak_scal(1)




% Strong scaling analysys plot
figure();
subplot(1,2,1);
plot(procs, str_scal,"LineWidth",2);
grid on
xlabel("Number of processors")
ylabel("Computational time (sec)")
title("Time vs Processors used")

subplot(1,2,2)
bar([1,2,3,4,5,6], str_par_eff(2:7),"LineWidth",2);
grid on
xlabel("Number of processors")
ylabel("Scaling with respect to 1 processor")
title("Parallel efficiency")
xticks([1 2 3 4 5 6])
xticklabels({'4','8','12','16','32','64'})




figure();
plot(procs, weak_scal,"LineWidth",2)
grid on 
xlabel("Number of processors")
ylabel("Computational time (sec)")
title("Weak scaling: Time vs Processors used")
xline(1)
xline(4)
xline(8)
xline(12)
xline(16)
xline(32)
xline(64)
