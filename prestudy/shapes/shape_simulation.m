clear all;
close all;

figure;
hold on;

s1 = shape(2*[-1 -1 -1.2 1.2 0.1],2*[-1 1 0 0 1.1],'r');
s2 = shape(2*[-0.3 -0.6 -1.2 1.5 0.3],2*[-1 1 0 0 1.3],'g');
s3 = shape(2*[-0.6 -1.2 0.9 0.6],2*[1 0 0 1.3],'b');
s4 = shape(2*[-0.5 -0.5 0.5 0.5],2*[0.5 -0.5 -0.5 0.5],'y');

s1.w = 0.08;
s2.p = [-4 4]';
s2.theta = 10;

s3.p = [4 -4]';
s4.p = [6 -6]';

%s2 = shape(5*[1 2 2 4 1],5*[1 2 1 5 2],'g');

s1.v = [0.15 0.40]';
s3.v = [-0.15 0.10]';

size = 11;

totalEnergy = s1.getKineticEnergy() + s2.getKineticEnergy() + s3.getKineticEnergy() + s4.getKineticEnergy() +  ...
             s1.getPotentialEnergy(size) + s2.getPotentialEnergy(size) + s3.getPotentialEnergy(size) + s4.getPotentialEnergy(size)

thermalEnergy = 0;
totalThermalEnergy = [thermalEnergy];

prevCollisions = 0;
currentCollisions = 0;

for t = 1:200000
    subplot(1, 2, 1);
    prevCollisions = currentCollisions;
    currentCollisions = 0;
    
    hold off;
    plot(size*[-1 -1 1 1 -1],size*[-1 1 1 -1 -1]);
    
    hold on;
    thermalEnergy = s1.move(size);
    thermalEnergy = thermalEnergy + s2.move(size);
    thermalEnergy = thermalEnergy + s3.move(size);
    thermalEnergy = thermalEnergy + s4.move(size);
    if (abs(thermalEnergy) < 0.000000001)
        thermalEnergy = 0;
    end
    totalThermalEnergy = [totalThermalEnergy totalThermalEnergy(end)+thermalEnergy];
    
    s1.plot();
    s2.plot();
    s3.plot();
    s4.plot();
  
    cc = collisionChecker();
    
    totalEnergy = [totalEnergy s1.getKineticEnergy() + s2.getKineticEnergy() + s3.getKineticEnergy() + s4.getKineticEnergy() +  ...
             s1.getPotentialEnergy(size) + s2.getPotentialEnergy(size) + s3.getPotentialEnergy(size) + s4.getPotentialEnergy(size)];
           
    if (cc.checkCollision(s1, s2) || cc.checkCollision(s1, s3) || cc.checkCollision(s2, s3) || cc.checkCollision(s1, s4) || cc.checkCollision(s2, s4) || cc.checkCollision(s3, s4)) 
%         fill(1*[-1 -1 1 1 -1] - size + 2,1*[-1 1 1 -1 -1] - size + 2, 'k');
        xlabel('COLLISION!')
        currentCollisions = currentCollisions + 1;
        %if abs(totalKineticEnergy - lastKineticEnergy) > 0.001
%             s1.v
%             s3.v
         %   xlabel('BAD COLLISION!') 
            %pause();
        %end
        %lastKineticEnergy = totalKineticEnergy;
    end
    
    hold off;
    subplot(1, 2, 2);
    plot (totalEnergy, 'b');
    hold on;
    plot (totalThermalEnergy, 'r');
    plot ((totalThermalEnergy + totalEnergy) / 2, 'g');
    (totalThermalEnergy(end) + totalEnergy(end)) / 2
        
     %if currentCollisions + prevCollisions > 1
      %   ylabel('OMFGWTFBBQ');
      %   pause();
     %end
         
    
    pause(0.001);
end