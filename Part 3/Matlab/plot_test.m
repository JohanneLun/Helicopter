close all;

figure('Name', 'Pitch', 'NumberTitle', 'off');
plot_func(plot_p, 'b');
hold on;
plot_func(plot_p_c, 'r');
hold off;
legend('pitch', 'pitch_ref');

figure('Name', 'Pitch dot', 'NumberTitle', 'off');
plot_func(plot_p_dot, 'b');

figure('Name', 'elevation dot', 'NumberTitle', 'off');
plot_func(plot_e_dot, 'b');
hold on;
plot_func(plot_e_dot_c, 'r');
hold off;
legend('elevation', 'elevation_ref');