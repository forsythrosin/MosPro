clear all;
close all;

figure;
hold on;

s1 = shape(2*[0 0 1 10 15 5.2 5.3],2*[0 1 1 0 0 0 0],'r');
s2 = shape(5*[1 2 2 4 1],5*[1 2 1 5 2],'g');
%s3 = shape([1 1 2],[1 2 2], 'b');
%s1 = shape([0 1 2], [0 1 0], 'b');

s1.p = [3, 5]';
s2.p = [16 6]';




for t = 1:10000
    hold off;
    plot(80*[-1 -1 1 1],80*[-1 1 1 -1]);
    
    hold on;
    s1.plot();
    s2.plot();
    %s3.plot();
    
    s1.w = s1.w + 0.01 * pi;
    s2.w = s2.w + 0.014;
    %s3.w = s3.w + 0.01;
  
    cc = collisionChecker();
    
    if (cc.checkCollision(s1, s2)) 
        fill(10*[-1 -1 1 1 -1] - 70,10*[-1 1 1 -1 -1] - 70, 'b');
    end
    
    pause(0.01);
end