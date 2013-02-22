clear all;
close all;

figure('units','normalized','outerposition',[0 0.25 0.5 0.75]);
hold on;

shapes = [
%     shape(3*[-5.5 -5.5 3 ],2*[16 5 5 ],'k', false)
%     shape(1*[1 -1 -1 1],2*[-5.5 -5.5 5.5 5.5],'k', false)
    shape(3*[-5.5 -5.5 5.5 5.5],1*[1 -1 -1 1],'k', false)
    shape(1*[-1 -1 1 1],1*[-1 1 1 -1],'c', true)
%     shape(1*[-1 -1 1 1],1*[-1 1 1 -1],'m', true)
%     shape(1*[-1 -1 1 1],1*[-1 1 1 -1],'y', true)
%     shape(1*[-0.5 -0.5 0.5 0.5],1*[1 -1 -1 1],'w', true)
];

shapes(1).p = [0 -7]';
% shapes(2).p = [11 0]';
% shapes(3).p = [0 5]';

% shapes(3).p = [3 8]';
% shapes(3).theta = 10;

%shapes(2).p = [0 -11]';
% shapes(4).p = [-3 8]';
shapes(2).p = [0 10]';
% shapes(5).p = [-0.1 -2]';
% shapes(6).p = [0 0]';
% shapes(7).p = [-7.5 -5]';
%shapes(8).p = [-7 -8]';
%shapes(9).p = [-1 -8.5]';
%shapes(10).p = [10.5 10.5]';

size = 11;

% totalKineticEnergy = 0;
% totalPotentialEnergy = 0;
% for i = 1:length(shapes)
%     totalKineticEnergy = totalKineticEnergy + shapes(i).getKineticEnergy();
%     totalPotentialEnergy = totalPotentialEnergy + shapes(i).getPotentialEnergy(size);
% end

% thermalEnergy = 0;
% totalThermalEnergy = [thermalEnergy];
% totalEnergy = (totalThermalEnergy(end) + totalKineticEnergy + totalPotentialEnergy);

prevCollisions = 0;
currentCollisions = 0;

for t = 1:200000
%     prevCollisions = currentCollisions;
%     currentCollisions = 0;
    
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
              pause();
              xlabel('COLLISION!');
          end
       end
    end
    pause(0.01);
end