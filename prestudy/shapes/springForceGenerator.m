classdef springForceGenerator < handle
    properties (GetAccess=private)
        k
        length
    end
    methods
        function obj = springForceGenerator(k, l)
            obj.k = k; obj.length = l;
        end
        
        function applyForces(obj, s1, s2)
            d = s2.p-s1.p;
            dHat = d / norm(d);
            j = - obj.k * (norm(d) - obj.length) * dHat;
            if(s1.movable)
                s1.impulse(s1.p, -j);
            end
            if(s2.movable)
                s2.impulse(s2.p, j);
            end
        end
        
        function [p1 p2] = applyForcesToPoint(obj, s1, s2, p1, p2)
            
            rot1 = [cos(s1.theta) -sin(s1.theta)
                    sin(s1.theta) cos(s1.theta)];
            rot2 = [cos(s2.theta) -sin(s2.theta)
                    sin(s2.theta) cos(s2.theta)];
           
            p1 = rot1 * p1 + s1.p;
            p2 = rot2 * p2 + s2.p;
            
            d = p2-p1;
            dHat = d / norm(d);
            j = - obj.k * (norm(d) - obj.length) * dHat;
            if(s1.movable)
                s1.impulse(p1, -j);
            end
            if(s2.movable)
                s2.impulse(p2, j);
            end
        end
        
    end
end