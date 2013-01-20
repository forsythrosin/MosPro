classdef physics_square < handle
    properties
        position
        theta
        v
        w
        size
        mass
        inertia
    end
    properties (GetAccess=private)
        diag
    end
    methods
        function obj = physics_square(position, v, w, size)
            obj.position = position; 
            obj.v = v;
            obj.w = w;
            obj.size = size;
            obj.mass = size*size;
            obj.theta = pi/4;
            obj.diag = size/2 * sqrt(1/2);
            obj.inertia = size^4 / 12;
        end
       
        function plot(obj)
            y = obj.position(2) + obj.diag*[sin(pi/4 + obj.theta); ...
                 sin(3*pi/4 + obj.theta); ...
                 sin(5*pi/4 + obj.theta); ...
                 sin(7*pi/4 + obj.theta); ...
                 sin(pi/4 + obj.theta)]';
             
             x = obj.position(1) + obj.diag*[cos(pi/4 + obj.theta); ...
                 cos(3*pi/4 + obj.theta); ...
                 cos(5*pi/4 + obj.theta); ...
                 cos(7*pi/4 + obj.theta); ...
                 cos(pi/4 + obj.theta)]';
            plot(x, y);
        end
        
        function move(obj)
            obj.position = obj.position + obj.v;
            obj.theta = obj.theta + obj.w;
        end
        
        
        function impulse(obj, anchor, force)  
            perp = [-anchor(2), anchor(1)];
            obj.v = obj.v + force / obj.mass;
            obj.w = obj.w + perp * force' / obj.inertia;
        end
        
        function j = getJ(obj, r, n)
            e = 1;
            m = obj.mass;
            i = obj.inertia;
            rort = [-r(2) r(1)];
            vr = obj.v + obj.w * rort;
                       
            jr = -(1 + e)*vr * n' / (1/m + 1/i * (n * rort')^2);
            j = jr*n;
        end
       
        
        function collideWalls(obj)
            collision = false;            
            for i = 1:2:7
                anchor = [obj.diag*cos(i*pi/4 + obj.theta) obj.diag*sin(i*pi/4 + obj.theta)];

                % check x
                if (obj.position(1) + anchor(1) > 10)
                    obj.position(1) = 10 - abs(obj.diag*cos(i*pi/4 + obj.theta));
                    n = [-1 0];
                    obj.impulse(anchor,obj.getJ(anchor,n));
                end

                if (obj.position(1) + anchor(1) < 0)
                    obj.position(1) = abs(obj.diag*cos(i*pi/4 + obj.theta));
                    n = [1 0];
                    obj.impulse(anchor,obj.getJ(anchor, n));
                end
                
                % check y
                if (obj.position(2) + anchor(2) > 10)
                    obj.position(2) = 10 - abs(obj.diag*sin(i*pi/4 + obj.theta));
                    n = [0 -1];
                    obj.impulse(anchor, obj.getJ(anchor, n));
                end
                
                if (obj.position(2) + anchor(2) < 0)
                    obj.position(2) = abs(obj.diag*sin(i*pi/4 + obj.theta));
                    n = [0 1];
                    obj.impulse(anchor, obj.getJ(anchor, n));
                end
            end
            
            % Calculate the kinetic energy
            % obj.mass * norm(obj.v)^2 / 2 + obj.inertia * obj.w^2 / 2
        end
        
    end        
end