classdef collisionChecker < handle
    properties (GetAccess=private)
        simplex
        d
    end
    methods
        function collision = checkCollision(obj, s1, s2)
            collision = false;
            
            obj.simplex = [];
            
            obj.d = s2.p - s1.p;
            obj.simplex = [obj.simplex obj.support(s1, s2)];
            obj.d = -obj.d;

            while true
                obj.simplex = [obj.simplex obj.support(s1, s2)];
                if obj.simplex(:, end)' * obj.d < 0
                    collision = false;
                    break;
                else
                    if obj.containsOrigin()
                        collision = true;
                        break;
                    end
                end
            end
        end
        
        function p3 = support(obj, s1, s2) 
            p1 = s1.getFarthestPointInDirection(obj.d);
            p2 = s2.getFarthestPointInDirection(-obj.d);
            p3 = p1 - p2;
            %plot([p1(1) p2(1)], [p1(2) p2(2)]);
        end
        
        function contains = containsOrigin(obj) 
            contains = false;
            a = obj.simplex(:, end);
            ao = -a;
            
            if length(obj.simplex) == 3
                b = obj.simplex(:, 2);
                c = obj.simplex(:, 1);
                ab = b - a;
                ac = c - a;
                
                %ac*ab*ab
                abPerp = ab*(ac'*ab) - ac * (ab'*ab);
                %ab*ac*ac
                acPerp = ac*(ab'*ac) - ab * (ac'*ac);
                
                if abPerp'*ao > 0
                    obj.simplex(:,1) = [];
                    obj.d = abPerp;
                elseif acPerp'*ao > 0
                    obj.simplex(:,2) = [];
                    obj.d = acPerp;
                else             
                    contains = true;
                end
            else
                b = obj.simplex(:, 1);
                ab = b - a;
                abPerp = ([-ab(2) ab(1)]*ao)*[-ab(2) ab(1)]';
                
                %abPerp = tripleProduct(ab, ao, ab);
                %abPerp = ab*(ac'*ab) - ac * (ab'*ab);
                %abPerp = ...
                obj.d = abPerp;
            end
        end
    end
    
end