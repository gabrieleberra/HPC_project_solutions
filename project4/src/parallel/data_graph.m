




ws612 =[0.196281,0.77066,3.73337]
ws125 =[1.28041,4.43689,23.6022]
ws251 =[8.81197,30.5576,293.759]
threadsP = [1,4,16]

supws612 = ws612(1)./ws612
supws125 = ws125(1)./ws125
supws251 = ws251(1)./ws251

figure()
semilogy(threadsP,ws612,"LineWidth",2)
hold on
semilogy(threadsP,ws125,"LineWidth",2)
hold on
semilogy(threadsP,ws251,"LineWidth",2)
grid on
xline(1)
xline(4)
xline(16)
xlabel("Threads number")
ylabel("Time (seconds)")
legend("64", "128", "256")


pause()













% from 1 to 10 threads
threads =[1,2,3,4,5,6,7,8,9,10]
x64 = [0.196281,0.187238,0.162066,0.165711,0.175701,0.171196,0.184268,0.192468,0.199429,0.268303]
x128 = [1.28041,0.953788,0.835927,0.77066,0.756458,0.752386,0.768854,0.773505,0.763555,0.776758]
x256 = [8.81197,6.15223,5.02967,4.43689,4.1095,3.9769,3.78487,3.86266,3.70059,3.61467]
x512 = [65.0061,45.2533,36.4704,30.5576,28.737,26.9436,26.2863,24.5194,25.2214,23.8828]
x1024 = [717.519,408.307,345.568,346.456,357.694,320.769,298.011,303.903,288.606,301.479]


sup64 = x64(1)./x64
sup128 = x128(1)./x128
sup256 = x256(1)./x256
sup512 = x512(1)./x512
sup1024 =x1024(1)./x1024



figure()
subplot(1,2,2)
plot(threads, sup64,"LineWidth",2)
hold on
plot(threads, sup128,"LineWidth",2)
hold on
plot(threads, sup256,"LineWidth",2)
hold on
plot(threads, sup512,"LineWidth",2)
hold on
plot(threads, sup1024,"LineWidth",2)
grid on
xlabel("Threads number")
ylabel("Speedup")

legend("64 x 64", "128 x 128","256 x 256","512 x 512", "1024 x 1024")

subplot(1,2,1)
semilogy(threads, x64,"LineWidth",2)
hold on
semilogy(threads, x128,"LineWidth",2)
hold on
semilogy(threads, x256,"LineWidth",2)
hold on
semilogy(threads, x512,"LineWidth",2)
hold on
semilogy(threads, x1024,"LineWidth",2)
grid on
xlabel("Threads number")
ylabel("Time (seconds)")

legend("64 x 64", "128 x 128","256 x 256","512 x 512", "1024 x 1024")