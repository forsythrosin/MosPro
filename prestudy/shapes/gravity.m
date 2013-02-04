clear all;
close all;

figure;
hold on;

s1 = shape(2*[-1 -1 -1.2 1.2 0.1],2*[-1 1 0 0 1.1],'r');

%s1.w = 0.08;
% s2.p = [-4 4]';
% s2.theta = 10;

s1.p(2) = 3.45;

size = 11;

totalEnergy = s1.getKineticEnergy() + s1.getPotentialEnergy(size);


for t = 1:200000
    subplot(1, 2, 1);
    hold off;
    plot(size*[-1 -1 1 1 -1],size*[-1 1 1 -1 -1]);
    
    hold on;
    s1.move(size);
   
    s1.plot();
    
  
    %cc = collisionChecker();
    
    totalEnergy = [totalEnergy s1.getKineticEnergy() + s1.getPotentialEnergy(size)];    
    
     subplot(1, 2, 2);
     hold off
     plot(1:length(totalEnergy), totalEnergy);
     
    
    pause(0.001);
end