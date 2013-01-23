classdef shape < handle  
    properties
        p
        theta
        v
        w
        vertices
        color
    end
    properties (GetAccess=private)
        mass
        inertia
    end
    methods
        function obj = shape(x, y, c)
            obj.p = [0 0]';
            obj.v = [0 0]';
            obj.w = 0;
            k = convhull(x', y');
            obj.vertices = [x(k); y(k)];
            obj.color = c;
            obj.calculateMass();
            cm = obj.centerOfMass();

            obj.vertices = obj.vertices - cm*ones(1, length(obj.vertices));
            obj.p = obj.p + cm;
            
            obj.calculateInertia();
            
        end
        
        function plot(obj)
            rot = [sin(obj.w) -cos(obj.w)
                   cos(obj.w) sin(obj.w)];
            
            verticesRot = rot*obj.vertices;
            
            plot(obj.p(1) + verticesRot(1, :), ...
                     obj.p(2) + verticesRot(2, :), obj.color);
                 
            plot(obj.p(1), obj.p(2), 'k*');
        end
        function calculateMass(obj) 
            v = obj.vertices;
            x = v(1,:);
            y = v(2,:);
            n = length(obj.vertices);
            
            obj.mass = 1/2 * sum(x(1:n-1).*y(2:n) - x(2:n).*y(1:n-1));
        end
        function cm = centerOfMass(obj)
            v = obj.vertices;
            x = v(1,:);
            y = v(2,:);
            n = length(obj.vertices);
             
            a = obj.mass; % mass = area
            cx = 1/(6*a) * sum((x(1:n-1) + x(2:n)) .* (x(1:n-1).*y(2:n) - x(2:n).*y(1:n-1)));
            cy = 1/(6*a) * sum((y(1:n-1) + y(2:n)) .* (x(1:n-1).*y(2:n) - x(2:n).*y(1:n-1)));
            
            cm = [cx cy]';
        end
        function calculateInertia(obj)
            n = length(obj.vertices);
            v = obj.vertices;
            obj.inertia = 0;
            
            for i = 1:(n - 1) 
                p1 = v(:,i);
                p2 = v(:,i + 1);

                b = p2 - p1;
                bhat = b/norm(b); 
                
                a = (p2' * bhat) * bhat;
                h = p2 - a;
                
                a = norm(a);
                b = norm(b);
                h = norm(h);
                  
                obj.inertia = obj.inertia + ...
                    (b^3*h - b^2*h*a + b*h*a^2 + b*h^3) / 36 + b*h/2 * norm((p1+p2)/3)^2;
            end            
        end
        function p = getFarthestPointInDirection(obj, d)
            d = d/norm(d);
            
            
            
            rot = [sin(obj.w) -cos(obj.w)
                   cos(obj.w) sin(obj.w)];
           
            verticesRot = rot*obj.vertices;
            dist = (verticesRot' * d);
           
            
            index = find(dist == max(dist));
            index = index(1);
            p = verticesRot(:, index) + obj.p;
        end
        
    end %end of methods  
end %end of classdef

