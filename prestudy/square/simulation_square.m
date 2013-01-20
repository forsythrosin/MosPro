clear;
close all;
figure;

s = physics_square([3, 3], [0, 0], 0, 4);
s.impulse([1, -1], [-0.8, 1]);

for t = 1:10000
    
    plot([0, 10, 10, 0, 0], [0, 0, 10, 10, 0]);
    hold on;
    s.plot;
    s.move;
    s.collideWalls();
    pause(1/60);
    axis equal;
    hold off;
end