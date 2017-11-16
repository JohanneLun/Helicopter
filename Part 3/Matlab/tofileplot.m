close all;

load('pitch.mat');
load('elevrate.mat');
load('data.mat'); 

figure('Name','Pitch comparison');
plot(pitch(1,:), pitch(2,:),'b',pitch(1,:), pitch(3,:),'r');
hold on;
legend('measured','reference');

figure('Name','Elevation comparison');
plot(elevrate(1,:), elevrate(2,:),'b', elevrate(1,:), elevrate(3,:),'r');
legend('measured','reference');

%% Plot 532
load('data.mat');  

figure('Name','Pitch comparison');
plot(data(1,:), data(2,:),'b',data(1,:), data(3,:),'r');
hold on;
legend('ref','messure');

figure('Name','Elevation comparison');
plot(data(1,:), data(4,:),'b',data(1,:), data(5,:),'r');
hold on;
legend('ref','messure');