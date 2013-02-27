function [theta point] = findClosestRotationAngle(a, b, n, p, r)
    theta = 0;
    v = a-b;
    rOrt = [-r(2) r(1)]';

    xrt = v(2)^2 * (2* b(2)* v(1)-2* b(1)* v(2)-2* p(2)* v(1)+2* p(1)* v(2))^2 ...
            -4* (v(2)^2+v(1)^2)* (b(2)^2 * v(1)^2-2* b(2)* b(1)* v(2)* v(1)-2* b(2)* p(2)* v(1)^2+ ...
            2* b(2)* p(1)* v(2)* v(1)+b(1)^2 * v(2)^2+2* b(1)* p(2)* v(2)* v(1)-2* b(1) *...
            p(1)* v(2)^2+p(2)^2 * v(1)^2-2* p(2)* p(1)* v(2)* v(1)+p(1)^2 * v(2)^2-r(1)^2 * v(1)^2-r(2)^2 * v(1)^2);
    
    xrst = v(2)* (2* b(2)* v(1)-2* b(1)* v(2)-2* p(2)* v(1)+2* p(1)* v(2));
    xqt = (2* (v(2)^2+v(1)^2));
    
    x1 = (sqrt(abs(xrt)) - xrst) / xqt;
    x2 = (-sqrt(abs(xrt)) - xrst) / xqt;
    
    y11 = sqrt(dot(r,r) - x1^2);
    y12 = sqrt(dot(r,r) - x2^2);
    y21 = -y11;
    y22 = -y12;
%     y21 = -sqrt(dot(r,r) - x1^2)
%     y22 = -sqrt(dot(r,r) - x2^2)
    
    z = zeros(2,4);
    z(:,1) = [x1 y11]';
    z(:,2) = [x1 y21]';
    z(:,3) = [x2 y12]';
    z(:,4) = [x2 y22]';
    
    %plotline(p, p+r, 'b');
    %hold on;
    %plotline(b, b+v, 'r');
    %plotline(p, p+z(:,1), 'r');
    %plotline(p, p+z(:,2), 'g');
    %plotline(p, p+z(:,3), 'c');
    %plotline(p, p+z(:,4), 'm');
    
    found = false;
    for l = 1:3
       for m = l+1:4
           c = z(:,l)+z(:,m);
           if(norm(c) > 0.01 && dot(c, r) > 0 && abs(dot(c, v)) < 0.1)
               %plotline(p, p+z(:,l), 'm');
               %plotline(p, p+z(:,m), 'm');
               %plotline(p, p+c, 'y');
               theta1 = acos(dot(z(:,l)/norm(z(:,l)),r/norm(r)));
               theta2 = acos(dot(z(:,m)/norm(z(:,m)),r/norm(r)));
               if (theta1 < theta2)
                  theta = sign(dot(n, rOrt)) * theta1;
                  q = z(:,l);
               else
                  theta = sign(dot(n, rOrt)) * theta2;
                  q = z(:,m);
               end
               found = true;
               break;
           end
       end
       if (found)
           break;
       end
    end
    point = p + q;
end