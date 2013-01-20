close all

r1 = 2;
r2 = 1;
a = [2, 3];
b = [8, 5];
v1 = [0.014, 0.01];
v2 = [-0.02, -0.01];

m1 = r1^2;
m2 = r2^2;

figure;

for i = 1:10000
    
    a(1) = min(10-r1, max(r1, a(1)));
    a(2) = min(10-r1, max(r1, a(2)));
    b(1) = min(10-r2, max(r2, b(1)));
    b(2) = min(10-r2, max(r2, b(2)));
    
    %move objects
    a = a + v1;
    b = b + v2; 
            
    %detect wall collisions
    if (a(1)+r1 >= 10 || a(1)-r1 <= 0)
        v1(1) = -v1(1);
    end
    if (a(2)+r1 >= 10 || a(2)-r1 <= 0)
        v1(2) = -v1(2);
    end
    
    %detect wall collisions
    if (b(1)+r2 >= 10 || b(1)-r2 <= 0)
        v2(1) = -v2(1);
    end
    if (b(2)+r2 >= 10 || b(2)-r2 <= 0)
        v2(2) = -v2(2);
    end
    
    %detect collision between circles
    if (abs(a - b) < r1 + r2)
        s = (a - b) / norm(a - b);
        t = [-s(2) s(1)];
        
        % velocity composants in collision angle
        v1s = v1*s';
        v2s = v2*s';
        
        % velocity composants perpendicular to collision angle
        v3t = v1*t';
        v4t = v2*t';
        
        v3s = (v1s*(m1 - m2) + 2*(m2*v2s))/(m1 + m2);
        v4s = (v2s*(m2 - m1) + 2*(m1*v1s))/(m1 + m2);
        
        v1 = v3t * t + v3s * s;
        v2 = v4t * t + v4s * s;
    end
    
    
    plot([0, 10, 10, 0, 0], [0, 0, 10, 10, 0]);
    hold on;
    
    circle(a, r1);
    circle(b, r2);
    axis([-1 11 -1 11]);
    axis equal;
    hold off;
    pause(1/6000);
    
end