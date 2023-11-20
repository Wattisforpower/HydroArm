% Arm Contraints
ArmLength = [0.225, 0.255];
Origin = [0, 0];
PointNo = 10000;

% Data Generation
Theta = UniformData(PointNo, 0, pi);

[ElbowJoint, EndPoints] = RevoluteForwardKinematics2D(ArmLength, Theta, Origin);

figure;
hold on;
plot(Origin(1), Origin(2), 'bo');
plot(EndPoints(1, :), EndPoints(2, :), 'r.');

xlabel('x [m]');
ylabel('y [m]');
title("Endeffecter Workspace Point Map");
legend('Origin', 'End Points');
hold off;


