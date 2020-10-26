%data mandelbrot
%%SEQUENTIAL

%%Iterations/second:          2.0764e+08
%%MFlop/s:                    1661.12


%starting from 128x128 to 4096x4096

millisec_par = [56.757,156.935,503.567,1769.81,6900.09,27433.1]

millisec_seq = [536.349,2141.22,8549.68,34210.4,136790,547154]

figure()
semilogx([128,256,512,1024,2048,4096],millisec_seq,"LineWidth",2)
hold on
semilogx([128,256,512,1024,2048,4096],millisec_par,"LineWidth",2)
xticks([128 256 512 1024 2048 4096])
xticklabels({"128","256","512","1024","2048","4096"})

xlabel("Figure size")
ylabel("Time (milliseconds)")

legend("Time sequential", "Time Parallel")












