close all;
load('x.mat');
load('x_hat.mat');
load('joyref.mat');

figure('Name','Comparison pitch','NumberTitle', 'off');
plot(x(1,:),x(2,:),'b',x_h(1,:),x_h(2,:),'r', joyref(1,:),joyref(2,:),'g');
legend('measured','estimated', 'reference');

figure('Name','Comparison pitch rate','NumberTitle', 'off');
plot(x(1,:),x(3,:),'b',x_h(1,:),x_h(3,:),'r');
legend('measured','estimated');

figure('Name','Comparison elevation','NumberTitle', 'off');
plot(x(1,:),x(4,:),'b',x_h(1,:),x_h(4,:),'r');
legend('measured','estimated');

figure('Name','Comparison elevation rate','NumberTitle', 'off');
plot(x(1,:),x(5,:),'b',x_h(1,:),x_h(5,:),'r',joyref(1,:),joyref(3,:),'g');
legend('measured','estimated','referemce');