% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
Joystick_gain_x = 1;
Joystick_gain_y = -1;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]

K_f = 0.14269; % Calculated from problem 5.1.4

L_1 = l_p*K_f;
L_2 = (l_c*m_c-2*l_h*m_p)*g;
L_3 = l_h*K_f;
L_4 = -K_f*l_h;

K_1 = K_f / (2*m_p*l_p);
K_2 = (l_h*K_f) / (m_c*l_c^2 + 2*m_p*l_h^2);
K_3 = (K_f*l_h*g*(l_c*m_c-2*l_h*m_p))/(l_h*K_f*(m_c*l_c^2 + 2*m_p*(l_h^2 + l_p^2)));
K_pd = 9; %Gain for derivative part of PD
%K_pp= 4.12;
K_pp = 0.25*K_1*K_pd^2; % xi = 1 for critical damped system

t_d = 0; % Time delay before PD regulation of pitch
K_rp = -1; % Gain for P regulator in travel controller

Vs_star = (L_2/L_3);
% Problem 5.3.2
A3_2 = [0 1 0;
    0 0 0;
    0 0 0];
B3_2 = [0 0;
    0 K_1;
    K_2 0];
C3_2= [1 0 0;
    0 0 1];

Q3_2 = diag([10 1 1000]);
R3_2 = diag([0.1 1]);
K3_2 = lqr(A3_2,B3_2,Q3_2,R3_2);
P3_2 = inv(C3_2*inv(B3_2*K3_2-A3_2)*B3_2);

% Problem 5.3.3
A3_3 = [0 1 0 0 0;
    0 0 0 0 0;
    0 0 0 0 0;
    1 0 0 0 0;
    0 0 1 0 0];
B3_3 = [0 0;
    0 K_1;
    K_2 0;
    0 0;
    0 0];
C3_3 = [C3_2, zeros(2)];
F3_3 = [0 0;
    0 0;
    0 0;
    -1 0;
    0 -1];

Q3_3 = diag([150 10 250 50 140]);
R3_3 = diag([1 1]);
K3_3 = lqr(A3_3, B3_3,Q3_3,R3_3);
P3_3 = inv(C3_2*inv(B3_2*K3_3(:,1:3)-A3_2)*B3_2);
