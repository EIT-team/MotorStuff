% http://letsmakerobots.com/node/31697
step_num=50;

t_full=1:step_num;
max_angle=1;

angle_full = zeros(size(t_full));

for tstep = t_full
    
 
angle_full(tstep) =(max_angle/pi) * (((pi / step_num) * tstep) - (cos((pi /step_num) * tstep)* sin((pi /step_num) * tstep)));
end

plot(t_full,angle_full)
%we can calc curve once and then scale - for speed

%%

ard_angle = [0.00000,0.00005,0.00042,0.00141,0.00333,0.00645,0.01105,0.01737,0.02562,0.03599,0.04863,0.06366,0.08116,0.10116,0.12366,0.14863,0.17599,0.20562,0.23737,0.27105,0.30645,0.34333,0.38141,0.42042,0.46005,0.50000,0.53995,0.57958,0.61859,0.65667,0.69355,0.72895,0.76263,0.79438,0.82401,0.85137,0.87634,0.89884,0.91884,0.93634,0.95137,0.96401,0.97438,0.98263,0.98895,0.99355,0.99667,0.99859,0.99958,0.99995];

%% mapping test

min_pw =       544; 
max_pw   =   2400; 

target_angle = 60;
current_angle = 20;

us_45 = map_ard(current_angle + (angle_full * target_angle), 0, 180, min_pw, max_pw);

plot(us_45)