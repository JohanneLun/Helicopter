% FOR HELICOPTER NR 3-10
% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert h�sten 2006 av Jostein Bakkeheim
% Oppdatert h�sten 2008 av Arnfinn Aas Eielsen
% Oppdatert h�sten 2009 av Jonathan Ronen
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
K_1 = K_f / (2*m_p*l_p);
K_2 = (l_h*K_f) / (m_c*l_c^2 + 2*m_p*l_h^2);
K_3 = (K_f*l_h*g*(l_c*m_c-2*l_h*m_p))/(l_h*K_f*(m_c*l_c^2 + 2*m_p*(l_h^2 + l_p^2)));
K_pd = 10; %Gain for derivative part of PD
%K_pp= 4.12;
K_pp = 0.25*K_1*K_pd^2; % xi = 1 for critical damped system

t_d = 0; % Time delay before PD regulation of pitch

K_rp = -2; % Gain for P regulator in travel controller