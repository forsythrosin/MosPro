clear all;
close all;

figure('units','normalized','outerposition',[0 0.25 0.5 0.60]);
hold on;

shapes = [
%     shape(3*[-5.5 -5.5 3 ],2*[16 5 5 ],'k', false)
%     shape(1*[1 -1 -1 1],2*[-5.5 -5.5 5.5 5.5],'k', false)
    shape(3*[-5.5 -5.5 5.5 5.5],1*[1 -1 -1 1],'k', false)
    
    shape(1*[1 cos(pi/6) cos(pi/3) 0 -cos(pi/3) -cos(pi/6) -1 -cos(pi/6) -cos(pi/3)  0  cos(pi/3)   cos(pi/6)], ...
          1*[0 sin(pi/6) sin(pi/3) 1  sin(pi/3)  sin(pi/6)  0 -sin(pi/6) -sin(pi/3) -1 -sin(pi/3)  -sin(pi/6)],'c', true)
    shape(1*[1 cos(pi/6) cos(pi/3) 0 -cos(pi/3) -cos(pi/6) -1 -cos(pi/6) -cos(pi/3)  0  cos(pi/3)   cos(pi/6)], ...
          1*[0 sin(pi/6) sin(pi/3) 1  sin(pi/3)  sin(pi/6)  0 -sin(pi/6) -sin(pi/3) -1 -sin(pi/3)  -sin(pi/6)],'c', true)
%     shape(3*[-1 -1 1 1],1*[1 -1 -1 1],'b', true)
%     shape(3*[-1 -1 1 1],1*[-1 1 1 -1],'m', true)
    
    shape(3*[-5.5 -5.5 5.5 5.5],1*[1 -1 -1 1],'k', true)
%     shape(1*[-1 -1 1 1],1*[-1 1 1 -1],'y', true)
%     shape(1*[-0.5 -0.5 0.5 0.5],1*[1 -1 -1 1],'w', true)
];

shapes(1).p = [0 10]';
shapes(2).p = [-2 -8]';
shapes(3).p = [2 -7]';
% shapes(4).p = [0 -5]';
shapes(4).p = [0.1 -10]';
% shapes(4).p = [-1 -5]';

spring = springForceGenerator(0.1, 1);
spring2 = springForceGenerator(0.05, 2);

size = 11;

for t = 1:200000
    
    shapes(2).w = 0.1;
    spring2.applyForces(shapes(2), shapes(1));
%     spring.applyForces(shapes(3), shapes(4));

    [c11 c12] = spring.applyForcesToPoint(shapes(1), shapes(4), shapes(1).vertices(:, 2), shapes(4).vertices(:, 1));
    [c21 c22] = spring.applyForcesToPoint(shapes(1), shapes(4), shapes(1).vertices(:, 3), shapes(4).vertices(:, 4));
    
    hold off;
    plot(size*[-1 -1 1 1 -1],size*[-1 1 1 -1 -1]);
    
    hold on;
    for i = 1:length(shapes)
        shapes(i).move(size);
    end
    
    for i = 1:length(shapes)
        shapes(i).plot();
    end
  
    cc = collisionChecker();

%     kineticEnergy = 0;
%     potentialEnergy = 0;
%     for i = 1:length(shapes)
%         kineticEnergy = kineticEnergy + shapes(i).getKineticEnergy();
%         potentialEnergy = potentialEnergy + shapes(i).getPotentialEnergy(size);
%     end
%     
%     totalKineticEnergy = [totalKineticEnergy kineticEnergy];
%     totalPotentialEnergy = [totalPotentialEnergy potentialEnergy];
%     lastTotalEnergy = totalEnergy;
%     totalEnergy = (totalKineticEnergy(end) + totalPotentialEnergy(end));
%     if (abs(totalEnergy - lastTotalEnergy) > 0.001)
%         %pause();
%     end
    
    for i = 1:length(shapes)-1
       for j = i+1:length(shapes)
          collision = cc.checkCollision(shapes(i), shapes(j));
          if collision
%               hold off;
%               if t>5
%               pause();
%               end
%               xlabel('COLLISION!');
          end
       end
    end
    
%     plotVector(shapes(2).p, shapes(3).p - shapes(2).p, 'r');
    plotVector(shapes(2).p, shapes(1).p-shapes(2).p, 'r');
    plotVector(c11, c12-c11, 'r');
    plotVector(c21, c22-c21, 'r');
    pause(0.01);
end