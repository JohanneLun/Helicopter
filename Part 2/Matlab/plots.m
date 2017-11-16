load('pitch.mat');
load('data.mat');

figure('Name','Comparison, ref and measure','numberTitle','off');
plot(pitch(1,:), pitch(2,:), pitch(1,:), pitch(3,:));
legend('reference','measurement');

figure('Name','Travelrate','numberTitle','off');
plot(data(1,:), data(2,:), data(1,:), data(3,:));
legend('reference','measurement');