classdef shape < handle  
    properties
        p
        theta
        v
        w
        vertices
        color
        gravity
        airResistance
        movable
    end
    properties (GetAccess=private)
        mass
        inertia
    end
    methods
        function m = getMass(obj)
            m = obj.mass;
        end
        function i = getInertia(obj)
            i = obj.inertia;
        end
        function vel = getVelocity(obj)
            vel = obj.v;
        end
        
        function obj = shape(x, y, c, movable)
            obj.p = [0 0]';
            obj.v = [0 0]';
            obj.w = 0;
            obj.movable = movable;

            k = convhull(x', y');
            obj.vertices = [x(k); y(k)];
            obj.color = c;
            obj.calculateMass();
            cm = obj.centerOfMass();

            obj.vertices = obj.vertices - cm*ones(1, length(obj.vertices));
            obj.p = obj.p + cm;
            
            obj.calculateInertia();
            obj.theta = 0;
            obj.gravity = [0 -0.02]';
            obj.airResistance = 0.0;
        end
        
        function teleport(obj, transVect, rotation)
            obj.p = obj.p + transVect;
            obj.theta = obj.theta + rotation;
            
            if (norm(obj.v) > 0)
                vMagnitude = sqrt(abs(norm(obj.v)^2 - 2*abs(obj.gravity(2))*transVect(2)));
                obj.v = obj.v / norm(obj.v) * vMagnitude;
            end
        end
        
        function move(obj, size)
            if (obj.movable)
                vBefore = obj.v;
                obj.v = obj.v + obj.gravity;
                obj.v = (1 - obj.airResistance) * obj.v;
                obj.w = (1 - obj.airResistance) * obj.w;
                obj.p = obj.p + (vBefore + obj.v) / 2;
                

                obj.theta = obj.theta + obj.w;

                if (abs(obj.p(1)) > size)
                    obj.v(1) = -obj.v(1);
                    if sign(obj.p(1)) > 0
                        obj.p(1) = size;
                    else
                        obj.p(1) = -size;
                    end
                end

                if (abs(obj.p(2)) > size)
                    obj.v(2) = -obj.v(2);
                    if sign(obj.p(2)) > 0
                        obj.teleport([0 (size - obj.p(2))]', 0);
                    else
                        obj.teleport([0 (-size - obj.p(2))]', 0);
                    end
                end
            end
        end
        
        
        function impulse(obj, anchor, force)
            r = anchor - obj.p;
            perp = [-r(2), r(1)]';

            obj.v = obj.v + force / obj.mass;
            obj.w = obj.w + perp' * force / obj.inertia;
        end
        
        
        
        function plot(obj)
            rot = [cos(obj.theta) -sin(obj.theta)
                   sin(obj.theta) cos(obj.theta)];
            
            verticesRot = rot*obj.vertices;
            
            fill(obj.p(1) + verticesRot(1, :), ...
                     obj.p(2) + verticesRot(2, :), obj.color);
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
            
            rot = [cos(obj.theta) -sin(obj.theta)
                   sin(obj.theta) cos(obj.theta)];
           
            verticesRot = rot*obj.vertices;
            dist = (verticesRot' * d);
                      
            index = find(dist == max(dist));
            index = index(1);
            p = verticesRot(:, index) + obj.p;
        end
        
        function k = getKineticEnergy(obj)
            k = (obj.mass*norm(obj.v)^2 + obj.inertia*(obj.w)^2) / 2;
        end

        function p = getPotentialEnergy(obj, groundY)
            p = obj.mass * norm(obj.gravity) * (obj.p(2) + groundY);
        end
        
    end %end of methods  
end %end of classdef

