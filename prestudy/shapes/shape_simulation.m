clear all;
close all;

figure;
hold on;

s1 = shape(2*[-1 -1 1 1 ],2*[-1 1 1 -1 ],'r');
s2 = shape(2*[-1 -1 1 1 ],2*[-1 1 1 -1 ],'g');

s1.w = 0.06;
s2.p = [-4 4]';
s2.theta = 10;

%s2 = shape(5*[1 2 2 4 1],5*[1 2 1 5 2],'g');
%s3 = shape([1 1 2],[1 2 2], 'b');
%s1 = shape([0 1 2], [0 1 0], 'b');

%s1.p = [3, 3]';
%s2.p = [16 6]';


s1.v = [0.06 0.02]';

size = 10;

totalKineticEnergy = s1.getKineticEnergy() + s2.getKineticEnergy()

for t = 1:10000
    hold off;
    plot(size*[-1 -1 1 1],size*[-1 1 1 -1]);
    
    hold on;
    s1.plot();
    s2.plot();
    %s3.plot();
    
    
    s1.move();
    s2.move();
%     s1.w = s1.w + 0.01 * pi;
%     s2.w = s2.w + 0.014;
%     s3.w = s3.w + 0.01;
  
    cc = collisionChecker();
    
    if (cc.checkCollision(s1, s2)) 
        fill(1*[-1 -1 1 1 -1] - size + 2,1*[-1 1 1 -1 -1] - size + 2, 'b');
%         break;
    end
    
    if (abs(s1.p(1)) > size)
        s1.v(1) = -s1.v(1);
    end
    if (abs(s1.p(2)) > size)
        s1.v(2) = -s1.v(2);        
    end
        
    if (abs(s2.p(1)) > size)
        s2.v(1) = -s2.v(1);
    end
    if (abs(s2.p(2)) > size)
        s2.v(2) = -s2.v(2);
    end
    
    
        
        
        
    
    pause(0.01);
end